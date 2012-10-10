/** \file   configuration.cpp
 *  \brief  Impl�mente la classe configuration
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
	//Cr�ation du mutex
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
 * @return		        Bool�enne Vrai si r�ussi, Faux si �chou�
 */
bool Configuration::addFile(string filename) {
	//On v�rouille le mutex
	SDL_LockMutex(lock);
	bool ret = true;
	try {
		map<string, string> cur_map;
        //On apelle la fonction ouvrant le fichier et donnant le couple cl�-valeur
		if(!loadPropertiesFile(filename + ext, cur_map))
            throw ERROR("File not found: " + filename + ext);
        //Si pas d'erreur, on assigne la map principale avec la map obtenue avec le fichier
		root_map[filename] = cur_map;
	} catch(ErrorMessage& e) {
		e.what();
		ret = false;
	}
    //On d�verouille le mutex
	SDL_UnlockMutex(lock);
	return ret;
}

/**
 * Recharge le fichier de configuration dans la map
 *
 * @param filename		Nom du fichier
 * @return		        Bool�enne Vrai si r�ussi, Faux si �chou�
 */
bool Configuration::reloadFile(string filename) {
	return addFile(filename);
}

/**
 * R�cup�re les couples cl�-valeur du fichier de configuration
 *
 * @param filename		Nom du fichier
 * @return		        la map contenant les couples cl�-valeur
 */
map<string, string> Configuration::getProperties(string filename) {
    //On v�rouille le mutex
	SDL_LockMutex(lock);
    //On consulte la map principale pour r�cup�rer 
    //  toutes les cl�-valeur du fichier charg� pr�c�demment
	map<string, string> ret = root_map[filename];
    //On d�verouille le mutex
	SDL_UnlockMutex(lock);
	return ret;
}

/**
 * R�cup�re les couples cl�-valeur du fichier de configuration
 *
 * @param filename		Nom du fichier
 * @param cur_map		Map temporaire pour stocker les cl�-valeur courante
 * @param separator		Caractere separant la cl� et la valeur dans le fichier
 * @return		        Bool�enne Vrai si r�ussi, Faux si �chou�
 */
bool Configuration::loadPropertiesFile(string filename, map<string, string> &cur_map, char separator) {
	//Ouverture du fichier dans un flux
	ifstream flux(filename);
	//Si le fichier a bien �t� ouvert
	if(flux)
	{
		string ligne;
        //tant qu'il y a une ligne � lire
		while(getline(flux, ligne))
		{
            //Si la ligne est vide ou si on rencontre # au d�but de la ligne
            //on ignore la ligne
			if(ligne.empty() || ligne[0] == '#')
				continue;

            //D�composition de la ligne pour r�cup�rer la cl� et la valeur
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

