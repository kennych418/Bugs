#include "GraphObject.h"
#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(int imageID, int startX, int startY, StudentWorld* world, Direction dir, int depth, double size)
	:GraphObject(imageID, startX, startY, dir, depth, size)
{
	m_passable = true;
	m_aliver = true;
	m_health = 9999;
	m_world = world;
	m_firstchecker = false;
	m_secondchecker = false;
	m_madefood = false;
	m_turnnumber = 2000;
	m_bitten = false;
	m_heldfood = 0;
	m_colony = 5;
}
Actor::~Actor() {

}

bool Actor::isWater() {
	return false;
}
bool Actor::isPoison() {
	return false;
}
bool Actor::isFood() {
	return false;
}
bool Actor::isBabyGrasshopper() {
	return false;
}
bool Actor::isAdultGrasshopper() {
	return false;
}
bool Actor::isPheromone() {
	return false;
}
bool Actor::isAnt() {
	return false;
}
bool Actor::isAnthill() {
	return false;
}

void Actor::setHealth(int health) {
	m_health = health;
}
int Actor::currentHealth() {
	return m_health;
}
bool Actor::isDead() {
	if (m_aliver == false)
		return true;
	return false;
}
void Actor::setDeadorAlive(bool status) {
	m_aliver = status;
}
GraphObject::Direction Actor::randDirection()
{
	int face = randInt(0, 3); //create a number 0-3
							  //choose direction based on number
	switch (face) {
	case 0:
		return right;
		break;
	case 1:
		return left;
		break;
	case 2:
		return up;
		break;
	case 3:
		return down;
		break;
	default:
		break;
	}
}
bool Actor::checkpassable() {
	return m_passable;
}
void Actor::editpassable(bool newPassable) {
	m_passable = newPassable;
}
StudentWorld* Actor::returnWorld() {
	return m_world;
}
bool Actor::checkFirst() {
	return m_firstchecker;
}
bool Actor::checkSecond() {
	return m_secondchecker;
}
void Actor::editFirst(bool changer) {
	m_firstchecker = changer;
}
void Actor::editSecond(bool changer) {
	m_secondchecker = changer;
}
bool Actor::checkfood() {
	return m_madefood;
}
void Actor::editfood(bool change) {
	m_madefood = change;
}
int Actor::checkturnnumber() {
	return m_turnnumber;
}
void Actor::editturnnumber(int changer) {
	m_turnnumber = changer;
}
void Actor::editbitten(bool changer) {
	m_bitten = changer;
}
bool Actor::checkbitten() {
	return m_bitten;
}
void Actor::editcarrying(int pickedup) {
	m_heldfood = pickedup;
}
int Actor::checkcarrying() {
	return m_heldfood;
}
int Actor::checkcolony() {
	return m_colony;
}
void Actor::editcolony(int changer) {
	m_colony = changer;
}
//////////////////////////////////////////////////////////////////////////////////////////////////

