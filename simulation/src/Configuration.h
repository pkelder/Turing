/*
 *  Configuration.h
 *  Machine_Turing
 *
 *  Created by Lou on 17/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include "Tape.h"
#define TAPE_SIZE 10000
#define DISPLAY_SIZE 22
#define MAX_TAPES 3
#define MAX_STATES 10000


typedef Tape tapes_t[MAX_TAPES];
typedef char* names_t[MAX_STATES];


class Configuration{
	
public:
	Configuration(char*);
	void config_print();

private:
	
	tapes_t m_tapes;
	int m_state;
}

#endif