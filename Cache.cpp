#include "Cache.h"
#include <cstdio>
#include <cstdlib>

struct cache_block {
    bool valid;
    bool dirty;
    uint32_t tag;
    uint32_t *block;
};

static inline int log2(int x) {
    // avoid floating point rounding errors with the float log2
    // repeatedly divide by 2 until result < 1
    int ret = 0;
    while (x >>= 1)
        ret++;
    return ret;
}

static inline uint32_t extract(int input, int length, int offset) {
    uint32_t mask = 1;
    mask <<= length;
    mask -= 1;
    mask <<= offset;
    return (input & mask) >> offset;
}

Cache::Cache(CacheConfig &config, MemoryStore *memory) {
    hits = 0;
    misses = 0;
    latencyLeft = 0;
    mem = memory;
    type = config.type;
    missLatency = config.missLatency;
    wordsPerBlock = config.blockSize / WORD_SIZE;
    if (type == DIRECT_MAPPED)
        sets = config.cacheSize / config.blockSize;
    else
        sets = config.cacheSize / config.blockSize / 2;

    way1 = new cache_block[sets];
    for (int i = 0; i < sets; i++) {
        way1[i].valid = false;
        way1[i].dirty = false;
        way1[i].block = new uint32_t[wordsPerBlock];
    }

    if (type == TWO_WAY_SET_ASSOC) {
        way2 = new cache_block[sets];
        lru = new bool[sets];
        for (int i = 0; i < sets; i++) {
            way2[i].valid = false;
            way2[i].dirty = false;
            way2[i].block = new uint32_t[wordsPerBlock];
            lru[i] = true;
        }
    }

    offset_bits = log2(config.blockSize);
    index_bits = log2(sets);
    tag_bits = 32 - offset_bits - index_bits;
}

Cache::~Cache() {
    delete[] way1;
    if (type == TWO_WAY_SET_ASSOC) {
        delete[] way2;
        delete[] lru;
    }
}

int Cache::GetMisses() const {
    return misses;
}

int Cache::GetHits() const {
    return hits;
}

void Cache::Decode(uint32_t address, uint32_t & tag, uint32_t & index, uint32_t & offset) const {
    tag = extract(address, tag_bits, index_bits + offset_bits);
    index = extract(address, index_bits, offset_bits);
    offset = extract(address, offset_bits, 0);
}

uint32_t Cache::Encode(uint32_t tag, uint32_t index, uint32_t offset) const {
    // assumes that tag, index, offset are in the form that would result from
    // Cache::Decode; also assumes tag, index, offset are all less than the fields
    // bit width
    uint32_t out = 0;
    out |= tag << (offset_bits + index_bits);
    out |= index << offset_bits;
    out |= offset;
    return out;
}

void Cache::Evict(cache_block & target, uint32_t index) {
    uint32_t address = Encode(target.tag, index, 0);
    int ret;
    if (target.dirty && target.valid) {
        for (int i = 0; i < wordsPerBlock; i++) {
            ret = mem->setMemValue(address + i * 4, target.block[i], WORD_SIZE);
            if (ret) {
                fprintf(stderr, "Could not access %u", address + i * 4);
                exit(EXIT_FAILURE);
            }
        }
        target.dirty = false;
    }
}

void Cache::Insert(cache_block & target, uint32_t tag, uint32_t index) {
    uint32_t address = Encode(tag, index, 0);
    int ret;
    for (int i = 0; i < wordsPerBlock; i++) {
        ret = mem->getMemValue(address + i * 4, target.block[i], WORD_SIZE);
        if (ret) {
            fprintf(stderr, "Could not access %u", address + i * 4);
            exit(EXIT_FAILURE);
        }
    }
    target.valid = true;
    target.dirty = false;
    target.tag = tag;
}

uint32_t Cache::SizeMask(uint32_t value, MemEntrySize size) const {
    switch (size) {
        case BYTE_SIZE:
            return value & 0xFF;
            break;
        case HALF_SIZE:
            return value & 0xFFFF;
            break;
        case WORD_SIZE:
        default:
            return value;
    }
}

