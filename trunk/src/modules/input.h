/** \file   Input.h
 *  \brief  D�finit la classe Input
 */
#ifndef INPUT_H
#define INPUT_H

#include <SDL/SDL.h>

#include "Module.h"

using namespace std;

class Core;

/** \class  Input
 *  \brief  G�re toute la partie entr�es utilisateur
 *
 * D�tecte et g�re les interraction avec la fen�tre, le clavier ainsi que la souris
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