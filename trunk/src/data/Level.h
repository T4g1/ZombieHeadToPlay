/** \file   Level.h
 *  \brief  Définit la classe Level
 */
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <SDL/SDL_image.h>

#include "Tileset.h"
#include "Tile.h"

using namespace std;


/** \class  Level
 *  \brief  Classe gérant un niveau
 */
class Level
{
    public:
        Level();
        virtual ~Level();

		void load(string name);
		bool isBlocked(float x, float y);

		void draw(SDL_Surface* screen, SDL_Rect center);

		SDL_Surface* getCacheSurface(int x, int y);

		// Accesseur
		Tile getTile(int id) const;
		int getCaseType(int x, int y) const;
		SDL_Surface* getCaseSurface(int type) const;
		int getNbCaseWidth() const;
		int getNbCaseHeight() const;
		int getTileWidth() const;
		int getTileHeight() const;
    private:
    protected:
		Tileset* tileset;

		SDL_Rect levelSize;
		int** ground;

		// Mise en cache de la map
		SDL_Surface*** cache;
		SDL_Rect nbTileCache;
		SDL_Rect cacheSize;
};

#endif // LEVEL_H