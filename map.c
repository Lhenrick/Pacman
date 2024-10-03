#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"


// Lê o mapa de um arquivo
void readmap(MAP *m)
{
    FILE *f;
    f = fopen("map.txt", "r");
    if (f == 0)
    {
        printf("Error reading map\n");
        exit(1);
    }

    fscanf(f, "%d %d", &(m->rows), &(m->columns));

    allocatemap(m);

    for (int i = 0; i < m->rows; i++)
    {
        fscanf(f, "%s", m->matrix[i]);
    }
    fclose(f);
}

// Aloca memória para o mapa
void allocatemap(MAP *m)
{
    m->matrix = malloc(sizeof(char *) * m->rows);
    for (int i = 0; i < m->rows; i++)
    {
        m->matrix[i] = malloc(sizeof(char) * m->columns + 1);
    }
}

// Copia o mapa de origem para o destino
void copymap(MAP *destiny, MAP *origin)
{
    destiny->rows = origin->rows;
    destiny->columns = origin->columns;

    allocatemap(destiny);
    for (int i = 0; i < origin->rows; i++)
    {
        strcpy(destiny->matrix[i], origin->matrix[i]);
    }
}

// Libera a memória alocada para o mapa
void freemap(MAP *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        free(m->matrix[i]);
    }

    free(m->matrix);
}

// Encontra um caractere específico no mapa e retorna sua posição
int findmap(MAP *m, POSITION *p, char c)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->columns; j++)
        {
            if (m->matrix[i][j] == c)
            {
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }
    return 0;
}

// Verifica se o personagem pode andar em uma determinada posição
int canwalk(MAP *m, char character, int x, int y)
{
    return isvalid(m, x, y) &&
           !iswall(m, x, y) &&
           !ischaracter(m, character, x, y);
}

// Verifica se a posição é válida no mapa
int isvalid(MAP *m, int x, int y)
{
    if (x >= m->rows)
        return 0;
    if (y >= m->columns)
        return 0;

    return 1;
}

// Verifica se há um personagem em uma determinada posição
int ischaracter(MAP *m, char character, int x, int y)
{
    return m->matrix[x][y] == character;
}

// Verifica se a posição é uma parede
int iswall(MAP *m, int x, int y)
{
    return m->matrix[x][y] == VERTICAL_WALL ||
           m->matrix[x][y] == HORIZONTAL_WALL;
}

// Move um personagem de uma posição para outra no mapa
void walk(MAP *m, int xorigin, int yorigin, int xdestiny, int ydestiny)
{

    char character = m->matrix[xorigin][yorigin];
    m->matrix[xdestiny][ydestiny] = character;
    m->matrix[xorigin][yorigin] = EMPTY;
}