void Cache::AugmentPortion(uint32_t & current, uint32_t newv, MemEntrySize size) const {
    switch (size) {
        case BYTE_SIZE:
            current = (current & 0xFFFFFF00) | SizeMask(newv, size);
            break;
        case HALF_SIZE:
            current = (current & 0xFFFF0000) | SizeMask(newv, size);
            break;
        case WORD_SIZE:
        default:
            current = newv;
    }
}

int Cache::Read(uint32_t address, uint32_t & value, MemEntrySize size) {
    uint32_t tag, index, offset;
    Decode(address, tag, index, offset);
    cache_block & from1 = way1[index];
    if (from1.valid && from1.tag == tag) {
        hits++;
        // "assume that your caches will never need to serve unaligned accesses"
        value = SizeMask(from1.block[offset >> 2], size);
        if (type == TWO_WAY_SET_ASSOC)
            lru[index] = false;
        return 0;
    }
    if (type == TWO_WAY_SET_ASSOC) {
        cache_block & from2 = way2[index];
        if (from2.valid && from2.tag == tag) {
            hits++;
            // "assume that your caches will never need to serve unaligned accesses"
            value = SizeMask(from2.block[offset >> 2], size);
            lru[index] = true;
            return 0;
        }
    }
    misses++;

    cache_block *toEvict;
    if (type == TWO_WAY_SET_ASSOC) {
        if (lru[index]) {
            toEvict = &way1[index];
            lru[index] = false;
        }
        else {
            toEvict = &way2[index];
            lru[index] = true;
        }
    } else {
        toEvict = &way1[index];
    }
    // modifying cache now (prior to the end of the miss penalty) is fine b/c
    // the cache wont be accessed or modified until the penalty is up
    Evict(*toEvict, index);
    Insert(*toEvict, tag, index);
    int ret = mem->getMemValue(address, value, size);
    if (ret) {
        fprintf(stderr, "Could not access %u", address);
        exit(EXIT_FAILURE);
    }
    latencyLeft = missLatency;
    return missLatency;
}

int Cache::Write(uint32_t address, uint32_t value, MemEntrySize size) {
    uint32_t tag, index, offset;
    Decode(address, tag, index, offset);
    cache_block & from1 = way1[index];
    if (from1.valid && from1.tag == tag) {
        hits++;
        // "assume that your caches will never need to serve unaligned accesses"
        AugmentPortion(from1.block[offset >> 2], value, size);
        from1.dirty = true;
        if (type == TWO_WAY_SET_ASSOC)
            lru[index] = false;
        return 0;
    }
    if (type == TWO_WAY_SET_ASSOC) {
        cache_block & from2 = way2[index];
        if (from2.valid && from2.tag == tag) {
            hits++;
            // "assume that your caches will never need to serve unaligned accesses"
            from2.dirty = true;
            AugmentPortion(from2.block[offset >> 2], value, size);
            lru[index] = true;
            return 0;
        }
    }
    misses++;

    cache_block *toEvict;
    if (type == TWO_WAY_SET_ASSOC) {
        if (lru[index]) {
            toEvict = &way1[index];
            lru[index] = false;
        }
        else {
            toEvict = &way2[index];
            lru[index] = true;
        }
    } else {
        toEvict = &way1[index];
    }
    // modifying cache now (prior to the end of the miss penalty) is fine b/c
    // the cache wont be accessed or modified until the penalty is up
    Evict(*toEvict, index);
    Insert(*toEvict, tag, index);
    AugmentPortion(toEvict->block[offset >> 2], value, size);
    toEvict->dirty = true;
    latencyLeft = missLatency;
    return missLatency;
}

int Cache::StallCyclesHavePassed(int cycles) {
    if (cycles > latencyLeft)
        latencyLeft = 0;
    else
        latencyLeft -= cycles;
    return latencyLeft;
}

void Cache::WriteAllDirtyToMain() {
    for (int i = 0; i < sets; i++)
        Evict(way1[i], i);
    if (type == TWO_WAY_SET_ASSOC)
        for (int i = 0; i < sets; i++)
            Evict(way2[i], i);
}
