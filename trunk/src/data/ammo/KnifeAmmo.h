/** \file   KnifeAmmo.h
 *  \brief  Définit la classe KnifeAmmo
 */
#ifndef KNIFEAMMO_H
#define KNIFEAMMO_H

#include "Ammo.h"


/** \class  KnifeAmmo
 *  \brief  Munitions pour le couteau
 */
class KnifeAmmo :
	public Ammo
{
    public:
        KnifeAmmo();
        virtual ~KnifeAmmo();

		void onHit();
		void onEnd();
    private:
    protected:
};

#endif // KNIFEAMMO_H