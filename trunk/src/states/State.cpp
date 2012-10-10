/** \file   State.cpp
 *  \brief  Impl�mente la classe State
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
 * Permet � n'importe quel �tat de changer
 * l'�tat courant
 */
void State::changeState(Logic* logic, State* state)
{
	logic->changeState(state);
}