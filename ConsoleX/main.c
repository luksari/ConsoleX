#include "rogue.h"
#include "utils.h"


int main()
{
	screenSetup();
	menuLoop();
	endwin();
	return 0;
}
int freeEverything(Level * level)
{
	Room ** rooms = level->rooms;
	Door ** doors = (*rooms)->doors;
	Monsters ** monsters = level->monsters;
	Position * mPosition = (*monsters)->position;
	Items ** items = level->items;
	Position * iPosition = (*items)->position;
	Player * user = level->user;
	Position * uPosition = level->user->position;

		free(level->tiles);
			free(doors);
		free(rooms);
			free(mPosition);
		free(monsters);
			free(iPosition);
		free(items);
			free(uPosition);
		free(user);
		free(level);

	return 1;
}



