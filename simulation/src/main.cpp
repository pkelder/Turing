#include <iostream>
#include "Simulation.h"

int main (int argc, char * const argv[]) {
    
    /*Simulation* simulemoi = new Simulation();
    vector<char> entree (1,'1');
    vector<char> entreeFoireuse (1,'0');
    vector<char> sortie (1,'1');
    vector<int> mouvement (1, 1);
    State* init = simulemoi->getStates()[0];
    State* accept = simulemoi->getStates()[1];
    State* reject = simulemoi->getStates()[2];
    simulemoi->addTransition(entreeFoireuse,sortie,mouvement,init,reject);
    simulemoi->addTransition(entree,sortie,mouvement,init,accept);
    simulemoi->wholeSimulation();*/

    /*vector<char> content = {'a', '1', 'b'};
    Tape* myTape = new Tape(content);
    if (myTape->getChar() == 'a') cout << "Okay !" << endl;
    myTape->move(-1);
    myTape->move(-1);
    myTape->move(-1);
    cout << myTape->getChar() << endl;
    for (char c : myTape->getContent()) {
        cout << c;
    }
    cout << endl;*/

    Simulation* simulemoi = new Simulation();
    State* init = simulemoi->getStates()[0];
    State* infinite = new State("infinite");
    vector<char> entry = {' '};
    vector<char> write = {' '};
    vector<int> move = {0};
    simulemoi->addTransition(entry,write,move,init,infinite);
    simulemoi->addTransition(entry,write,move,infinite,infinite);
    simulemoi->wholeSimulation();
    return 0;
}
