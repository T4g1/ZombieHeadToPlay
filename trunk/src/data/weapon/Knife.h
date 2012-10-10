/** \file   Knife.h
 *  \brief  D�finit la classe Knife
 */
#ifndef KNIFE_H
#define KNIFE_H

#include "Weapon.h"


/** \class  Knife
 *  \brief  Sp�cifications du couteau de cuisine
 */
class Knife :
	public Weapon
{
    public:
        Knife();
        virtual ~Knife();
		
		void onPrimaryAttack();
		void onSecondaryAttack();
		void onSwitchAmmo();
    private:
    protected:
};

#endif // KNIFE_H