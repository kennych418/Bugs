#include "StudentWorld.h"
#include <string>
#include "Field.h" // you must include this file to use our Field class
#include "Actor.h"
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}
StudentWorld::StudentWorld(string assetDir)
	: GameWorld(assetDir)
{
	m_numberticks = 2000;
	m_antscolony0 = 0;
	m_antscolony1 = 0;
	m_antscolony2 = 0;
	m_antscolony3 = 0;
}
StudentWorld::~StudentWorld() {
	cleanUp();
}
/////////////////////////////////////////////////////////////////////////////////////
bool StudentWorld::loadingField()
{
	Field f;
	string fieldFile = getFieldFilename();

	if (f.loadField(fieldFile) != Field::LoadResult::load_success)
		return false; // something bad happened!

	vector<string> fileNames = getFilenamesOfAntPrograms();

	std::string error;

	for (unsigned int k = 0; k < fileNames.size(); k++) {
		m_compinitarray[k] = new Compiler;
		if (m_compinitarray[k]->compile(fileNames[k], error)) {
			m_colonyNamesHolder[k] = m_compinitarray[k]->getColonyName();
		}
		else {
			setError(fileNames[0] + " " + error);
			return GWSTATUS_LEVEL_ERROR;
		}
	}

	/*Compiler* m_array[4];

	// get the names of all of the ant program source files we provide the getFilenamesOfAntPrograms() function for you in our GameWorld class. 
	vector<string> fileNames = getFilenamesOfAntPrograms();

	string error;
	for (unsigned int k = 0; k < fileNames.size(); k++) {
		m_array[k] = new Compiler;
		if (m_array[k]->compile(fileNames[k], error)) {
			m_colonyNames[k] = m_array[k]->getColonyName();
		}
	}*/

	////////////////


	for (int i = 0; i < VIEW_HEIGHT; i++) {
		for (int j = 0; j < VIEW_WIDTH; j++) {
			Field::FieldItem item = f.getContentsOf(j, i); // note it’s x,y and not y,x!!!
			switch (item) {
			case (Field::FieldItem::rock): {
				Actor* temp = new Pebble(j, i, this);
				m_virtualfield[j][i].push_back(temp);
				break; }
			case (Field::FieldItem::grasshopper): {
				/*Actor* temp = new AdultGrasshopper(j, i, this, m_numberticks);
				m_virtualfield[j][i].push_back(temp);
				break; }*/
				Actor* temp = new BabyGrasshopper(j, i, this, IID_BABY_GRASSHOPPER);
				m_virtualfield[j][i].push_back(temp);
				break; }
			case (Field::FieldItem::poison): {
				Actor* temp = new Poison(j, i, this);
				m_virtualfield[j][i].push_back(temp);
				break; }
			case (Field::FieldItem::food): {
				Actor* temp = new Food(j, i, this);
				m_virtualfield[j][i].push_back(temp);
				break; }
			case (Field::FieldItem::water): {
				Actor* temp = new Water(j, i, this);
				m_virtualfield[j][i].push_back(temp);
				break; }
			case(Field::FieldItem::anthill0): {
				Actor* temp = new Anthill(j, i, this, 0, m_compinitarray[0]);
				m_virtualfield[j][i].push_back(temp);
				break; }
			case(Field::FieldItem::anthill1): {
				Actor* temp = new Anthill(j, i, this, 1, m_compinitarray[1]);
				m_virtualfield[j][i].push_back(temp);
				break; }
			case(Field::FieldItem::anthill2): {
				Actor* temp = new Anthill(j, i, this, 2, m_compinitarray[2]);
				m_virtualfield[j][i].push_back(temp);
				break; }
			case(Field::FieldItem::anthill3): {
				Actor* temp = new Anthill(j, i, this, 3, m_compinitarray[3]);
				m_virtualfield[j][i].push_back(temp);
				break; }
			default: {
				m_virtualfield[j][i].push_back(nullptr);
				break; }
			}
		}
		
	}
	return true;
}
bool StudentWorld::getPassability(int posX, int posY) {
	bool temp = true;
	for(int i = 0; i < m_virtualfield[posX][posY].size(); i++){
		Actor* it = m_virtualfield[posX][posY][i];
		if (it != nullptr) {
			temp = (it)->checkpassable();
		}
	}
	return temp;
}
void StudentWorld::setDisplayText(string& output, int& winnernum) {
	string stringtoreturn;
	
	int ticks = m_numberticks;
	int numAnts0, numAnts1, numAnts2, numAnts3;
	int winnernumber;

	numAnts0 = m_antscolony0;
	numAnts1 = m_antscolony1;
	numAnts2 = m_antscolony2;
	numAnts3 = m_antscolony3;
	
	if (numAnts0 > numAnts1 && numAnts0 > numAnts2 && numAnts0 > numAnts3)
		winnernumber = 0;
	if (numAnts1 > numAnts2 && numAnts1 > numAnts3 && numAnts1 > numAnts0)
		winnernumber = 1;
	if (numAnts2 > numAnts0 && numAnts2 > numAnts1 && numAnts2 > numAnts3)
		winnernumber = 2;
	if (numAnts3 > numAnts0 && numAnts3 > numAnts1 && numAnts3 > numAnts2)
		winnernumber = 3;
	else
		winnernumber = 4;	//no winner
	
	string snum0 = to_string(numAnts0);
	string snum1 = to_string(numAnts1);
	string snum2 = to_string(numAnts2);
	string snum3 = to_string(numAnts3);
	string sticks = to_string(ticks);

	string tickpart;
	if (m_numberticks < 1000)
		tickpart = "Ticks:  " + sticks;
	else if (m_numberticks < 100)
		tickpart = "Ticks:   " + sticks;
	else if (m_numberticks < 10)
		tickpart = "Ticks:    " + sticks;
	else
		tickpart = "Ticks: " + sticks;
	string dividerpart = " - ";
	
	string part0;
	string part1;
	string part2;
	string part3;

	if (winnernumber == 0) {
		part0 = m_colonyNamesHolder[0] + "*: ";
		part1 = m_colonyNamesHolder[1] + ": ";
		part2 = m_colonyNamesHolder[2] + ": ";
		part3 = m_colonyNamesHolder[3] + ": ";
	}
	if (winnernumber == 1) {
		part0 = m_colonyNamesHolder[0] + ": ";
		part1 = m_colonyNamesHolder[1] + "*: ";
		part2 = m_colonyNamesHolder[2] + ": ";
		part3 = m_colonyNamesHolder[3] + ": ";
	}
	if (winnernumber == 2) {
		part0 = m_colonyNamesHolder[0] + ": ";
		part1 = m_colonyNamesHolder[1] + ": ";
		part2 = m_colonyNamesHolder[2] + "*: ";
		part3 = m_colonyNamesHolder[3] + ": ";
	}
	if (winnernumber == 3) {
		part0 = m_colonyNamesHolder[0] + ": ";
		part1 = m_colonyNamesHolder[1] + ": ";
		part2 = m_colonyNamesHolder[2] + ": ";
		part3 = m_colonyNamesHolder[3] + "*: ";
	}
	else {
		part0 = m_colonyNamesHolder[0] + ": ";
		part1 = m_colonyNamesHolder[1] + ": ";
		part2 = m_colonyNamesHolder[2] + ": ";
		part3 = m_colonyNamesHolder[3] + ": ";
	}
	string antspart = " ants";

		tickpart += dividerpart;
		tickpart += part0;
		if(m_antscolony0 < 10)
			tickpart += "0" + snum0 + antspart;
		else
			tickpart += snum0;
		tickpart += "  ";
		tickpart += part1;
		if (m_antscolony1 < 10)
			tickpart += "0" + snum1 + antspart;
		else
			tickpart += snum1;
		tickpart += "  ";
		tickpart += part2;
		if (m_antscolony2 < 10)
			tickpart += "0" + snum2 + antspart;
		else
			tickpart += snum2;
		tickpart += "  ";
		tickpart += part3;
		if (m_antscolony3 < 10)
			tickpart += "0" + snum3 + antspart;
		else
			tickpart += snum3;
		tickpart += "";
	
	output = tickpart;
	winnernum = winnernumber;
}
//////////////////////////////////////////////////////////////////////
void StudentWorld::poisonAll(int posX, int posY) {
	for (int i = 0; i < m_virtualfield[posX][posY].size(); i++) {
		if(m_virtualfield[posX][posY][i] != nullptr && m_virtualfield[posX][posY][i]->isBabyGrasshopper() && !m_virtualfield[posX][posY][i]->isDead())
		m_virtualfield[posX][posY][i]->getDamage(150);
	}
}
void StudentWorld::feedAll(int posX, int posY) {
	for (int i = 0; i < m_virtualfield[posX][posY].size(); i++) {
		if (m_virtualfield[posX][posY][i] != nullptr && m_virtualfield[posX][posY][i]->isBabyGrasshopper())
		m_virtualfield[posX][posY][i]->setHealth(m_virtualfield[posX][posY][i]->currentHealth() + 200);
	}	//unused
}
void StudentWorld::areYouWaterBecauseYoureStunningAll(int posX, int posY) {
	for (int i = 0; i < m_virtualfield[posX][posY].size(); i++) {
		if (m_virtualfield[posX][posY][i] != nullptr && m_virtualfield[posX][posY][i]->isBabyGrasshopper() && !m_virtualfield[posX][posY][i]->isDead())
		m_virtualfield[posX][posY][i]->editFirst(true);
	}
}
void StudentWorld::moveSomeShit(Actor* q, int OldX, int OldY, int NewX, int NewY) {
	m_virtualfield[NewX][NewY].push_back(q);
	m_virtualfield[OldX][OldY].pop_back();
}
bool StudentWorld::checkforenemies(int posX, int posY, Actor *checker) {
	for (int k = 0; k < m_virtualfield[posX][posY].size(); k++)
		if (m_virtualfield[posX][posY][k] != nullptr && m_virtualfield[posX][posY][k]->isAdultGrasshopper() || m_virtualfield[posX][posY][k]->isBabyGrasshopper() || (m_virtualfield[posX][posY][k]->isAnt() && m_virtualfield[posX][posY][k]->checkcolony() != checker->checkcolony()))
			return true;	//found an enemy (true)
	return false;	//did not find an enemy (false)
}
bool StudentWorld::checkforfood(int posX, int posY) {
	for (int k = 0; k < m_virtualfield[posX][posY].size(); k++)
		if (m_virtualfield[posX][posY][k] != nullptr && m_virtualfield[posX][posY][k]->isFood())
			return true;	//found food (true)
	return false;	//did not find food (false)
}
bool StudentWorld::checkforanthill(int posX, int posY, Actor *checker) {
	for (int k = 0; k < m_virtualfield[posX][posY].size(); k++)
		if (m_virtualfield[posX][posY][k] != nullptr && m_virtualfield[posX][posY][k]->isAnthill() && checker->checkcolony() == m_virtualfield[posX][posY][k]->checkcolony())
			return true;	//found anthill (true)
	return false;	//did not find anthill (false)
}
bool StudentWorld::checkforpheromones(int posX, int posY, Actor *checker) {
	for (int k = 0; k < m_virtualfield[posX][posY].size(); k++)
		if (m_virtualfield[posX][posY][k] != nullptr && m_virtualfield[posX][posY][k]->isPheromone() && checker->checkcolony() == m_virtualfield[posX][posY][k]->checkcolony() && !m_virtualfield[posX][posY][k]->isDead())
			return true;	//found food (true)
	return false;	//did not find food (false)
}
bool StudentWorld::checkfordanger(int posX, int posY, Actor *checker) {
	for (int k = 0; k < m_virtualfield[posX][posY].size(); k++)
		if (m_virtualfield[posX][posY][k] != nullptr && m_virtualfield[posX][posY][k]->isAdultGrasshopper() || m_virtualfield[posX][posY][k]->isBabyGrasshopper() || (m_virtualfield[posX][posY][k]->isAnt() && m_virtualfield[posX][posY][k]->checkcolony() != checker->checkcolony()) || m_virtualfield[posX][posY][k]->isPoison() || m_virtualfield[posX][posY][k]->isWater())
			return true;	//found an enemy (true)
	return false;	//did not find an enemy (false)
}

