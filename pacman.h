#ifndef _RUN_H_
#define _RUN_H_

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define BOMB 'b'

int over();
void move(char direction);

int isdirection(char direction);
void ghosts();
void explodepill();
void explodepill2(int x, int y, int sumx, int sumy, int qtt);


#endif

