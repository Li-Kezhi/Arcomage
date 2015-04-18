#include "Cardslib.h"
#include "Cards.h"

//Initiation of all the cards data:
Card cardlibrary[3][34];
Card* card_bricks = cardlibrary[0];
Card* card_gems = cardlibrary[1];
Card* card_recruits = cardlibrary[2];

////////////////////////////////////////////////////////////
//Initiation of the effects
//Notes:
//If Effect returns 0, this is a normal card; if 1, then play again; if 2, draw 1 card, discard 1 card and play again
//ATTENTION: There's a card G5 which can't be discarded!
//Brick Shortage(#Bricks 0)
int Effect_B0(Condition &mine, Condition &yours){
	mine.bricks -= 8;
	yours.bricks -= 8;
	if(mine.bricks <= 0)
		mine.bricks = 0;
	if(yours.bricks <= 0)
		yours.bricks =0;
	return 0;
}

//Lucky Cache(#Bricks 1)
int Effect_B1(Condition &mine, Condition &yours){
	mine.bricks += 2;
	mine.gems += 2;
	return 1;
}

//Friendly Terrain(#Bricks 2)
int Effect_B2(Condition &mine, Condition &yours){
	mine.wall += 1;
	return 1;
}

//Miners(#Bricks 3)
int Effect_B3(Condition &mine, Condition &yours){
	mine.quarry += 1;
	return 0;
}

//Mother Lode(#Bricks 4)
int Effect_B4(Condition &mine, Condition &yours){
	if(mine.quarry < yours.quarry)
		mine.quarry += 2;
	else
		mine.quarry += 1;
	return 0;
}

//Dwarven Miners(#Bricks 5)
int Effect_B5(Condition &mine, Condition &yours){
	mine.wall += 4;
	mine.quarry += 1;
	return 0;
}

//Work Overtime(#Bricks 6)
int Effect_B6(Condition &mine, Condition &yours){
	mine.wall += 5;
	mine.gems -= 6;
	if(mine.gems < 0)
		mine.gems = 0;
	return 0;
}

//Copping the Tech(#Bricks 7)
int Effect_B7(Condition &mine, Condition &yours){
	if(mine.quarry < yours.quarry)
		mine.quarry = yours.quarry;
	return 0;
}

//Basic Wall(#Bricks 8)
int Effect_B8(Condition &mine, Condition &yours){
	mine.wall += 3;
	return 0;
}

//Sturdy Wall(#Bricks 9)
int Effect_B9(Condition &mine, Condition &yours){
	mine.wall += 4;
	return 0;
}

//Innovations(#Bricks 10)
int Effect_B10(Condition &mine, Condition &yours){
	mine.quarry += 1;
	yours.quarry += 1;
	mine.gems += 4;
	return 0;
}

//Foundations(#Bricks 11)
int Effect_B11(Condition &mine, Condition &yours){
	if(mine.wall == 0)
		mine.wall += 6;
	else 
		mine.wall += 3;
	return 0;
}

//Tremors(#Bricks 12)
int Effect_B12(Condition &mine, Condition &yours){
	mine.wall -= 5;
	yours.wall -= 5;
	if(mine.wall < 0)
		mine.wall = 0;
	if(yours.wall < 0)
		yours.wall = 0;
	return 1;
}

//Secret Room(#Bricks 13)
int Effect_B13(Condition &mine, Condition &yours){
	mine.magic += 1;
	return 1;
}

//Earthquake(#Bricks 14)
int Effect_B14(Condition &mine, Condition &yours){
	mine.quarry -= 1;
	yours.quarry -= 1;
	if(mine.quarry < 0)
		mine.quarry = 0;
	if(yours.quarry < 0)
		yours.quarry = 0;
	return 0;
}

//Big Wall(#Bricks 15)
int Effect_B15(Condition &mine, Condition &yours){
	mine.wall += 6;
	return 0;
}

//Collapse!(#Bricks 16)
int Effect_B16(Condition &mine, Condition &yours){
	yours.quarry -= 1;
	if(yours.quarry < 0)
		yours.quarry = 0;
	return 0;
}

//New Equipment(#Bricks 17)
int Effect_B17(Condition &mine, Condition &yours){
	mine.quarry += 2;
	return 0;
}

//Strip Mine(#Bricks 18)
int Effect_B18(Condition &mine, Condition &yours){
	mine.quarry -= 1;
	mine.wall += 10;
	mine.gems += 5;
	if(mine.quarry < 0)
		mine.quarry = 0;
	return 0;
}

//Reinforced Wall(#Bricks 19)
int Effect_B19(Condition &mine, Condition &yours){
	mine.wall += 8;
	return 0;
}

//Porticulus(#Bricks 20)
int Effect_B20(Condition &mine, Condition &yours){
	mine.wall += 5;
	mine.dungeon += 1;
	return 0;
}