void StudentWorld::grasshopperbite(int posX, int posY, Actor* biter) {
	for (int k = 0; k < m_virtualfield[posX][posY].size(); k++) {
		if (m_virtualfield[posX][posY][k]!=nullptr && (m_virtualfield[posX][posY][k]->isBabyGrasshopper() || m_virtualfield[posX][posY][k]->isAnt()) && biter->checkbitten()== false) {
			m_virtualfield[posX][posY][k]->setHealth(m_virtualfield[posX][posY][k]->currentHealth() - 50);
			biter->editbitten(true);
		}
	}
}
void StudentWorld::antbite(int posX, int posY, Actor* biter) {
	for (int k = 0; k < m_virtualfield[posX][posY].size(); k++) {	//add statement that cant bite ants of the same colony
		if (m_virtualfield[posX][posY][k] != nullptr && (m_virtualfield[posX][posY][k]->isBabyGrasshopper() || (m_virtualfield[posX][posY][k]->isAnt()) && m_virtualfield[posX][posY][k]->getID()!= biter->getID()) && biter->checkbitten() == false) {
			m_virtualfield[posX][posY][k]->setHealth(m_virtualfield[posX][posY][k]->currentHealth() - 50);
			biter->editbitten(true);
		}
	}
}
bool StudentWorld::attempteat(int posX, int posY, Actor* eater, int amount) {
	for (int k = 0; k < m_virtualfield[posX][posY].size(); k++) {
		if (m_virtualfield[posX][posY][k] != nullptr && m_virtualfield[posX][posY][k]->isFood()) {
			if (m_virtualfield[posX][posY][k]->currentHealth() >= amount) {
				m_virtualfield[posX][posY][k]->setHealth(m_virtualfield[posX][posY][k]->currentHealth() - amount);
				eater->setHealth(eater->currentHealth() + amount);
			}
			else if (m_virtualfield[posX][posY][k]->currentHealth() < amount && m_virtualfield[posX][posY][k]->currentHealth() > 0) {
				eater->setHealth(eater->currentHealth() + m_virtualfield[posX][posY][k]->currentHealth());
				m_virtualfield[posX][posY][k]->setHealth(0);
			}
			return true;	//true == did eat
		}
		return false;		//false == didnt eat
	}
}
bool StudentWorld::pickupfood(int posX, int posY, Actor* pickerupper, int amount) {
		for (int k = 0; k < m_virtualfield[posX][posY].size(); k++) {
			if (pickerupper->checkcarrying() + amount > 1800)
				amount = 1800 - pickerupper->checkcarrying();
			if (m_virtualfield[posX][posY][k] != nullptr && m_virtualfield[posX][posY][k]->isFood()) {
				if (m_virtualfield[posX][posY][k]->currentHealth() >= amount) {
					m_virtualfield[posX][posY][k]->setHealth(m_virtualfield[posX][posY][k]->currentHealth() - amount);
					pickerupper->editcarrying(pickerupper->checkcarrying() + amount);
				}
				else if (m_virtualfield[posX][posY][k]->currentHealth() < amount && m_virtualfield[posX][posY][k]->currentHealth() > 0) {
					pickerupper->editcarrying(pickerupper->checkcarrying() + m_virtualfield[posX][posY][k]->currentHealth());
					m_virtualfield[posX][posY][k]->setHealth(0);
				}
				return true;	//true == did eat
			}
			return false;		//false == didnt eat
		}
}

