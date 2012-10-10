/** \file   Level.cpp
 *  \brief  Implémente la classe Level
 */
#include "Level.h"

#include "../ErrorMessage.h"
#include "../TMXLoader.h"


/**
 * Constructeur de Level
 */
Level::Level()
{
	tileset = new Tileset();

	// Nombre de tiles par surface en cache
	nbTileCache.w = 25;
	nbTileCache.h = 25;
} // Level

/**
 * Destructeur de Level
 */
Level::~Level()
{
	// Libére le ground
    for(int x=0; x<levelSize.w; x++)
		delete ground[x];
	delete ground;

	// Libére le cache
    for(int x=0; x<cacheSize.w; x++)
		delete cache[x];
	delete cache;
} // ~Player


/**
 * Charge un niveau
 *
 * @param name		Nom du niveau
 */
void Level::load(string name)
{
	SDL_Rect positionBlit;
	positionBlit.x = 0;
	positionBlit.y = 0;
	
	TMXLoader* tmxLoader = new TMXLoader();
    tmxLoader->loadDocument(name.c_str());

	// Taille des tiles
	SDL_Rect tileSize;
	tileSize.w = tmxLoader->getTileWidth();
	tileSize.h = tmxLoader->getTileHeight();

	// Taille du niveau
	levelSize.w = tmxLoader->getNumMapColumns();
	levelSize.h = tmxLoader->getNumMapRows();

	// Chargement du tileset
	tileset->load(tmxLoader->getTilesetPath(), tileSize);

	// Layer du sol
	vector<vector<int>> layerData = tmxLoader->getLayerData();

	// Allocation de la mémoire pour le niveau
	ground = new int* [levelSize.w];
	for(int x=0; x<levelSize.w; x++) {
		ground[x] = new int[levelSize.h];
		for(int y=0; y<levelSize.h; y++) {
			ground[x][y] = layerData[x][y];
		}
	}

	// Préparation du cache
	cacheSize.w = (int)floor((double)levelSize.w / nbTileCache.w);
	cacheSize.h = (int)floor((double)levelSize.h / nbTileCache.h);

	cache = new SDL_Surface** [cacheSize.w];
	for(int x=0; x<cacheSize.w; x++) {
		cache[x] = new SDL_Surface*[cacheSize.h];
		for(int y=0; y<cacheSize.h; y++) {
			cache[x][y] = NULL;
		}
	}
}


/**
 * Indique si une position est bloquée ou non
 *
 * @param x		Coordonnée en x sur la map
 * @param y		Coordonnée en y sur la map
 *
 * @return		True si bloqué, false sinon
 */
bool Level::isBlocked(float x, float y)
{
	// Position en tile
	int caseX = (int)floor(x / getTileWidth());
	int caseY = (int)floor(y / getTileHeight());
	
	// Dépassement négatif
	while(caseX < 0)
		caseX += getNbCaseWidth();
	while(caseY < 0)
		caseY += getNbCaseHeight();

	// Dépassement positif
	caseX %= getNbCaseWidth();
	caseY %= getNbCaseHeight();

	return tileset->isBlockingTile(getCaseType(caseX, caseY));
}


/**
 * Affiche le niveau sur la surface donnée
 *
 * @param screen		Surface sur laquelle afficher le niveau
 * @param center		Position du centre de la surface sur la map
 */
void Level::draw(SDL_Surface* screen, SDL_Rect center)
{
	// Coin supérieur gauche
	SDL_Rect upperLeftBorder;
	upperLeftBorder.x = center.x - (screen->w / 2);
	upperLeftBorder.y = center.y - (screen->h / 2);
	
	// Coin inférieur droit
	SDL_Rect bottomRightBorder;
	bottomRightBorder.x = center.x + (screen->w / 2);
	bottomRightBorder.y = center.y + (screen->h / 2);
	
	// Premier groupe de case
	SDL_Rect firstCase;
	firstCase.x = (int)floor((double)upperLeftBorder.x / getTileWidth());
	firstCase.y = (int)floor((double)upperLeftBorder.y / getTileHeight());
	firstCase.x = (int)floor((double)firstCase.x / nbTileCache.w);
	firstCase.y = (int)floor((double)firstCase.y / nbTileCache.h);
	
	// Dernier groupe de case
	SDL_Rect lastCase;
	lastCase.x = (int)ceil((double)bottomRightBorder.x / getTileWidth());
	lastCase.y = (int)ceil((double)bottomRightBorder.y / getTileHeight());
	lastCase.x = (int)ceil((double)lastCase.x / nbTileCache.w);
	lastCase.y = (int)ceil((double)lastCase.y / nbTileCache.h);

	// Affichage des cases
	for(int x=firstCase.x; x<=lastCase.x; x++) {
		for(int y=firstCase.y; y<=lastCase.y; y++) {
			// Position ou l'on affiche la case
			SDL_Rect blitPosition;
			blitPosition.x = (x * nbTileCache.w * getTileWidth()) - upperLeftBorder.x;
			blitPosition.y = (y * nbTileCache.h * getTileHeight()) - upperLeftBorder.y;
			
			SDL_BlitSurface(getCacheSurface(x, y), NULL, screen, &blitPosition);
		}
	}
}


