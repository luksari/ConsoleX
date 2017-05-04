#include "rogue.h"

Player * playerSetUp()
{
	Player * newPlayer;
	newPlayer = (Player*)malloc(sizeof(Player));
	newPlayer->position;
	newPlayer->position = (Position*)malloc(sizeof(Position));

	newPlayer->health = 25;
	newPlayer->attack = 2;
	newPlayer->gold = 0;
	newPlayer->experience = 0;
	newPlayer->maxHealth = 25;
	newPlayer->inroom = 0;

	return newPlayer;
}
/*Umieszczanie gracza w danym pokoju*/
int placePlayer(Room ** rooms, Player * user)
{
	int n = rand() % 6;
	user->position->x = rooms[n]->position.x + 1;
	user->position->y = rooms[n]->position.y + 1;
	mvaddch(user->position->y, user->position->x, PLAYER);
	return 1;
}
int killPlayer(Player * player)
{
	mvaddch(player->position->y, player->position->x, FLOOR);
	return 1;
}
Position * getInput(int input, Player * user)
{
	Position * newPosition;
	newPosition = (Position*) malloc(sizeof(Position));
	switch (input)
	{
		/*w gore*/
	case 'w':
	case 'W':
		newPosition->y = user->position->y - 1;
		newPosition->x = user->position->x;
		break;
		/*w dol*/
	case 's':
	case 'S':
		newPosition->y = user->position->y + 1;
		newPosition->x = user->position->x;
		break;
		/*w lewo*/
	case 'a':
	case 'A':
		newPosition->y = user->position->y;
		newPosition->x = user->position->x - 1;
		break;
		/*w prawo*/
	case 'd':
	case 'D':
		newPosition->y = user->position->y;
		newPosition->x = user->position->x + 1;
		break;
	}
	return newPosition;
}
int playerInRoom(Position * newPosition, Level * level)
{
	int x, y, i;
	Room ** rooms;
	Player * player;
	player = level->user;
	rooms = level->rooms;
	player->position->y = newPosition->y;
	player->position->x = newPosition->x;
	for (i = 0; i < level->numberOfRooms; i++)
	{
		for (y = rooms[i]->position.y; y < rooms[i]->position.y + rooms[i]->height; y++)
		{
			for (x = rooms[i]->position.x; x < rooms[i]->position.x + rooms[i]->width; x++)
			{
				if (x == newPosition->x && y == newPosition->y)
				{
					player->inroom = 1;
					changePathfinding(level);
					return 1;
				}
				else
				{
					player->inroom = 0;
					changePathfinding(level);
				}
			}
		}
	}
	return 1;
}
/*sprawdzanie pozycji nastepujacej*/
int checkPosition(Position * newPosition, Level * level)
{
	Player * user;
	user = level->user;
	if (user->health > 0)
	{
		switch (mvinch(newPosition->y, newPosition->x))
		{
		case FLOOR:
			printTextBox("This floor is so cold");
			playerMove(newPosition, user, level->tiles);
			playerInRoom(newPosition, level);
			break;
		case DOOR:
			printTextBox("This doors are totally destroyed");
			playerMove(newPosition, user, level->tiles);
			playerInRoom(newPosition, level);
			break;
		case ROAD:
			printTextBox("You feel scared");
			playerMove(newPosition, user, level->tiles);
			playerInRoom(newPosition, level);
			break;
			//Potwory
		case SPIDER:
			printTextBox("You've attacked Spider");
			combat(user, getMonsterAt(newPosition, level->monsters), 1);
			break;
		case GOBLIN:
			printTextBox("You've attacked Goblin");
			combat(user, getMonsterAt(newPosition, level->monsters), 1);
			break;
		case TROLL:
			printTextBox("You've attacked Troll");
			combat(user, getMonsterAt(newPosition, level->monsters), 1);
			break;
		case DOG:
			printTextBox("You've attacked Dog");
			combat(user, getMonsterAt(newPosition, level->monsters), 1);
			break;
		case HP_POTION:
			printTextBox("Your hp has been restored");
			useItem(user, getItemAt(newPosition, level->items), 1);
			break;
		case HP_BOOSTER:
			printTextBox("Your hp has been increased");
			useItem(user, getItemAt(newPosition, level->items), 2);
			break;
		case ATK_BOOSTER:
			printTextBox("Your attack has been increased");
			useItem(user, getItemAt(newPosition, level->items), 3);
			break;
		case GOLD:
			printTextBox("Gold is what you need");
			useItem(user, getItemAt(newPosition, level->items), 4);
			break;
		default:
			printTextBox("Your brain has been damaged");
			break;
		}
	}

	return 1;
}
int playerMove(Position * newPosition, Player * user, char ** level)
{
	{
		char buffer[8];

		sprintf(buffer, "%c", level[user->position->y][user->position->x]);

		mvprintw(user->position->y, user->position->x, buffer); // drukowanie znaku poprzedzaj¹cego pozycje gracza

		user->position->y = newPosition->y; 
		user->position->x = newPosition->x; 

		mvprintw(user->position->y, user->position->x,"@");

	}
	return 1;
}