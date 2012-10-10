/** \file   configuration.cpp
 *  \brief  Implémente la classe configuration
 */
#include "configuration.h"
#include <fstream>
#include <sstream>
#include "ErrorMessage.h"
#include <iostream>
using namespace std;


SDL_mutex* Configuration::lock;
map<string, map<string, string>> Configuration::root_map;


/**
 * Constructeur de Configuration
 *
 * @param ext		Extension du fichier
 */
Configuration::Configuration(string ext) {
	//ext = extension du fichier de configuration
	this->ext = ext;
	//Création du mutex
	lock = SDL_CreateMutex();
}

/**
 * Destructeur de Configuration
 */
Configuration::~Configuration() {
	//Destruction du mutex
	SDL_DestroyMutex(lock);
}

/**
 * Charge le fichier de configuration dans la map
 *
 * @param filename		Nom du fichier
 * @return		        Booléenne Vrai si réussi, Faux si échoué
 */
bool Configuration::addFile(string filename) {
	//On vérouille le mutex
	SDL_LockMutex(lock);
	bool ret = true;
	try {
		map<string, string> cur_map;
        //On apelle la fonction ouvrant le fichier et donnant le couple clé-valeur
		if(!loadPropertiesFile(filename + ext, cur_map))
            throw ERROR("File not found: " + filename + ext);
        //Si pas d'erreur, on assigne la map principale avec la map obtenue avec le fichier
		root_map[filename] = cur_map;
	} catch(ErrorMessage& e) {
		e.what();
		ret = false;
	}
    //On déverouille le mutex
	SDL_UnlockMutex(lock);
	return ret;
}

/**
 * Recharge le fichier de configuration dans la map
 *
 * @param filename		Nom du fichier
 * @return		        Booléenne Vrai si réussi, Faux si échoué
 */
bool Configuration::reloadFile(string filename) {
	return addFile(filename);
}

/**
 * Récupère les couples clé-valeur du fichier de configuration
 *
 * @param filename		Nom du fichier
 * @return		        la map contenant les couples clé-valeur
 */
map<string, string> Configuration::getProperties(string filename) {
    //On vérouille le mutex
	SDL_LockMutex(lock);
    //On consulte la map principale pour récupérer 
    //  toutes les clé-valeur du fichier chargé précédemment
	map<string, string> ret = root_map[filename];
    //On déverouille le mutex
	SDL_UnlockMutex(lock);
	return ret;
}

/**
 * Récupère les couples clé-valeur du fichier de configuration
 *
 * @param filename		Nom du fichier
 * @param cur_map		Map temporaire pour stocker les clé-valeur courante
 * @param separator		Caractere separant la clé et la valeur dans le fichier
 * @return		        Booléenne Vrai si réussi, Faux si échoué
 */
bool Configuration::loadPropertiesFile(string filename, map<string, string> &cur_map, char separator) {
	//Ouverture du fichier dans un flux
	ifstream flux(filename);
	//Si le fichier a bien été ouvert
	if(flux)
	{
		string ligne;
        //tant qu'il y a une ligne à lire
		while(getline(flux, ligne))
		{
            //Si la ligne est vide ou si on rencontre # au début de la ligne
            //on ignore la ligne
			if(ligne.empty() || ligne[0] == '#')
				continue;

            //Décomposition de la ligne pour récupérer la clé et la valeur
            //et assigner ce couple dans cur_map
			string key;
			string value;
			istringstream my_split(ligne);
			getline(my_split, key, separator);
			getline(my_split, value, separator); 
			cur_map[key]=value;
		}
        //On ferme le fichier
		flux.close();
		return true;
	}
	return false;
}

