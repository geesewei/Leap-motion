
#include "Swordsource.h"

//Update the slash move's id
int Swordmove::setID(int input)
{
	Swordmove::moveid = input;
    return input;
}

// Get the slash's damage value
int Swordmove::setDamage(int id)
{
	switch ( id ) {
		case 1:
			Swordmove::damage = 50;
			break;
		case 2: 
			Swordmove::damage = 50;
			break;
		case 3:
			Swordmove::damage = 70;
			break;
		default:
			Swordmove::damage = 0;
			break;
	}	
    return Swordmove::damage;
}

//Get the name string of the slash move
std::string Swordmove::getmoveName (int id) {
	if (id  == 1) {
		return "Right slash!";
	} else if(id  == 2)  {
		return "left slash!";
	} else if(id  == 3)  {
		return "Stab!!";
	} 
	return " ";
}

//Tool move analyzer function 
void Swordmove::getMove (const Leap::Controller& controller) {
	
	const Leap::Frame frame = controller.frame();
	int toolnum = frame.tools().count();

  
  const Leap::ToolList tools = frame.tools();

  //Check if hand is shown in the controller
  if (!frame.hands().isEmpty()) {
		Swordmove::handin = true;
  }
  //Check if 
  if (frame.tools().count() < 1) {
	  Swordmove::ready = false;
	  Swordmove::movecnt = 0;
	  return ;
  }

  Swordmove::ready = true;
  const Leap::Tool toolitem = *(tools.begin());
  float tipspeedx = toolitem.tipVelocity().x; 
  float tipspeedy = toolitem.tipVelocity().y; 
  float tipspeedz = toolitem.tipVelocity().z; 
  float tiphight = toolitem.tipPosition().y; 
  float tipAngle = toolitem.direction().pitch();
  const Leap::ToolList pretools = controller.frame(1).tools();
  const Leap::Tool pretoolitem = *(pretools.begin());
  float Speeddiffx = abs(pretoolitem.tipVelocity().x-tipspeedx); 
  float Speeddiffy = abs(pretoolitem.tipVelocity().y-tipspeedy); 
  float Speeddiffz = abs(pretoolitem.tipVelocity().z-tipspeedz); 
  float Posdiffx = toolitem.tipPosition().x -pretoolitem.tipPosition().x; 
  float Posdiffy = toolitem.tipPosition().y -pretoolitem.tipPosition().y;  
  float Posdiffz = toolitem.tipPosition().z -pretoolitem.tipPosition().z; 

  std::string moveName = "";
  int movedamage = 0;
  int moveID = 0;

  if (Swordmove::movecnt == 0) {
	if (tipspeedx > 100 && tipspeedy < -100 && Posdiffx > 5 && Posdiffy < -5) {
		moveID = Swordmove::setID(1);
		movedamage = Swordmove::setDamage(1);
		moveName = getmoveName(1);
		Swordmove::movecnt++;
	} else if (tipspeedx < -100 && tipspeedy < -100 && Posdiffx < -5 && Posdiffy < -5){
		moveID = Swordmove::setID(2);
		movedamage = Swordmove::setDamage(2);
		moveName = getmoveName(2);
		Swordmove::movecnt++;
	} else if (tipspeedz < -400 && Speeddiffx < 100 && Speeddiffy < 100) {
		moveID = Swordmove::setID(3);
		movedamage = Swordmove::setDamage(3);
		moveName = getmoveName(3);
		Swordmove::movecnt++;
	} else {
		moveID = Swordmove::setID(0);
		movedamage = Swordmove::setDamage(0);
		Swordmove::movecnt++;
	}

  } else if (Swordmove::movecnt <= 2) {
	Swordmove::movecnt++;
  } 
  else if (Swordmove::movecnt >= 3) {
	Swordmove::movecnt = 0;
  }


  //hp = boss.getHP(hp, movedamage);
  //boss.showBoss(hp);

 // std::cout << std::string(2, ' ') <<" Angle: " << tipAngle<<" , position: " << toolitem.tipPosition()
             //<< ", velocity: " <<  toolitem.tipVelocity() << std::endl;

	return ;
}

