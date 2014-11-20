#ifndef _BOSS_
#define _BOSS_

#include <iostream>
//#include <string>
//#include <Windows.h>
#include <stdlib.h>
 
#define FULLHP 500

class Boss {

	public:
	//static int hp;
	virtual int	getHP(int hp, int hit);
	virtual void showBoss(int hp);
	virtual int initBoss(int hp);
	
};

#endif