//Crystal Rocks(#Bricks 21)
int Effect_B21(Condition &mine, Condition &yours){
	mine.wall += 7;
	mine.gems += 7;
	return 0;
}

//Harmonic Ore(#Bricks 22)
int Effect_B22(Condition &mine, Condition &yours){
	mine.wall += 6;
	mine.tower += 3;
	return 0;
}

//Mondo Wall(#Bricks 23)
int Effect_B23(Condition &mine, Condition &yours){
	mine.wall += 12;
	return 0;
}

//Focused Designs(#Bricks 24)
int Effect_B24(Condition &mine, Condition &yours){
	mine.wall += 8;
	mine.tower += 5;
	return 0;
}

//Great Wall(#Bricks 25)
int Effect_B25(Condition &mine, Condition &yours){
	mine.wall += 15;
	return 0;
}

//Rock Launcher(#Bricks 26)
int Effect_B26(Condition &mine, Condition &yours){
	mine.wall += 6;
	damage(yours, 10);
	return 0;
}

//Dragon's Heart(#Bricks 27)
int Effect_B27(Condition &mine, Condition &yours){
	mine.wall += 20;
	mine.tower += 8;
	return 0;
}

//Forced Labor(#Bricks 28)
int Effect_B28(Condition &mine, Condition &yours){
	mine.wall += 9;
	mine.recruits -= 5;
	if(mine.recruits < 0)
		mine.recruits = 0;
	return 0;
}

//Rock Garen(#Bricks 29)
int Effect_B29(Condition &mine, Condition &yours){
	mine.wall += 1;
	mine.tower += 1;
	mine. recruits += 2;
	return 0;
}

//Flood Water(#Bricks 30)
int Effect_B30(Condition &mine, Condition &yours){
	if(mine.wall < yours.wall){
		mine.dungeon -= 1;
		mine.tower -= 2;
	}
	else if(mine.wall > yours.wall){
		yours.dungeon -= 1;
		yours.wall -= 2;
	}
	else{
		mine.dungeon -= 1;
		mine.tower -= 2;
		yours.dungeon -= 1;
		yours.wall -= 2;
	}
	return 0;
}

//Barracks(#Bricks 31)
int Effect_B31(Condition &mine, Condition &yours){
	mine.recruits += 6;
	mine.wall += 6;
	if(mine.dungeon < yours.dungeon)
		mine.dungeon += 1;
	return 0;
}

//Battlements(#Bricks 32)
int Effect_B32(Condition &mine, Condition &yours){
	mine.wall += 7;
	damage(yours, 6);
	return 0;
}

//Shift(#Bricks 33)
int Effect_B33(Condition &mine, Condition &yours){
	int temp = mine.wall;
	mine.wall = yours.wall;
	yours.wall = temp;
	return 0;
}

//Quartz(#Gems 0)
int Effect_G0(Condition &mine, Condition &yours){
	mine.tower += 1;
	return 1;
}

//Smoky Quartz(#Gems 1)
int Effect_G1(Condition &mine, Condition &yours){
	yours.tower -= 1;
	return 1;
}

//Amethsy(#Gems 2)
int Effect_G2(Condition &mine, Condition &yours){
	mine.tower += 3;
	return 0;
}

//Spell Weavers(#Gems 3)
int Effect_G3(Condition &mine, Condition &yours){
	mine.magic += 1;
	return 0;
}

//Return 2
//Prism(#Gems 4)
int Effect_G4(Condition &mine, Condition &yours){
	return 2;
}

//Can't be discarded
//Lodestone(#Gems 5)
int Effect_G5(Condition &mine, Condition &yours){
	mine.tower += 3;
	return 0;
}

//Solar Alare(#Gems 6)
int Effect_G6(Condition &mine, Condition &yours){
	mine.tower += 2;
	yours.tower -= 2;
	return 0;
}

//Crystal Matrix(#Gems 7)
int Effect_G7(Condition &mine, Condition &yours){
	mine.magic += 1;
	mine.tower += 3;
	yours.tower += 1;
	return 0;
}

//Gemstone Flaw(#Gems 8)
int Effect_G8(Condition &mine, Condition &yours){
	mine.tower -= 3;
	yours.tower -= 3;
	return 0;
}

//Ruby(#Gems 9)
int Effect_G9(Condition &mine, Condition &yours){
	mine.tower += 5;
	return 0;
}

//Gem Spear(#Gems 10)
int Effect_G10(Condition &mine, Condition &yours){
	yours.tower -= 5;
	return 0;
}

//Power Burn(#Gems 11)
int Effect_G11(Condition &mine, Condition &yours){
	mine.tower -= 5;
	mine.magic += 2;
	return 0;
}

