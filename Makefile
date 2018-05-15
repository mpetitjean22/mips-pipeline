all:
	g++ Cache.cpp cycle_sim.cpp Decode.cpp driver.cpp Execute.cpp EXtoMemRegister.cpp IDtoExRegister.cpp IFtoIDRegister.cpp InstructionFetch.cpp  Memory.cpp MemToWBRegister.cpp register.cpp WriteBack.cpp UtilityFunctions.o -o cycle_sim
