/** \file   Ammo.h
 *  \brief  D�finit la classe Ammo
 */
#ifndef AMMO_H
#define AMMO_H

#include <string>

using namespace std;


/** \class  Ammo
 *  \brief  Classe g�rant les types de munitions
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
		float dammage;		// D�gats provoqu�
		
		int range;			// Port�e du boulet
		int dammageRadius;	// Rayon des d�g�ts si d�g�ts de zone
};

#endif // AMMO_H