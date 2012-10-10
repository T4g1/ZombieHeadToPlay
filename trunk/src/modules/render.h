/** \file   Render.h
 *  \brief  Définit la classe Render
 */
#ifndef RENDER_H
#define RENDER_H

#include <SDL/SDL.h>

#include "Module.h"


// Temps entre les affichage du FPS
#define UPDATE_FPS		200

using namespace std;

class Core;

/** \class  Render
 *  \brief  Gére toute la partie affichage du jeu
 *
 * Gére la partie afichage du jeu, les animations et l'affichage des menus
 */
class Render :
    public Module
{
    public:
		Render(Core* core);
		~Render();

        void initialize();
        void unInitialize();
        void frame();
    protected:
    private:
		SDL_Surface* screen;

		string caption;
};

#endif // RENDER_H