#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include <list>
#include <vector>
#include "GameWorld.h"
#include "GameConstants.h"
#include "Compiler.h"
#include "Actor.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class Pebble;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir);
	~StudentWorld();
	bool loadingField();
	bool getPassability(int posX, int posY);
	void setDisplayText(std::string& output, int& winnernum);
	
	void poisonAll(int posX, int posY);
	void feedAll(int posX, int posY);
	void areYouWaterBecauseYoureStunningAll(int posX, int posY);
	void moveSomeShit(Actor* q, int oldX, int oldY, int NewX, int NewY);

	bool checkforenemies(int posX, int posY, Actor* checker);
	bool checkforfood(int posX, int posY);
	bool checkforanthill(int posX, int posY, Actor *checker);
	bool checkforpheromones(int posX, int posY, Actor *checker);
	bool checkfordanger(int posX, int posY, Actor* checker);

	void grasshopperbite(int posX, int posY, Actor* biter);
	void antbite(int posX, int posY, Actor* biter);
	bool attempteat(int posX, int posY, Actor* eater, int amount);
	bool pickupfood(int posX, int posY, Actor* pickerupper, int amount);
	void createFood(int posX, int posY, int amount);
	void makePheromoneStrongerDaddy(int posX, int posY, Actor* squirter);
	
	void increase0();
	void increase1();
	void increase2();
	void increase3();

	void createNewAnt(int posX, int posY, int id);

	virtual int init();
	virtual int move();
	virtual void cleanUp();
private:
	std::vector<Actor*> m_virtualfield[VIEW_WIDTH][VIEW_HEIGHT];
	Compiler* m_compinitarray[4];
	int m_numberticks;
	int m_antscolony0;
	int m_antscolony1;
	int m_antscolony2;
	int m_antscolony3;

	std::string m_colonyNamesHolder[4];

	Compiler num0;
	Compiler num1;
	Compiler num2;
	Compiler num3;

	Anthill* a0;
	Anthill* a1;
	Anthill* a3;
	Anthill* a4;
};

#endif // STUDENTWORLD_H_
