/** \file   common.h
 *  \brief  D�finit plusieurs fonctons et �num�rations
 *          utile dans tout le programme.
 */
#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <map>

#define PI			3.14159265
#define NB_WEAPON	2
#define NB_AMMO		1

using namespace std;


/** \enum   EnumModuleId
 *  \brief  Contient les identifiants des diff�rents modules.
 */
enum EnumModuleId {
    CORE, RENDER, INPUT, LOGIC, IA
};

/** \enum   EnumWeaponId
 *  \brief  Contient les diff�rentes armes.
 */
enum EnumWeaponId {
    SPANNER, KNIFE
};

/** \enum   EnumAmmoId
 *  \brief  Contient les diff�rentes munitions.
 */
enum EnumAmmoId {
    KNIFE_AMMO
};

#endif // COMMON_H
