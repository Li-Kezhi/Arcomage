#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Game.h"
#include "Cardslib.h"
#include "TavernList.h"
using namespace std;

int Game(Userdata &_data){
	//If winner = 0, the game is on; 1, I'm the winner; 2, enemy's the winner; -1, a tie
	int winner = 0;
	////////////////////////////////////////////////////////////
	//Initiation
	static int turns = _data._turns;
	int choice = 0;
	//players[0] is the user, players[1] is the enemy
	Condition players[2];
	
	if(_data.history == false){
		choice = game_choice();      //choice = 0 ~ 12
		taverns[choice].winning_output();
		system("pause");
		init_cards();
		init_game(choice, players[0], players[1]);
	}
	else{
		cout << "The game is continuing..." << endl;
				int choice = _data._choice;
		//players[0] is the user, players[1] is the enemy
		players[0] = _data._players[0];
		players[1] = _data._players[1];
		//modify the cards position
		for(int i = 0; i < 6; i++){
			players[0].cards.Change(i, _data._cards_position0[i]);
		}
		for(int i = 0; i < 6; i++){
			players[1].cards.Change(i, _data._cards_position1[i]);
		}
		choice = _data._choice;      //choice = 0 ~ 12
		taverns[choice].winning_output();
		system("pause");
		init_cards();
	}

	////////////////////////////////////////////////////////////
	//Game on
	int usercard = 0;
	char _userdemand;
	int special_demand = 0;
	char quit_choice = 'N';

	while(1){
		//My turn:
		
		//1. Produce more resources
		if(turns != 0)
			produce(players[0]);

		//2. Display the condition in the game
		display(choice, players[0], players[1]);

		//3. Response to user's command
		for(bool flag = false; flag == false;){    //If flag == true, my turn is over
			_userdemand = demand();
			switch(_userdemand){
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
				usercard = int(_userdemand) - int('1');
				if(test_cost( get_cost(usercard, players[0]), players[0]) == false){
					cout << "There's not enough resources to draw this card!" << endl;
					break;
				}
				else{
					pay( get_cost(usercard, players[0]), players[0]);   //Pay the resources
					special_demand = get_effect(usercard, players[0])(players[0], players[1]);  //Take effection
					switch(special_demand){
					case 0:
						flag = true;
						break;
					case 1:
						cout << "Your extra turn." << endl;
						break;
					case 2:
						extra_discard(usercard, players[0]);
						break;
					}
					players[0].cards.Change(usercard, (rand()%102) );  //Get a new card
					break;
				}
			case 'D':
			case 'd':
				//
				discard(players[0]);
				flag = true;
				break;
			case 'S':
			case 's':
				winner = 2;   //To quit the game
				flag = true;
				break;
			case 'Q':
			case 'q':
				cout << "Are you sure to quit the game now? This will add a lose mark." << endl;
				cout << "Yes/No?(Y/N):";
				cin >> quit_choice;
				if(quit_choice == 'Y' || quit_choice == 'y'){
					winner = 2;
					flag = true;
				}
				break;
			default:
				cout << "An unavailable order." << endl;
				break;
			}
			system("pause");
		}

		if(winner == 0)
			winner = check_winner(choice, players[0], players[1]);
		if(winner == 1){
			display(choice, players[0], players[1]);
			cout << '\a' << endl;
			system("pause");
			system("cls");
			cout << "----------------------------------------------------" << endl;
			cout << "               You have won the game!" << endl;
			cout << "----------------------------------------------------" << endl;
			system("pause");
			break;
		}
		else if(winner == 2){
			if(_userdemand == 'S' || _userdemand == 's')
				break;
			display(choice, players[0], players[1]);
			cout << '\a' << endl;
			system("pause");
			system("cls");
			cout << "----------------------------------------------------" << endl;
			cout << "              But you failed at last..." << endl;
			cout << "----------------------------------------------------" << endl;
			system("pause");
			break;
		}
		else if(winner == -1){
			display(choice, players[0], players[1]);
			cout << '\a' << endl;
			system("pause");
			system("cls");
			cout << "----------------------------------------------------" << endl;
			cout << "              A fierce fighting! A tie." << endl;
			cout << "----------------------------------------------------" << endl;
			system("pause");
			break;
		}

		//Enemy's turn
		//More work can be done here!!!
		//The simplest AI strategy: always draw the first card.
		//1. Produce more resources
		if(turns != 0)
			produce(players[1]);

		//2. Display the condition in the game
		display(choice, players[0], players[1]);
		system("pause");
		
		//3. AI strategy
		char AI_choice = '0';    //extra AI logic
		for(bool flag = false; flag == false;){    //If flag == true, my turn is over
			AI_choice++;         //extra AI logic
			if(AI_choice == '7') //extra AI logic
				AI_choice = 'D'; //extra AI logic
			_userdemand = AI_choice;  //extra AI logic
			switch(_userdemand){
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
				usercard = int(_userdemand) - int('1');
				if(test_cost( get_cost(usercard, players[1]), players[1]) == false){
					//cout << "There's not enough resources to draw this card!" << endl;
					break;
				}
				else{
					pay( get_cost(usercard, players[1]), players[1]);   //Pay the resources
					cout << "The enemy used the card below:" << endl;
					//extra AI logic
					players[1].cards.display(usercard);
					system("pause");
					special_demand = get_effect(usercard, players[1])(players[1], players[0]);  //Take effection
					switch(special_demand){
					case 0:
						flag = true;
						break;
					case 1:
						//extra AI logic
						//cout << "Your extra turn." << endl;
						break;
					case 2:
						/*cout << "The enemy discarded the card below:" << endl;
						players[1].cards.display(usercard);
						system("pause");*/
						AI_extra_discard(usercard, players[1]);
						break;
					}
					players[1].cards.Change(usercard, (rand()%102) );  //Get a new card
					break;
				}
			case 'D':
				/*cout << "The enemy discarded the card below:" << endl;
				players[1].cards.display(usercard);
				system("pause");*/
				AI_discard(players[1]);
				flag = true;
				break;
			case 'S':
				flag = true;
				break;
			case 'Q':
				cout << "Are you sure to quit the game now? This will add a lose mark." << endl;
				cout << "Yes/No?(Y/N):";
				cin >> quit_choice;
				if(quit_choice == 'Y' || quit_choice == 'y'){
					winner = 2;
					flag = true;
				}
				break;
			default:
				//cout << "An unavailable order." << endl;
				break;
			}
		}
		cout << "The enemy has finished his turn." << endl;
		system("pause");

		if(winner == 0)
			winner = check_winner(choice, players[0], players[1]);
		if(winner == 1){
			display(choice, players[0], players[1]);
			cout << '\a' << endl;
			system("pause");
			system("cls");
			cout << "----------------------------------------------------" << endl;
			cout << "               You have won the game!" << endl;
			cout << "----------------------------------------------------" << endl;
			system("pause");
			break;
		}
		else if(winner == 2){
			display(choice, players[0], players[1]);
			cout << '\a' << endl;
			system("pause");
			system("cls");
			cout << "----------------------------------------------------" << endl;
			cout << "              But you failed at last..." << endl;
			cout << "----------------------------------------------------" << endl;
			system("pause");
			break;
		}
		else if(winner == -1){
			display(choice, players[0], players[1]);
			cout << '\a' << endl;
			system("pause");
			system("cls");
			cout << "----------------------------------------------------" << endl;
			cout << "              A fierce fighting! A tie." << endl;
			cout << "----------------------------------------------------" << endl;
			system("pause");
			break;
		}
		display(choice, players[0], players[1]);
		cout << "It's your turn now!" << endl;
		system("pause");

		turns++;
	}

	//Save the game data
	if(_userdemand == 'S' || _userdemand == 's'){
		_data.history = true;
		_data._players[0] = players[0];
		_data._players[1] = players[1];
		_data._choice = choice;
		_data._turns = turns;
		for(int i = 0; i < 6; i++){
			_data._cards_position0[i] = (players[0].cards.Show_Sequence())[i];
			_data._cards_position1[i] = (players[1].cards.Show_Sequence())[i];
		}
	}
	//Clear the userdata history
	else{
		_data.history = false;
		_data._turns = 0;
	}
	return winner;
}

