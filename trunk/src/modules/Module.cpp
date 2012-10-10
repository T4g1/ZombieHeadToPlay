/** \file   Module.cpp
 *  \brief  Implémente la classe Module
 */
#include "Module.h"

#include "../Core.h"


/**
 * Constructeur d'un module
 *
 * @param id                            Identifiant du module
 * @param name                          Nom du module
 * @param core                          Reference vers le Core du programme
 */
Module::Module(EnumModuleId id, string name, Core* core)
{
    LOG("Initialisation du module '" + name + "'");

    this->id = id;
    this->name = name;
    this->core = core;
	
    this->thread = NULL;

    core->registerModule(this);
} // Module

/**
 * Destructeur d'un module
 */
Module::~Module()
{
    // dtor
} // ~Module


/**
 * Lance le thread
 */
void Module::start() {
    if (thread)
		ERROR("Thread déjà lancé");

    thread = SDL_CreateThread(thread_runner, this);
} // start


/**
 * Attend la fin du thread
 */
void Module::wait() {
    if (thread == NULL)
		ERROR("Thread NULL");

    SDL_WaitThread(thread, NULL);
} // wait


// Accesseurs
/**
 * Donne l'identifiant du Module
 *
 * @return  Identifiant du Module
 */
EnumModuleId Module::getId()
{
    return id;
} // getId


/**
 * Donne le nom du Module.
 * Seulement utile pour le Logger.
 *
 * @return  Nom du Module
 */
string Module::getName()
{
    return name;
} // getName


/**
 * Donne un pointeur sur le thread
 *
 * @return          Pointeur sur le thread
 */
SDL_Thread* Module::getThread()
{
    return thread;
} // getThread


// Mutateurs
/**
 * Modifie le thread
 *
 * @param thread        Pointeur sur le thread
 */
void Module::setThread(SDL_Thread* thread)
{
    this->thread = thread;
} // setThread


/**
 * Permet de lancer le thread car SDL_CreateThread() n'accepte
 * pas de fonctions membres C++
 */
int thread_runner(void* data) { 
    reinterpret_cast<Module*>(data)->frame();

	return 0;
} // thread_runner