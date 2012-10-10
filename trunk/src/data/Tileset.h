/** \file   Tileset.h
 *  \brief  Définit la classe Tileset
 */
#ifndef TILESET_H
#define TILESET_H

#include <map>
#include <SDL/SDL_image.h>

#include "../tinyxml/tinyxml.h"
#include "tile.h"

using namespace std;


/** \class  Tileset
 *  \brief  Classe permettant la gestion d'un tileset
 *
 * Gére les surfaces concernant chaque tiles ainsi que leurs propriétés
 */
class Tileset :
	public TiXmlVisitor
{
    public:
        Tileset();
        virtual ~Tileset();

		// Callback de TinyXML
		virtual bool VisitEnter  (const TiXmlDocument  &) { return true; }
        virtual bool VisitExit (const TiXmlDocument &) { return true; }
        virtual bool VisitExit (const TiXmlElement &) { return true; }
		virtual bool Visit (const TiXmlDeclaration &) { return true; }
        virtual bool Visit (const TiXmlText &) { return true; }
        virtual bool Visit (const TiXmlComment &) { return true; }
        virtual bool Visit (const TiXmlUnknown &) { return true; }
		
        virtual bool VisitEnter (const TiXmlElement &, const TiXmlAttribute *);

		bool load(string filename, SDL_Rect tileSize);
        bool loadConfig(string filename);

		SDL_Rect getPositionOnTileset(int type) const;

		// Accesseur
		Tile getTile(int id) const;
		SDL_Surface* getTileSurface(int id) const;
		int getTileWidth() const;
		int getTileHeight() const;
		bool isBlockingTile(int id) const;
    protected:
    private:
		SDL_Surface* image;
		int nbTileOnWidth;
		int nbTileOnHeight;
		
		SDL_Rect tileSize;
		Tile* l_tiles;
};

#endif // TILESET_H