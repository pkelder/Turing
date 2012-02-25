/*
 *  MachineConfig.cpp
 *  Turing
 *
 *  Created by Lou on 24/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#include <vector>
#include <string>
#include "MachineConfig.h"

MachineConfig::MachineConfig(const std::string s, vector<Tape*> ta){
    state = s;
    tapes = ta;
}

const std::string MachineConfig::getState() const{
	
	return state;

}

vector<Tape*> MachineConfig::getTape() const{
	return tapes;
}
