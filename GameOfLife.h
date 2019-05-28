#pragma once
#include <iostream>
#include <vector>
//#include <set> set up rules with sets
#include <ctime>

using namespace std;

struct Position {
	int x, y;
};

struct Rules {
	vector<int> birth;
	vector<int> survive;
};

struct Shape {
	int x, y, w, h;
	char * form;
};

class GameOfLife {
public:
	GameOfLife() {};
	~GameOfLife() {};

	void initGameOfLife(int mwidth, int mheight, Rules rles);
	void fillMapRandomly();
	void nextGeneration();
	char getCellValue(int x, int y);
	char & getCellByRef(int x, int y);
	vector<char> getMap();
	const int getTotalSize();
	int indexFromCoord(int x, int y);
	void clearMap();
	unsigned int getGenerationNumber();
	Position coordFromIndex(int i);
	void setRules(Rules rles);
	void setRules(vector<int> birth, vector<int> survive);
	Rules getRules();

private:
	int width, height;
	unsigned int genNum = 0;
	vector<char> map;
	Rules rules;

	int icheckNeighbors(int i);
	int checkNeighbors(int x, int y);
};

// IMPLEMENTATIONS

inline void GameOfLife::initGameOfLife(int mwidth, int mheight, Rules rles) {
	this->map.clear();
	this->map.resize(mwidth * mheight);
	this->width = mwidth;
	this->height = mheight;
	srand(time(NULL));
	this->rules.birth.assign(rles.birth.begin(), rles.birth.end());
	this->rules.survive.assign(rles.survive.begin(), rles.survive.end());
}

inline void GameOfLife::fillMapRandomly() {
	int num;
	for (unsigned int i = 0; i < this->map.size(); i++) {
		num = rand() % 100;
		if (num > 65) this->map[i] = '1';
	}
}

inline void GameOfLife::nextGeneration() {
	vector<char> nextGen(this->height * this->width, '0');
	int livecount;
	for (unsigned int i = 0; i < this->map.size(); i++) {
		livecount = icheckNeighbors(i);
		if (this->map[i] == '1') {
			for (unsigned int j = 0; j < this->rules.survive.size(); j++) {
				if (this->rules.survive[j] == livecount) nextGen[i] = '1';
			}
		}
		else if (this->map[i] == '0') {
			for (unsigned int j = 0; j < this->rules.birth.size(); j++) {
				if (this->rules.birth[j] == livecount) nextGen[i] = '1';
			}
		}
	}
	this->map.assign(nextGen.begin(), nextGen.end());
	this->genNum++;
}

inline char GameOfLife::getCellValue(int x, int y) { return this->map[indexFromCoord(x, y)]; }

inline char & GameOfLife::getCellByRef(int x, int y) { return this->map[indexFromCoord(x, y)]; }

inline vector<char> GameOfLife::getMap() { return this->map; }

inline const int GameOfLife::getTotalSize() { return this->map.size(); }

inline int GameOfLife::indexFromCoord(int x, int y) { return x + this->width * y; }

inline void GameOfLife::clearMap() { fill(this->map.begin(), this->map.end(), '0'); }

inline unsigned int GameOfLife::getGenerationNumber() { return this->genNum; }

inline Position GameOfLife::coordFromIndex(int i) {
	Position temp;
	temp.x = i % this->width;
	temp.y = i / this->width;
	return temp;
}

inline void GameOfLife::setRules(Rules rles) {
	this->rules.birth.assign(rles.birth.begin(), rles.birth.end());
	this->rules.survive.assign(rles.survive.begin(), rles.survive.end());
}

inline void GameOfLife::setRules(vector<int> birth, vector<int> survive) {
	this->rules.birth.assign(birth.begin(), birth.end());
	this->rules.survive.assign(survive.begin(), survive.end());
}

inline Rules GameOfLife::getRules() { return this->rules; }

inline int GameOfLife::icheckNeighbors(int i) {
	Position temp = coordFromIndex(i);
	return checkNeighbors(temp.x, temp.y);
}

inline int GameOfLife::checkNeighbors(int x, int y) {
	int counter = 0;
	Position temp;
	//x-1, y-1
	temp.x = x - 1;
	temp.y = y - 1;
	if (temp.x < 0) temp.x = this->width - 1;
	if (temp.y < 0) temp.y = this->height - 1;
	if (this->map[indexFromCoord(temp.x, temp.y)] == '1') counter++;

	//x, y-1
	temp.x = x;
	temp.y = y - 1;
	if (temp.y < 0) temp.y = this->height - 1;
	if (this->map[indexFromCoord(temp.x, temp.y)] == '1') counter++;

	//x+1, y-1
	temp.x = x + 1;
	temp.y = y - 1;
	if (temp.x > (this->width - 1)) temp.x = 0;
	if (temp.y < 0) temp.y = this->height - 1;
	if (this->map[indexFromCoord(temp.x, temp.y)] == '1') counter++;

	//x+1, y
	temp.x = x + 1;
	temp.y = y;
	if (temp.x > (this->width - 1)) temp.x = 0;
	if (this->map[indexFromCoord(temp.x, temp.y)] == '1') counter++;

	//x+1, y+1
	temp.x = x + 1;
	temp.y = y + 1;
	if (temp.x > (this->width - 1)) temp.x = 0;
	if (temp.y > (this->height - 1)) temp.y = 0;
	if (this->map[indexFromCoord(temp.x, temp.y)] == '1') counter++;

	//x, y+1
	temp.x = x;
	temp.y = y + 1;
	if (temp.y > (this->height - 1)) temp.y = 0;
	if (this->map[indexFromCoord(temp.x, temp.y)] == '1') counter++;

	//x-1, y+1
	temp.x = x - 1;
	temp.y = y + 1;
	if (temp.x < 0) temp.x = this->width - 1;
	if (temp.y > (this->height - 1)) temp.y = 0;
	if (this->map[indexFromCoord(temp.x, temp.y)] == '1') counter++;

	//x-1, y
	temp.x = x - 1;
	temp.y = y;
	if (temp.x < 0) temp.x = this->width - 1;
	if (this->map[indexFromCoord(temp.x, temp.y)] == '1') counter++;

	return counter;
}