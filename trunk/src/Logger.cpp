/** \file   Logger.cpp
 *  \brief  Implémente la classe Logger
 */
#include "Logger.h"

#include <time.h>

ofstream Logger::outputFile;
SDL_mutex* Logger::lock;


/**
 * Fonction permettant d'afficher un message de debugage
 *
 * @param message       Message
 * @param level         Importance du message
 */
void Logger::log(
		string file, int line, string fucntion, 
		string message, EnumLogLevel level)
{
#ifdef _DEBUG
	// Création du mutex
	if(lock == NULL)
		lock = SDL_CreateMutex();
	
	SDL_LockMutex(lock);

	// Ouverture du fichier
	if(!outputFile.is_open())
		outputFile.open("log.txt", ios::out);

	outputFile << "(" << clock() << ")";
	
	// Message personnalisé en fonction du niveau d'erreur
    if(level == WARNING)
        outputFile << " <WARNING>";
    else if(level == ERROR) {
		int pos = file.find("\\src\\");
		if (pos != string::npos)
			file = file.substr(pos+5);
		
        outputFile << " <-ERROR-> " << file << ":" << line;
        cerr << " <-ERROR-> " << file << ":" << line << " : (" << fucntion << ") " << message << endl;
	}

    outputFile << " : (" << fucntion << ") " << message << endl;

	SDL_UnlockMutex(lock);
#endif
} // log


/**
 * Ferme le stream sur lequel on sort les messages
 */
void Logger::close()
{
	SDL_DestroyMutex(lock);

	if(outputFile.is_open())
		outputFile.close();
} // close