//Harmonic Vibe(#Gems 12)
int Effect_G12(Condition &mine, Condition &yours){
	mine.magic += 1;
	mine.tower += 3;
	mine.wall += 3;
	return 0;
}

//Parity(#Gems 13)
int Effect_G13(Condition &mine, Condition &yours){
	if(mine.magic < yours.magic)
		mine.magic = yours.magic;
	else
		yours.magic = mine.magic;
	return 0;
}

//Ernerald(#Gems 14)
int Effect_G14(Condition &mine, Condition &yours){
	mine.tower += 8;
	return 0;
}

//Pearl of Wisdom(#Gems 15)
int Effect_G15(Condition &mine, Condition &yours){
	mine.tower += 5;
	mine.magic += 1;
	return 0;
}

//Shatterer(#Gems 16)
int Effect_G16(Condition &mine, Condition &yours){
	mine.magic -= 1;
	yours.tower -= 9;
	return 0;
}

//Crumblestone(#Gems 17)
int Effect_G17(Condition &mine, Condition &yours){
	mine.tower += 5;
	yours.bricks -= 6;
	if(yours.bricks < 0)
		yours.bricks = 0;
	return 0;
}

//Sapphire(#Gems 18)
int Effect_G18(Condition &mine, Condition &yours){
	mine.tower += 11;
	return 0;
}

//Discord(#Gems 19)
int Effect_G19(Condition &mine, Condition &yours){
	mine.tower -= 7;
	yours.tower -= 7;
	mine.magic -= 1;
	yours.magic -= 1;
	return 0;
}

//Fire Ruby(#Gems 20)
int Effect_G20(Condition &mine, Condition &yours){
	mine.tower += 6;
	yours.tower -= 4;
	return 0;
}

//Quarry's Help(#Gems 21)
int Effect_G21(Condition &mine, Condition &yours){
	mine.tower += 7;
	mine.bricks -= 10;
	if(mine.bricks < 0)
		mine.bricks = 0;
	return 0;
}

//Crystal Shield(#Gems 22)
int Effect_G22(Condition &mine, Condition &yours){
	mine.tower += 8;
	mine.wall += 3;
	return 0;
}

//Empathy Gem(#Gems 23)
int Effect_G23(Condition &mine, Condition &yours){
	mine.tower += 8;
	mine.dungeon += 1;
	return 0;
}

//Diamond(#Gems 24)
int Effect_G24(Condition &mine, Condition &yours){
	mine.tower += 15;
	return 0;
}

//Sanctuary(#Gems 25)
int Effect_G25(Condition &mine, Condition &yours){
	mine.tower += 10;
	mine.wall += 5;
	mine.recruits += 5;
	return 0;
}

//Lava Jewel(#Gems 26)
int Effect_G26(Condition &mine, Condition &yours){
	mine.tower += 12;
	damage(yours, 6);
	return 0;
}

//Dragon's Eye(#Gems 27)
int Effect_G27(Condition &mine, Condition &yours){
	mine.tower += 20;
	return 0;
}

//Crystallize(#Gems 28)
int Effect_G28(Condition &mine, Condition &yours){
	mine.tower += 11;
	damage(mine, 6);
	return 0;
}

//Bag of Baubles(#Gems 29)
int Effect_G29(Condition &mine, Condition &yours){
	if(mine.tower < yours.tower)
		mine.tower += 2;
	else 
		mine.tower += 1;
	return 0;
}

//Rainbow(#Gems 30)
int Effect_G30(Condition &mine, Condition &yours){
	mine.tower += 1;
	yours.tower += 1;
	mine.gems += 3;
	return 0;
}

//Apprentice(#Gems 31)
int Effect_G31(Condition &mine, Condition &yours){
	mine.tower += 4;
	mine.recruits -= 3;
	yours.tower -= 2;
	if(mine.recruits < 0)
		mine.recruits = 0;
	return 0;
}

//Lightning Shard(#Gems 32)
int Effect_G32(Condition &mine, Condition &yours){
	if(mine.tower > yours.tower)
		yours.tower -= 8;
	else
		damage(yours, 8);
	return 0;
}

//Phase Jewel(#Gems 33)
int Effect_G33(Condition &mine, Condition &yours){
	mine.tower += 13;
	mine.recruits += 6;
	mine.bricks += 6;
	return 0;
}

//Mad Cow Disease(#Recruits 0)
int Effect_R0(Condition &mine, Condition &yours){
	mine.recruits -= 6;
	yours.recruits -= 6;
	if(mine.recruits < 0)
		mine.recruits = 0;
	if(yours.recruits < 0)
		yours.recruits = 0;
	return 0;
}

//Faerie(#Recruits 1)
int Effect_R1(Condition &mine, Condition &yours){
	damage(yours, 2);
	return 1;
}

