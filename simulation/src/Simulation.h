/*
 *  Simulation.h
 *  Machine_Turing
 *
 *  Created by Lou on 17/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#ifndef SIMULATION_H
#define SIMULATION_H


#include"Configuration.h"
#include"Transition.h"
#define MAX_BRANCHING 10000
#define MAX_TRANSITIONS 10000
typedef Configuration config_list[MAX_BRANCHING];
typedef Transition* transition_list[MAX_TRANSITIONS];

class Simulation
{
public:
	void Help(char* s);
	Configuration next_conf(Transition* t);	 //reprise de  next(tmconfig_t * c, transition_t * t)
    void succesors(config_list l);	//	successors(tmconflist_t R, tmconflist_t L);
	void conf_shallow_copy(config_list l); //void tmconf_shallow_copy(tmconflist_t R, tmconflist_t L);
	void tmprintsep(int display);	//void tmprintsep(int display);
	int tmisall(int s);	//int tmisall(tmconflist_t L, int s);
	int conf_contains(int s);	//int tmcontains(tmconflist_t L, int s);
	void add_transitions(char ** ,char** , char* , int, int, int, char_tuple_t, char_tuple_t, char_tuple_t, int);

	
	
private:
	
	config_list liste_config;
	transition_list liste_transitions;
    
};

#endif