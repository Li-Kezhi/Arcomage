#include <iostream>
#include <iomanip>
#include "Cardslib.h"
#include "Cards.h"
using namespace std;

extern Card cardlibrary[3][34];

////////////////////////////////////////////////////////////

//class Source
int Source::get_gems() const{return gems;}
int Source::get_bricks() const{return bricks;}
int Source::get_recruits() const{return recruits;}

////////////////////////////////////////////////////////////

//class Hold_Cards
Hold_Cards::Hold_Cards(int _0 = 0, int _1 = 0, int _2 = 0, int _3 = 0,
						int _4 = 0, int _5 = 0){
	holding[0] = cardlibrary[0] + _0;
	holding[1] = cardlibrary[0] + _1;
	holding[2] = cardlibrary[0] + _2;
	holding[3] = cardlibrary[0] + _3;
	holding[4] = cardlibrary[0] + _4;
	holding[5] = cardlibrary[0] + _5;
}

/*
Hold_Cards::Hold_Cards(const Hold_Cards & _hold_cards){
	//int size = sizeof(Card);
	//Card cards[6];

	for(int i = 0;i<6;i++)
		holding[i] = new Card();
	/*Card* cards = new Card[6];
	for(int i = 0; i < 6; i++)
		cards[i] = *_hold_cards.holding[i];
	for(int i = 0; i < 6; i++)
		holding[i] = &cards[i];
}
*/

void Hold_Cards::Change(int seq, int num){
	holding[seq] = &cardlibrary[num / 34][num % 34];
}

int* Hold_Cards::Show_Sequence(){
	int sequence[6];
	for(int i = 0; i < 6; i++)
		sequence[i] = holding[i] - &cardlibrary[0][0];
	return sequence;
}

void Hold_Cards::display() const{
	for(int n = 0; n < 6; n++){
		//To get the category
		string category;
		switch(holding[n] -> category){
		case Bricks:
			category = "Bricks";
			break;
		case Gems:
			category = "Gems";
			break;
		case Recruits:
			category = "Recruits";
			break;
		}
		//To get the cost
		int cost = 0;
		if(holding[n] -> cost.bricks != 0)
			cost = holding[n] -> cost.bricks;
		else if(holding[n] -> cost.gems != 0)
			cost = holding[n] -> cost.gems;
		else
			cost = holding[n] -> cost.recruits;
		cout << n + 1 << ". " << holding[n] -> name;
		cout << "(Costs: " << category << " " << cost << ")" << endl;
		cout << "   " << holding[n] -> notes << endl;
	}
}

void Hold_Cards::display(int num) const{
	//To get the category
	string category;
	switch(holding[num] -> category){
	case Bricks:
		category = "Bricks";
		break;
	case Gems:
		category = "Gems";
		break;
	case Recruits:
		category = "Recruits";
		break;
	}
	//To get the cost
	int cost = 0;
	if(holding[num] -> cost.bricks != 0)
		cost = holding[num] -> cost.bricks;
	else if(holding[num] -> cost.gems != 0)
		cost = holding[num] -> cost.gems;
	else
		cost = holding[num] -> cost.recruits;
	cout << holding[num] -> name;
	cout << "(Costs: " << category << " " << cost << ")" << endl;
	cout << "   " << holding[num] -> notes << endl;
}


////////////////////////////////////////////////////////////

//struct Condition
Condition::Condition(int _b, int _g, int _r, int _q, int _m, int _d, int _t, int _w,
					 Hold_Cards _cards):cards(_cards){
	gems = _g;
	bricks = _b;
	recruits = _r;
	magic = _m;
	quarry = _q;
	dungeon = _d;
	tower = _t;
	wall = _w;
}

Condition::Condition(){}

void damage(Condition &someone, int _damage){
	someone.wall -= _damage;
	int _damage_tower = 0 - someone.wall;
	if(someone.wall < 0 ){
		someone.wall = 0;
		someone.tower -= _damage_tower;
	}
}

////////////////////////////////////////////////////////////

//class Card
void Card::Setcard(std::string _name, std::string _notes, Source _cost, 
					int (*_Effect)(Condition &mine, Condition &yours), 
					int r_number, Category _category){
	name = _name;
	notes = _notes;
	Effect = _Effect;
	re_number = r_number;
	category = _category;
	ab_number = 34 * int(_category) + r_number;
	cost = _cost;
	flag = 1;
}

Card::Card(std::string _name = "None", std::string _notes = "None", 
			Source _cost = Source(0, 0, 0), 
			int (*_Effect)(Condition &mine, Condition &yours) = 0, 
			int r_number = 0, Category _category = Gems)
{
	Setcard(_name, _notes, _cost, _Effect, r_number, _category);
	flag = 0;
}

bool Card::ready(){
	if (flag == 0)
		return false;
	else 
		return true;
}

ostream & operator << (ostream & out, const Card & _card){
	out << setw(2) << (_card.re_number + 1) << ". " << _card.name << endl;
	out << "  Costs: ";
	switch(_card.category){
	case Bricks:
		out << "Bricks " << _card.cost.get_bricks() << endl;
		break;
	case Gems:
		out << "Gems " << _card.cost.get_gems() << endl;
		break;
	case Recruits:
		out << "Recruits " << _card.cost.get_recruits() << endl;
		break;
	}
	out << "  " << _card.notes << endl;
	return out;
}
