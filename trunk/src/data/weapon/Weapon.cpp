/** \file   Weapon.cpp
 *  \brief  Implémente la classe Weapon
 */
#include "Weapon.h"


/**
 * Constructeur de Weapon
 */
Weapon::Weapon(string name)
{
	this->name = name;

	unlocked = false;
} // Weapon

/**
 * Destructeur de Weapon
 */
Weapon::~Weapon()
{
	// dtor
} // ~Weapon


// Accesseur
/**
 * Donne le nom du type de munition
 *
 * @return		Nom du type de munition
 */
string Weapon::getName() const
{
	return name;
}


/**
 * Indique si l'arme est débloquée ou non
 *
 * @return		true si l'arme est disponnible
 */
bool Weapon::isUnlocked() const
{
	return unlocked;
}