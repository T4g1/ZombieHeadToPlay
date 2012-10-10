/** \file   Sprite.cpp
 *  \brief  Implémente la classe Sprite
 */
#include "Sprite.h"


/**
 * Constructeur de Sprite
 */
Sprite::Sprite(string filename)
{
	// Charge l'image du sprite
	image = IMG_Load(filename.c_str());
} // Sprite

/**
 * Destructeur d'un Sprite
 */
Sprite::~Sprite()
{
	// Libére la mémoire utilisée
	SDL_FreeSurface(image);
} // ~Sprite


// Accesseur
/**
 * Donne la surface du sprite
 *
 * @return		La surface du sprite
 */
SDL_Surface* Sprite::getSurface() const
{
	return image;
}