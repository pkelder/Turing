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


tlist_t transitions;



void Simulation::Help(char* s)
{
    printf("Bienvenue dans le super simulateur de Machine de Turing de la mort qui tue! \n");
	printf("By Didier Lime, Thomas Salliou & Pauline Kelder \n");
    printf("\n");
    printf("Usage: %s [-hqcp] -m input_file -i input_word \n", s);
    printf("Options:\n");
    printf("    -h | --help         print this help\n");
    printf("    -q | --quiet        print only errors\n");
    printf("    -c | --configs      print the computed configurations\n");
    printf("    -p | --plot         print only \"input_size DTIME DSPACE\"\n");
    printf("    -m s | --machine s  simulate the machine given in file s\n");
    printf("    -i s | --input s    simulate the machine on input s\n");
    printf("\n");
    printf("\n");
    printf("Syntax of the machine file:\n");
    printf("    // Comment until the end of the line\n");
    printf("    or\n");
    printf("    src -- A,B,D -> dest\n");
    printf("\n");
    printf("    src and dest may be one of:\n");
    printf("      - \"init\"    the initial state\n");
    printf("      - \"accept\"  the accepting state\n");
    printf("      - \"reject\"  the rejecting state\n");
    printf("      - \"str\"    any other state, with str being any string not\n");
    printf("                 containing ,{}() or -- \n");
    printf("\n");
    printf("    A is what is read on the tape. It is either:\n");
    printf("      - a character: e.g. 'a','b',...,'1','0','=',...\n");
    printf("      - a set of characters denoting an OR on the character to be read:\n");
    printf("        e.g. {a,b,c} means the transitions may be taken when reading\n");
    printf("        either 'a' or 'b' or 'c'\n");
    printf("      - a tuple of the first two possibilities: e.g. (a,{0,1},b)\n");
    printf("        means that 'a' is to be read on the first tape, '0' or '1' on\n");
    printf("        the second tape and 'b' on the third tape.\n");
    printf("      - two characters have a special meaning:\n");
    printf("        '_' is the blank character\n");
    printf("        '*' matches any character (the transition may be taken regardless\n");
    printf("            of the contents of the tape.)\n");
    printf("\n");
    printf("    B is what is written on the tape. It is either:\n");
    printf("      - a character: e.g. 'a','b',...,'1','0','=',...\n");
    printf("      - a set of characters denoting non-deterministic machine:\n");
    printf("        e.g. {a,b,c} means the machine will branch in three machines,\n");
    printf("        one writing 'a', the second 'b' and the third 'c'.\n");
    printf("      - a tuple of the first two possibilities: e.g. (a,{0,1},b)\n");
    printf("        means that 'a' is to be written on the first tape, '0' and '1' on\n");
    printf("        the second tape (by branching) and 'b' on the third tape.\n");
    printf("      - two characters have a special meaning:\n");
    printf("        '_' is the blank character\n");
    printf("        '\"' denotes the character that was read\n");
    printf("\n");
    printf("    D tells how to move the tape head(s). It is one of:\n");
    printf("      - '+' or 'r'  to make the head move right (increasing indexes)\n");
    printf("        '-' or 'l'  to make the head move left (decreasing indexes)\n");
    printf("        or any other character to leave the head unmoved\n");
    printf("      - a tuple of the above to indicate the moves on each tape:\n");
    printf("        e.g. (+,0,-) means the first tape head moves right, the\n");
    printf("        second stays put and the third moves left\n");
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


void Simulation::add_transitions(char ** R,char** W, char* D, int m, int n, int s, char_tuple_t reads, char_tuple_t writes, char_tuple_t dirs, int d)
{
    int i;
    
    if (W[m] == NULL)
    {
        writes[m] = '\0';
        if (m == n) {
            if (ntapes < m) ntapes = m;
			
            transitions[nt] = new_transition(s,reads,writes,dirs,d);
            ++nt;
        } else {
            fprintf(stderr, "Parse error: Tuples for read, write and direction should have the same size\n");
            exit(1);
        }
    } else if (R[n] == NULL) {
        reads[n] = '\0';
        dirs[m] = D[m];
        for (i=0; i < strlen(W[m]); ++i)
        {
            writes[m] = W[m][i];
            add_transitions(R,W,D,m+1,n,s,reads,writes,dirs,d);
        }
        
    } else {
        for (i=0; i < strlen(R[n]); ++i)
        {
            reads[n] = R[n][i];
            add_transitions(R,W,D,m,n+1,s,reads,writes,dirs,d);
        }
    }
	
}


