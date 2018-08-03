tinyspec : tinyspec.c
	gcc -lm -O3 tinyspec.c -o tinyspec

play : tinyspec
	./tinyspec | aplay -c1 -f FLOAT_LE -r 44100
