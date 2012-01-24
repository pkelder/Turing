/*
 *  State.cpp
 *  Turing
 *
 *  Created by Lou on 24/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#include "State.h"
#include <string>

State::State(){}


void State::setName(std::string s)
{
	name=s;
}

std::string State::getName(){

	return name;
}