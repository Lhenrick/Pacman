#ifndef _MAP_H_
#define _MAP_H_

#define HERO '@'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define GHOST 'G'
#define PILL 'P'


struct map
{
    char **matrix;
    int rows;
    int columns;
};

typedef struct map MAP;

void allocatemap(MAP *m);
void readmap(MAP *m);
void freemap(MAP *m);

struct position
{
    int x;
    int y;
};

typedef struct position POSITION;

int findmap(MAP* m, POSITION* p, char c);

int isvalid(MAP* m, int X, int y);
int iswall(MAP* m, int x, int y);

int ischaracter(MAP* m, char character, int x, int y);

void walk(MAP* m,int xorigin, int yorigin, int xdestiny, int ydestiny);

void copymap(MAP* destiny, MAP* origin);

int canwalk(MAP* m, char character, int x, int y);

#endif
