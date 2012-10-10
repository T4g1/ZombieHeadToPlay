/** \file   Core.h
 *  \brief  D�finit la classe Core
 */
#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <map>
#include <SDL/SDL_mutex.h>

#include "common.h"
#include "ErrorMessage.h"
#include "Logger.h"

#include "states/State.h"

using namespace std;

class Module;


/** \class  Core
 *  \brief  G�re les interactions entre les diff�rents Module
 *
 * Enregistre tout les Module lors de leurs d�finition et leurs fournit
 * diff�rentes m�thodes leurs permettant de s'envoyer des messages et des
 * donn�es.
 */
class Core
{
    public:
        Core();
        virtual ~Core();

        void run();
        void registerModule(Module* module);

		// Mutateurs
		void stop();

		// Accesseurs
		bool isRunning();
		Logic* getLogic();
		State* currentState();
    protected:
    private:
        map<EnumModuleId, Module*>  l_module;

		SDL_mutex* lock;
		
		bool running;
};

#endif // CORE_H
