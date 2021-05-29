CC = g++
outfile = out

LIBs = lib/
INCl = include/

build:
	$(CC) src/*.cpp src/grid/*.cpp -o $(outfile) -lm -L$(LIBs) -I$(INCl) -lraylib
	if ![ -d "saves/" ]; then \
        mkdir saves; \
    fi
start:
	make build
	./$(outfile)