////////////////////////////////////////////////////////////
//Initiation of the game
//To choose a game mode
int game_choice(){
	system("cls");    //To clear the screen
	cout << "Welcome to Arcomage Game Mode!" << endl;
	cout << "====================================================" << endl;
	cout << "You can choose a tavern to play Arcomage:" << endl;
	cout << "(Different winning requirements differ in different taverns.)" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "1.  Harmondale: On the House" << endl;
	cout << "2.  Barrow Downs: Miner's Only" << endl;
	cout << "3.  Stone City: Grogg's Grog" << endl;
	cout << "4.  Bracada Desert: Familiar Place" << endl;
	cout << "5.  Erathia: Griffin's Rest" << endl;
	cout << "6.  Tularean Forest: Emerald Inn" << endl;
	cout << "7.  Tatalia: The Loyal Mercenary" << endl;
	cout << "8.  Deyja Moors: The Snobbish Goblin" << endl;
	cout << "9.  Avlee: The Potted Pixie" << endl;
	cout << "10. Evenmorn Island: The Laughing Monk" << endl;
	cout << "11. Mount Nighon: Fortune's Folly" << endl;
	cout << "12. Celeste: The Blessed Brew" << endl;
	cout << "13. The Pit: The Vampyre Lounge" << endl;
	cout << "----------------------------------------------------" << endl;
	int choice = 0;
	int times = 0;
	while((choice < 1 )||( choice > 13)){
		if(times == 0)
			cout << "Your choice is:";
		else
			cout << "An unavailable choice. Your choice is:";
		cin.sync();
		cin >> choice;
		times++;
	}
	return --choice;
}

