#ifndef __TAVERNLIST_H_
#define __TAVERNLIST_H_
using namespace std;

struct Tavern{
	Tavern(int, int, int, int, int, int, int, int, int, int, int);
	int start_tower, start_wall;
	int start_quarry, start_magic, start_dungeon;
	int start_bricks, start_gems, start_recruits;
	int winning_tower, winning_resources;
	int prize;
	void winning_output();
//	friend ostream & operator<< (ostream &out, const Tavern &tavern);
};

//ostream & operator<< (ostream &out, const Tavern &tavern);

extern Tavern taverns[13];

#endif
