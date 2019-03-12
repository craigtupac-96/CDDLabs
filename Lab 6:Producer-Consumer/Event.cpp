/*! \file Event.cpp
    \brief A documented file.

    Craig Lawlor
    Mar 2019
*/
#include "Event.h"
#include <iostream>
#include <stdlib.h>

/*! \fn Event::Event()
    \brief the constructor
    \var eric a random character
*/
Event::Event(){
	eric = 'a' + rand()%26;
	std::cout << eric ;
}

/*! \fn void Event::consume()
*/
bool Event::consume(){
	char betterEric = eric-32;
	std::cout << betterEric ;
}