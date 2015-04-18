#include <iostream>
#include <fstream>
#include <iomanip>
#include "Arcomage.h"
#include "Game.h"
#include "Cardslib.h"
#include "Cited_LinkedList.h"
#include "Cited_LinkedList.cpp"   //A strange citing! I don't know why.
using namespace std;

int main(){
	char choice_menu = '1';
	int winner = 0;
	////////////////////////////////////////////////////////////
	//Initiation
	string name;
	int position;
	string help;
	int cards_position[6];

	ifstream filein("Users.dat", ios_base::in | ios_base::binary);
	ifstream userguide("User_Guide.txt", ios_base::in);
	Userdata *temp;

	//To get the user data from the file.
	LinkedList<Userdata> userdata;
	if(filein){
		temp = (Userdata*)malloc(sizeof(Userdata));
		filein.read(reinterpret_cast<char*> (&position), sizeof(position));
		while(filein){
		//	filein.read(reinterpret_cast<char*> (&temp), sizeof(temp));
			filein.read(reinterpret_cast<char*> (temp), sizeof(Userdata));
			userdata.InsertRear(*temp);
		}
		userdata.DeleteAt();
		userdata.Reset(position);
		free(temp);
	}
	else{
		ofstream fileout("Users.dat", ios_base::out | ios_base::binary);
	/*	ofstream out("jijif.txt");
		if(!out.is_open()){
		cerr<<"File not open!";
		return - 1;
		}
		//out<<1<<endl;*/
		fileout.close();
	}
	filein.close();

	for(bool flag = false; flag == false;){
		system("cls");
		cout << "Welcome to Arcomage!" << endl;

		//The first time to run this game
		if(userdata.EndOfList()){
			cout << "Please input your name here:";
			cin >> name;
			userdata.InsertFront(Userdata(name));
		}

		cout << userdata.Data();
		cout << "====================================================" << endl;
		cout << "                  Main menu                         " << endl;
		cout << "----------------------------------------------------" << endl;
		cout << "1. Start game/Continue game" << endl;
		cout << "2. Show my history" << endl;
		cout << "3. Change the user account"  << endl;
		cout << "4. Have a look at all the cards" << endl;
		cout << "5. Help" << endl;
		cout << "0. Quit game" << endl;
		cout << "====================================================" << endl;
		cout << "Your choice:";
		cin >> choice_menu;
		switch(choice_menu){
		////////////////////////////////////////////////////////////
		//The game part
		case '1':
			winner = Game(userdata.Data());
			if(userdata.Data().history == false){
				switch(winner){
				case 1:               //I'm the winner
					userdata.Data().win++;
					break;
				case 2:               //I'm the loser
					userdata.Data().lose++;
					break;
				case -1:              //A tie
					userdata.Data().tie++;
					break;
				}
			}
			break;
		////////////////////////////////////////////////////////////
		//Show the history
		case '2':
			show_history(userdata);
			break;
		////////////////////////////////////////////////////////////
		//Change the account
		case '3':
			change_account(userdata);
			break;
		////////////////////////////////////////////////////////////
		//To show all the cards
		case '4':
			init_cards();
			system("cls");
			cout << "====================================================" << endl;
			cout << "                    Cards List                      " << endl;
			cout << "====================================================" << endl;
			cout << "You can have a look at all the cards' infomation here:" << endl;
			for(int i = 0; i < 3; i ++){
				cout << "----------------------------------------------------" << endl;
				if(i == 0)
					cout << "                     BRICKS" << endl;
				else if(i == 1)
					cout << "                     GEMS" << endl;
				else
					cout << "                     RECRUITS" << endl;
				cout << "----------------------------------------------------" << endl;
				for(int j = 0; j < 34; j++)
					cout << cardlibrary[i][j];
				system("pause");
			}
			break;
		////////////////////////////////////////////////////////////
		//Help
		case '5':
			system("cls");
			cout << "====================================================" << endl;
			cout << "                  User Guide                        " << endl;
			cout << "====================================================" << endl;
			if(userguide){
				getline(userguide, help,'$');
				cout << help << endl;
			}
			else
				cout << "Error: File userguide.txt is lost!" << endl;
			system("pause");
			break;
		////////////////////////////////////////////////////////////
		//The exit
		case '0':
			flag = true;
			cout << "Welcome back the next time!" << endl;
			system("pause");
			break;
		default:
			cout << "An unacceptable demand." << endl;
			system("pause");
		}
	}
	
	////////////////////////////////////////////////////////////
	//To save the user's data
	ofstream fileout("Users.dat", ios_base::out | ios_base::binary);
	position = userdata.CurrentPosition();
	fileout.write(reinterpret_cast<char*> (&position), sizeof(position));
	userdata.Reset();
	while(!userdata.EndOfList()){
	//	temp = userdata.Data();
	//	fileout.write(reinterpret_cast<char*> (&temp), sizeof(temp));
		fileout.write(reinterpret_cast<char*> (&userdata.Data()), sizeof(userdata.Data()));
		userdata.Next();
	}
	fileout.close();
//	temp.~Userdata();
	return 0;
}

//struct Userdata
Userdata::Userdata(string _name, int _win, int _lose, int _tie){
	username = _name;
	win = _win;
	lose = _lose;
	tie = _tie;
	win_ratio = (float)win / (win + lose + tie);
	history = false;
	_turns = 0;
}

Userdata::~Userdata() {

}

void Userdata::cal_ratio(){
	win_ratio = (float)win / (win + lose + tie);
}

ostream& operator<< (ostream &out, const Userdata& data){
	cout << "Hello, " << data.username << "!" << endl;
	return cout;
}