//The initiation of all the players infomation
void init_game(int _choice, Condition &players0, Condition &players1){
	players0.tower = taverns[_choice].start_tower;
	players0.wall = taverns[_choice].start_wall;
	players0.bricks = taverns[_choice].start_bricks;
	players0.gems = taverns[_choice].start_gems;
	players0.recruits = taverns[_choice].start_recruits;
	players0.quarry = taverns[_choice].start_quarry;
	players0.magic = taverns[_choice].start_magic;
	players0.dungeon = taverns[_choice].start_dungeon;
	players1.tower = taverns[_choice].start_tower;
	players1.wall = taverns[_choice].start_wall;
	players1.bricks = taverns[_choice].start_bricks;
	players1.gems = taverns[_choice].start_gems;
	players1.recruits = taverns[_choice].start_recruits;
	players1.quarry = taverns[_choice].start_quarry;
	players1.magic = taverns[_choice].start_magic;
	players1.dungeon = taverns[_choice].start_dungeon;

#ifndef TEST_MARK
	srand((unsigned)time(0));
#endif

	for(int i = 0; i < 6; i ++){
		players0.cards.Change(i, (rand()%102) );
	}
	for(int i = 0; i < 6; i ++){
		players1.cards.Change(i, (rand()%102) );
	}
}

//Display
void display(int choice, Condition mine, Condition yours){
	system("cls");    //To clear the screen

	//To display the winning requirements
	taverns[choice].winning_output();
	cout << "====================================================" << endl;
	
	//To display my condition:
	cout << "My resources and the producers:(Resources/Prodecers)" << endl;
	cout << "Bricks: " << setw(3) << setfill(' ') << mine.bricks << " / " << setw(2) << setfill(' ') << mine.quarry;
	cout << "     ";
	cout << "Gems: " << setw(3) << setfill(' ') << mine.gems << " / " << setw(2) << setfill(' ') << mine.magic;
	cout << "     ";
	cout << "Recruits: " << setw(3) << setfill(' ') << mine.recruits << " / " << setw(2) << setfill(' ') << mine.dungeon;
	cout << endl;
	cout << endl;
	cout << "My tower and wall:" << endl;
	cout << "Tower: " << setw(3) << setfill(' ') << mine.tower;
	float tower = float(mine.tower * 70 / taverns[choice].winning_tower);
	for(; tower > 0; tower--){
		cout << "#";
	}
	cout << endl;
	cout << "Wall:  " << setw(3) << setfill(' ') << mine.wall;
	float wall = float(mine.wall * 70 / taverns[choice].winning_tower);
	for(; wall > 0; wall--){
		cout << "#";
	}
	cout << endl;
	cout << "----------------------------------------------------" << endl;

	//To display enemy's condition:
	cout << "Enemy's tower and wall:" << endl;
	cout << "Wall:  " << setw(3) << setfill(' ') << yours.wall;
	wall = float(yours.wall * 70 / taverns[choice].winning_tower);
	for(; wall > 0; wall--){
		cout << "#";
	}
	cout << endl;
	cout << "Tower: " << setw(3) << setfill(' ') << yours.tower;
	tower = float(yours.tower * 70 / taverns[choice].winning_tower);
	for(; tower > 0; tower--){
		cout << "#";
	}
	cout << endl << endl;
	cout << "Enemy's resources and the producers:(Resources/Prodecers)" << endl;
	cout << "Bricks: " << setw(3) << setfill(' ') << yours.bricks << " / " << setw(2) << setfill(' ') << yours.quarry;
	cout << "     ";
	cout << "Gems: " << setw(3) << setfill(' ') << yours.gems << " / " << setw(2) << setfill(' ') << yours.magic;
	cout << "     ";
	cout << "Recruits: " << setw(3) << setfill(' ') << yours.recruits << " / " << setw(2) << setfill(' ') << yours.dungeon;
	cout << endl;
	cout << "====================================================" << endl;
	cout << endl;

	//To display your cards:
	cout << "Your cards in hand: (Name/Cost/Discription)" << endl;
	mine.cards.display();
}

////////////////////////////////////////////////////////////
//User interaction
char demand(){
	char temp;
	cout << "Please choose a card to draw(1-6), or input 'D' to discard a card, or 'S' to save the game and quit, or 'Q' to quit the game." << endl;
	cout << "Your demand(1-6, D, S, Q):";
	cin.sync();
	cin >> temp;
	return temp;
}

