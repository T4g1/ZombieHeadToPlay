/** \file   KnifeAmmo.cpp
 *  \brief  Impl�mente la classe KnifeAmmo
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
 * Fonction appell�e lorsque le boulet touche quelque chose
 */
void KnifeAmmo::onHit()
{
} // onHit


/**
 * Fonction appell�e lorsque le boulet atteint la fin de sa course
 */
void KnifeAmmo::onEnd()
{
} // onEnd