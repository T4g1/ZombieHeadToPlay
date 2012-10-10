/** \file   Input.h
 *  \brief  Définit la classe Input
 */
#ifndef INPUT_H
#define INPUT_H

#include <SDL/SDL.h>

#include "Module.h"

using namespace std;

class Core;

/** \class  Input
 *  \brief  Gére toute la partie entrées utilisateur
 *
 * Détecte et gére les interraction avec la fenêtre, le clavier ainsi que la souris
 */
class Input :
    public Module
{
    public:
		Input(Core* core);
		~Input();

        void frame();
    protected:
    private:
};

#endif // INPUT_H