//Moody Gobins(#Recruits 2)
int Effect_R2(Condition &mine, Condition &yours){
	mine.gems -= 3;
	damage(yours, 4);
	if(mine.gems < 0)
		mine.gems = 0;
	return 0;
}

//Minotaur(#Recruits 3)
int Effect_R3(Condition &mine, Condition &yours){
	mine.dungeon += 1;
	return 0;
}

//Elven Scout(#Recruits 4)
int Effect_R4(Condition &mine, Condition &yours){
	return 2;
}

//Goblin Mob(#Recruits 5)
int Effect_R5(Condition &mine, Condition &yours){
	damage(mine, 3);
	damage(yours, 6);
	return 0;
}

//Goblin Archers(#Recruits 6)
int Effect_R6(Condition &mine, Condition &yours){
	yours.tower -= 3;
	damage(mine, 1);
	return 0;
}

//Shadow Faerie(#Recruits 7)
int Effect_R7(Condition &mine, Condition &yours){
	yours.tower -= 2;
	return 1;
}

//Orc(#Recruits 8)
int Effect_R8(Condition &mine, Condition &yours){
	damage(yours, 5);
	return 0;
}

//Dwarves(#Recruits 9)
int Effect_R9(Condition &mine, Condition &yours){
	mine.wall += 3;
	damage(yours, 4);
	return 0;
}

//Little Snakes(#Recruits 10)
int Effect_R10(Condition &mine, Condition &yours){
	yours.tower -= 4;
	return 0;
}

//Troll Trainer(#Recruits 11)
int Effect_R11(Condition &mine, Condition &yours){
	mine.dungeon += 2;
	return 0;
}

//Tower Gremlin(#Recruits 12)
int Effect_R12(Condition &mine, Condition &yours){
	damage(yours, 2);
	mine.wall += 4;
	mine.tower += 2;
	return 0;
}

//Full Moon(#Recruits 13)
int Effect_R13(Condition &mine, Condition &yours){
	mine.dungeon += 1;
	yours.dungeon += 1;
	mine.recruits += 3;
	return 0;
}

//Slasher(#Recruits 14)
int Effect_R14(Condition &mine, Condition &yours){
	damage(yours, 6);
	return 0;
}

//Ogre(#Recruits 15)
int Effect_R15(Condition &mine, Condition &yours){
	damage(yours, 7);
	return 0;
}

//Rabid Sheep(#Recruits 16)
int Effect_R16(Condition &mine, Condition &yours){
	damage(yours, 6);
	yours.recruits -= 3;
	if(yours.recruits < 0)
		yours.recruits = 0;
	return 0;
}

//Imp(#Recruits 17)
int Effect_R17(Condition &mine, Condition &yours){
	damage(yours, 6);
	mine.bricks -= 5;
	yours.bricks -= 5;
	mine.gems -= 5;
	yours.gems -= 5;
	mine.recruits -= 5;
	yours.recruits -= 5;
	if(mine.bricks < 0)
		mine.bricks = 0;
	if(yours.bricks < 0)
		yours.bricks = 0;
	if(mine.gems < 0)
		mine.gems = 0;
	if(yours.gems < 0)
		yours.gems = 0;
	if(mine.recruits < 0)
		mine.recruits = 0;
	if(yours.recruits < 0)
		yours.recruits = 0;
	return 0;
}

//Spizzer(#Recruits 18)
int Effect_R18(Condition &mine, Condition &yours){
	if(yours.wall == 0)
		damage(yours, 10);
	else
		damage(yours, 6);
	return 0;
}

//Werewolf(#Recruits 19)
int Effect_R19(Condition &mine, Condition &yours){
	damage(yours, 9);
	return 0;
}

//Corrosion Cloud(#Recruits 20)
int Effect_R20(Condition &mine, Condition &yours){
	if(yours.wall > 0)
		damage(yours, 10);
	else
		damage(yours, 7);
	return 0;
}

//Unicorn(#Recruits 21)
int Effect_R21(Condition &mine, Condition &yours){
	if(mine.magic > yours.magic)
		damage(yours, 12);
	else
		damage(yours, 8);
	return 0;
}

//Elven Archers(#Recruits 22)
int Effect_R22(Condition &mine, Condition &yours){
	if(mine.wall > yours.wall)
		yours.tower -= 6;
	else
		damage(yours, 6);
	return 0;
}

//Succubus(#Recruits 23)
int Effect_R23(Condition &mine, Condition &yours){
	yours.tower -= 5;
	yours.recruits -= 8;
	if(yours.recruits < 0)
		yours.recruits = 0;
	return 0;
}

//Rock Stompers(#Recruits 24)
int Effect_R24(Condition &mine, Condition &yours){
	damage(yours, 8);
	yours.quarry -= 1;
	if(yours.quarry < 0)
		yours.quarry = 0;
	return 0;
}

