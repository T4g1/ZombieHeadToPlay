/** \file   Weapon.h
 *  \brief  D�finit la classe Weapon
 */
#ifndef WEAPON_H
#define WEAPON_H

#include <string>

#include "../Ammo/Ammo.h"

using namespace std;


/** \class  Weapon
 *  \brief  Classe g�rant les types d'armes
 */
class Weapon
{
    public:
        Weapon(string name);
        virtual ~Weapon();
		
		virtual void onPrimaryAttack() = 0;
		virtual void onSecondaryAttack() = 0;
		virtual void onSwitchAmmo() = 0;

		// Accesseur
		string getName() const;
		bool isUnlocked() const;
    private:
    protected:
		string name;				// Nom de l'arme

		enum EnumAmmoId* l_ammo;	// Liste des munitions accept�e
		int selectedAmmo;			// Type de munition s�l�ctionn�

		bool unlocked;				// Si l'arme est disponnible
};

#endif // WEAPON_H