/**
 * Donne la surface représentant la zone demandée
 * Une zone de taille "cacheGroupSize"
 *
 * @param x		Absice de la zone
 * @param y		Ordonnée de la zone
 *
 * @return		Surface voulue
 */
SDL_Surface* Level::getCacheSurface(int cacheX, int cacheY)
{
	// Dépassement négatif
	while(cacheX < 0)
		cacheX += cacheSize.w;
	while(cacheY < 0)
		cacheY += cacheSize.h;
	
	// Dépassement positif
	while(cacheX >= cacheSize.w)
		cacheX -= cacheSize.w;
	while(cacheY >= cacheSize.h)
		cacheY -= cacheSize.h;

	// Si la zone existe
	if(cache[cacheX][cacheY])
		return cache[cacheX][cacheY];

	// Premiére case
	SDL_Rect first;
	first.x = (cacheX * nbTileCache.w);
	first.y = (cacheY * nbTileCache.h);

	// Deriére case
	SDL_Rect last;
	last.x = first.x + nbTileCache.w;
	last.y = first.y + nbTileCache.h;

	// Crée la surface
	cache[cacheX][cacheY] = SDL_CreateRGBSurface(
			SDL_HWSURFACE, 
			nbTileCache.w * tileset->getTileWidth(),
			nbTileCache.h * tileset->getTileHeight(),
			32, 0, 0, 0, 0
	);
	
	// Colle les tiles sur la surface
	for(int x=first.x; x<last.x; x++) {
		for(int y=first.y; y<last.y; y++) {
			// Position ou l'on affiche la case
			SDL_Rect blitPosition;
			blitPosition.x = ((x - first.x) * getTileWidth());
			blitPosition.y = ((y - first.y) * getTileHeight());

			int caseType = getCaseType(x, y);
			SDL_BlitSurface(
					getCaseSurface(caseType), NULL,
					cache[cacheX][cacheY], &blitPosition
			);
		}
	}

	return cache[cacheX][cacheY];
}


// Accesseur
/**
 * Donne une tile voulue
 *
 * @param id	Id de la tile
 *
 * @return		Tileset du niveau
 */
Tile Level::getTile(int id) const
{
	return tileset->getTile(id);
}


/**
 * Donne la surface correspondant aux coordonées de case données
 *
 * @param x		Absice de la case
 * @param y		Ordonnée de la case
 *
 * @return		Type de la case
 */
int Level::getCaseType(int x, int y) const
{
	// Dépassement négatif
	while(x < 0)
		x += getNbCaseWidth();
	while(y < 0)
		y += getNbCaseHeight();

	// Dépassement positif
	x %= levelSize.w;
	y %= levelSize.h;
	
	return ground[x][y];
}


/**
 * Donne la surface du type de case
 *
 * @param type	Type de la case
 *
 * @return		Surface de la case
 */
SDL_Surface* Level::getCaseSurface(int type) const
{
	return tileset->getTileSurface(type);
}


/**
 * Donne le nombre de cases sur la largeur
 *
 * @return		Nombre de cases sur la largeur
 */
int Level::getNbCaseWidth() const
{
	return levelSize.w;
}


/**
 * Donne le nombre de cases sur la hauter
 *
 * @return		Nombre de cases sur la hauter
 */
int Level::getNbCaseHeight() const
{
	return levelSize.h;
}


/**
 * Donne la largeur des tiles
 *
 * @return		Largeur des tiles
 */
int Level::getTileWidth() const
{
	return tileset->getTileWidth();
}


/**
 * Donne la hauteur des tiles
 *
 * @return		Hauteur des tiles
 */
 int Level::getTileHeight() const
{
	return tileset->getTileHeight();
}
