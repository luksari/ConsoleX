#include "rogue.h"

Items * createItem(char symbol, int value, int type)
{
	Items * newItem;

	newItem =(Items*) malloc(sizeof(Items));
	newItem->position =(Position*) malloc(sizeof(Position));

	newItem->symbol = symbol;
	newItem->value = value;
	newItem->type = type;

	sprintf(newItem->string, "%c", symbol);

	return newItem;
}
Items * selectItems(int level)
{
	int item;
	switch (level)
	{
	case 1:
		item = (rand() % 4) + 1;
		break;
	case 2:
		item = (rand() % 4) + 1;
		break;
	case 3:
		item = (rand() % 4) + 1;
		break;
	case 4:
		item = (rand() % 4) + 1;
		break;
	case 5:
		item = (rand() % 4) + 1;
		break;
	case 6:
		item = (rand() % 4) + 1;
		break;
	}
	switch (item)
	{
	case 1: /*HP POTION*/
		return createItem(HP_POTION, 5, 1);
	case 2: /*HP BOOSTER*/
		return createItem(HP_BOOSTER, 2, 2);
	case 3: /*ATTACK BOOSTER*/
		return createItem(ATK_BOOSTER, 2, 3);
	case 4:
		return createItem(GOLD, 1, 4);
	default:
		return NULL;
	}
}
int addItems(Level * level)
{
	int i;
	level->items = (Items**) malloc(sizeof(Items *) * 6);
	level->numberOfItems = 0;

	for (i = 0; i < level->numberOfRooms; i++)
	{
		if ((rand() % 3) == 0)
		{
			level->items[level->numberOfItems] = selectItems((int)level->round);
			setItemPosition(level->items[level->numberOfItems], level->rooms[i]);
			level->numberOfItems++;
		}
	}
	return 1;
}
int setItemPosition(Items * item, Room  * room)
{
	item->position =(Position*) malloc(sizeof(Position));

	item->position->x = (rand() % (room->width - 2)) + room->position.x + 1;
	item->position->y = (rand() % (room->height - 2)) + room->position.y + 1;

	mvprintw(item->position->y, item->position->x, item->string);
	return 1;
}
Items * getItemAt(Position * position, Items ** item)
{
	int i;
	for (i = 0; i < 6; i++)
	{
		if ((position->y == item[i]->position->y) && (position->x == item[i]->position->x))
			return item[i];
	}
	return NULL;
}
int useItem(Player * player, Items * item, int type)
{
	switch (type)
	{
	case 1:
		if (player->health <= (player->maxHealth - item->value)) /*HP Potion*/
		{
			player->health += item->value;
			destroyItem(item);
		}
		else
		{
			player->health = player->maxHealth; 
			destroyItem(item);
		}
		break;
	case 2:
		player->maxHealth += item->value; /*HP Booster*/
		destroyItem(item);
		break;
	case 3:
		player->attack += item->value; /*Attack Booster*/
		destroyItem(item);
		break;
	case 4:
		player->gold++;
		destroyItem(item);
		break;
	}
	return 1;
}
int destroyItem(Items * item)
{
	Level * level;
	mvaddch(item->position->y, item->position->x, FLOOR);
	level->numberOfItems--;

	return 1;
}