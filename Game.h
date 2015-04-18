//This mark delete srand()
//#define TEST_MARK

#ifndef __GAME_H_
#define __GAME_H_

#include "Cards.h"
#include "Arcomage.h"

enum winning_condition{WIN, LOSE, ON};

////////////////////////////////////////////////////////////
//Initiation of the game
int game_choice();
int Game(Userdata &_data);
void init_game(int _choice, Condition &players0, Condition &players1);
//Display
void display(int choice, Condition mine, Condition yours);

////////////////////////////////////////////////////////////
//User interaction
char demand();

////////////////////////////////////////////////////////////
//Game functions
bool test_cost(Source cost, Condition player);
void pay(Source cost, Condition &player);
//discard is triggered by user's order
void discard(Condition &player);
//extra_discard is triggered by some special cards
void extra_discard(int cardnum, Condition &player);
//AI_discard is triggered by AI's order
void AI_discard(Condition &player);
//AI_extra_discard is triggered by some special cards
void AI_extra_discard(int cardnum, Condition &player);
void produce(Condition &player);
int check_winner(int choice, Condition mine, Condition yours);
winning_condition win(int _choice, Condition player);

////////////////////////////////////////////////////////////
//Private visiting
//To get the private data from some class
Source get_cost(int num, const Condition player);
EFFECT get_effect(int num, const Condition player);
int get_ab_number(int num, const Condition player);

#endif
