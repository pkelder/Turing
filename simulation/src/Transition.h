/*
 *  Transition.h
 *  Turing
 *
 *  Created by Lou on 24/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#ifndef DEF_TRANSITION
#define DEF_TRANSITION

#include <vector>
#include <string>

using namespace std;

class Transition{
	
public:
        Transition(vector<char>,vector<char>,vector<int>, const std::string, const std::string);
        vector<char> getRead() const;
        vector<char> getWrite() const;
        vector<int> getMove() const;
        const std::string getDestState() const;
	
	
private:
	vector<char> read;
	vector<char> write;
	vector<int> move;
        std::string sourceState;
        std::string destState;
	
};




#endif
