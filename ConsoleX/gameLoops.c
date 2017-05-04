#include "rogue.h"


int gameLoop(int round)
{
	clear();
	refresh();
	int ch;
	
	Position * newPosition = NULL;
	Level * level = NULL;

	level = createLevel(round);

	printGameHub(level);

	/*Petla 1 poziomu*/

	while (ch = getch())
	{
		if ((level->numberOfMonsters == 0 && level->numberOfItems == 0) || ch == 'b')
		{
			betweenLevel(level);
			return 1;
		}
		if (level->user->health <= 0)
		{
			killPlayer(level->user);
			endGame(level);
			break;
		}
		if (ch == 'q')
		{
			if (ch = getch() == 'q')
			{
				printTextBox("press [q] to quit");
				break;
			}
			else
			{
				continue;
			}
		}
		if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')
		{
			printGameHub(level);
			newPosition = getInput(ch, level->user);
			checkPosition(newPosition, level);
			moveMonster(level);
		}
	}
	/*Zwalnianie Level * level z pamiêci*/
	freeEverything(level);
	return 0;
}
int nextLevelLoop(int round, Level * level)
{
	int ch;
	Position * newPosition = NULL;

	level = nextLevel(round, level);

	printGameHub(level);

	/*Petla nowego poziomu*/

	while (ch = getch())
	{
		if ((level->numberOfMonsters == 0 && level->numberOfItems == 0) || ch == 'b')
		{
			if (level->round == 6)
			{
				endGame(level);
			}
			else
			{
				betweenLevel(level);
			}
			return 1;
		}
		if (level->user->health <= 0)
		{
			killPlayer(level->user);
			endGame(level);
			break;
		}
		if (ch == 'q')
		{
			if (ch = getch() == 'q')
			{
				printTextBox("press [q] to quit");
				break;
			}
			else
			{
				continue;
			}
		}
		if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')
		{
			printGameHub(level);
			newPosition = getInput(ch, level->user);
			checkPosition(newPosition, level);
			moveMonster(level);
		}
	}
	/*Zwalnianie Level * level z pamiêci*/
	freeEverything(level);
	return 0;
}