/*
 *  MachineConfig.cpp
 *  Turing
 *
 *  Created by Lou on 24/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#include <vector>
#include "MachineConfig.h"

MachineConfig::MachineConfig(){}

void MachineConfig::setTape(vector<Tape> t)
{
	this->tapes=t;
	
}

void MachineConfig::setState(State s){
	
	this->state.setName(s.getName());
}

State MachineConfig::getState() const{
	
	return state;

}

vector<Tape> MachineConfig::getTape() const{
	return tapes;
}
