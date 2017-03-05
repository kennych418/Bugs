#ifndef ACTOR_H_
#define ACTOR_H_

#include <string>
#include "GraphObject.h"
#include "Compiler.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject{
public:
	Actor(int imageID, int startX, int startY, StudentWorld* world, Direction dir = right, int depth = 0, double size = 0.25);
	virtual ~Actor();
	virtual void getDamage(int damage) = 0;
	virtual void doSomething()=0;

	virtual bool isPoison();
	virtual bool isWater();
	virtual bool isFood();
	virtual bool isBabyGrasshopper();
	virtual bool isAdultGrasshopper();
	virtual bool isPheromone();
	virtual bool isAnt();
	virtual bool isAnthill();

	void setHealth(int health);
	int currentHealth();

	bool isDead();
	void setDeadorAlive(bool status);

	GraphObject::Direction Actor::randDirection();

	bool checkpassable();
	void editpassable(bool newPassable);

	StudentWorld* returnWorld();

	bool checkFirst();
	bool checkSecond();

	void editFirst(bool changer);
	void editSecond(bool changer);

	bool checkfood();
	void editfood(bool change);

	int checkturnnumber();
	void editturnnumber(int changer);

	void editbitten(bool changer);
	bool checkbitten();

	void editcarrying(int pickedup);
	int checkcarrying();

	void editcolony(int changer);
	int checkcolony();

private:
	bool m_passable;
	int m_health;
	bool m_aliver;
	StudentWorld* m_world;
	bool m_firstchecker;
	bool m_secondchecker;
	bool m_madefood;
	int m_turnnumber;
	bool m_bitten;
	int m_heldfood;
	int m_colony;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class inanimate : public Actor {
public:
	inanimate(int imageID, int startX, int startY, StudentWorld* world, Direction dir, int depth, double size);
	virtual ~inanimate();
	virtual void getDamage(int damage);
};
class animate : public Actor {
public:
	animate(int imageID, int startX, int startY, StudentWorld* world, Direction dir, int depth, double size);
	virtual ~animate();
	virtual void getDamage(int damage);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Pebble : public inanimate {
public:
	Pebble(int startX, int startY, StudentWorld* startworld);
	virtual ~Pebble();
	virtual void doSomething();
private:
};

class Poison : public inanimate {
public:
	Poison(int startX, int startY, StudentWorld* startworld);
	virtual ~Poison();
	virtual bool isPoison();
	virtual void doSomething();
private:
	int m_xcoord;
	int m_ycoord;
};
class Food : public animate {
public:
	Food(int startX, int startY, StudentWorld* startworld);
	virtual ~Food();
	virtual bool isFood();
	virtual void doSomething();
	//virtual void setHealth(int health);
private:
	int m_xcoord;
	int m_ycoord;
};
class Water : public inanimate {
public:
	Water(int startX, int startY, StudentWorld* startworld);
	virtual ~Water();
	virtual bool isWater();
	virtual void doSomething();
private:
	int m_xcoord;
	int m_ycoord;
};
class BabyGrasshopper : public animate {
public:
	BabyGrasshopper(int startX, int startY, StudentWorld* startworld, int IMAGEID);
	virtual ~BabyGrasshopper();
	virtual bool isBabyGrasshopper();
	int checkMoveNumber();
	void editMoveNumber(int changed);
	virtual void doSomething();
	int checkDistance();
	void editDistance(int newDistance);
	virtual void moveitmoveit(GraphObject::Direction dir);
	bool stunbencher();
	bool distancebencher();
	bool sleepbencher();
	bool eatbencher();
private:
	int m_movenumber;
	int m_distance;
	bool m_alreadymoved;
};

class AdultGrasshopper : public BabyGrasshopper {
public:
	AdultGrasshopper(int startX, int startY, StudentWorld* startworld, int turner);
	virtual ~AdultGrasshopper();
	virtual bool isAdultGrasshopper();
	virtual bool isBabyGrasshopper();
	virtual void doSomething();
	//virtual void moveitmoveit(GraphObject::Direction dir);
	bool babydoSomething();
	void reset();
	bool bitebencher();
	bool jumpbencher();
	bool openspot(int xcoord, int ycoord);
private:
	bool m_canjump;
};

class Pheromone : public inanimate {
public:
	Pheromone(int startX, int startY, StudentWorld* startworld, int IMAGEID, int colony, int turner);
	virtual ~Pheromone();
	virtual bool isPheromone();
	virtual void doSomething();
private:
};

class Ant : public BabyGrasshopper {
public:
	Ant(int startX, int startY, StudentWorld* startworld, int IMAGEID, Compiler* instructions, int turnnumber);
	virtual ~Ant();
	virtual bool isAnt();
	bool babydoSomething();
	bool moveitbutreturnbool(GraphObject::Direction dir);
	bool ifstatementsareannoying(Compiler::Command& cmd);
	virtual void doSomething();
private:
	Compiler *m_compiler;
	int m_instructioncounter;
	std::string m_nextinstruction;
	int m_nextinstructionnumber;	//temporary
	bool m_moved;	//determines whether ant moved (true) or got blocked (false)
	bool m_biten;	//records whether ant was biten there

	bool m_ifwastrue;
	int m_ic;
	int m_randomgenerated;

};

class Anthill : public animate {
public:
	Anthill(int startX, int startY, StudentWorld* startworld, int ID, Compiler *comppointer);
	virtual ~Anthill();
	virtual bool isAnthill();
	void doSomething();
private:
	Compiler *m_compiler;
};
#endif // ACTOR_H_
