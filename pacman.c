#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "pacman.h"
#include "map.h"
#include "ui.h"

MAP m;
POSITION hero;
int haspill = 0;


// Verifica se o jogo acabou (vencido ou perdido)
int over()
{
    POSITION pos;

    int lost = !findmap(&m, &pos, HERO);
    int won = !findmap(&m, &pos, GHOST);

    if(won){

        printf("You won! Congratulations!");
        return won;
    } else {
        printf("You lost! :( Try again!");
        return lost;
    }

    //return won || lost;
}

// Determina para onde o fantasma deve ir
int wheretheghostgoes(int currentx, int currenty, int *xdestiny, int *ydestiny)
{
    int options[4][2] = {
        {currentx, currenty + 1},
        {currentx + 1, currenty},
        {currentx, currenty - 1},
        {currentx - 1, currenty},

    };

    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        int position = rand() % 4;

        if (canwalk(&m, GHOST, options[position][0], options[position][1]))
        {
            *xdestiny = options[position][0];
            *ydestiny = options[position][1];

            return 1;
        }
    }
    return 0;
}

// Move todos os fantasmas no mapa
void ghosts()
{
    MAP copy;

    copymap(&copy, &m);
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {

            if (copy.matrix[i][j] == GHOST)
            {
                int xdestiny;
                int ydestiny;

                int found = wheretheghostgoes(i, j, &xdestiny, &ydestiny);

                if (found)
                {
                    walk(&m, i, j, xdestiny, ydestiny);
                }
            }
        }
    }

    freemap(&copy);
}

// Verifica se a direção fornecida é válida
int isdirection(char direction)
{
    return

        direction == LEFT ||
        direction == UP ||
        direction == DOWN ||
        direction == RIGHT;
}

// Verifica se a direção fornecida é válida
void move(char direction)
{

    int nextx = hero.x;
    int nexty = hero.y;

    switch (direction)
    {
    case LEFT:
        nexty--;
        break;
    case UP:
        nextx--;
        break;
    case DOWN:
        nextx++;
        break;
    case RIGHT:
        nexty++;
        break;
    }

    if (!canwalk(&m, HERO, nextx, nexty))// Verifica se o herói pode andar na nova direção
        return;

    if (ischaracter(&m, PILL, nextx, nexty))// Verifica se há uma pílula na nova posição
    {
        haspill = 1;
    }

    walk(&m, hero.x, hero.y, nextx, nexty);// Move o herói para a nova posição
    hero.x = nextx;
    hero.y = nexty;
}

// Função recursiva para limpar o mapa em uma direção específica após usar uma pílula
void explodepill2(int x, int y, int sumx, int sumy, int qtt)
{
    if (qtt == 0)
        return;

    int newx = x + sumx;
    int newy = y + sumy;

    if (!isvalid(&m, newx, newy))// Verifica se a nova posição é válida
        return;
    if (iswall(&m, newx, newy))// Verifica se a nova posição é uma parede
        return;

    m.matrix[newx][newy] = EMPTY;
    explodepill2(newx, newy, sumx, sumy, qtt - 1);
}

// Função recursiva para limpar o mapa em uma direção específica após usar uma pílula
void explodepill()
{
    if (!haspill)
        return;

    explodepill2(hero.x, hero.y, 0, 1, 3);
    explodepill2(hero.x, hero.y, 0, -1, 3);
    explodepill2(hero.x, hero.y, 1, 0, 3);
    explodepill2(hero.x, hero.y, -1, 0, 3);

    haspill = 0;// A pílula foi usada
}

// Função principal: executa o loop do jogo
int main()
{

    readmap(&m);
    findmap(&m, &hero, HERO);

    do
    {
        printf("Pill: %s\n", (haspill ? "YES" : "NO"));
        printmap(&m);

        char command;
        scanf(" %c", &command);

        if (isdirection(command))
            move(command);
        if (command == BOMB)
            explodepill();
        
        ghosts();

    } while (!over());

    freemap(&m);
}