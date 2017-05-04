#include "rogue.h"

int combat(Player * player, Monsters * monster, int order)
{
	/*Gracz atakuje*/
	if (order == 1)
	{
		monster->health -= player->attack;
		if (monster->health > 0)
		{
			player->health -= monster->attack;
		}
		else if(monster->health <= 0)
		{
			killMonster(monster);
			player->experience++;
		}
		else if (player->health <= 0)
		{
			killPlayer(player);
		}
	}
	/*Potwor atakuje*/
	else
	{
		player->health -= monster->attack;
		if (monster->health > 0)
		{
			monster->health -= player->attack;
		}
		else if (monster->health <= 0)
		{
			killMonster(monster);
			player->experience++;
		}
		else if (player->health <= 0)
		{
			killPlayer(player);
		}
	}
	return 1;
}	