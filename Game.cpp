#include "Game.h"

const char * getinfo_str(int str_id) {
	const char * info_str[] = {"Start slahing!!", 
		"Prepare your sword!!",
		"Please adjust your sword's position!",
		"Stab to continue / right or left slash to quit",
		"Continued!!My hero!!!", 
		"Adios!!My firend!!!",
		"Press Enter to quit...",
		"Go ahead and slash!",
		"Right slash!",
		"Left slash!",
		"Stab!!"
	};

	return info_str[str_id];
}

void Gamerun (int str_id, int hp, int damagecnt, float recordtime, SDL_Window * window, TTF_Font * font, SDL_Renderer * renderer) {
	static float rcdtime;
	if  (recordtime >= 2)
		rcdtime = recordtime;
	
	static int dmgcn;
	if (damagecnt > 0) {
	dmgcn++;
	}

	SDL_Surface * image = SDL_LoadBMP("Slaymonster1.bmp");
    if (image == NULL)
        SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(), window);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_Color color = { 15, 255, 0 };
	SDL_Color color2 = { 15, 155, 75 };
	int texW = 0;
	int texH = 0;
	int texW3 = 0;
	int texH3 = 0;
	int texW4 = 0;
	int texH4 = 0;
	int texW5 = 0;
	int texH5 = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };
	//SDL_DestroyTexture(texture);

	const char * curr_char = getinfo_str(str_id);
		std::string curr_str2 = "HP: " + std::to_string(hp);
		const char * curr_char2 = curr_str2.c_str();
		
	SDL_Surface * surface3 = TTF_RenderText_Solid(font, curr_char, color);
	SDL_Surface * surface4 = TTF_RenderText_Solid(font, curr_char2, color2);
	SDL_Texture * texture3 = SDL_CreateTextureFromSurface(renderer, surface3);
	SDL_Texture * texture4 = SDL_CreateTextureFromSurface(renderer, surface4);

	SDL_QueryTexture(texture3, NULL, NULL, &texW3, &texH3);
	SDL_QueryTexture(texture4, NULL, NULL, &texW4, &texH4);
	SDL_Rect dstrect3 = { 0, 0, texW3, texH3 };
	SDL_Rect dstrect4 = { 25, 25, texW4, texH4 };

	SDL_Texture * texture5;
	SDL_Surface * surface5; 
	//SDL_Rect dstrect5;
	//if (hp <= 0) {
		std::string curr_str3 = "You used " + std::to_string(rcdtime) + " seconds to slayed the monster!!!";
		const char * curr_char3 = curr_str3.c_str();
		surface5 = TTF_RenderText_Solid(font, curr_char3, color2);
		texture5 = SDL_CreateTextureFromSurface(renderer, surface5);
		SDL_QueryTexture(texture5, NULL, NULL, &texW5, &texH5);	
		SDL_Rect dstrect5 = { 0, 50, texW5, texH5 };
	//}

	if (dmgcn > 0 && dmgcn < 3 && str_id == 8 && hp > 0) {
		SDL_DestroyTexture(texture);
		image = SDL_LoadBMP("Slaymonsters1.bmp");
		if (image == NULL)
			SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(), window);
		texture = SDL_CreateTextureFromSurface(renderer, image);
		dmgcn++;
	} else if (dmgcn > 0 && dmgcn < 3 && str_id == 9 && hp > 0) {
		SDL_DestroyTexture(texture);
		image = SDL_LoadBMP("Slaymonsters2.bmp");
		if (image == NULL)
			SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(), window);
		texture = SDL_CreateTextureFromSurface(renderer, image);
		dmgcn++;
	} else if (dmgcn > 0 && dmgcn < 3 && str_id == 10 && hp > 0) {
		SDL_DestroyTexture(texture);
		image = SDL_LoadBMP("Slaymonsters3.bmp");
		if (image == NULL)
			SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(), window);
		texture = SDL_CreateTextureFromSurface(renderer, image);
		dmgcn++;
	} else if (dmgcn > 0 && dmgcn < 4 && hp > 0) {
		SDL_DestroyTexture(texture);
		image = SDL_LoadBMP("Slaymonster.bmp");
		if (image == NULL)
			SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(), window);
		texture = SDL_CreateTextureFromSurface(renderer, image);
		dmgcn++;
	} else if (hp <= 0){
		SDL_DestroyTexture(texture);
		image = SDL_LoadBMP("Slaymonster2.bmp");
		if (image == NULL)
			SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(), window);
		texture = SDL_CreateTextureFromSurface(renderer, image);
		dmgcn = 0;
	} else  {
		SDL_DestroyTexture(texture);
		image = SDL_LoadBMP("Slaymonster1.bmp");
		if (image == NULL)
			SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(), window);
		texture = SDL_CreateTextureFromSurface(renderer, image);
		dmgcn = 0;
	}
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_RenderCopy(renderer, texture3, NULL, &dstrect3);
	SDL_RenderCopy(renderer, texture4, NULL, &dstrect4);	
	//if (hp <= 0) 
		SDL_RenderCopy(renderer, texture5, NULL, &dstrect5);	
	SDL_RenderPresent(renderer);
	
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(texture3);
	SDL_DestroyTexture(texture4);
	SDL_FreeSurface(surface3);
	SDL_FreeSurface(surface4);

	//if (hp <= 0) {
		SDL_DestroyTexture(texture5);
		SDL_FreeSurface(surface5);
	//}
	return ;
}
