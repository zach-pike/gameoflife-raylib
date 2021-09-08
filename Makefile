CC = g++
outfile = out

FILES = src/*.cpp src/grid/*.cpp

build:
	$(CC) $(FILES) -o $(outfile) -lm -lraylib
	if ![ -d "saves/" ]; then \
        mkdir saves; \
    fi
start:
	make build
	./$(outfile)