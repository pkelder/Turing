/*
 *  transition.h
 *  Machine_Turing
 *
 *  Created by Lou on 17/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */
#ifndef TRANSITION_H
#define TRANSITION_H

#include <string>
#include <iostream>


#define MAX_TAPES 3


typedef int char_tuple_t[MAX_TAPES];
typedef int dir_tuple_t[MAX_TAPES];

class Transition
{
public:
	Transition(int, char_tuple_t, char_tuple_t, char_tuple_t, int);
	
	
private:
	
	char_tuple_t m_read;
    char_tuple_t m_write;
    int m_src;
    int m_dest;
    dir_tuple_t m_dir;

};

#endif