#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


#define MAZE_SIZE 6
#define VISITED 3
#define WALL 0
#define ROOM 1
#define DOOR_SYM '.'
#define WALL_SYM '#'


int getRandom(int lower, int upper) { 
    return rand() % (upper - lower + 1) + lower;  
} 


struct Cell {
    int x;
    int y;
};


struct CellStack {
    struct Cell cell;
    struct CellStack *next_cell;
};

struct CellsList{ 
    struct Cell* cells;
    int size;
};


void push(struct Cell cur_cell, struct CellStack **s){
   struct CellStack *tmp = malloc(sizeof(struct CellStack));
   tmp->next_cell = *s;
   tmp->cell = cur_cell;
   *s = tmp;
}


struct Cell pop(struct CellStack **s){
    struct CellStack *out = *s;
    *s = (*s)->next_cell;
    struct Cell c = out->cell;
    free(out);
    return c;
}


struct CellsList getNeighbours(int maze_size, int **maze, struct Cell c) {
    int x = c.x;
    int y = c.y;

    struct Cell coords[4]  = {{x, y + 2}, {x + 2, y}, {x, y - 2}, {x - 2, y}};
    struct CellsList cells;
    cells.cells = malloc(4 * sizeof(struct Cell));
    int size = 0;

    for (int i = 0; i < 4; ++i) {
        if (coords[i].x > 0 && coords[i].x < maze_size && coords[i].y > 0 && coords[i].y < maze_size) {
            int cur_cell_status = maze[coords[i].y][coords[i].x];
            struct Cell cur_cell = coords[i];
            if (cur_cell_status != VISITED && cur_cell_status != WALL) {
                cells.cells[size] = cur_cell;
                ++size;
            }
        }
    }

    cells.size = size;
    return cells;
}


int unvisitedCount(int maze_size, int** maze) {
    int count = 0;

    for (int i = 0; i < maze_size; ++i) {
        for (int j = 0; j < maze_size; ++j) {
            if (maze[i][j] != WALL && maze[i][j] != VISITED) {
                ++count;
            }
        }
    }

    return count;
}


int main(int argc, char **argv) {
    srand(time(0));
    int maze_size = MAZE_SIZE * 2 + 1;
    int **maze  = malloc(maze_size * sizeof(int*));

    for (int i = 0; i < maze_size; ++i) {
        maze[i] = malloc(maze_size  * sizeof(int));
        for (int j = 0; j < maze_size; j++){
            if ((i % 2 != 0 && j % 2 != 0) && (i < maze_size - 1 && j < maze_size - 1)) {
                maze[i][j] = ROOM;    
            } else {
                maze[i][j] = WALL;
            }
        }
    }

    struct Cell cur_cell = {1, 1};
    struct Cell neighbour_cell;
    struct CellStack *cell_stack = NULL;
    do {
        struct CellsList neighbours = getNeighbours(maze_size, maze, cur_cell);
        if (neighbours.size) {
            neighbour_cell = neighbours.cells[getRandom(0, neighbours.size - 1)];
            push(cur_cell, &cell_stack);
            
            int dx = neighbour_cell.x - cur_cell.x;
            int dy = neighbour_cell.y - cur_cell.y;
            dx = (dx != 0) ? (dx / abs(dx)) : 0;
            dy = (dy != 0) ? (dy / abs(dy)) : 0;
            int wall_x = cur_cell.x + dx;
            int wall_y = cur_cell.y + dy;
            maze[wall_y][wall_x] = VISITED;

            cur_cell = neighbour_cell;
            maze[cur_cell.y][cur_cell.x] = VISITED;
            free(neighbours.cells);
        } else if (cell_stack) {
            cur_cell = pop(&cell_stack);
        } else {
            struct CellsList unvisited_cells;
            int size = 0;

            unvisited_cells.cells = malloc(maze_size * maze_size *sizeof(struct Cell));

            for (int i = 0; i < maze_size; ++i) {
                for (int j = 0; j < maze_size; ++j) {
                    if ((maze[i][j] != WALL) && (maze[i][j] != VISITED)) {
                        unvisited_cells.cells[size].x = j;
                        unvisited_cells.cells[size].y = i;
                        size++;
                    }
                }
            }
            unvisited_cells.size = size;

            cur_cell = unvisited_cells.cells[getRandom(0, unvisited_cells.size - 1)];
            free(unvisited_cells.cells);
        }
    } while(unvisitedCount(maze_size, maze) > 0);

    for (int i = 0; i < maze_size; ++i) {
        for (int j = 0; j < maze_size; ++j) {
            if (maze[i][j] == WALL) {
                printf("%c", WALL_SYM);
            } else {
                printf("%c", DOOR_SYM);
            }
        }
        printf("\n");
        free(maze[i]);
    }
    free(maze);
    return 0;
}
