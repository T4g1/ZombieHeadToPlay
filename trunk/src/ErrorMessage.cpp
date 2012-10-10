/** \file   ErrorMessage.cpp
 *  \brief  Implémente la classe ErrorMessage
 */
#include "ErrorMessage.h"

#include "Logger.h"

/**
 * Constructeur de ErrorMessage
 */
ErrorMessage::ErrorMessage(string filename, int line, string function, string message)
{
	this->filename = filename;
	this->line = line;
	this->function = function;
	this->message = message;
} // ErrorMessage

/**
 * Destructeur de ErrorMessage
 */
ErrorMessage::~ErrorMessage()
{
} // ~ErrorMessage


/**
 * Affiche l'erreur
 */
void ErrorMessage::what()
{
	Logger::log(filename, line, function, message, ERROR);
} // what