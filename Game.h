#ifndef _GAME_
#define _GAME_

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vld.h>
const char *getinfo_str(int str_id);

void Gamerun (int str_id, int hp, int damagecnt, float recordtime, SDL_Window * window, TTF_Font * font, SDL_Renderer * renderer);

#endif
