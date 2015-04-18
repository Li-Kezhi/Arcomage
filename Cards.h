#ifndef __CARDS_H_
#define __CARDS_H_

#include <string>
using namespace std;

enum Category{Bricks, Gems, Recruits};

//A temperary declaration
class Card;
struct Condition;

typedef int (*EFFECT)(Condition &mine, Condition &yours);

////////////////////////////////////////////////////////////

//The data of sources of one player
class Source{        
public:
	Source(int _bricks = 0, int _gems = 0, int _recruits = 0):
				bricks(_bricks), gems(_gems), recruits(_recruits){}
	int get_bricks() const;
	int get_gems() const;
	int get_recruits() const;
	friend class Hold_Cards;
	friend EFFECT get_effect(int num, const Condition player);
private:
	int bricks;
	int gems;
	int recruits;
};

////////////////////////////////////////////////////////////

//All the 6 cards one is holding
class Hold_Cards{
public:
	Hold_Cards(int _0, int _1, int _2, int _3, int _4, int _5);
	~Hold_Cards(){ }
	//Hold_Cards(const Hold_Cards & _hold_cards);
	void Change(int seq, int num);
	int* Show_Sequence();
	void display() const;
	void display(int num) const;
	friend void extra_discard(int cardnum, Condition &player);
	friend Source get_cost(int num, const Condition player);
	friend EFFECT get_effect(int num, const Condition player);
	friend int get_ab_number(int num, const Condition player);
private:
	Card* holding[6];
//	bool condition[6];
};

////////////////////////////////////////////////////////////

//All the data of one player
struct Condition{ 
public:
	Condition(int _b, int _g, int _r, int _q, int _m, int _d, int _t, int _w, 
		      Hold_Cards _cards);
	Condition();
	int bricks, gems, recruits, quarry, magic, dungeon, tower, wall;
	Hold_Cards cards;

	//
};
void damage(Condition &someone, int _damage);

////////////////////////////////////////////////////////////

//The whole infomation of one card.
class Card{
public:
	Card(std::string _name, std::string _notes, Source _cost, int (*_Effect)(Condition &mine, Condition &yours), 
		 int r_number, Category _category);
	void Setcard(std::string _name, std::string _notes, Source _cost, int (*_Effect)(Condition &mine, Condition &yours), 
		 int r_number, Category _category);
	Card(){}
	~Card(){}
	//If this card is initiated, this function returns "true".
	bool ready();
	//To show the infomation
	friend ostream & operator << (ostream & out, const Card & _card);

	friend class Hold_Cards;
	friend void extra_discard(int cardnum, Condition &player);
	friend Source get_cost(int num, const Condition player);
	friend EFFECT get_effect(int num, const Condition player);
	friend int get_ab_number(int num, const Condition player);
private:
	std::string name;     //Further modification needed!
	std::string notes;
	//Cost should be included in the game function!!!!!
	Source cost;
	EFFECT Effect;

	//The absolute and relative number of the card.
	int ab_number;
	Category category;
	int re_number;

	//If flag = 1, then this card is initiated.
	int flag;
};




//class Data;

#endif
