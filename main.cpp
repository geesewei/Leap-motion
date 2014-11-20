//#include <iostream>
//#include <string>
//#include "Leap.h"
#include <windows.h>
//#include <stdlib.h> 
#include <time.h> 
#include "Swordsource.h" 
//#include "spell.h" 
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <string.h>
#include <vector>
#include "Game.h"

Swordmove Swordm;
Boss boss;

using std::string;

using namespace Leap;

class SampleListener : public Listener {
    public:
    virtual void onConnect(const Controller&);
    virtual void onFrame(const Controller&); 
	//virtual void toolMove(const Controller&);
};

const string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};


void SampleListener::onConnect(const Controller& controller) {
	;
}

void SampleListener::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information

  const Frame frame = controller.frame();
 
// Get tools
  const ToolList tools = frame.tools();
  for (ToolList::const_iterator tl = tools.begin(); tl != tools.end(); ++tl) {
    const Tool tool = *tl;
  
  }

  Swordm.getMove(controller);
 
  Sleep(50);
}
    
            
int main(int argc, char** argv) {

  // Create a sample listener and controller
  SampleListener listener;
  Controller controller;
  static int hp = FULLHP;
  int conflag = 1;
  int newhp = 1;
  int readyflag = 0, readyflag2 = 0;
  int concnt = 0;
  string curr_str = "";
  string curr_str2 = "";
  int str_id = 0;
  int damageflag = 0;
  float recordtime = 0;

  time_t now = time(NULL);  
  time_t starttime = now;

	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	  SDL_Window * window = SDL_CreateWindow("Slaymonster",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 738, 660, 0);
    if (window == NULL)
        SDL_ShowSimpleMessageBox(0, "Window init error", SDL_GetError(), window);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
        SDL_ShowSimpleMessageBox(0, "Renderer init error", SDL_GetError(), window);
    SDL_Surface * image = SDL_LoadBMP("Slaymonster1.bmp");
    if (image == NULL)
        SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(), window);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    if (texture == NULL)
        SDL_ShowSimpleMessageBox(0, "Texture init error", SDL_GetError(), window);

	TTF_Font * font = TTF_OpenFont("FreeSans.ttf", 26);
	const char * error = TTF_GetError();
	SDL_Color color = { 15, 255, 0 };
	SDL_Surface * surface2 = TTF_RenderText_Solid(font, "Start slahing!!", color);
	SDL_Texture * texture2 = SDL_CreateTextureFromSurface(renderer, surface2);

	int texW = 0;
	int texH = 0;
	int texW2 = 0;
	int texH2 = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_QueryTexture(texture2, NULL, NULL, &texW2, &texH2);
	SDL_Rect dstrect = { 0, 0, texW, texH };
	SDL_Rect dstrect2 = { 0, 0, texW2, texH2 };

	std::cout<<"Start slahing!!"<<std::endl;
	hp = boss.initBoss(FULLHP);
	boss.showBoss(hp);
	conflag = 1;

	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_RenderPresent(renderer);
	str_id = 0;
  while(conflag) {
	  
	  if (SDL_PollEvent(&event))
  {
   // Check for the quit message
   if (event.type == SDL_QUIT)
   {
    conflag = 0;
    break;
   }
  }
	    // Have the sample listener receive events from the controller
		controller.addListener(listener);		

		if (argc > 1 && strcmp(argv[1], "--bg") == 0)
			controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
		
		//reset damageflag
		damageflag = 0;
		if (Swordm.ready == false && readyflag == 0) {
			std::cout<<"Prepare your sword!!!"<<std::endl;
			str_id = 1;
			readyflag = 1;
		} else if (Swordm.ready == false && Swordm.handin == true && readyflag2 == 0) {
			std::cout<<"Please adjust your sword's position!"<<std::endl;
			str_id = 2;
			readyflag2 = 1;
		} 
		else  if (Swordm.ready == true && Swordm.moveid > 0) {
			str_id = 7 + Swordm.moveid;
			//damageflag++;
		}
		
		//Handle game when monster is defeated
		if (hp == 0) {
				recordtime = (float)difftime(time(NULL), starttime);
				starttime = time(NULL);
			if (concnt == 0) {				
				std::cout<<"You used "<<recordtime<<" seconds to slayed the monster!!!"<<std::endl;
				std::cout<<"Stab to continue / right or left slash to quit"<<std::endl;
				str_id = 3;
				concnt++;
				//Sleep(10);
			}
			if (Swordm.ready == true && Swordm.movecnt == 0 && Swordm.damage == 70){ //Continue reset game
				std::cout<<"Continued!!My hero!!!"<<std::endl;
				str_id = 4;
				hp = FULLHP;
				boss.showBoss(hp);
				concnt = 0;
			} else if (Swordm.ready == true && Swordm.movecnt == 0 && Swordm.damage == 50) { //Quit game
				std::cout<<"Adios!!My firend!!!"<<std::endl;
				str_id = 5;
				conflag = 0;
				//concnt = 0;
				//std::cout << "Press Enter to quit..." << std::endl;
				//std::cin.get();
			} else {
				conflag = 1;
			}
		}

		if (hp > 0 && Swordm.ready == true && Swordm.movecnt == 0){
			newhp = boss.getHP(hp, Swordm.damage);
			readyflag = 0;
			readyflag2 = 0;
			if (newhp < hp) {
				hp = newhp;
				damageflag++;
				if (Swordm.damage > 0) {
					std::cout << Swordm.getmoveName(Swordm.moveid) << std::endl;
					std::cout << Swordm.getmoveName(Swordm.moveid) << std::endl;
					std::cout << Swordm.getmoveName(Swordm.moveid) << std::endl;
				}
				boss.showBoss(hp);
			}
		}
		
		Gamerun (str_id, hp, damageflag, recordtime, window, font, renderer);

		

  // Remove the sample listener when done
  controller.removeListener(listener);

  }
  /*SDL_WaitEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
		conflag = 0;
		break;
	} */	
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(texture2);
	SDL_FreeSurface(surface2);
	TTF_CloseFont(font);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	controller.removeListener(listener);

  return 0;
}