inanimate::inanimate(int imageID, int startX, int startY, StudentWorld* world, Direction dir, int depth, double size)
	:Actor(imageID, startX, startY, world, dir, depth, 0.25)
{

}
inanimate::~inanimate() {

}
void inanimate::getDamage(int damage) {
	return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

animate::animate(int imageID, int startX, int startY, StudentWorld* world, Direction dir, int depth, double size)
	:Actor(imageID, startX, startY, world, dir, depth, 0.25)
{

}
animate::~animate() {

}
void animate::getDamage(int damage) {
	setHealth(currentHealth() - damage);
}
//////////////////////////////////////////////////////////////////////////////////////////////////

Pebble::Pebble(int startX, int startY, StudentWorld* startworld)
	:inanimate(IID_ROCK,startX,startY,startworld, right, 1, 0.25)
{
	editpassable(false);
}
Pebble::~Pebble() {

}
void Pebble::doSomething() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////

BabyGrasshopper::BabyGrasshopper(int startX, int startY, StudentWorld* startworld, int IMAGEID)
	:animate(IMAGEID,startX,startY,startworld,randDirection(),1,0.25)
{
	setHealth(500);
	editMoveNumber(0);
	editDistance(randInt(2,10));
	editpassable(true);
}
BabyGrasshopper::~BabyGrasshopper() {

}
bool BabyGrasshopper::isBabyGrasshopper() {
	return true;
}
int BabyGrasshopper::checkMoveNumber() {
	return m_movenumber;
}
void BabyGrasshopper::editMoveNumber(int changed) {
	m_movenumber = changed;
}
int BabyGrasshopper::checkDistance() {
	return m_distance;
}
void BabyGrasshopper::editDistance(int newDistance) {
	m_distance = newDistance;
}

void BabyGrasshopper::moveitmoveit(GraphObject::Direction dir) {
	if (dir == left) {
		if (returnWorld()->getPassability(getX() - 1, getY())) {
			moveTo(getX() - 1, getY());
			return;
		}
		editDistance(0);	//Bumped into a pebble and needs to change direction
		//std::cout << "Bumped into pebble" << std::endl;
	}
	if (dir == right) {
		if (returnWorld()->getPassability(getX() + 1, getY())) {
			moveTo(getX() + 1, getY());
			return;
		}
		editDistance(0);	//Bumped into a pebble and needs to change direction
		//std::cout << "Bumped into pebble" << std::endl;
	}
	if (dir == up) {
		if (returnWorld()->getPassability(getX(), getY() + 1)) {
			moveTo(getX(), getY() + 1);
			return;
		}
		editDistance(0);	//Bumped into a pebble and needs to change direction
		//std::cout << "Bumped into pebble" << std::endl;
	}
	if (dir == down) {
		if (returnWorld()->getPassability(getX(), getY() - 1)) {
			moveTo(getX(), getY() - 1);
			return;
		}
		editDistance(0);	//Bumped into a pebble and needs to change direction
		//std::cout << "Bumped into pebble" << std::endl;
	}
}
bool BabyGrasshopper::stunbencher() {
	if (checkFirst() == true && checkSecond() == false) {
		editFirst(false);
		editSecond(true);
		return true;
	}
	if (checkFirst() == true && checkSecond() == true) {
		editFirst(false);
		editSecond(false);
		return false;
	}
	return false;
}
bool BabyGrasshopper::distancebencher() {
	if (checkDistance() <= 0) {
		setDirection(randDirection());
		editDistance(randInt(2, 10));
		return true;
	}
	editDistance(checkDistance() - 1);
	return false;
}
bool BabyGrasshopper::sleepbencher() {
	if (checkMoveNumber() < 2) {
		editMoveNumber(checkMoveNumber() + 1);
		return true;
	}
	if (checkMoveNumber() >= 2) {
		editMoveNumber(0);
		return false;
	}
}
bool BabyGrasshopper::eatbencher() {
	bool checker = returnWorld()->attempteat(getX(), getY(), this, 200);
	if (checker) {
		//std::cout << "Ate" << std::endl;
		int tosleepornottosleep = randInt(1, 2);
		if (tosleepornottosleep == 1)
			return true;
	}
	return false;
}

void BabyGrasshopper::doSomething() {
	setHealth(currentHealth() - 1);
	if (currentHealth() <= 0) {
		setDeadorAlive(false);
		return;
	}
	if (isDead())
		return;
	if (sleepbencher())
		return;
	if (stunbencher())
		return;
	if (eatbencher())
		return;
	if (distancebencher())
		return;
	moveitmoveit(getDirection());
}

/////////////////////////////////////////////////////////////////////////////////////////////

Poison::Poison(int startX, int startY, StudentWorld* startworld) 
	:inanimate(IID_POISON, startX, startY, startworld, right, 2, 0.25)
{
	m_xcoord = startX;
	m_ycoord = startY;
}
Poison::~Poison() {

}
bool Poison::isPoison() {
	return true;
}
void Poison::doSomething() {
	returnWorld()->poisonAll(m_xcoord, m_ycoord);
}

///////////////////////////////////////////////////////////////////////////////////////////////

Food::Food(int startX, int startY, StudentWorld* startworld) 
	:animate(IID_FOOD, startX, startY, startworld, right, 2, 0.25)
{
	setHealth(6000);
	editpassable(true);
	//m_xcoord = startX;
	//m_ycoord = startY;
	//editturnnumber(turner-1);
}
Food::~Food() {

}
bool Food::isFood() {
	return true;
}
void Food::doSomething() {
	//returnWorld()->feedAll(m_xcoord, m_ycoord);
}
/*void Food::setHealth(int health) {

}*/

////////////////////////////////////////////////////////////////////////////////////////////////

Water::Water(int startX, int startY, StudentWorld* startworld)
	:inanimate(IID_WATER_POOL, startX, startY, startworld, right, 2, 0.25)
{
	editpassable(true);
	m_xcoord = startX;
	m_ycoord = startY;
}
Water::~Water() {

}
bool Water::isWater() {
	return true;
}
void Water::doSomething() {
	returnWorld()->areYouWaterBecauseYoureStunningAll(m_xcoord, m_ycoord);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

AdultGrasshopper::AdultGrasshopper(int startX, int startY, StudentWorld* startworld, int turner)
	:BabyGrasshopper(startX, startY, startworld, IID_ADULT_GRASSHOPPER)
{
	editturnnumber(turner);
	//std::cout << checkturnnumber();
	m_canjump = false;
}
AdultGrasshopper::~AdultGrasshopper() {

}
bool AdultGrasshopper::isAdultGrasshopper() {
	return true;
}
bool AdultGrasshopper::isBabyGrasshopper() {
	return false;
}
bool AdultGrasshopper::babydoSomething() {
	setHealth(currentHealth() - 1);
	if (currentHealth() <= 0) {
		setDeadorAlive(false);
		return false;
	}
	if (isDead())
		return false;
	if (sleepbencher())
		return false;
	if (stunbencher())
		return false;
	if (eatbencher())
		return false;
	/*if (distancebencher())	//DECREMENT DISTANCE IS STILL IN HERE
		return false;*/
	//std::cout << "Moved it" << std::endl;
	//moveitmoveit(getDirection());
	return true;
}
bool AdultGrasshopper::bitebencher() {
	int oneinthree = randInt(1, 3);
	if (oneinthree == 3) {
		returnWorld()->grasshopperbite(getX(), getY(), this);
		reset();
		//std::cout << "Tried biting" << std::endl;
		return true;
	}
	return false;
}
/*void AdultGrasshopper::moveitmoveit(GraphObject::Direction dir) {
	if (dir == left) {
		if (returnWorld()->getPassability(getX() - 1, getY())) {
			moveTo(getX() - 1, getY());
			return;
		}
		editDistance(0);	//Bumped into a pebble and needs to change direction
		std::cout << "Bumped into pebble" << std::endl;
	}
	if (dir == right) {
		if (returnWorld()->getPassability(getX() + 1, getY())) {
			moveTo(getX() + 1, getY());
			return;
		}
		editDistance(0);	//Bumped into a pebble and needs to change direction
		std::cout << "Bumped into pebble" << std::endl;
	}
	if (dir == up) {
		if (returnWorld()->getPassability(getX(), getY() + 1)) {
			moveTo(getX(), getY() + 1);
			return;
		}
		editDistance(0);	//Bumped into a pebble and needs to change direction
		std::cout << "Bumped into pebble" << std::endl;
	}
	if (dir == down) {
		if (returnWorld()->getPassability(getX(), getY() - 1)) {
			moveTo(getX(), getY() - 1);
			return;
		}
		editDistance(0);	//Bumped into a pebble and needs to change direction
		std::cout << "Bumped into pebble" << std::endl;
	}
}*/
bool AdultGrasshopper::jumpbencher() {
	int count = 0;
	int xcoord = 0;
	int ycoord = 0;
	int oneintenchance = randInt(1, 10);
	if (oneintenchance == 1) {
		while (m_canjump == false) {
			count++;
			double pi = 3.1415926535897;
			int radius = randInt(1, 10);
			int degree = randInt(0, 2 * pi);
			xcoord = radius*cos(degree) + getX();
			ycoord = radius*cos(degree) + getY();
			if (openspot(xcoord, ycoord)) {
				//std::cout << "Found a jump" << std::endl;
				break;
			}
			if (count >= 200)
				return false;
		}
		if (count < 200) {
			m_canjump = false;
			moveTo(xcoord, ycoord);
			//std::cout << "Jumped" << std::endl;
			return true; //return true == did jump
		}
	}
	return false;
}
bool AdultGrasshopper::openspot(int xcoord, int ycoord) {
	if ((xcoord >= VIEW_WIDTH - 1 || xcoord <= 0) || (ycoord >= VIEW_HEIGHT - 1 || ycoord <= 0)) {
		m_canjump = false;
		return false;
	}
	if (!(returnWorld()->getPassability(getX(), getY()))) {
		m_canjump = false;
		return false;
	}
	m_canjump = true;
	return true;
}
void AdultGrasshopper::doSomething() {
	if (!babydoSomething())	//check if it even can do a move
		return;
	if (bitebencher())	//decide whether or not to bite
		return;
	if (jumpbencher())	//decide whether to jump
		return;
	if (distancebencher())	//if not, check whether it can even move in that direction
		return;
	moveitmoveit(getDirection());	//move it move it
}
void AdultGrasshopper::reset() {
	editbitten(false);
}
//////////////////////////////////////////////////////////////////////////////////////////

Pheromone::Pheromone(int startX, int startY, StudentWorld* startworld, int IMAGEID, int colony, int turner)
	:inanimate(IMAGEID, startX,startY,startworld,right,2,0.25)
{
	editcolony(colony);
	editturnnumber(turner);
	setHealth(256);
}
Pheromone::~Pheromone() {

}
bool Pheromone::isPheromone() {
	return true;
}
void Pheromone::doSomething() {
	
	if (currentHealth() <= 0)
		setDeadorAlive(false);
	setHealth(currentHealth() - 1);
}

///////////////////////////////////////////////////////////////////////////////////////////

Ant::Ant(int startX, int startY, StudentWorld* startworld, int IMAGEID, Compiler* instructions, int turnnumber)
	:BabyGrasshopper(startX,startY,startworld, IMAGEID)
{
	m_ic = 0;
	editturnnumber(turnnumber);
	m_compiler = instructions;
	switch (IMAGEID){
	case IID_ANT_TYPE0: {
		editcolony(0);
		break;
	}
	case IID_ANT_TYPE1: {
		editcolony(1);
		break;
	}
	case IID_ANT_TYPE2: {
		editcolony(2);
		break;
	}
	case IID_ANT_TYPE3: {
		editcolony(3);
		break;
	}
	default:
		break;
	}
	setHealth(1500);
	editcarrying(0);
	//m_nextinstruction = "";
	m_biten = false;
}
Ant::~Ant() {

}
bool Ant::isAnt() {
	return true;
}

bool Ant::babydoSomething() {
	setHealth(currentHealth() - 1);
	if (currentHealth() <= 0) {
		setDeadorAlive(false);
		return false;
	}
	if (isDead())
		return false;
	if (stunbencher())
		return false;
	/*if (distancebencher())	//DECREMENT DISTANCE IS STILL IN HERE
	return false;*/
	//std::cout << "Moved it" << std::endl;
	//moveitmoveit(getDirection());
	return true;
}
bool Ant::moveitbutreturnbool(GraphObject::Direction dir) {
	if (dir == left) {
		if (returnWorld()->getPassability(getX() - 1, getY())) {
			moveTo(getX() - 1, getY());
			return true;
		}
		editDistance(0);	//Bumped into a pebble and needs to change direction
		return false;		//std::cout << "Bumped into pebble" << std::endl;
	}
	if (dir == right) {
		if (returnWorld()->getPassability(getX() + 1, getY())) {
			moveTo(getX() + 1, getY());
			return true;
		}
		editDistance(0);
		return false;		//Bumped into a pebble and needs to change direction
							//std::cout << "Bumped into pebble" << std::endl;
	}
	if (dir == up) {
		if (returnWorld()->getPassability(getX(), getY() + 1)) {
			moveTo(getX(), getY() + 1);
			return true;
		}
		editDistance(0);	//Bumped into a pebble and needs to change direction
		return false;		//std::cout << "Bumped into pebble" << std::endl;
	}
	if (dir == down) {
		if (returnWorld()->getPassability(getX(), getY() - 1)) {
			moveTo(getX(), getY() - 1);
			return true;
		}
		editDistance(0);	//Bumped into a pebble and needs to change direction
		return false;		//std::cout << "Bumped into pebble" << std::endl;
	}
}
void Ant::doSomething() {
	editturnnumber(checkturnnumber() - 1);
	if(!babydoSomething())
	return;

	Compiler::Command cmd;

	for (int k = 0; k < 10; k++) {
		if (!m_compiler->getCommand(0, cmd)) {
			setDeadorAlive(false);
			return;
		}

		m_compiler->getCommand(m_ic, cmd);
		m_ifwastrue = false;

		switch (cmd.opcode) {
		case Compiler::Opcode::moveForward: {	//moveForward
			if (moveitbutreturnbool(getDirection())) {
				m_moved = true;
				m_biten = false;
				//std::cout << checkcolony() << std::endl;
			}
			else
				m_moved = false;
			m_ic++;
			break;
		}
		case Compiler::Opcode::eatFood: {	//eatFood
			if (checkcarrying() <= 0) {
				m_ic++;
			}
			else if (checkcarrying() < 100) {
				setHealth(currentHealth() + checkcarrying());
				editcarrying(0);
				m_ic++;
			}
			else {
				setHealth(currentHealth() + 100);
				editcarrying(checkcarrying() - 100);
				m_ic++;
			}
			break;
		}
		case Compiler::Opcode::dropFood: {	//dropFood
			returnWorld()->createFood(getX(), getY(), checkcarrying());
			editcarrying(0);
			m_ic++;
			break;
		}
		case Compiler::Opcode::bite: {	//bite
			returnWorld()->antbite(getX(), getY(), this);
			m_ic++;
			break;
		}
		case Compiler::Opcode::pickupFood: {	//pickupFood
			returnWorld()->pickupfood(getX(), getY(), this, 400);
			m_ic++;
			break;
		}
		case Compiler::Opcode::emitPheromone: {	//emitPheromone
			returnWorld()->makePheromoneStrongerDaddy(getX(), getY(), this);
			m_ic++;
			break;
		}
		case Compiler::Opcode::faceRandomDirection: {	//faceRandomDirection
			int temp = randInt(0, 3);
			GraphObject::Direction newDirection;
			switch (temp) {
			case 0:
				newDirection = right;
				break;
			case 1:
				newDirection = left;
				break;
			case 2:
				newDirection = up;
				break;
			case 3:
				newDirection = down;
				break;
			default:
				break;
			}
			setDirection(newDirection);
			m_ic++;
			break;
		}
		case Compiler::Opcode::rotateClockwise: {	//rotateClockwise
			GraphObject::Direction oldDirection = getDirection();
			if (oldDirection == up)
				setDirection(right);
			if (oldDirection == right)
				setDirection(down);
			if (oldDirection == down)
				setDirection(left);
			if (oldDirection == left)
				setDirection(up);
			m_ic++;
			break;
		}
		case Compiler::Opcode::rotateCounterClockwise: {	//rotateCounterClockwise
			GraphObject::Direction oldDirection = getDirection();
			if (oldDirection == up)
				setDirection(left);
			if (oldDirection == left)
				setDirection(down);
			if (oldDirection == down)
				setDirection(right);
			if (oldDirection == right)
				setDirection(up);
			m_ic++;
			break;
		}
		case Compiler::Opcode::generateRandomNumber: {	//generateRandomNumber
			if (stoi(cmd.operand1) <= 0)
				m_randomgenerated = 0;
			m_randomgenerated = randInt(0, stoi(cmd.operand1) - 1);
			m_ic++;
			break;
		}
		case Compiler::Opcode::goto_command: {	//goto_command
			m_ic = stoi(cmd.operand1);		//change the later so that it works
			break;
		}
		case Compiler::Opcode::if_command: {	//if_command
			if (ifstatementsareannoying(cmd)) {
				m_ic = stoi(cmd.operand2);
				break;
			}
			m_ic++;
			break;
		}	//not incrementing
		}
	}
}
bool Ant::ifstatementsareannoying(Compiler::Command& cmd) {
	int newkey = stoi(cmd.operand1);
	switch (newkey) {
	case 9: {	//last_random_number_was_zero
		if (m_randomgenerated == 0) {
			return false;
		}
		return true;
		break;
	}
	case 3: {	//I_am_carrying_food
		if (checkcarrying() > 0) {
			return true;
		}
		return false;
		break;
	}
	case 4: { //I_am_hungry
		if (currentHealth() <= 25) {
			return true;
		}
		return false;
		break;
	}
	case 7: {	//I_am_standing_with_an_enemy
		if (returnWorld()->checkforenemies(getX(), getY(), this)) {
			return true;
		}
		return false;
		break;
	}
	case 6: {	//I_am_standing_on_food
		if (returnWorld()->checkforfood(getX(), getY())) {
			return true;
		}
		return false;
		break;
	}
	case 5: {	//I_am_standing_on_my_anthill
		if (returnWorld()->checkforanthill(getX(), getY(), this)) {
			return true;
		}
		return false;
		break;
	}
	case 1: {	//I_smell_pheromone_in_front_of_me
		if (getDirection() == up)
			if (returnWorld()->checkforpheromones(getX(), getY() - 1, this)) {
				return true;
			}
		if (getDirection() == right)
			if (returnWorld()->checkforpheromones(getX() + 1, getY(), this)) {
				return true;
			}
		if (getDirection() == down)
			if (returnWorld()->checkforpheromones(getX(), getY() + 1, this)) {
				return true;
			}
		if (getDirection() == left)
			if (returnWorld()->checkforpheromones(getX() - 1, getY(), this)) {
				return true;
			}
		return false;
		break;
	}
	case 0: {	//I_smell_danger_in_front_of_me
		if (getDirection() == up)
			if (returnWorld()->checkfordanger(getX(), getY() - 1, this)) {
				return true;
			}
		if (getDirection() == right)
			if (returnWorld()->checkfordanger(getX() + 1, getY(), this)) {
				return true;
			}
		if (getDirection() == down)
			if (returnWorld()->checkfordanger(getX(), getY() + 1, this)) {
				return true;
			}
		if (getDirection() == left)
			if (returnWorld()->checkfordanger(getX() - 1, getY(), this)) {
				return true;
			}
		return false;
		break;
	}
	case 2: {	//I_was_bit
		if (m_biten == true) {
			return true;
		}
		return false;
		break;
	}
	case 8: {	//I_was_blocked_from_moving
		if (m_moved == false) {
			return true;
		}
		return false;
		break;
	}
	default:
		return false;
		break;
	}
}
/*int Ant::AntID() {
	return m_id;
}*/

//////////////////////////////////////////////////////////////////////////////

Anthill::Anthill(int startX, int startY, StudentWorld* startworld, int ID, Compiler *comppointer) 
	:animate(IID_ANT_HILL,startX,startY,startworld,right,2,0.25)
{
	editcolony(ID);
	setHealth(8999);
	m_compiler;
}
Anthill::~Anthill() {

}
bool Anthill::isAnthill() {
	return true;
}
/*int Anthill::AnthillID() {
	return m_id;
}*/
void Anthill::doSomething() {
	setHealth(currentHealth() - 1);
	if (currentHealth() <= 0) {
		setDeadorAlive(false);
		return;
	}
	if (isDead())
		return;

	if (returnWorld()->attempteat(getX(), getY(), this, 10000))
		return;

	if (currentHealth() >= 2000) {
		//std::cout << "hiller";
		returnWorld()->createNewAnt(getX(), getY(), checkcolony());
		setHealth(currentHealth() - 1500);
		switch (checkcolony()) {
		case 0:
			returnWorld()->increase0();
			break;
		case 1:
			returnWorld()->increase1();
			break;
		case 2:
			returnWorld()->increase2();
			break;
		case 3:
			returnWorld()->increase3();
			break;
		default:
			break;
		}
		return;
	}

}
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
//check if can jump