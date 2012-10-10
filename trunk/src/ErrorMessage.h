/** \file   ErrorMessage.h
 *  \brief  Définit la classe ErrorMessage
 */
#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include <string>
#include <exception>

#define ERROR(message) ErrorMessage(__FILE__, __LINE__, __FUNCTION__, message)

using namespace std;


/** \class  ErrorMessage
 *  \brief  Gére les exceptions
 *
 * Contient la ligne, le fichier, la fonction et un message concernant
 * l'erreur rencontrée
 */
class ErrorMessage :
	public exception
{
    public:
        ErrorMessage(string filename, int line, string function, string message);
        ~ErrorMessage();

		void what();
    protected:
    private:
		string filename;
		int line;
		string function;
		string message;
};

#endif // ERRORMESSAGE_H
