#include "rogue.h"
#include "utils.h"

Level * createLevel(int round)
{
	Level * newLevel;

	newLevel = (Level*) malloc(sizeof(Level));

	newLevel->round = round;
	newLevel->numberOfRooms = 6;
	newLevel->rooms = roomsSetUp();
	connectDoors(newLevel);
	newLevel->tiles = saveLevelPositions();
	newLevel->user = playerSetUp();
	placePlayer(newLevel->rooms, newLevel->user); 
	addMonsters(newLevel);
	addItems(newLevel);
	newLevel->firstTime = round;

	return newLevel;
}
Level * nextLevel(int round, Level * level)
{
	Level * newLevel;

	newLevel = (Level*) malloc(sizeof(Level));
	
	newLevel->round = round;
	newLevel->numberOfRooms = 6;
	newLevel->rooms = roomsSetUp();
	connectDoors(newLevel);
	newLevel->tiles = saveLevelPositions();
	newLevel->user = level->user;
	placePlayer(newLevel->rooms, newLevel->user);
	addMonsters(newLevel);
	addItems(newLevel);
	newLevel->firstTime = round;

	return newLevel;
}

int endLevel(Level * level)
{
	clear();
	int round = level->round;
	if ((int)level->round == 6)
	{
		endGame(level);
	}
	else 
	{
		round++;
		nextLevelLoop(round, level);
	}

	return 1;
}
Room ** roomsSetUp()
{
	int i;
	Room ** rooms;
	rooms = (Room **) malloc(sizeof(Room) * 6);
	/*Kreowanie pomieszczeñ*/
	for(i = 0; i < 6; i++)
	{
		rooms[i] = createRoom(i, 4);
		drawRoom(rooms[i]); 
	}
	return rooms;
}
/*£¹czenie drzwi*/
void connectDoors(Level * level)
{
	int i, j;
	int randomRoom, randomDoor;
	int count;

	for (i = 0; i < level->numberOfRooms; i++)
	{
		for (j = 0; j < level->rooms[i]->numberOfDoors; j++)
		{
			if (level->rooms[i]->doors[j]->isConnected == 1)
			{
				continue;
			}

			count = 0;

			while (count < 10) /*Iloœæ prób po³¹czenia drzwi*/
			{
				randomRoom = rand() % level->numberOfRooms;
				randomDoor = rand() % level->rooms[randomRoom]->numberOfDoors;

				if (level->rooms[randomRoom]->doors[randomDoor]->isConnected == 1 || randomRoom == i)
				{
					count++;
					continue;
				}

				pathFind(&level->rooms[randomRoom]->doors[randomDoor]->position, &level->rooms[i]->doors[j]->position);

				level->rooms[randomRoom]->doors[randomDoor]->isConnected = 1;
				level->rooms[i]->doors[j]->isConnected = 1;
				break;
			}
		}
	}
}
/*Zapisywanie stanu konsoli*/
char ** saveLevelPositions()
{
	int x, y;
	char ** positions;
	positions = malloc(sizeof(char *) * MAX_HEIGHT);
	for (y = 0; y < MAX_HEIGHT; y++)
	{
		positions[y] = malloc(sizeof(char) * MAX_WIDTH);
		for (x = 0; x < MAX_WIDTH; x++)
		{
			positions[y][x] = (char) mvinch(y, x);
		}
	}
	return positions;
}