//Thief(#Recruits 25)
int Effect_R25(Condition &mine, Condition &yours){
	yours.gems -= 10;
	yours.bricks -= 5;
	if(yours.gems < 0){
		mine.gems += (10 + yours.gems) / 2;
		yours.gems = 0;
	}
	else
		mine.gems += 10 / 2;
	if(yours.bricks < 0){
		mine.bricks += (5 + yours.bricks) /2;
		yours.bricks = 0;
	}
	else
		mine.gems += 5 / 2;
	return 0;
}

//Stone Giant(#Recruits 26)
int Effect_R26(Condition &mine, Condition &yours){
	damage(yours, 10);
	mine.wall += 4;
	return 0;
}

//Vampire(#Recruits 27)
int Effect_R27(Condition &mine, Condition &yours){
	damage(yours, 10);
	yours.recruits -= 5;
	yours.dungeon -= 1;
	if(yours.recruits < 0)
		yours.recruits = 0;
	if(yours.dungeon < 0)
		yours.dungeon = 0;
	return 0;
}

//Dragon(#Recruits 28)
int Effect_R28(Condition &mine, Condition &yours){
	damage(yours, 20);
	yours.gems -= 10;
	yours.dungeon -= 1;
	if(yours.gems < 0)
		yours.gems = 0;
	if(yours.dungeon < 0)
		yours.dungeon = 0;
	return 0;
}

//Spearman(#Recruits 29)
int Effect_R29(Condition &mine, Condition &yours){
	if(mine.wall > yours.wall)
		damage(yours, 3);
	else
		damage(yours, 2);
	return 0;
}

//Gnome(#Recruits 30)
int Effect_R30(Condition &mine, Condition &yours){
	damage(yours, 3);
	mine.gems += 1;
	return 0;
}

//Berserker(#Recruits 31)
int Effect_R31(Condition &mine, Condition &yours){
	damage(yours, 8);
	mine.tower -= 3;
	return 0;
}

//Warlord(#Recruits 32)
int Effect_R32(Condition &mine, Condition &yours){
	damage(yours, 13);
	mine.gems -= 3;
	if(mine.gems < 0)
		mine.gems = 0;
	return 0;
}

//Pegasus Lancer(#Recruits 33)
int Effect_R33(Condition &mine, Condition &yours){
	yours.tower -= 12;
	return 0;
}

