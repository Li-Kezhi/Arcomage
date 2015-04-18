#ifndef __ARCOMAGE_H__
#define __ARCOMAGE_H__

#include <iostream>
#include "Cards.h"
#include "Cited_LinkedList.h"
using namespace std;

struct Userdata{
public:
	Userdata(string _name = "Somebody", int _win = 0, int _lose = 0, int _tie = 0);
	~Userdata();
	string username;
    //Winning data
	int win, lose, tie;
	float win_ratio;
	void cal_ratio();
	friend ostream & operator << (ostream &out, const Userdata & data);
	
	//Game save
	void _get_position();
	bool history;
	Condition _players[2];
	int _cards_position0[6];
	int _cards_position1[6];
	int _choice;
	int _turns;
};

void change_account(LinkedList<Userdata> &userdata);
void show_history(LinkedList<Userdata> userdata);

//Ranking
//template<class T>
//void mySwap(T &x, T &y){
//	T temp = x;
//	x = y;
//	y = temp;
//}


//&LinkedList selectionSort(LinkedList userdata);

#endif
