/** \file   MenuState.cpp
 *  \brief  Implémente la classe MenuState
 */
#include "MenuState.h"
#include "../Logger.h"
#include "PlayState.h"
#include <SDL/SDL_ttf.h>
#include "../color.h"
MenuState MenuState::menuState;


/**
 * Constructeur de MenuState
 */
MenuState::MenuState()
{
} // MenuState

/**
 * Destructeur de MenuState
 */
MenuState::~MenuState()
{
} // ~MenuState


/**
 * Initialise le menu
 */
void MenuState::init()
{
	if(!(root = TTF_OpenFont("media/font/zombie.ttf", 60))) LOGERROR("Cannot load font media/font/zombie.ttf");
	if(!(sub_menu = TTF_OpenFont("media/font/zombie.ttf", 30))) LOGERROR("Cannot load font media/font/zombie.ttf");

	refresh = false;
	iCurrentPosition = -1;
	iNbElemMenu = 4;
	arElemMenu = (elemMenu*)calloc(4, sizeof(elemMenu));

	iPosition = MAINMENU;

	arElemMenu->text = "Menu";
	arElemMenu->pos.x = 50;
	arElemMenu->pos.y = 50;
	arElemMenu->font = root;
	arElemMenu->bIsActive = false;
	arElemMenu->bRefresh = false;
	arElemMenu->action = NA;
	arElemMenu->active = Color::ttf_black;
	arElemMenu->pasive = Color::ttf_black;
	arElemMenu->cur_surface = TTF_RenderText_Blended(root, (arElemMenu)->text.c_str(), (arElemMenu)->pasive);

	(arElemMenu+1)->text = "Play";
	(arElemMenu+1)->pos.x = 50;
	(arElemMenu+1)->pos.y = 150;
	(arElemMenu+1)->font = sub_menu;
	(arElemMenu+1)->bIsActive = false;
	(arElemMenu+1)->bRefresh = false;
	(arElemMenu+1)->action = GAME;
	(arElemMenu+1)->active = Color::ttf_grey;
	(arElemMenu+1)->pasive = Color::ttf_black;
	(arElemMenu+1)->cur_surface = TTF_RenderText_Blended(sub_menu, (arElemMenu+1)->text.c_str(), (arElemMenu+1)->pasive);

	(arElemMenu+2)->text = "Options";
	(arElemMenu+2)->pos.x = 50;
	(arElemMenu+2)->pos.y = 200;
	(arElemMenu+2)->font = sub_menu;
	(arElemMenu+2)->bIsActive = false;
	(arElemMenu+2)->bRefresh = false;
	(arElemMenu+2)->action = OPTION;
	(arElemMenu+2)->active = Color::ttf_grey;
	(arElemMenu+2)->pasive = Color::ttf_black;
	(arElemMenu+2)->cur_surface = TTF_RenderText_Blended(sub_menu, (arElemMenu+2)->text.c_str(), (arElemMenu+2)->pasive);

	(arElemMenu+3)->text = "Quit";
	(arElemMenu+3)->pos.x = 50;
	(arElemMenu+3)->pos.y = 250;
	(arElemMenu+3)->font = sub_menu;
	(arElemMenu+3)->bIsActive = false;
	(arElemMenu+3)->bRefresh = false;
	(arElemMenu+3)->action = QUIT;
	(arElemMenu+3)->active = Color::ttf_grey;
	(arElemMenu+3)->pasive = Color::ttf_black;
	(arElemMenu+3)->cur_surface = TTF_RenderText_Blended(sub_menu, (arElemMenu+3)->text.c_str(), (arElemMenu+3)->pasive);
	LOG("Initialisation du menu");
} // init


/**
 * Termine le menu
 */
void MenuState::cleanUp()
{
	if(root) TTF_CloseFont(root);
	if(sub_menu) TTF_CloseFont(sub_menu);
	LOG("Fermetre du menu");
} // cleanUp


/**
 * Met le menu en pause
 */
void MenuState::pause()
{
	LOG("Mise en pause");
} // pause


/**
 * Sort le menu de pause
 */
void MenuState::resume()
{
	LOG("Sortie de pause");
} // resume


/**
 * Gestion des entrées
 */
void MenuState::input(Logic* logic, SDL_Event* SDLevent)
{	
	int x, y;
	switch (SDLevent->type) {
		case SDL_QUIT:
			LOG("Fermeture de la fenêtre");
			logic->stop();
			break;

		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&x, &y);
			for(int i=0; i<iNbElemMenu; i++)
			{
				SDL_Rect curPos = arElemMenu[i].pos;
				if((x >= curPos.x && x<= curPos.x+curPos.w) && (y >= curPos.y && y <= curPos.y + curPos.h))
				{
					if(!arElemMenu[i].bIsActive)
					{
						arElemMenu[i].cur_surface = TTF_RenderText_Blended(arElemMenu[i].font, arElemMenu[i].text.c_str(), arElemMenu[i].active);
						arElemMenu[i].bIsActive = true;
						refresh = true;
					}
					for(int j=0; j<iNbElemMenu; j++)
					{
						if(i != j)
						{
							if(arElemMenu[j].bIsActive)
							{
								arElemMenu[j].cur_surface = TTF_RenderText_Blended(arElemMenu[j].font, arElemMenu[j].text.c_str(), arElemMenu[j].pasive);
								arElemMenu[j].bIsActive = false;
							}
						}
					}

					break;
				}
			}
			break;

		case SDL_MOUSEBUTTONDOWN:

			break;


		case SDL_MOUSEBUTTONUP:
						SDL_GetMouseState(&x, &y);
			for(int i=0; i<iNbElemMenu; i++)
			{
				SDL_Rect curPos = arElemMenu[i].pos;
				if((x >= curPos.x && x<= curPos.x+curPos.w) && (y >= curPos.y && y <= curPos.y + curPos.h))
				{
					if(arElemMenu[i].bIsActive && arElemMenu[i].action == GAME)
						logic->changeState(PlayState::instance());
					if(arElemMenu[i].bIsActive && arElemMenu[i].action == QUIT)
						logic->stop();
				}
			}
			break;

	}
} // input


/**
 * Gestion de la logique du jeu
 */
void MenuState::logic(Logic* logic)
{
	logic->changeState(PlayState::instance());
} // logic


/**
 * Gestion de l'affichage
 */
void MenuState::render(Logic* logic, SDL_Surface* screen)
{
	if(iCurrentPosition != iPosition || refresh)
	{
		cout << "refresh" << endl;
		SDL_FillRect(screen, 0, SDL_MapRGBA(screen->format, 255, 255, 255, 0));
		iCurrentPosition = iPosition;

		if(iCurrentPosition == MAINMENU)
			displayMainScreen(screen);
		
	}
	
	SDL_Flip(screen);
} // render


/**
 * Donne un pointeur sur une instance MenuState
 *
 * @return		Objet MenuState
 */
MenuState* MenuState::instance()
{
	return &menuState;
} // instance

void displayMainMenu(SDL_Surface* screen) {



}

void MenuState::displayMainScreen(SDL_Surface* screen) {

	for(int i=0; i<iNbElemMenu; i++) 
	{
		SDL_BlitSurface(arElemMenu[i].cur_surface, NULL, screen, &arElemMenu[i].pos);
	}
	
}
