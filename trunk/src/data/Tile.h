/** \file   Tile.h
 *  \brief  Définit la classe Tile
 */
#ifndef TILE_H
#define TILE_H

#include <SDL/SDL.h>

using namespace std;


/** \class  Tile
 *  \brief  Classe stockant les informations d'une tile
 */
class Tile
{
    public:
        Tile();
        virtual ~Tile();

		bool block;
		SDL_Surface* image;
};

#endif // TILE_H