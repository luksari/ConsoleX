#pragma once
#ifndef  ROGUE_H
#define ROGUE_H

#include "curses.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Struktury*/

typedef struct Position {
	int x;
	int y;
}Position;

typedef struct Door
{
	Position position;
	int isConnected;

}Door;

typedef struct Room
{
	Position position;
	int height;
	int width;
	Door ** doors;
	int numberOfDoors;

}Room;

typedef struct Player
{
	Position * position;
	int health;
	int attack;
	int gold;
	int experience;
	int maxHealth;
	int inroom;

} Player;

typedef struct Items
{
	Position * position;
	char symbol;
	char string[2];
	int value;
	int type;

} Items;

typedef struct Level
{
	char ** tiles;
	int round;
	int numberOfRooms;
	struct Room ** rooms;
	struct Monsters ** monsters;
	struct Items ** items;
	int numberOfMonsters;
	struct Player * user;
	int numberOfItems;
	int firstTime;

}Level;

typedef struct Monsters
{
	char string[2];
	char symbol;
	int health;
	int attack;
	int speed;
	int defence;
	int pathfinding;
	int alive;
	Position * position;

}Monsters;


/*Funkcje interfejsu*/
int screenSetup();
int printGameHub(Level * level);
int menuLoop(void);
int gameLoop(int round);
int nextLevelLoop(int round, Level * level);
int helpLoop(void);
int betweenLevel(Level * level);
int printTextBox(char *ch);
int endGame(Level * level);

/*Funkcje poziomu*/

Level * createLevel(int level); /*Tworzenie poziomu*/
Room ** roomsSetUp(); /*Tworzenie pokojów*/
char ** saveLevelPositions(); /*Cachowanie*/
void connectDoors(Level * level); /*£¹czenie drzwi*/
int endLevel(Level * level); /*Koniec poziomu*/
Level * nextLevel(int round, Level * level); /*Tworzenie kolejnego poziomu*/
void pathFind(Position * start, Position * end);
int freeEverything(Level * level);

/*Funkcje gracza*/

Player * playerSetUp(); /*Ustawienie gracza*/
Position * getInput(int input, Player * user); /*Pobieranie input*/
int playerMove(Position * newPosition, Player * user, char ** level); /*Ruch*/
int checkPosition(Position * newPosition, Level * level); /*Sprawdzanie kolizji*/
int placePlayer(Room ** rooms, Player * user); /*Umieszczanie gracza*/
int killPlayer(Player * user); /*Smierc gracza*/
int playerInRoom(Position * newPosition, Level * level); /*Sprawdzanie czy gracz jest w pokojach*/

/*Funkcje dotyczace pomieszczeñ*/

Room * createRoom(int grid, int numberOfDoors); /*Ustalanie rozmiarow i koordynatow pomieszczenia*/
int drawRoom(Room *room); /*Rysowanie pomieszczeñ*/

/*Funkcje przedmiotów*/
Items * createItem(char symbol, int value, int type);
int setItemPosition(Items * item, Room  * room); /*Wybranie pozycji startowej przedmiotu*/
int addItems(Level * level); /*Dodanie przedmiotu*/
Items * selectItems(int level); /*Wybranie przedmiotu do addItems*/
int destroyItem(Items * item); /*Znikniecie przedmiotu*/
int useItem(Player * player, Items * item, int type); /*U¿ycie konkretnego przedmiotu*/
Items * getItemAt(Position * position, Items ** item); /*Pozyskanie konkretnego przedmiotu*/

/*Funkcje potworów*/

int addMonsters(Level * level); /*Dodawanie potwora do planszy*/
Monsters * selectMonsters(int level); /*Wybieranie potwora do addMonsters*/
Monsters * createMonster(char symbol, int health, int attack, int pathfinding); /*Tworzenie potwora*/
int setStartingPosition( Monsters * monster, Room  * room); /*Ustawianie pozycji potwora*/
int moveMonster(Level * level); /*Wybieranie trybu poruszania*/
int pathfindingSeek(Position * start, Position * destination); /*Tryb szukania gracza*/
int pathfindingRandom(Position * position); /*Losowe poruszanie siê*/
Monsters * getMonsterAt(Position * position, Monsters ** monsters); /*Pozyskanie pozycji potwora*/
int killMonster( Monsters * monsters); /*Zabicie potwora*/
int changePathfinding(Level * level); /*Zmiana trybu ruchu*/

/*Funkcje walki*/
int combat(Player *player, Monsters *monsters, int order);

/*Funkcje plikow*/
int printLogo(WINDOW * window);

/*
void saveLevel();
char ** loadLevel();
Level * loadedGame(int round)
*/

/*Zdefiniowane znaki*/

#define PLAYER '@'

#define DOG 'D'
#define GOBLIN 'G'
#define SPIDER 'X'
#define TROLL 'T'

#define HP_POTION 197
#define ATK_BOOSTER 175
#define HP_BOOSTER 206
#define GOLD '$'

#define ROAD 177
#define FLOOR 178
#define DOOR 176
#define SIDEWALL 219
#define TOPWALL 220
#define BOTWALL 223

#define MAX_HEIGHT 30
#define MAX_WIDTH 105
#define MAX_LEN 128


/*Kolory*/

#define YELLOW COLOR_PAIR(1)
#define RED    COLOR_PAIR(2)
#define GREEN COLOR_PAIR(3)


#endif // ! ROGUE_H