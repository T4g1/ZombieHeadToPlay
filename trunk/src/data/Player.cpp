/** \file   Player.cpp
 *  \brief  Implémente la classe Player
 */
#include "Player.h"

#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

#include "../configuration.h"
#include "../common.h"

#include "weapon/Spanner.h"
#include "weapon/Knife.h"

#include "ammo/KnifeAmmo.h"


/**
 * Constructeur de Player
 *
 * @param screenSize		Taille de l'écran
 */
Player::Player()
{
	orientation = 0;

	sprite = IMG_Load("media/sprites/player.png");
	rotatedSprite = rotozoomSurface(sprite, orientation, 1.0, 1);

	// Position de départ
	x = 0;
	y = 0;

	// Déplacements
	speed = 0.15f;
	lastMove = SDL_GetTicks();

	// Gestion des armes
	selectedWeapon = SPANNER;

	// Armes
	l_weapon = new Weapon* [NB_WEAPON];
	l_weapon[SPANNER] = new Spanner();
	l_weapon[KNIFE] = new Knife();

	// Munitions
	l_ammo = new Ammo* [NB_AMMO];
	l_ammo[KNIFE_AMMO] = new KnifeAmmo();
} // Player

/**
 * Destructeur de Player
 */
Player::~Player()
{
	// Libére l'espace alloué pour les images
    SDL_FreeSurface(sprite);
	SDL_FreeSurface(rotatedSprite);

	// Libére l'espace alloué pour les armes
	for(int i=0; i<NB_WEAPON; i++)
		delete l_weapon[i];
	delete l_weapon;
} // ~Player


/**
 * Déplace le joueur
 *
 * @param up		Deplacement vers le haut
 * @param down		Deplacement vers le bas
 * @param left		Deplacement vers la gauche
 * @param right		Deplacement vers le droite
 */
void Player::walk(Level* level, bool up, bool down, bool left, bool right)
{
	// Temp de déplacement
	int now = SDL_GetTicks();
	int deltaTime = now - lastMove;

	// Si on se déplace en diagonale
	float factor = 1;
	if((up ^ down) && (right ^ left))
		factor = 0.7f; // racine de 2 sur 2 (cos 45°)

	// Distance parcourue
	float distance = deltaTime * (speed * factor);

	// Nouvelle position
	float newPositionX = x;
	float newPositionY = y;
	
	if(up)
		newPositionY -= distance;
	if(down)
		newPositionY += distance;
	if(left)
		newPositionX -= distance;
	if(right)
		newPositionX += distance;
	
	int maxValueX = level->getNbCaseWidth() * level->getTileWidth();
	int maxValueY = level->getNbCaseHeight() * level->getTileHeight();

	// Corrige les valeurs de newPosition trop petites
	while(newPositionX < 0)
		newPositionX += maxValueX;
	while(newPositionY < 0)
		newPositionY += maxValueY;
	
	// Corrige les valeurs de newPosition trop grandes
	while(newPositionX >= maxValueX)
		newPositionX -= maxValueX;
	while(newPositionY >= maxValueY)
		newPositionY -= maxValueY;

	// Verifie les collisions avec la map
	if(isValidLocation(level, newPositionX, y))
		x = newPositionX;
	if(isValidLocation(level, x, newPositionY))
		y = newPositionY;

	lastMove = SDL_GetTicks();
}


/**
 * Indique si la position du joueur est valide
 *
 * @param level		Niveau sur lequel on se trouve
 * @param x			Position à tester en x
 * @param y			Position à tester en y
 *
 * @return			True si valide, False sinon
 */
bool Player::isValidLocation(Level* level, float x, float y)
{
	// On ne prend que 90% de la taille rééle pour être plus 'permissif'
	int w = (int)((sprite->w / 2) * 0.90);
	int h = (int)((sprite->h / 2) * 0.90);
	
	if(level->isBlocked(x - w, y - h))
		return false;
	if(level->isBlocked(x - w, y + h))
		return false;
	if(level->isBlocked(x + w, y - h))
		return false;
	if(level->isBlocked(x + w, y + h))
		return false;

	return true;
}


// Accesseur
/**
 * Récupére le sprite du joueur
 *
 * @return		Pointeur sur l'image représentant le joueur
 */
SDL_Surface* Player::getSprite() const
{
	return sprite;
}


/**
 * Récupére le sprite du joueur bien orienté
 *
 * @return		Pointeur sur l'image représentant le joueur orienté
 */
SDL_Surface* Player::getRotatedSprite() const
{
	return rotatedSprite;
}


/**
 * Donne la position du joueur
 *
 * @return		Position du joueur
 */
SDL_Rect Player::getPosition() const
{
	SDL_Rect position;
	position.x = (int)x;
	position.y = (int)y;

	return position;
}


/**
 * Donne l'orientation du joueur
 *
 * @return		Orientation du joueur
 */
int Player::getOrientation() const
{
	return orientation;
}


// Mutateur
/**
 * Met a jour la position du joueur
 *
 * @param position			Nouvelle position
 */
void Player::updatePosition(SDL_Rect position)
{
	x = position.x;
	y = position.y;
}


/**
 * Met a jour l'orientation du joueur
 *
 * @param mousePosition		Position de la souris
 */
void Player::updateOrientation(SDL_Rect mousePosition)
{
	// Taille de l'ecran
	SDL_Rect screenSize;
	screenSize.w = atoi(Configuration::getProperties("game")["width"].c_str());
	screenSize.h = atoi(Configuration::getProperties("game")["height"].c_str());

	// Calcul le centre de l'ecran (ou l'on affiche le joueur)
	SDL_Rect center;
	center.x = screenSize.w / 2;
	center.y = screenSize.h / 2;

	// Calcul la position réele de la souris
	SDL_Rect realMousePosition;
	realMousePosition.x = mousePosition.x - center.x;
	realMousePosition.y = mousePosition.y - center.y;

	// Calcul de l'orientation du vecteur
	orientation = (int)(
			-atan2((double)realMousePosition.y,
			(double)realMousePosition.x) * 180 / PI
	);

	// Met a jour le sprite
	if(rotatedSprite)
		SDL_FreeSurface(rotatedSprite);
	rotatedSprite = rotozoomSurface(sprite, orientation, 1.0, 1);
}