////////////////////////////////////////////////////////////
//Game functions
bool test_cost(Source cost, Condition player){
	player.bricks -= cost.get_bricks();
	player.gems -= cost.get_gems();
	player.recruits -= cost.get_recruits();
	if(player.bricks >= 0 && player.gems >= 0 && player.recruits >= 0)
		return true;
	else 
		return false;
}

void pay(Source cost, Condition &player){
	player.bricks -= cost.get_bricks();
	player.gems -= cost.get_gems();
	player.recruits -= cost.get_recruits();
}

void discard(Condition &player){
	int input = 0;
	for(bool flag = false; flag == false;){
		cout << "You can choose a card to discard:(1-6)";
		cin.sync();
		cin >> input;
		//G5 card cannot be discarded
		if(get_ab_number(input - 1, player) == 39)
			cout << "This card cannont be discarded." << endl;
		else{
			player.cards.Change(input - 1, (rand()%102) );  //Get a new card
			flag = true;
		}
	}
}

void extra_discard(int cardnum, Condition &player){
	int input = 0;
	for(bool flag = false; flag == false;){
		cout << "You can choose another card to discard:(1-6)";
		cin.sync();
		cin >> input;
		if(input == cardnum + 1)
			cout << "This card has just been drawn." << endl;
		//G5 card cannot be discarded
		else if(get_ab_number(input - 1, player) == 39)
			cout << "This card cannont be discarded." << endl;
		else{
			player.cards.Change(input - 1, (rand()%102) );  //Get a new card
			flag = true;
		}
	}
}

void AI_discard(Condition &player){
	int input = 0;
	int AI_commend = -1;
	for(bool flag = false; flag == false;){
		AI_commend++;
		//cout << "You can choose a card to discard:(1-6)";
		//cin >> input;
		input = AI_commend + 1;
		//G5 card cannot be discarded
		if(get_ab_number(input - 1, player) == 39)
			;
			//cout << "This card cannont be discarded." << endl;
		else{
			cout << "The enemy discarded the card below:" << endl;
			player.cards.display(AI_commend);
			system("pause");
			player.cards.Change(input - 1, (rand()%102) );  //Get a new card
			flag = true;
		}
	}
}

void AI_extra_discard(int cardnum, Condition &player){
	int input = 0;
	int AI_commend = -1;
	for(bool flag = false; flag == false;){
		AI_commend++;
		//cout << "You can choose another card to discard:(1-6)";
		//cin >> input;
		input = AI_commend + 1;
		if(input == cardnum + 1);
			//cout << "This card has just been drawn." << endl;
		//G5 card cannot be discarded
		else if(get_ab_number(input - 1, player) == 39)
			;
			//cout << "This card cannont be discarded." << endl;
		else{
			cout << "The enemy discarded the card below:" << endl;
			player.cards.display(AI_commend);
			system("pause");
			player.cards.Change(input - 1, (rand()%102) );  //Get a new card
			flag = true;
		}
	}
}

void produce(Condition &player){
	player.bricks += player.quarry;
	player.gems += player.magic;
	player.recruits += player.dungeon;
}

int check_winner(int choice, Condition mine, Condition yours){
	if(win(choice, mine) == WIN && win(choice, yours) != WIN)
		return 1;
	else if(win(choice, mine) != LOSE && win(choice, yours) == LOSE)
		return 1;
	else if(win(choice, mine) == LOSE && win(choice, yours) != LOSE)
		return 2;
	else if(win(choice, mine) != WIN && win(choice, yours) == WIN)
		return 2;
	else if(win(choice, mine) == WIN && win(choice, yours) == WIN)
		return -1;
	else if(win(choice, mine) == LOSE && win(choice, yours) == LOSE)
		return -1;
	else
		return 0;
}

winning_condition win(int _choice, Condition player){
	if(player.tower <= 0)
		return LOSE;
	else if(player.tower >= taverns[_choice].winning_tower)
		return WIN;
	else if(player.bricks >= taverns[_choice].winning_resources)
		return WIN;
	else if(player.gems >= taverns[_choice].winning_resources)
		return WIN;
	else if(player.recruits >= taverns[_choice].winning_resources)
		return WIN;
	else
		return ON;
}

////////////////////////////////////////////////////////////
//Private visiting
Source get_cost(int num, const Condition player){
	return (player.cards.holding[num] -> cost);
}

EFFECT get_effect(int num, const Condition player){
	return player.cards.holding[num] -> Effect;
}

int get_ab_number(int num, const Condition player){
	return player.cards.holding[num] -> ab_number;
}
