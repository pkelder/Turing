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

State::State(std::string n){
    name = n;
}

std::string State::getName() const{

	return name;
}