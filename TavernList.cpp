#include "TavernList.h"
#include <iostream>
using namespace std;

Tavern::Tavern(int _1, int _2, int _3, int _4, int _5, int _6, int _7, int _8, int _9, int _10, int _11):
				start_tower(_1), start_wall(_2), start_quarry(_3), start_magic(_4), start_dungeon(_5),
				start_bricks(_6), start_gems(_7), start_recruits(_8), 
				winning_tower(_9), winning_resources(_10), prize(_11){};

void Tavern::winning_output(){
	cout << "Winning requirements:" << endl;
	cout << "Your tower should be higher than " << winning_tower << ", or any source is more that " << winning_resources << "." << endl;
}

/*
ostream & operator<< (ostream &out, const Tavern &tavern){
	out << "("<<tavern.winning_tower<<", "<<tavern.winning_resources<<")";
	return out;
}
*/


//The winning requirements of different taverns
/*
	1.  Harmondale: On the House
	2.  Barrow Downs: Miner's Only
	3.  Stone City: Grogg's Grog
	4.  Bracada Desert: Familiar Place
	5.  Erathia: Griffin's Rest
	6.  Tularean Forest: Emerald Inn
	7.  Tatalia: The Loyal Mercenary
	8.  Deyja Moors: The Snobbish Goblin
	9.  Avlee: The Potted Pixie
	10. Evenmorn Island: The Laughing Monk
	11. Mount Nighon: Fortune's Folly
	12. Celeste: The Blessed Brew
	13. The Pit: The Vampyre Lounge
	*/
Tavern taverns[13] = {
	Tavern(15, 5, 2, 2, 2, 10, 10, 10, 30, 100, 6),
	Tavern(20, 50, 1, 1, 5, 5, 5, 25, 100, 300, 18),
	Tavern(50, 50, 5, 3, 5, 20, 10, 20, 100, 300, 20),
	Tavern(20, 10, 3, 3, 3, 5, 5, 5, 75, 200, 14),
	Tavern(20, 5, 2, 2, 2, 5, 5, 5, 50, 100, 12),
	Tavern(20, 5, 2, 2, 2, 5, 5, 5, 50, 150, 12),
	Tavern(10, 20, 3, 1, 2, 15, 5, 10, 125, 350, 20),
	Tavern(25, 10, 3, 3, 3, 5, 5, 5, 75, 200, 14),
	Tavern(10, 20, 3, 1, 2, 15, 5, 10, 125, 350, 20),
	Tavern(20, 10, 5, 5, 5, 25, 25, 25, 150, 400, 6),
	Tavern(20, 10, 1, 1, 1, 15, 15, 15, 200, 500, 60),
	Tavern(30, 15, 4, 4, 4, 10, 10, 10, 100, 300, 30),
	Tavern(30, 15, 4, 4, 4, 10, 10, 10, 100, 300, 30)
};