////////////////////////////////////////////////////////////
//Initiation of the cards
void init_cards(){
	card_bricks[0].Setcard("Brick Shortage", "All players lose 8 bricks", Source(0, 0, 0), Effect_B0, 0, Bricks);
	card_bricks[1].Setcard("Lucky Cache", "+2 Bricks, +2 Gems. Play again", Source(0, 0, 0), Effect_B1, 1, Bricks);
	card_bricks[2].Setcard("Friendly Terrain", "+1 Wall. Play again", Source(1, 0, 0), Effect_B2, 2, Bricks);
	card_bricks[3].Setcard("Miners", "+1 Quarry", Source(3, 0, 0), Effect_B3, 3, Bricks);
	card_bricks[4].Setcard("Mother Lode", "If quarry < enemy quarry, +2 quarry. Else, +1 quarry", Source(4, 0, 0), Effect_B4, 4, Bricks);
	card_bricks[5].Setcard("Dwarven Miners", "+4 Wall, +1 Quarry", Source(7, 0, 0), Effect_B5, 5, Bricks);
	card_bricks[6].Setcard("Work Overtime", "+5 Wall, You lose 6 gems", Source(2, 0, 0), Effect_B6, 6, Bricks);
	card_bricks[7].Setcard("Copping the Tech", "If quarry < enemy quarry, quarry = enemy quarry", Source(5, 0, 0), Effect_B7, 7, Bricks);
	card_bricks[8].Setcard("Basic Wall", "+3 Wall", Source(2, 0, 0), Effect_B8, 8, Bricks);
	card_bricks[9].Setcard("Sturdy Wall", "+4 Wall", Source(3, 0, 0), Effect_B9, 9, Bricks);
	card_bricks[10].Setcard("Innovations", "+1 To all players' quarrys, you gain 4 gems", Source(2, 0, 0), Effect_B10, 10, Bricks);
	card_bricks[11].Setcard("Foundations", "If wall = 0, +6 wall, else +3 wall", Source(3, 0, 0), Effect_B11, 11, Bricks);
	card_bricks[12].Setcard("Terrors", "All walls take 5 damage. Play again", Source(7, 0, 0), Effect_B12, 12, Bricks);
	card_bricks[13].Setcard("Secret Room", "+1 Magic. Play again", Source(8, 0, 0), Effect_B13, 13, Bricks);
	card_bricks[14].Setcard("Earthquake", "-1 To all players' quarrys", Source(0, 0, 0), Effect_B14, 14, Bricks);
	card_bricks[15].Setcard("Big Wall", "+6 Wall", Source(5, 0, 0), Effect_B15, 15, Bricks);
	card_bricks[16].Setcard("Collapse!", "-1 Enemy quarry", Source(4, 0, 0), Effect_B16, 16, Bricks);
	card_bricks[17].Setcard("New Equipment", "+2 Quarry", Source(6, 0, 0), Effect_B17, 17, Bricks);
	card_bricks[18].Setcard("Strip Mine", "-1 Quarry, +10 wall. You gain 5 gems", Source(0, 0, 0), Effect_B18, 18, Bricks);
	card_bricks[19].Setcard("Reinforced Wall", "+8 Wall", Source(8, 0, 0), Effect_B19, 19, Bricks);
	card_bricks[20].Setcard("Porticulus", "+5 Wall, +1 Dungeon", Source(9, 0, 0), Effect_B20, 20, Bricks);
	card_bricks[21].Setcard("Crystal Rocks", "+7 Wall, gain 7 gems", Source(9, 0, 0), Effect_B21, 21, Bricks);
	card_bricks[22].Setcard("Harmonic Ore", "+6 Wall, +3 Tower", Source(11, 0, 0), Effect_B22, 22, Bricks);
	card_bricks[23].Setcard("Mondo Wall", "+12 Wall", Source(13, 0, 0), Effect_B23, 23, Bricks);
	card_bricks[24].Setcard("Focused Designs", "+8 Wall, +5 Tower", Source(15, 0, 0), Effect_B24, 24, Bricks);
	card_bricks[25].Setcard("Great Wall", "+15 Wall", Source(16, 0, 0), Effect_B25, 25, Bricks);
	card_bricks[26].Setcard("Rock Launcher", "+6 Wall, 10 Damage to enemy", Source(18, 0, 0), Effect_B26, 26, Bricks);
	card_bricks[27].Setcard("Dragon's Heart", "+20 Wall, +8 Tower", Source(24, 0, 0), Effect_B27, 27, Bricks);
	card_bricks[28].Setcard("Forced Labor", "+9 Wall, Lose 5 recruits", Source(7, 0, 0), Effect_B28, 28, Bricks);
	card_bricks[29].Setcard("Rock Garden", "+1 Wall, +1 Tower, +2 recruits", Source(1, 0, 0), Effect_B29, 29, Bricks);
	card_bricks[30].Setcard("Flood Water", "Player(s) with worst Wall are -1 Dungeon and 2 damage to Tower", Source(6, 0, 0), Effect_B30, 30, Bricks);
	card_bricks[31].Setcard("Barracks", "+6 recruits, +6 Wall. If dungeon < enemy dungeon, +1 dungeon", Source(10, 0, 0), Effect_B31, 31, Bricks);
	card_bricks[32].Setcard("Battlements", "+7 Wall, 6 damage to enemy", Source(14, 0, 0), Effect_B32, 32, Bricks);
	card_bricks[33].Setcard("Shift", "Switch your Wall with enemy Wall", Source(17, 0, 0), Effect_B33, 33, Bricks);
	card_gems[0].Setcard("Quartz", "+1 Tower, play again", Source(0, 1, 0), Effect_G0, 0, Gems);
	card_gems[1].Setcard("Smoky Quartz", "1 Damage to enemy tower. Play again", Source(0, 2, 0), Effect_G1, 1, Gems);
	card_gems[2].Setcard("Amethyst", "+3 Tower", Source(0, 2, 0), Effect_G2, 2, Gems);
	card_gems[3].Setcard("Spell Weavers", "+1 Magic", Source(0, 3, 0), Effect_G3, 3, Gems);
	card_gems[4].Setcard("Prism", "Draw 1 card. Discard 1 card. Play again", Source(0, 2, 0), Effect_G4, 4, Gems);
	card_gems[5].Setcard("Lodestone", "+3 Tower. This card can't be discarded without playing it", Source(0, 5, 0), Effect_G5, 5, Gems);
	card_gems[6].Setcard("Solar Flare", "+2 Tower, 2 Damage to enemy tower", Source(0, 4, 0), Effect_G6, 6, Gems);
	card_gems[7].Setcard("Crystal Matrix", "+1 Magic, +3 Tower, +1 Enemy tower", Source(0, 6, 0), Effect_G7, 7, Gems);
	card_gems[8].Setcard("Gemstone Flaw", "3 Damage to enemy tower", Source(0, 2, 0), Effect_G8, 8, Gems);
	card_gems[9].Setcard("Ruby", "+5 Tower", Source(0, 3, 0), Effect_G9, 9, Gems);
	card_gems[10].Setcard("Gem Spear", "5 Damage to enemy tower", Source(0, 4, 0), Effect_G10, 10, Gems);
	card_gems[11].Setcard("Power Burn", "5 Damage to your tower, +2 Magic", Source(0, 3, 0), Effect_G11, 11, Gems);
	card_gems[12].Setcard("Harmonic Vibe", "+1Magic, +3 Tower, +3 Wall", Source(0, 7, 0), Effect_G12, 12, Gems);
	card_gems[13].Setcard("Parity", "All player's magic equals the highest players magic", Source(0, 7, 0), Effect_G13, 13, Gems);
	card_gems[14].Setcard("Ernald", "+8 Tower", Source(0, 6, 0), Effect_G14, 14, Gems);
	card_gems[15].Setcard("Pearl of Wisdom", "+5 Tower, +1 Magic",Source(0, 9, 0), Effect_G15, 15, Gems);
	card_gems[16].Setcard("Shatterer", "-1 Magic, 9 Damage to enemy tower", Source(0, 8, 0), Effect_G16, 16, Gems);
	card_gems[17].Setcard("Crumblestone", "+5 Tower. Enemy loses 6 bricks", Source(0, 7, 0), Effect_G17, 17, Gems);
	card_gems[18].Setcard("Sapphire", "+11 Tower", Source(0, 10, 0), Effect_G18, 18, Gems);
	card_gems[19].Setcard("Discord", "7 Damage to all towers, all players' magic -1", Source(0, 5, 0), Effect_G19, 19, Gems);
	card_gems[20].Setcard("Fire Ruby", "+6 Tower, 4 Damage to all enemy towers", Source(0, 13, 0), Effect_G20, 20, Gems);
	card_gems[21].Setcard("Quarry's Help", "+7 Tower. Lose 10 bricks", Source(0, 4, 0), Effect_G21, 21, Gems);
	card_gems[22].Setcard("Crystal Shield", "+8 Tower, +3 Wall", Source(0, 12, 0), Effect_G22, 22, Gems);
	card_gems[23].Setcard("Empathy Gem", "+8 Tower, +1 Dungeon", Source(0, 14, 0), Effect_G23, 23, Gems);
	card_gems[24].Setcard("Diamond", "+15 Tower", Source(0, 16, 0), Effect_G24, 24, Gems);
	card_gems[25].Setcard("Sanctuary", "+10 Tower, +5 Wall. Gain 5 recruits", Source(0, 15, 0), Effect_G25, 25, Gems);
	card_gems[26].Setcard("Lava Jewel", "+12 Tower, 6 Damage to all enemies", Source(0, 17, 0), Effect_G26, 26, Gems);
	card_gems[27].Setcard("Dragon's Eye", "+20 Tower", Source(0, 21, 0), Effect_G27, 27, Gems);
	card_gems[28].Setcard("Crystallize", "+11 Tower, -6 Wall", Source(0, 8, 0), Effect_G28, 28, Gems);
	card_gems[29].Setcard("Bag of Baubles", "If Tower < enemy Tower, +2 Tower, else +1 Tower", Source(0, 0, 0), Effect_G29, 29, Gems);
	card_gems[30].Setcard("Rainbow", "+1 Tower to all players. You gain 3 gems", Source(0, 0, 0), Effect_G30, 30, Gems);
	card_gems[31].Setcard("Apprentice", "+4 Tower, you lose 3 recruits, 2 damage to enemy Tower", Source(0, 5, 0), Effect_G31, 31, Gems);
	card_gems[32].Setcard("Lightning Shard", "If Tower > enemy Wall, 8 damage to enemy Tower, else 8 damage", Source(0, 11, 0), Effect_G32, 32, Gems);
	card_gems[33].Setcard("Phase Jewel", "+13 Tower, +6 recuits, +6 bricks", Source(0, 18, 0), Effect_G33, 33, Gems);
	card_recruits[0].Setcard("Mad Cow Disease", "All players lose 6 recruits", Source(0, 0, 0), Effect_R0, 0, Recruits);
	card_recruits[1].Setcard("Faerie", "2 Damage. Play again", Source(0, 0, 1), Effect_R1, 1, Recruits);
	card_recruits[2].Setcard("Moody Gobins", "4 Damage. You lose 3 gems", Source(0, 0, 1), Effect_R2, 2, Recruits);
	card_recruits[3].Setcard("Minotaur", "+1 Dungeon", Source(0, 0, 3), Effect_R3, 3, Recruits);
	card_recruits[4].Setcard("Elven Scout", "Draw 1 card. Discard 1 card. Play again", Source(0, 0, 2), Effect_R4, 4, Recruits);
	card_recruits[5].Setcard("Goblin Mob", "6 Damage. You take 3 damage", Source(0, 0, 3), Effect_R5, 5, Recruits);
	card_recruits[6].Setcard("Goblin Archers", "3 Damage to enemy tower. You take 1 damage", Source(0, 0, 4), Effect_R6, 6, Recruits);
	card_recruits[7].Setcard("Shadow Faerie", "2 Damage to enemy tower. Play again", Source(0, 0, 6), Effect_R7, 7, Recruits);
	card_recruits[8].Setcard("Orc", "5 Damage", Source(0, 0, 3), Effect_R8, 8, Recruits);
	card_recruits[9].Setcard("Dwarves", "4 Damage, +3 Wall", Source(0, 0, 5), Effect_R9, 9, Recruits);
	card_recruits[10].Setcard("Little Snakes", "4 Damage to enemy tower", Source(0, 0, 6), Effect_R10, 10, Recruits);
	card_recruits[11].Setcard("Troll Trainer", "+2 Dungeon", Source(0, 0, 7), Effect_R11, 11, Recruits);
	card_recruits[12].Setcard("Tower Gremlin", "2 Damage, +4 Wall, +2 Tower", Source(0, 0, 8), Effect_R12, 12, Recruits);
	card_recruits[13].Setcard("Full Moon", "+1 to all player's Dungeon. You gain 3 recruits", Source(0, 0, 0), Effect_R13, 13, Recruits);
	card_recruits[14].Setcard("Slasher", "6 Damage", Source(0, 0, 5), Effect_R14, 14, Recruits);
	card_recruits[15].Setcard("Ogre", "7 Damage", Source(0, 0, 6), Effect_R15, 15, Recruits);
	card_recruits[16].Setcard("Rabid Sheep", "6 Damage. Enemy loses 3 recruits", Source(0, 0, 6), Effect_R16, 16, Recruits);
	card_recruits[17].Setcard("Imp", "6 Damage. All players lose 5 bricks, gems and recruits", Source(0, 0, 5), Effect_R17, 17, Recruits);
	card_recruits[18].Setcard("Spizzer", "If enemy wall = 0, 10 damage, else 6 damage", Source(0, 0, 8), Effect_R18, 18, Recruits);
	card_recruits[19].Setcard("Werewolf", "9 Damage", Source(0, 0, 9), Effect_R19, 19, Recruits);
	card_recruits[20].Setcard("Corrosion Cloud", "If enemy wall > 0, 10 damage, else 7 damage", Source(0, 0, 11), Effect_R20, 20, Recruits);
	card_recruits[21].Setcard("Unicorn", "If magic > enemy magic, 12 damage, else 8 damage", Source(0, 0, 9), Effect_R21, 21, Recruits);
	card_recruits[22].Setcard("Elven Archers", "If wall > enemy wall, 6 damage to enemy tower, else 6 damage", Source(0, 0, 10), Effect_R22, 22, Recruits);
	card_recruits[23].Setcard("Succubus", "5 Damage to enemy tower, enemy loses 8 recruits", Source(0, 0, 14), Effect_R23, 23, Recruits);
	card_recruits[24].Setcard("Rock Stompers", "8 Damage. -1 Enemy quarry", Source(0, 0, 11), Effect_R24, 24, Recruits);
	card_recruits[25].Setcard("Thief", "Enemy loses 10 gems, 5 bricks, you gain 1/2 amt round up", Source(0, 0, 12), Effect_R25, 25, Recruits);
	card_recruits[26].Setcard("Stone Giant", "10 Damage, +4 Wall", Source(0, 0, 15), Effect_R26, 26, Recruits);
	card_recruits[27].Setcard("Vampire", "10 Damage. Enemy loses 5 recruits, -1 enemy Dungeon", Source(0, 0, 17), Effect_R27, 27, Recruits);
	card_recruits[28].Setcard("Dragon", "20 Damage. Enemy loses 10 gems, -1 enemy Dungeon", Source(0, 0, 25), Effect_R28, 28, Recruits);
	card_recruits[29].Setcard("Spearman", "If Wall > enemy Wall, do 3 Damage, else do 2 damage", Source(0, 0, 2), Effect_R29, 29, Recruits);
	card_recruits[30].Setcard("Gnome", "3 Damage, +1 gem", Source(0, 0, 2), Effect_R30, 30, Recruits);
	card_recruits[31].Setcard("Berserker", "8 Damage. 3 Damage to your Tower", Source(0, 0, 4), Effect_R31, 31, Recruits);
	card_recruits[32].Setcard("Warlord", "13 Damage. You lose 3 gems", Source(0, 0, 13), Effect_R32, 32, Recruits);
	card_recruits[33].Setcard("Pegasus Lancer", "12 Damage to enemy tower", Source(0, 0, 18), Effect_R33, 33, Recruits);
}
