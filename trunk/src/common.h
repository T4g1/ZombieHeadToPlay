/** \file   common.h
 *  \brief  Définit plusieurs fonctons et énumérations
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
 *  \brief  Contient les identifiants des différents modules.
 */
enum EnumModuleId {
    CORE, RENDER, INPUT, LOGIC, IA
};

/** \enum   EnumWeaponId
 *  \brief  Contient les différentes armes.
 */
enum EnumWeaponId {
    SPANNER, KNIFE
};

/** \enum   EnumAmmoId
 *  \brief  Contient les différentes munitions.
 */
enum EnumAmmoId {
    KNIFE_AMMO
};

#endif // COMMON_H
