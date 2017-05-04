#include "rogue.h"

int printLogo(WINDOW * window)
{
	clear();
	refresh();
	char *filename = "image.txt";
	FILE *file;
	int i = 1;
	char read_string[MAX_LEN];
	if ((file = fopen(filename, "r+")) == NULL)
	{
		fprintf(stderr, "error opening %s\n", filename);
		return 1;
	}
	while (fgets(read_string, sizeof(read_string), file) != NULL)
	{
		wmove(window, 3 + i, 20);
		wprintw(window, "%s", read_string);
		i++;
	}
	fclose(file);
	return 1;
}
/*
void saveLevel()
{
	FILE * file;
	char * filename = "save.txt";
	int x, y;
	char ** map;
	map =  saveLevelPositions();
	if ((file = fopen(filename, "w")) == NULL)
	{
		fprintf(stderr, "error creating %s\n", filename);
		return 1;
	}
	else
	{
		for (y = 0; y < MAX_HEIGHT; y++)
		{
			for (x = 0; x < MAX_WIDTH; x++)
			{
				fwrite(&map[y][x], sizeof(char), 1, file);
			}
		}
	}
	fclose(file);
}
char ** loadLevel()
{
	FILE * file;
	char * filename = "save.txt";
	int x, y;
	char ** map;
	map = saveLevelPositions();
	if ((file = fopen(filename, "w")) == NULL)
	{
		fprintf(stderr, "error creating %s\n", filename);
		return 1;
	}
	else
	{
		for (y = 0; y < MAX_HEIGHT; y++)
		{
			for (x = 0; x < MAX_WIDTH; x++)
			{
				fread(&map[y][x], sizeof(char), 1, file);
			}
		}
	}
	fclose(file);
}*/

	