void Userdata::_get_position(){
	for(int i = 0; i < 6; i++){
		_cards_position0[i] = get_ab_number(i, _players[0]);
	}
	for(int i = 0; i < 6; i++){
		_cards_position1[i] = get_ab_number(i, _players[1]);
	}
}

////////////////////////////////////////////////////////////
//Change the account
void change_account(LinkedList<Userdata> &userdata){
	for(bool flag = false; flag == false;){
		char input;
		cout << "----------------------------------------------------" << endl;
		cout << "You can choose an existed account below, or use extra functions." << endl;
		int position = userdata.CurrentPosition();
		userdata.Reset();
		for(int i = 0; i < userdata.ListSize(); i++){
			cout << (i + 1) << ". " << userdata.Data().username << endl;
			//i++;
			userdata.Next();
		}
		userdata.Reset(position);
		cout << "----------------------------------------------------" << endl;
		cout << "Input a number or \"E\" for extra functions:";
		cin >> input;
		//Look for an existed account
		if(input >= '1' && input < ('1' + userdata.ListSize())){
			userdata.Reset(input - '1');
			flag = true;
		}
		//Extra functions
		else if(input == 'E' || input == 'e'){
			cout << "----------------------------------------------------" << endl;
			cout << "Choose a function below:" << endl;
			cout << "1. Create a new account" << endl;
			//cout << "2. Delete an account" << endl;
			cout << "2. Delete all accounts" << endl;
			cout << "3. Back" << endl;
			cout << "----------------------------------------------------" << endl;
			cout << "Input a number as the command:";
			cin >> input;
			for(bool flag = false; flag == false;){
				string name;
				switch(input){
				case '1':
					//Add new account
					for(bool _flag = false; _flag == false;){
						bool _subflag = false;
						cout << "Please input your name here:";
						cin >> name;
						//To check whether there are the same name existing
						for(userdata.Reset();!userdata.EndOfList();userdata.Next()){
							if(userdata.Data().username == name)
								_subflag = true;
						}
						if(_subflag == true){
							cout << "This name is existing. Please change a name." << endl;
						}
						else{
							userdata.InsertRear(Userdata(name));
							_flag = true;
						}
						_subflag = false;
					}
					break;
				/*case '2':
					//Delete an account
					for(char n;;){
						cout << "Please input the number of account to delete:";
						cin >> n;
						if(!(n >= '1' && n < '1' + userdata.ListSize())){
							cout << "An available input." << endl;
							continue;
						}
						userdata.Reset(int(n - '1'));
						cout << "The account of " << userdata.Data().username << " is deleted!" << endl;
						userdata.DeleteAt();
						break;
					}
					//After that, you have to choose an account
					flag = true;
					break;
				}
				*/
				case '2':
					//Delete all accounts
					cout << "Are you sure to delete all the accounts? Y/N:";
					char yes;
					cin >> yes;
					if(!(yes == 'Y' || yes == 'y'))
						break;
					userdata.ClearList();
					//Add new account
					cout << "You have to create a new account." << endl;
					cout << "Please input your name here:";
					cin >> name;
					userdata.InsertRear(Userdata(name));
					flag = true;
					break;
				default:
					cout << "An unavailable command." << endl;
				}
				flag = true;
			}
		}
		else{
			cout << "An unavailable command." << endl;
			system("pause");
		}
	}
}

////////////////////////////////////////////////////////////
//Show the history
void show_history(LinkedList<Userdata> userdata){
	userdata.Data().cal_ratio();
	cout << "----------------------------------------------------" << endl;
	cout << "                  Geme history                      " << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "You have won " << userdata.Data().win 
			<< (userdata.Data().win > 1 ? " times,": " time,") << endl;
	cout << "But only be defeated for " << userdata.Data().lose 
			<< (userdata.Data().lose > 1 ? " times,": " time,") << endl;
	cout << "And " << userdata.Data().tie 
			<< (userdata.Data().tie > 1 ? " times": " time") << " to a tie." << endl;
	if(userdata.Data().win + userdata.Data().lose + userdata.Data().tie != 0)
		cout << "Your winning ratio is " << setw(5) << setiosflags(ios_base::fixed)
				<< setprecision(2) << (userdata.Data().win_ratio * 100) << "%." << endl;
	system("pause");
	//cout << "----------------------------------------------------" << endl;
	//cout << "                  Ranking list                      " << endl;
	//cout << "----------------------------------------------------" << endl;
	//LinkedList<Userdata> ranked = selectionSort(userdata);
	//int n = userdata.ListSize();
	//for(int i = 0; i < n; i++){
	//	cout << i << ". " << ranked.Data().username;
	//	cout << "   " << ranked.Data().win_ratio;
	//}
	//system("pause");
}

//////////////////////////////////////////////////////////////
////Ranking
//&LinkedList selectionSort(LinkedList userdata){
//	int n = userdata.ListSize();
//	Userdata temp[3n];
//	for(int i = 0; i < n - 1; i++){
//		int leastIndex = i;
//		for(int j = i + 1; j < n; j ++){
//			float a_j, a_leastIndex;
//			userdata.Reset(j);
//			a_j = userdata.Data().cal_ratio();
//			a_j = userdata.Data().win_ratio;
//			userdata.Reset(leastIndex);
//			a_leastIndex = userdata.Data().cal_ratio();
//			a_leastIndex = userdata.Data().win_ratio;
//			if(a_j < a_leastIndex)
//				leastIndex = j;
//		}
//		//Swap
//		n++
//		userdata.Reset(i);
//		temp[n] = userdata.Data();
//		userdata.Reset(leastIndex);
//		temp[n + 1] = userdata.Data();
//		userdata.DeleteAt();
//		userdata.InsertAt(temp[n]);
//		userdata.Reset(i);
//		userdata.DeleteAt();
//		userdata.InsertAt(temp[n + 1]);
//	}
//	return userdata;
//}
