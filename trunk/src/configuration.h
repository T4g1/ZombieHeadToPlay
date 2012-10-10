/** \file   configuration.h
 *  \brief  Classe de gestion des configurations
 */
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <map>
#include <SDL/SDL_mutex.h>

using namespace std;

/** \class  Configuration
 *  \brief  Classe g�rant les fichiers de configuration 
 */
class Configuration 
{
    public:
	    Configuration(string ext);
	    ~Configuration();

	    //Fonctions pour charger le fichier
	    bool addFile(string filename);
	    bool reloadFile(string filename);

        //Acces � la map principale et � la sous map
	    static map<string, string> getProperties(string filename);

    private:
	    static SDL_mutex* lock;
	    string ext;
	    static map<string, map<string, string>> root_map;
	    bool loadPropertiesFile(string filename, map<string, string> &cur_map, char separator = '=');

};

#endif // CONFIGURATION_H