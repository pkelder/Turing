/*
 *  Simulation.cpp
 *  Machine_Turing
 *
 *  Created by Lou on 17/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#include "Simulation.h"
#include"Configuration.h"
#include "Transition.h"



void Simulation::Help()
{
	
}



Configuration Simulation::next_conf(Transition* t)	 //reprise de  next(tmconfig_t * c, transition_t * t)
{
	Configuration conf("");
	
	return conf;
}


void Simulation::succesors(config_list l)	//	successors(tmconflist_t R, tmconflist_t L);
{
	int i,j,k,n;
    int match;
    k = 0;
	

	
    // For each configuration
    for (i=0; &l[i] != NULL; ++i)
    {
        // For each transition of the machine
        for (j=0; transitions[j] != NULL; ++j)
        {
            // If the transition starts from the machine state
            // And the letter pointed by the head corresponds.
            if (transitions[j]->m_src == l[i].getState()) 
            {
                match = 1;
                //for (n=0; n < ntapes && match && transitions[j]->m_read[n] != '\0'; ++n)
                for (n=0; n < 1 && match && transitions[j]->m_read[n] != '\0'; ++n)
				{
                    match = (transitions[j]->m_read[n] == '*') 
					|| (transitions[j]->m_read[n] == l[i].getTapes()[n].getContent()[L[i]->m_tapes[n].m_head]);
                }
                if (match)
                {
                    // Compute the successor
                    &liste_config[k] = next_conf(transitions[j]);
                    ++k;
                }
            }
        } 
    }
	
    // Mark the end of the list
    liste_config[k] = NULL;
	
}


void Simulation::conf_shallow_copy(config_list l) //void tmconf_shallow_copy(tmconflist_t R, tmconflist_t L);
{
	int i;
    for (i=0; i<MAX_BRANCHING; ++i)
        liste_config[i] = l[i];
}


void Simulation::tmprintsep(int display)	//void tmprintsep(int display);
{
	int i;
    if (display)
    {
        for (i=0; i< DISPLAY_SIZE; ++i)
            printf("====");
        printf("=\n");
    }
}


int Simulation::tmisall(int s)	//int tmisall(tmconflist_t L, int s);
{
	int i = 0;
    while (&liste_config[i] != NULL && liste_config[i].getState() == s) ++i;
    return (&liste_config[i] == NULL);
}


int Simulation::conf_contains(int s)	//int tmcontains(tmconflist_t L, int s);
{
	int i = 0;
    while (&liste_config[i] != NULL && liste_config[i].getState() != s) ++i;	
    return (&liste_config[i] != NULL);
}


