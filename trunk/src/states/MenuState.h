/** \file   MenuState.h
 *  \brief  Définit la classe MenuState
 */
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include <SDL/SDL_ttf.h>
using namespace std;

typedef struct {
	SDL_Surface* cur_surface;
	string text;
	bool bIsActive;
	bool bRefresh;
	SDL_Rect pos;
	TTF_Font *font;
	SDL_Color pasive;
	SDL_Color active;
	char action;
} elemMenu;

enum arCurrentMenu {NA, MAINMENU, OPTION, GAME, QUIT};

/** \class  MenuState
 *  \brief  Gestion du menu principal
 */
class MenuState : 
	public State
{
    public:
		MenuState();
		~MenuState();

		void init();
		void cleanUp();

		void pause();
		void resume();

		void input(Logic* logic, SDL_Event* SDLevent);
		void logic(Logic* logic);
		void render(Logic* logic, SDL_Surface* screen) const {};
		void render(Logic* logic, SDL_Surface* screen);

		static MenuState* instance();
    protected:
    private:
		static MenuState menuState;

		//Fonts
		TTF_Font *root;
		TTF_Font *sub_menu;

		//Current position
		int iPosition;
		int iCurrentPosition;

		bool refresh;

		//Main Menu
		elemMenu* arElemMenu;
		int iNbElemMenu;
		void displayMainScreen(SDL_Surface* screen);

		
};

#endif // MENUSTATE_H
