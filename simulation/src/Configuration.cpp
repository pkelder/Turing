/*
 *  Configuration.cpp
 *  Machine_Turing
 *
 *  Created by Lou on 17/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#include "Configuration.h"
#include "Tape.h"
#include<string>
extern names_t names;


Configuration::Configuration(char* t)
{
	
   // tmconfig_t* r = (tmconfig_t*) malloc(sizeof(tmconfig_t));
    int i;
    int size = strlen(t);
	
    this->m_state = 0;
    //for (i=0; i < ntapes; ++i)
	for (i=0; i < 1; ++i)
    {
        Tape tape_init;
		tape_init.setHead(TAPE_SIZE/2);
		m_tapes[i]=tape_init;
    }
    
    for (i=0; i < size; ++i)
	{
		std::string current_content=m_tapes[0].getContent();
		int current_head=m_tapes[0].getHead();
        current_content[current_head + i] = t[i];
	}
	
	
	
}

void Configuration::config_print()
{
	
	int i,j;
	
	// Global variables for sharing with the parser
	names_t names;
	// Predefined state names: à retirer ensuite
	
	names[0] = strdup("init");
	names[1] = strdup("accept");
	names[2] = strdup("reject");
	
	
	
    printf("State: %s\n", names[this->m_state]);
    //for (j=0; j< ntapes; ++j)
		 for (j=0; j< 1; ++j)
    {
        Tape current_tape=m_tapes[j];
		current_tape.tape_print();
		
        for (i=0; i < DISPLAY_SIZE/2+(this->m_tapes[j].getHead() - TAPE_SIZE/2); ++i)
            printf("    ");
        printf("  ^\n"); 
    }
	
}

int Configuration::getState(){
	return m_state;
}

tapes_t Configuration::getTapes(){
	return m_tapes;

}

