CC = g++
outfile = out

LIBs = lib/
INCl = include/

FILES = src/*.cpp src/grid/*.cpp

build:
	$(CC) $(FILES) -o $(outfile) -lm -L$(LIBs) -I$(INCl) -lraylib
	if ![ -d "saves/" ]; then \
        mkdir saves; \
    fi
start:
	make build
	./$(outfile)