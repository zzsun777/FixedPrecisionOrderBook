ifeq ($(CLANG), 1)
	CC=clang
	STDCPP=-lstdc++
else
	CC=g++
	STDCPP=
endif

INC = $(BOOST_ROOT)/ ../OrderBook/
INC_PARAMS=$(foreach d, $(INC), -I$d)

LIB_DIRS = ./ $(BOOST_ROOT)/stage/lib/
LIB_PARAMS=$(foreach d, $(LIB_DIRS), -L$d)

LIBS = -lm -lOrderBook

# Removing warnings on unused typedefs to quiet down boost
COMMON = -std=c++11 -Wall -Wno-unused-local-typedefs $(STDCPP) $(LIB_PARAMS) $(LIBS) $(INC_PARAMS) -pthread -Wl,--no-as-needed

all:
	make release

debug:
	$(CC) -g -DDEBUG $(COMMON) FHErrorTracker.cpp main.cpp -o FixedOrderBookProcessor

release:
	$(CC) -O3 -DNDEBUG $(COMMON) FHErrorTracker.cpp main.cpp -o FixedOrderBookProcessor

test:
	$(CC) -g -DDEBUG $(COMMON) FHErrorTracker.cpp Tester.cpp -o UtilityTester

perftest:
	$(CC) -O3 -g -DDEBUG $(COMMON) FHErrorTracker.cpp Tester.cpp -o UtilityTester

profile:
	$(CC) -O3 -DNDEBUG -DPROFILE $(COMMON) FHErrorTracker.cpp main.cpp -o FixedOrderBookProcessor

grind:
	$(CC) -g -O3 -DNDEBUG -DPROFILE $(COMMON) FHErrorTracker.cpp main.cpp -o FixedOrderBookProcessor

clean:
	rm -f FixedOrderBookProcessor
	rm -f UtilityTester
	rm -f test.out
