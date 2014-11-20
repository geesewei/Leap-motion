

#include "Boss.h"

//Get the monster's hp value
int	Boss::getHP(int hp, int hit) {

	return (hp - hit) > 0? (hp-hit): 0;
}

//Initialize the monster hp
int Boss::initBoss(int hp) {

	hp = FULLHP;
	return hp;
}

//Display the monster status in cmd console
void Boss::showBoss(int hp) {

	if (hp > 0) {
		std::cout <<"    /\\                 /\\ "<< std::endl;
		std::cout <<"   /  \\               /  \\ "<< std::endl;
		std::cout <<"  /    \\_ _ _ _ _ _ _/    \\ "<< std::endl;
		std::cout <<" /                         \\ "<< std::endl;
		std::cout <<"|  __ _ _            _ _ _  |"<< std::endl;
		std::cout <<"|  \\     \\          /     / |"<< std::endl;
		std::cout <<"|   \\ _ __\\        /_ _ _/  |"<< std::endl;
		std::cout <<"|                           | "<< std::endl;
		std::cout <<"| _ _/\\ /\\ /\\ /\\ /\\ /\\_ _ _ | "<< std::endl;
		std::cout <<" \\      \\/ \\/ \\/ \\/ \\/     / "<< std::endl;
		std::cout <<"  \\       \\/\\/\\/\\/\\/      / "<< std::endl;
		std::cout <<"   \\_ _ _ _ _ _ _ _ _ _ _/ "<< std::endl;

		std::cout <<"  HP: "<<hp<< std::endl;
	} else if (hp <= 0) {
	
		std::cout <<"    /\\                 /\\ "<< std::endl;
		std::cout <<"   /  \\               /  \\ "<< std::endl;
		std::cout <<"  /    \\_ _ _ _ _ _ _/    \\ "<< std::endl;
		std::cout <<" /                         \\ "<< std::endl;
		std::cout <<"|                           |"<< std::endl;
		std::cout <<"|     _|_           _|_     |"<< std::endl;
		std::cout <<"|      |             |      |"<< std::endl;
		std::cout <<"|                           | "<< std::endl;
		std::cout <<"|                           | "<< std::endl;
		std::cout <<" \\  _ _/\\_/\\_/\\_/\\_/\\_ _   / "<< std::endl;
		std::cout <<"  \\                       / "<< std::endl;
		std::cout <<"   \\_ _ _ _ _ _ _ _ _ _ _/ "<< std::endl;

		std::cout <<" You defeated the boss!!!!"<< std::endl;
		std::cout <<" You defeated the boss!!!!"<< std::endl;
		std::cout <<" You defeated the boss!!!!"<< std::endl;

	}


	return;
}
