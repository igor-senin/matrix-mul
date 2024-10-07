all: simple fast

libDir = include
srcDir = src

fastFlags = -pthread -O3 -march=native -ffast-math

simple:
	gcc -I$(libDir) simple_main.c $(srcDir)/fill_matrices.c $(srcDir)/simple_mul.c $(srcDir)/writer.c -o simple_main

fast:
	gcc -I$(libDir) $(fastFlags) fast_main.c $(srcDir)/* -o fast_main

clean:
	rm -f *main