void StudentWorld::createFood(int posX, int posY, int amount) {
	for (int k = 0; k < m_virtualfield[posX][posY].size(); k++) {
		if (m_virtualfield[posX][posY][k]->isFood()) {
			m_virtualfield[posX][posY][k]->setHealth(m_virtualfield[posX][posY][k]->currentHealth() + amount);
			return;
		}
	}
	m_virtualfield[posX][posY].push_back(new Food(posX, posY, this));
}
void StudentWorld::makePheromoneStrongerDaddy(int posX, int posY, Actor* squirter) {
	for (int k = 0; k < m_virtualfield[posX][posY].size(); k++) {
		if (m_virtualfield[posX][posY][k]->isPheromone() && m_virtualfield[posX][posY][k]->checkcolony()==squirter->checkcolony() && m_virtualfield[posX][posY][k]->currentHealth() + 256 <= 768) {
			m_virtualfield[posX][posY][k]->setHealth(m_virtualfield[posX][posY][k]->currentHealth() + 256);
			return;
		}
		else if (m_virtualfield[posX][posY][k]->isPheromone() && m_virtualfield[posX][posY][k]->checkcolony() == squirter->checkcolony()){
			int newamount = 768 - m_virtualfield[posX][posY][k]->currentHealth();
			m_virtualfield[posX][posY][k]->setHealth(m_virtualfield[posX][posY][k]->currentHealth() + newamount);
			return;
		}
	}
	int colonynum;
	switch (squirter->checkcolony()) {
	case 0:
		colonynum = IID_PHEROMONE_TYPE0;
		break;
	case 1:
		colonynum = IID_PHEROMONE_TYPE1;
		break;
	case 2:
		colonynum = IID_PHEROMONE_TYPE2;
		break;
	case 3:
		colonynum = IID_PHEROMONE_TYPE3;
		break;
	}
	Actor *tempasfuck = new Pheromone(posX, posY, this, colonynum, squirter->checkcolony(), m_numberticks-1);
	m_virtualfield[posX][posY].push_back(tempasfuck);
}

