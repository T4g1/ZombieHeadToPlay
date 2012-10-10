/** \file   Tile.cpp
 *  \brief  Impl�mente la classe Tile
 */
#include "Tile.h"


/**
 * Constructeur de Tile
 */
Tile::Tile()
{
	image = NULL;
	block = false;
} // Tile

/**
 * Destructeur d'un Tile
 */
Tile::~Tile()
{
	SDL_FreeSurface(image);
} // ~Tile