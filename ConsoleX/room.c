#include "rogue.h"

Room * createRoom(int grid, int numberOfDoors)
{
	int i;
	Room * newRoom;
	newRoom = (Room*) malloc(sizeof(Room));
	newRoom->numberOfDoors = numberOfDoors;
	/*6 przestrzeni*/
	switch (grid)
	{
	case 0: /*1 przestrzeñ*/
		newRoom->position.x = 0; 
		newRoom->position.y = 0;
		break;
	case 1: /*2 przestrzeñ*/
		newRoom->position.x = 33;
		newRoom->position.y = 0;
		break;
	case 2: /*3 przestrzeñ*/
		newRoom->position.x = 66;
		newRoom->position.y = 0;
		break;
	case 3:/*4 przestrzeñ*/
		newRoom->position.x = 0;
		newRoom->position.y = 14;
		break;
	case 4:/*5 przestrzeñ*/
		newRoom->position.x = 33;
		newRoom->position.y = 14;
		break;
	case 5:/*6 przestrzeñ*/
		newRoom->position.x = 66;
		newRoom->position.y = 14;
		break;
	}
	newRoom->height = (rand() % 6) + 4; /*maksimum 9*/
	newRoom->width = (rand() % 14) + 4; /*maksimum 17*/

	/*Losowosc odstepow pomiedzy pokojami*/
	newRoom->position.x += rand() % (30 - newRoom->width) + 2;
	newRoom->position.y += rand() % (10 - newRoom->height) + 2;

	newRoom->doors = (Door **)malloc(sizeof(Door *) * numberOfDoors);

	for (i = 0; i < numberOfDoors; i++)
	{
		newRoom->doors[i] = (Door*) malloc(sizeof(Door));
		newRoom->doors[i]->isConnected = 0;
	}
	/*Gorne drzwi*/

	newRoom->doors[0]->position.x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
	newRoom->doors[0]->position.y = newRoom->position.y;
	/*Lewe drzwi*/

	newRoom->doors[1]->position.y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;
	newRoom->doors[1]->position.x = newRoom->position.x;
	/*Dolne drzwi*/

	newRoom->doors[2]->position.x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
	newRoom->doors[2]->position.y = newRoom->position.y + newRoom->height - 1;
	/*Prawe drzwi*/

	newRoom->doors[3]->position.y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;
	newRoom->doors[3]->position.x = newRoom->position.x + newRoom->width - 1;

	return newRoom;
}
int drawRoom(Room * room)
{
	int x;
	int y;
	/*Rysowanie gornej i dolnej sciany*/
	for (x = room->position.x; x < room->position.x + room->width; x++)
	{
		mvaddch(room->position.y, x, TOPWALL); /*Gorna sciana*/
		mvaddch(room->position.y + room->height - 1, x, BOTWALL); /*Dolna sciana*/
	}
	/*Rysowanie podlog i bocznych scian*/
	for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++)
	{
		/*boczne sciany*/
		mvaddch(y, room->position.x, SIDEWALL);
		mvaddch(y, room->position.x + room->width - 1, SIDEWALL);
		/*podlogi*/
		for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
		{
			
			mvaddch(y, x, FLOOR);
		}
	}
	/*Rysowanie drzwi*/
	mvaddch(room->doors[0]->position.y, room->doors[0]->position.x, DOOR);
	mvaddch(room->doors[1]->position.y, room->doors[1]->position.x, DOOR);
	mvaddch(room->doors[2]->position.y, room->doors[2]->position.x, DOOR);
	mvaddch(room->doors[3]->position.y, room->doors[3]->position.x, DOOR);
	return 1;
}


