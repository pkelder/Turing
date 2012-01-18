#include <iostream>
#include "Configuration.h"

#include "Tape.h"




int main (int argc, char * const argv[]) {
	
	
	// Global variables for sharing with the parser
	names_t names;
	
	
	// Predefined state names
	
	names[0] = strdup("init");
	names[1] = strdup("accept");
	names[2] = strdup("reject");
	

	
	
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

