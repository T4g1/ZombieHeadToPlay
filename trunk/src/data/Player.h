/** \file   Player.h
 *  \brief  Implémente la classe Player
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL/SDL.h>

#include "Level.h"
#include "weapon/Weapon.h"
#include "ammo/Ammo.h"


/** \class  Player
 *  \brief  Classe gérant un joueur
 */
class Player
{
    public:
        Player();
        virtual ~Player();
		
		void walk(Level* level, bool up, bool down, bool left, bool right);
		bool isValidLocation(Level* level, float x, float y);

		// Accesseur
		SDL_Surface* getSprite() const;
		SDL_Surface* getRotatedSprite() const;
		SDL_Rect getPosition() const;
		int getOrientation() const;

		// Mutateur
		void updatePosition(SDL_Rect position);
		void updateOrientation(SDL_Rect mousePosition);
    protected:
    private:
		SDL_Surface* sprite;
		SDL_Surface* rotatedSprite;
		float x;
		float y;
		int orientation;

		// Déplacements du joueur
		float speed;
		int lastMove;

		// Gestion des armes
		Weapon** l_weapon;
		enum EnumWeaponId selectedWeapon;

		// Gestion des munitions
		Ammo** l_ammo;
};

#endif // PLAYER_H