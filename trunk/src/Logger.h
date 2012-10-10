/** \file   Logger.h
 *  \brief  Définit la classe Logger
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <SDL/SDL_mutex.h>
 
#define LOG(message) Logger::log(__FILE__, __LINE__, __FUNCTION__, message, SIMPLE)
#define LOGWARNING(message) Logger::log(__FILE__, __LINE__, __FUNCTION__, message, WARNING)
#define LOGERROR(message) Logger::log(__FILE__, __LINE__, __FUNCTION__, message, ERROR)

using namespace std;

/** \enum   EnumLogLevel
 *  \brief  Niveaux de log que le logger peut gérer
 */
enum EnumLogLevel {
    SIMPLE=0, WARNING=1, ERROR=2
};


/** \class  Logger
 *  \brief  Permet d'afficher des messages dans la console.
 *
 * Les messages affichés peuvent être accompagné de différentes options
 * permettant de les faire ressortir dans le log en fonction de leurs
 * importance.
 */
class Logger
{
    public:
        static void log(
				string file, int line, string function, 
				string message, EnumLogLevel level=SIMPLE);
        static void close();
    protected:
    private:
		static ofstream outputFile;
		static SDL_mutex* lock;
};

#endif // LOGGER_H
