/** \file   Module.h
 *  \brief  Définit la classe Module
 */
#ifndef MODULE_H
#define MODULE_H

#include <map>
#include <queue>
#include <SDL/SDL_thread.h>

#include "../common.h"
#include "../Logger.h"

using namespace std;

class Core;
class Data;


/** \class  Module
 *  \brief  Classe mére de tout les module du jeu.
 *
 * Définit les composants de base de chaque module.
 * Fournit une interface permettant au Core d'envoyer des messages
 * vers n'importe quel module.
 */
class Module
{
    public:
        Module(EnumModuleId id, string name, Core* core);
        virtual ~Module();
		
        // Boucle principale de chaque module
        virtual void frame() = 0;
		
		void start();
		void wait();

        // Accesseurs
        EnumModuleId getId();
        string getName();
        SDL_Thread* getThread();

        // Mutateurs
        void setThread(SDL_Thread* thread);
    private:
    protected:
        EnumModuleId id;
        string name;
        Core* core;

		SDL_Thread* thread;
	friend int thread_runner(void*);
};

#endif // MODULE_H
