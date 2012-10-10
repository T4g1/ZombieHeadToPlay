/** \file   Sprite.h
 *  \brief  Définit la classe Sprite
 */
#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Animation.h"

using namespace std;


/** \class  Sprite
 *  \brief  Classe permettant la gestion des Sprites
 */
class Sprite
{
    public:
        Sprite(string filename);
        virtual ~Sprite();

		// Accesseur
		SDL_Surface* getSurface() const;
    protected:
    private:
		SDL_Surface* image;
		Animation* l_animation;		// Animations contenues sur le sprite
};

#endif // SPRITE_H