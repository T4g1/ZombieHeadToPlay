/** \file   main.cpp
 *  \brief  Instancie le Core et les Module
 */
#include <iostream>
#include <SDL/SDL.h>

#include "Core.h"

#include "modules/Ai.h"
#include "modules/Render.h"
#include "modules/Logic.h"
#include "modules/Input.h"
#include "common.h"
#include "configuration.h"
#include "jsmn.h"
#include "color.h"

using namespace std;

int main(int argc, char *argv[])
{
	//Chargement des fichiers de configuration
	Configuration configuration(".cfg");
	configuration.addFile("game");

    // Déclaration du core
    Core core;

    // Déclaration des modules
    //AiEngine			ai(&core);
    Logic logic(&core);
    Input input(&core);
    Render render(&core);

    try {
        core.run();
    } catch(ErrorMessage& e) {
		e.what();
    }

	// Fermeture du Logger
	Logger::close();
	
    return EXIT_SUCCESS;
} // main