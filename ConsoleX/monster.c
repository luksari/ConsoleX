#include "rogue.h"

int addMonsters(Level * level)
{
	int x;
	level->monsters =(Monsters**) malloc(sizeof(Monsters *) * 6);
	level->numberOfMonsters = 0;

	for (x = 0; x < level->numberOfRooms; x++)
	{
			level->monsters[level->numberOfMonsters] = selectMonsters((int)level->round);
			setStartingPosition(level->monsters[level->numberOfMonsters], level->rooms[x]);
			level->numberOfMonsters++;
	}
	return 1;
}
Monsters * selectMonsters(int level)
{
	int monster;
	switch (level)
	{
	case 1:
		monster = (rand() % 2) + 1;
		break;
	case 2:
		monster = (rand() % 3) + 1;
		break;
	case 3:
		monster = (rand() % 4) + 1;
		break;
	case 4:
		monster = (rand() % 4) + 1;
		break;
	case 5:
		monster = (rand() % 4) + 1;
		break;
	case 6:
		monster = (rand() % 4) + 1;
		break;
	}
	switch (monster)
	{
	case 1: /*Dog*/
		return createMonster(DOG, 1, 1, 1);
	case 2: /*Spider*/
		return createMonster(SPIDER, 3, 2, 1);
	case 3: /*Goblin*/
		return createMonster(GOBLIN, 5, 3, 1);
	case 4: /*Troll*/
		return createMonster(TROLL, 8, 4, 1);
	default: return NULL;
	}
}
Monsters * createMonster(char symbol, int health, int attack, int pathfinding)
{
	Monsters * newMonster;

	newMonster = (Monsters*) malloc(sizeof(Monsters));
	newMonster->position = (Position*) malloc(sizeof(Position));
	
	newMonster->symbol = symbol;
	newMonster->health = health;
	newMonster->attack = attack;
	newMonster->pathfinding = pathfinding;
	newMonster->alive = 1;
	
	sprintf(newMonster->string, "%c", symbol);

	return newMonster;
}
int killMonster(Monsters * monsters)
{
	Level * level;
	mvaddch(monsters->position->y, monsters->position->x, FLOOR);
	monsters->alive = 0;

	level->numberOfMonsters--;

	return 1;
}
int setStartingPosition(Monsters * monster, Room  * room)
{
	monster->position = (Position*) malloc(sizeof(Position));

	monster->position->x = (rand() % (room->width - 2)) + room->position.x +1;
	monster->position->y = (rand() % (room->height - 2)) + room->position.y +1;
	mvprintw(monster->position->y, monster->position->x, monster->string); //Drukowanie pozycji startowej potwora
	return 1;
}
int changePathfinding(Level * level)
{
	int i;
		for (i = 0; i < 6; i++)
		{
			if (level->user->inroom == 1)
			{
				level->monsters[i]->pathfinding = 1;
			}
			else
			{
				level->monsters[i]->pathfinding = 0;
			}
		}
		return 1;
	}

int moveMonster(Level * level)
{
	int i;
	for (i = 0; i < 6; i++)
	{
		if (level->monsters[i]->alive == 0)
			continue;
		else
		{
			mvaddch(level->monsters[i]->position->y, level->monsters[i]->position->x, FLOOR);

			if (level->monsters[i]->pathfinding == 1)
			{
				pathfindingSeek(level->monsters[i]->position, level->user->position);
			}
			else
			{
				pathfindingRandom(level->monsters[i]->position);
			}

			mvprintw(level->monsters[i]->position->y, level->monsters[i]->position->x, level->monsters[i]->string); // Drukowanie znaku potwora
		}
	}
	return 1;
}
int pathfindingRandom(Position *position)
{
	int random;

	random = rand() % 5;

	switch (random)
	{
	/*do gory*/
	case 0:
		if (mvinch(position->y - 1, position->x) == FLOOR)
		{
			position->y =position->y - 1;
		}
		break;
	/*w dol*/
	case 1:
		if (mvinch(position->y + 1, position->x) == FLOOR)
		{
			position->y = position->y + 1;
		}
		break;
	/*w lewo*/
	case 2:
		if (mvinch(position->y, position->x - 1) == FLOOR)
		{
			position->x = position->x - 1;
		}
		break;
	/*w prawo*/
	case 3:
		if (mvinch(position->y, position->x + 1) == FLOOR)
		{
			position->x = position->x + 1;
		}
		break;
	/*nic nie rob*/
	case 4:
		break;
	}
	return 1;
}
int pathfindingSeek(Position * start, Position * destination)
{
	//Krok w lewo
	if ((abs((start->x - 1) - destination->x) < abs(start->x - destination->x)) && (mvinch(start->y, start->x - 1) == FLOOR))
	{
		start->x = start->x - 1;
	} //krok w prawo
	else if ((abs((start->x + 1) - destination->x) < abs(start->x - destination->x)) && (mvinch(start->y, start->x + 1) == FLOOR))
	{
		start->x = start->x + 1;
	} //krok w dol
	else if ((abs((start->y + 1) - destination->y) < abs(start->y - destination->y)) && (mvinch(start->y + 1, start->x) == FLOOR))
	{
		start->y = start->y + 1;
	} //krok w gore
	else if ((abs((start->y - 1) - destination->y) < abs(start->y - destination->y)) && (mvinch(start->y - 1, start->x) == FLOOR))
	{
		start->y = start->y - 1;
	}
	else
	{
		/*Nic nie robi*/
	}
	return 1;
}
Monsters * getMonsterAt(Position * position, Monsters ** monsters)
{
	int i;
	for (i = 0; i < 6; i++)
	{
		if ((position->y == monsters[i]->position->y) && (position->x == monsters[i]->position->x))
			return monsters[i];
	}
	return NULL;
}

