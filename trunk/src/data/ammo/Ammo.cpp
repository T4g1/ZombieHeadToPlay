/** \file   Ammo.cpp
 *  \brief  Implémente la classe Ammo
 */
#include "Ammo.h"


/**
 * Constructeur de Ammo
 */
Ammo::Ammo(string name)
{
	this->name = name;
} // Ammo

/**
 * Destructeur de Ammo
 */
Ammo::~Ammo()
{
	// dtor
} // ~Ammo


// Accesseur
/**
 * Donne le nom du type de munition
 *
 * @return		Nom du type de munition
 */
string Ammo::getName() const
{
	return name;
}


/**
 * Donne la taille d'un chargeur
 *
 * @return		Taille d'un chargeur
 */
int Ammo::getClipSize() const
{
	return clipSize;
}


/**
 * Donne la vitesse d'un boulet
 *
 * @return		Vitesse d'un boulet
 */
float Ammo::getSpeed() const
{
	return speed;
}


/**
 * Donne les dégâts provoqué par le boulet
 *
 * @return		Dégâts provoqué par le boulet
 */
float Ammo::getDammage() const
{
	return dammage;
}


/**
 * Donne la portée du boulet
 *
 * @return		Portée du boulet
 */
int Ammo::getRange() const
{
	return range;
}


/**
 * Donne le rayon des dégâts si dégâts de zone
 *
 * @return		Rayon des dégâts si dégâts de zone
 */
int Ammo::getDammageRadius() const
{
	return dammageRadius;
}