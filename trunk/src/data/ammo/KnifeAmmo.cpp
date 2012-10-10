/** \file   KnifeAmmo.cpp
 *  \brief  Implémente la classe KnifeAmmo
 */
#include "KnifeAmmo.h"


/**
 * Constructeur de KnifeAmmo
 */
KnifeAmmo::KnifeAmmo() :
	Ammo("Couteau")
{
	// ctor
} // KnifeAmmo

/**
 * Destructeur de KnifeAmmo
 */
KnifeAmmo::~KnifeAmmo()
{
	// dtor
} // ~KnifeAmmo


/**
 * Fonction appellée lorsque le boulet touche quelque chose
 */
void KnifeAmmo::onHit()
{
} // onHit


/**
 * Fonction appellée lorsque le boulet atteint la fin de sa course
 */
void KnifeAmmo::onEnd()
{
} // onEnd