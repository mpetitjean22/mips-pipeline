#ifndef CACHE_H
#define CACHE_H

#ifndef CACHECONFIG_H
#define CACHECONFIG_H
#include "CacheConfig.h"
#endif
#ifndef MEMORYSTORE_H
#define MEMORYSTORE_H
#include "MemoryStore.h"
#endif

struct cache_block;

class Cache {
public:
    Cache(CacheConfig &config, MemoryStore *memory);
    ~Cache();
    int Read(uint32_t address, uint32_t & value, MemEntrySize size);
    int Write(uint32_t address, uint32_t value, MemEntrySize size);
    int StallCyclesHavePassed(int cycles);
    int GetMisses() const;
    int GetHits() const;
    void WriteAllDirtyToMain();
private:
    void Decode(uint32_t address, uint32_t & tag, uint32_t & index, uint32_t & offset) const;
    uint32_t Encode(uint32_t tag, uint32_t index, uint32_t offset) const;
    void Evict(cache_block & target, uint32_t index);
    void Insert(cache_block & target, uint32_t tag, uint32_t index);
    uint32_t SizeMask(uint32_t value, MemEntrySize size) const;
    void AugmentPortion(uint32_t & current, uint32_t newv, MemEntrySize size) const;
    cache_block *way1;
    cache_block *way2;
    bool *lru; // true if block in first way is LRU
    int index_bits, offset_bits, tag_bits;
    int hits, misses;
    CacheType type;
    MemoryStore *mem;
    int wordsPerBlock;
    int sets;
    uint32_t missLatency;
    uint32_t latencyLeft;
};

#endif
