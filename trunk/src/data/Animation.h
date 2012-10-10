/** \file   Animation.h
 *  \brief  Définit la classe Animation
 */
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL/SDL.h>


/** \class  Animation
 *  \brief  Classe permettant la gestion des Animation
 */
class Animation
{
    public:
        Animation();
        virtual ~Animation();

		bool addFrame(int x, int y, int w, int h);
    protected:
    private:
		SDL_Rect* l_frames;		// Liste des coordonnées des images composant l'animation
		int frameCount;			// Nombre de frame composant l'animation

		int currentFrame;		// Frame affichée
};

#endif // SPRITE_H