void StudentWorld::increase0() {
	m_antscolony0++;
}
void StudentWorld::increase1() {
	m_antscolony1++;
}
void StudentWorld::increase2() {
	m_antscolony2++;
}
void StudentWorld::increase3() {
	m_antscolony3++;
}

void StudentWorld::createNewAnt(int posX, int posY, int id) {
	if (id == 0)
		m_virtualfield[posX][posY].push_back(new Ant(posX, posY, this, IID_ANT_TYPE0, m_compinitarray[0], m_numberticks -10));
	if (id == 1)
		m_virtualfield[posX][posY].push_back(new Ant(posX, posY, this, IID_ANT_TYPE1, m_compinitarray[1], m_numberticks - 10));
	if (id == 2)
		m_virtualfield[posX][posY].push_back(new Ant(posX, posY, this, IID_ANT_TYPE2, m_compinitarray[2], m_numberticks - 10));
	if (id == 3)
		m_virtualfield[posX][posY].push_back(new Ant(posX, posY, this, IID_ANT_TYPE3, m_compinitarray[3], m_numberticks - 10));
}
///////////////////////////////////////////////////////////////////////////

int StudentWorld::init()
{
	loadingField();
	return GWSTATUS_CONTINUE_GAME;
}
int StudentWorld::move()
{
	
	for(int i = 0; i < VIEW_HEIGHT; i++) {
		for (int j = 0; j < VIEW_WIDTH; j++) {
			for (int k = 0; k < m_virtualfield[j][i].size(); k++) {
				Actor* it = m_virtualfield[j][i][k];
				if (it != nullptr && it->checkturnnumber() == m_numberticks) {
					int Xer = (it)->getX(); int Yer = (it)->getY();
					(it)->doSomething();
					(it)->editturnnumber(it->checkturnnumber() - 1);
					int NewXer = (it)->getX(); int NewYer = (it)->getY();
					moveSomeShit(it, Xer,Yer,NewXer,NewYer);
				}
			}
			/*vector<Actor*>::iterator it = m_virtualfield[j][i].begin();
			while(it != m_virtualfield[j][i].end()) {
				if ((*it) != nullptr) {
					if ((*it)->isDead()) {
						m_virtualfield[j][i].erase(it);
					}
				}
			}*/
		}
	}
	
	for (int i = 0; i < VIEW_HEIGHT; i++) {
		for (int j = 0; j < VIEW_WIDTH; j++) {
			for (int k = 0; k < m_virtualfield[j][i].size(); k++) {
				Actor* it = m_virtualfield[j][i][k];
				if (it != nullptr && it->isBabyGrasshopper() && it->isDead() && !it->checkfood()) {
					it->editfood(true);
					Actor* temp = new Food(j, i, this);
					m_virtualfield[j][i].push_back(temp);
					break;
				}
				if (it != nullptr && it->isBabyGrasshopper() && !it->isDead() && it->currentHealth() >= 1600 && !it->checkfood()) {
					it->editfood(true);
					it->setDeadorAlive(false);
					//std::cout << "Evolve";
					Actor* temp = new AdultGrasshopper(j, i, this, m_numberticks-1);
					m_virtualfield[j][i].push_back(temp);
					break;
				}
				/*if (it != nullptr && it->isDead()) {

				}*/
				//empty
			}
		}
	}
	for (int i = 0; i < VIEW_HEIGHT; i++) {
		for (int j = 0; j < VIEW_WIDTH; j++) {
			//std::cout << "1" << std::endl;
			bool checker = false;
			vector<Actor*>::iterator it = m_virtualfield[j][i].begin();
			while (it != m_virtualfield[j][i].end()) {
				if ((*it) != nullptr) {
					if ((*it)->isDead()) {
						Actor *temp = (*it);
						//delete temp;
						it = m_virtualfield[j][i].erase(it);
						//(*it) = nullptr;
						checker = true;
					}
				}
				if (checker == true) {
					//cout << "Deleted one";
					break;
				} else
					it++;
			}
		}
	}

		
	string s;
	int w;
	setDisplayText(s, w);
	setGameStatText(s);
	m_numberticks--;

	if (m_numberticks == 0 && w == 0) {
		setWinner(m_colonyNamesHolder[0]);
		return GWSTATUS_PLAYER_WON;
	}
	if (m_numberticks == 0 && w == 1) {
		setWinner(m_colonyNamesHolder[1]);
		return GWSTATUS_PLAYER_WON;
	}
	if (m_numberticks == 0 && w == 2) {
		setWinner(m_colonyNamesHolder[2]);
		return GWSTATUS_PLAYER_WON;
	}
	if (m_numberticks == 0 && w == 3) {
		setWinner(m_colonyNamesHolder[3]);
		return GWSTATUS_PLAYER_WON;
	}
	if (m_numberticks == 0 && w == 4) {
		return GWSTATUS_NO_WINNER;
	}
	return 0;
}
void StudentWorld::cleanUp()
{
	for (int i = 0; i < VIEW_HEIGHT; i++) {
		for (int j = 0; j < VIEW_WIDTH; j++) {
			int sizer = m_virtualfield[j][i].size();
			int counter = 0;
			while (counter < sizer) {
				m_virtualfield[j][i].pop_back();
				counter++;
			}
			
			/*for(int k=0; k < m_virtualfield[j][i].size(); k++){
			Actor* it = m_virtualfield[j][i][k];
			delete it;*/
		}	
		
	}
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
