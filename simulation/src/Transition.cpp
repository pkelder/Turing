/*
 *  transition.cpp
 *  Machine_Turing
 *
 *  Created by Lou on 17/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#include "Transition.h"
extern int ntapes=2;



Transition::Transition(int s, char_tuple_t r, char_tuple_t w, char_tuple_t dir, int d)
{
	
    int i;
	
    m_src = s;
    m_dest = d;
    
    for (i=0; i < ntapes; ++i)
    {
        this->m_read[i] = r[i];
		
        if (w[i] == '"')
            this->m_write[i] = r[i];
        else
            this->m_write[i] = w[i];
		
		
        if (dir[i] == '+' || dir[i] == 'r')
        {
            this->m_dir[i] = 1;
        } else if (dir[i] == '-' || dir[i] == 'l') {
            this->m_dir[i] = -1;
        } else {
            this->m_dir[i] = 0;
        }
    }
	
}
