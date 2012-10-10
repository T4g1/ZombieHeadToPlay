/** \file   Tileset.cpp
 *  \brief  Implémente la classe Tileset
 */
#include "Tileset.h"

#include <string>


/**
 * Constructeur de Tileset
 */
Tileset::Tileset()
{
	l_tiles = NULL;
	image = NULL;

	nbTileOnWidth = 0;
	nbTileOnHeight = 0;
	
	tileSize.w = 0;
	tileSize.h = 0;
} // Tileset

/**
 * Destructeur d'un Tileset
 */
Tileset::~Tileset()
{
	SDL_FreeSurface(image);
} // ~Tileset


/**
 * Entrée dans un noeud du document de config des tiles
 *
 * @param		Géré par tinyXML
 */
bool Tileset::VisitEnter(const TiXmlElement &elem, const TiXmlAttribute *attrib)
{
    if (string("tile") == elem.Value()) {
		int id, block;

        elem.Attribute("id", &id);
        elem.Attribute("block", &block);

		l_tiles[id].block = (block == 1);
    }

    return true;
}


/**
 * Charge le tileset donné
 *
 * @param filename		Nom de l'image correspondant au tileset
 * @param tileSize		Taille des tiles
 *
 * @return				False si erreur
 */
bool Tileset::load(string filename, SDL_Rect tileSize)
{
	this->tileSize.w = tileSize.w;
	this->tileSize.h = tileSize.h;

	// Chargement de l'image
	image = IMG_Load(filename.c_str());
	if(image == NULL)
		return false;

	// Caclul du nombre de tiles
	nbTileOnWidth = image->w / tileSize.w;
	nbTileOnHeight = image->h / tileSize.h;

	l_tiles = new Tile[nbTileOnWidth * nbTileOnHeight];

	SDL_Rect positionBlit;
	positionBlit.x = 0;
	positionBlit.y = 0;
	
	// Crée les surfaces de chaque tiles
	for(int x=0; x<nbTileOnWidth; x++) {
		for(int y=0; y<nbTileOnHeight; y++) {
			int id = (y * nbTileOnWidth) + x;

			SDL_Rect positionOnTileset = getPositionOnTileset(id);

			// Crée la surface
			l_tiles[id].image = SDL_CreateRGBSurface(
					SDL_HWSURFACE, tileSize.w, tileSize.h, 
					32, 0, 0, 0, 0
			);

			// Place l'image dedans
			SDL_BlitSurface(image, &positionOnTileset, l_tiles[id].image, &positionBlit);
		}
	}

	// Charge le fichier de config
	filename.append(".cfg");
	return loadConfig(filename);
}


/**
 * Charge un document précis
 *
 * @param filename		Nom du fichier de config de tileset que l'on doit charger
 *
 * @return				False si erreur
 */
bool Tileset::loadConfig(string filename)
{
    TiXmlDocument doc(filename.c_str());

    if(!doc.LoadFile())
		return false;

    doc.Accept(this);

    return true;
}


/**
 * Donne les coordonées du type de case sur le tileset
 *
 * @param type	Type de la case
 *
 * @return		Position sur le tileset
 */
SDL_Rect Tileset::getPositionOnTileset(int type) const
{
	SDL_Rect position;
	position.x = (type % nbTileOnWidth) * tileSize.w;
	position.y = (type / nbTileOnWidth) * tileSize.h;
	
	position.w = tileSize.w;
	position.h = tileSize.h;

	return position;
}


// Accesseur
/**
 * Donne une tile voulue
 *
 * @param id	Id de la tile
 *
 * @return		Tileset du niveau
 */
Tile Tileset::getTile(int id) const
{
	return l_tiles[id];
}


/**
 * Donne la largeur d'une tile
 *
 * @param id	Id de la tile
 *
 * @return		Largeur d'une tile
 */
SDL_Surface* Tileset::getTileSurface(int id) const
{
	return l_tiles[id].image;
}


/**
 * Donne la largeur d'une tile
 *
 * @return		Largeur d'une tile
 */
int Tileset::getTileWidth() const
{
	return tileSize.w;
}


/**
 * Donne la hauteur d'une tile
 *
 * @return		Hauteur d'une tile
 */
int Tileset::getTileHeight() const
{
	return tileSize.h;
}


/**
 * Indique si une tile bloque le joueur ou non
 *
 * @param id		Id de la tile
 *
 * @return			True si la tile bloque
 */
bool Tileset::isBlockingTile(int id) const
{
	return l_tiles[id].block;
}