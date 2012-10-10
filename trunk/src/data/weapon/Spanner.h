/** \file   Spanner.h
 *  \brief  D�finit la classe Spanner
 */
#ifndef SPANNER_H
#define SPANNER_H

#include "Weapon.h"


/** \class  Spanner
 *  \brief  Sp�cifications de la cl� � molette
 */
class Spanner :
	public Weapon
{
    public:
        Spanner();
        virtual ~Spanner();
		
		void onPrimaryAttack();
		void onSecondaryAttack();
		void onSwitchAmmo();
    private:
    protected:
};

#endif // SPANNER_H