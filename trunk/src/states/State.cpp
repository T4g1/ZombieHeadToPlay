/** \file   State.cpp
 *  \brief  Implémente la classe State
 */
#include "State.h"


/**
 * Constructeur de State
 */
State::State()
{
	// ctor
} // State

/**
 * Destructeur de State
 */
State::~State()
{
	// dtor
} // ~State


/**
 * Permet à n'importe quel état de changer
 * l'état courant
 */
void State::changeState(Logic* logic, State* state)
{
	logic->changeState(state);
}