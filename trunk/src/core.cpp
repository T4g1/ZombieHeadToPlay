/** \file   Core.cpp
 *  \brief  Implémente la classe Core
 */
#include "Core.h"

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_ttf.h>
#include "modules/Module.h"
#include "modules/Logic.h"


/**
 * Constructeur de Core
 */
Core::Core()
{
    LOG("Initialisation du Core");

	SDL_Init(SDL_INIT_VIDEO);
	if(TTF_Init() == -1) ERROR("Cannot initialize SDL_ttf");

	lock = SDL_CreateMutex();
	running = false;
} // Core

/**
 * Destructeur de Core
 */
Core::~Core()
{
    SDL_DestroyMutex(lock);
	TTF_Quit();
	SDL_Quit();
} // ~Core


/**
 * Fonction appellée après l'enregistrement de tout les modules.
 * Lance les thread et attend leurs fin
 */
void Core::run()
{
    map<EnumModuleId, Module*>::iterator iteratorModule;
	running = true;

    // Lance les thread
    for(iteratorModule = l_module.begin();
        iteratorModule != l_module.end();
        iteratorModule++)
    {
        Module* module = iteratorModule->second;

		// La gestion des événements doit se faire dans le thread principal
		if(module->getId() == INPUT)
			continue;

        string name = module->getName();

        LOG("Lancement du thread '" + name + "'");
        module->start();
    }
	
	l_module[INPUT]->frame();
	
    // Attend la fin des thread
    LOG("Attente de la fin des thread ...");
    for(iteratorModule = l_module.begin();
        iteratorModule != l_module.end();
        iteratorModule++)
    {
        Module* module = iteratorModule->second;

		if(module->getId() == INPUT)
			continue;
			
		module->wait();
    }

    LOG("Tout les thread sont termine");
    LOG("Fermeture de l'application");
	
	//throw ERROR("Exception de test");
} // run


/**
 * Fonction permettant d'enregistrer un module dans le core
 *
 * @param module       Module que l'on souhaite enregistrer
 */
void Core::registerModule(Module* module)
{
    LOG("Enregistrement du module '" + module->getName() + "'");
    l_module[module->getId()] = module;
} // registerModule

// Mutateurs
/**
 * Indique que l'application doit se terminer
 */
void Core::stop()
{
	SDL_LockMutex(lock);
	running = false;
	SDL_UnlockMutex(lock);
} // stop

// Accesseurs
/**
 * Permet de savoir si l'application doit tourner ou non
 *
 * @return		True si l'application tourne
 */
bool Core::isRunning()
{
	SDL_LockMutex(lock);
	bool temp = running;
	SDL_UnlockMutex(lock);

	return temp;
} // isRunning


/**
 * Donne un pointeur sur le module logique
 *
 * @return		True si l'application tourne
 */
Logic* Core::getLogic()
{
	return ((Logic*)l_module[LOGIC]);
} // getLogic


/**
 * Donne un pointeur sur l'état courant
 *
 * @retrun		Pointeur sur l'état du jeu actuel
 */
State* Core::currentState()
{
	return ((Logic*)l_module[LOGIC])->currentState();
} // currentState