/** \file   Ammo.h
 *  \brief  Définit la classe Ammo
 */
#ifndef AMMO_H
#define AMMO_H

#include <string>

using namespace std;


/** \class  Ammo
 *  \brief  Classe gérant les types de munitions
 */
class Ammo
{
    public:
        Ammo(string name);
        virtual ~Ammo();
		
		virtual void onHit() = 0;
		virtual void onEnd() = 0;

		// Accesseur
		string getName() const;
		int getClipSize() const;
		float getSpeed() const;
		float getDammage() const;
		int getRange() const;
		int getDammageRadius() const;
    private:
    protected:
		string name;		// Nom du boulet

		int clipSize;		// Taille d'un chargeur
		float speed;		// Vitesse du boulet
		float dammage;		// Dégats provoqué
		
		int range;			// Portée du boulet
		int dammageRadius;	// Rayon des dégâts si dégâts de zone
};

#endif // AMMO_H