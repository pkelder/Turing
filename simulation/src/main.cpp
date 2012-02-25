#include <iostream>
#include <string>
#include "Simulation.h"
#include "TmParser.h"

int main (int argc, char * const argv[]) {

    /*Simulation* simulemoi = new Simulation();
    vector<char> entree (1,'1');
    vector<char> entreeFoireuse (1,'0');
    vector<char> sortie (1,'1');
    vector<int> mouvement (1, 1);
    simulemoi->addTransition(entreeFoireuse,sortie,mouvement,"init","reject");
    simulemoi->addTransition(entree,sortie,mouvement,"init","accept");
    simulemoi->wholeSimulation();

    vector<char> content = {'a', '1', 'b'};
    Tape* myTape = new Tape(content);
    if (myTape->getChar() == 'a') cout << "Okay !" << endl;
    myTape->move(-1);
    myTape->move(-1);
    myTape->move(-1);
    cout << myTape->getChar() << endl;
    for (char c : myTape->getContent()) {
        cout << c;
    }
    cout << endl;

    Simulation* simulemoi2 = new Simulation();
    vector<char> entry = {' '};
    vector<char> write = {' '};
    vector<int> move = {0};
    simulemoi2->addTransition(entry,write,move,"init","infinite");
    simulemoi2->addTransition(entry,write,move,"infinite","infinite");
    simulemoi2->wholeSimulation();
    return 0;*/

    //std::string str = "patate->a,b,<--navet\nnavet->r,z,>--grenouille";
    //std::string str = "patate->{a,c},{b,d},{<,0}--navet\nnavet->r,z,>--grenouille";
    Simulation* sim = new Simulation();
    std::string str = "patate->{a,b,c},{d,e,f},{-1,0,1}--navet\nnavet->r,z,0--grenouille";
    parseTuring(str,sim);
}
