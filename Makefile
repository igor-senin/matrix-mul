all: simple fast

libDir = include
srcDir = src

fastFlags = -pthread -O3 -march=native -ffast-math
simpleSrc = $(srcDir)/fill_matrices.c $(srcDir)/simple_mul.c $(srcDir)/writer.c

simple:
	gcc -I$(libDir) simple_main.c $(simpleSrc) -o simple_main

fast:
	gcc -I$(libDir) $(fastFlags) fast_main.c $(srcDir)/* -o fast_main

clean:
	rm -f *main
