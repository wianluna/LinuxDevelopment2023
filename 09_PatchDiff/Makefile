GENERATES = *.o maze maze_v2 maze_v3 maze_v4 maze_v2.c maze_v3.c maze_v4.c

all: maze maze_v2 maze_v3 maze_v4 run

maze: maze.c
	cc $< -o $@

maze_v2.c: maze.c v2.patch
	patch -b $< v2.patch
	mv $< maze_v2.c
	mv $<.orig $<

maze_v2: maze_v2.c
	cc $< -o $@

maze_v3.c: maze_v2.c v3.patch
	patch -b $< v3.patch
	mv $< maze_v3.c
	mv $<.orig $<

maze_v3: maze_v3.c
	cc $< -o $@

maze_v4.c: maze_v3.c v4.patch
	patch -b $< v4.patch
	mv $< maze_v4.c
	mv $<.orig $<

maze_v4: maze_v4.c
	cc $< -o $@

run: maze maze_v2 maze_v3 maze_v4
	./maze
	./maze_v2 6
	./maze_v3 " #" 6
	./maze_v4 42 " #" 6

clean:
	rm -f $(GENERATES)