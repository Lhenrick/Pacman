#include <stdio.h>
#include "map.h"

char wallformat[4][7] = {
	{"......"},
	{"......"},
	{"......"},
	{"......"}};

char ghostformat[4][7] = {
	{" .-.  "},
	{"| OO| "},
	{"|   | "},
	{"'^^^' "}};

char pacmanformat[4][7] = {
	{" .--. "},
	{"/ _.-'"},
	{"\\  '-."},
	{" '--' "}};

char pillformat[4][7] = {
	{"      "},
	{" .-.  "},
	{" '-'  "},
	{"      "}};

char emptyformat[4][7] = {
	{"      "},
	{"      "},
	{"      "},
	{"      "}};


// Imprime o formato especificado para uma peça do mapa
void printformat(char format[4][7], int piece)
{
	printf("%s", format[piece]);
}

// Imprime o mapa completo
void printmap(MAP *m)
{
	for (int i = 0; i < m->rows; i++)
	{
		for (int piece = 0; piece < 4; piece++)
		{
			for (int j = 0; j < m->columns; j++)
			{

				switch (m->matrix[i][j])
				{
				case GHOST:
					printformat(ghostformat, piece);
					break;

				case HERO:
					printformat(pacmanformat, piece);
					break;
				
				case PILL:
					printformat(pillformat, piece);
					break;

				case VERTICAL_WALL:
				case HORIZONTAL_WALL:
					printformat(wallformat, piece);
					break;

				case EMPTY:
					printformat(emptyformat, piece);
					break;
				}
			}

			printf("\n");
		}
	}
}