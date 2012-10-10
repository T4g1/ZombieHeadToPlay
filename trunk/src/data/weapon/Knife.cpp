/** \file   Knife.cpp
 *  \brief  Implémente la classe Knife
 */
#include "Knife.h"


/**
 * Constructeur de Knife
 */
Knife::Knife() :
	Weapon("Couteau de cuisine")
{
	// ctor
} // Knife

/**
 * Destructeur de Knife
 */
Knife::~Knife()
{
	// dtor
} // ~Knife


/**
 * Attaque principale
 */
void Knife::onPrimaryAttack()
{
}


/**
 * Attaque secondaire
 */
void Knife::onSecondaryAttack()
{
}


/**
 * Changement de munition
 */
void Knife::onSwitchAmmo()
{
}