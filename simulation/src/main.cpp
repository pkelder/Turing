#include <iostream>
#include "Configuration.h"
#include "Simulation.h"
#include "Tape.h"

// Global variables for sharing with the parser
names_t names;
tlist_t transitions;
int nt = 0;
int ntapes = 0;
extern FILE * yyin;


int main(int argc, char * const argv[])
{
	Simulation simulation;
	
	// Predefined state names
	
	names[0] = strdup("init");
	names[1] = strdup("accept");
	names[2] = strdup("reject");
	
	 std::cout << "Hello, World!\n";
    int display = 0;
    int plot = 0;
    int verbose = 1;
    char* filename = NULL;
    char* input = NULL;
	
    int c;
	
    // Long options descriptor
    static struct option longopts[] = {
        {"quiet", NULL,   'q'},
        {"configs",NULL,   'c'},
        {"plot", NULL,   'p'},
        {"input", NULL,   'i'},
        {"machine",NULL,   'm'},
        {"help", NULL,   'h'},
        {NULL, NULL,   0}
    };
	
	 std::cout << "Hello, World!\n";
	
    // Parse options
    while ((c = getopt_long(argc,argv,"qchpi:m:",longopts,NULL)) != -1)
    {
        switch (c)
        {
            case 'q': verbose = 0; break;
            case 'c': if (!plot) display = 1; break;
            case 'p': plot = 1; verbose = 0; display = 0; break;
            case 'm': filename = strdup(optarg); break;
            case 'i': input = strdup(optarg); break;
            case 'h':
            default : simulation.Help(argv[0]); return 1; break;
        }
    }
	
	 std::cout << "Hello, World!\n";
    // Those are mandatory
    if (filename == NULL || input == NULL)
    {
        simulation.Help(argv[0]);
        return 1;
    }
	
    if (verbose) printf("%s: Turing machine simulator by Didier Lime (2009)\n", argv[0]);
    if (verbose) printf("%s: Running machine %s with input %s\n", argv[0], filename, input);
	
    if (verbose) printf("%s: Parsing...", argv[0]);
	 yyin = fopen(filename,"r");
	 if (yyin == NULL)
	 {
	 fprintf(stderr,"%s: Error: could not open file %s\n", argv[0], filename);
	 return 1; 
	 }
	 
	 if (yyparse())
	 
	 {
	 fprintf(stderr,"%s: Error: Incorrect syntax when parsing %s\n", argv[0], filename);
	 return 1;
	 }
	 fclose(yyin);
	 
    if (verbose) printf("done\n");
    if (verbose) printf("%s: Found %d tape(s)\n", argv[0], ntapes);
	
    // Mark end of list
    transitions[nt] = NULL;
	
    int steps = 0;
    int i,j,k,mem,max_mem;
    int input_size;
	config_list L1,L2; 
	
    // First configuration
	L1[0]=Configuration(input);
	
    // End of lists
    L1[1] = NULL;
    L2[0] = NULL;
	
    // Predefined state names
    names[0] = strdup("init");
    names[1] = strdup("accept");
    names[2] = strdup("reject");
	
    // The memory initially used is the size of the input
    max_mem = strlen(input);
    input_size = max_mem;
	
    if (verbose) printf("%s: Input size is %d\n", argv[0], input_size);
    if (verbose) printf("%s: Starting simulation...\n", argv[0]);
	
    // Print separator
    simulation.tmprintsep(display);
	
    // Print the first configuration
    if (display) L1[0].config_print();
	
    // While not deadlocked and not have an accept and not have only rejects
    while (L1[0] != NULL && !L1.conf_contains(1) && !L1.tmisall(2))
    {
        simulation.succesors(L1);
       simulation.conf_shallow_copy(L2);
		
		
        // Separate steps
        simulation.tmprintsep(display);
		
        // For each configuration
        for (i=0; L1[i] != NULL; ++i)
        {
            // If the machine is non-deterministic, we only take the max of
            // all parallel computations
            mem = 0;
            
            if (display) L1[i].config_print();
            for (j=0; j < ntapes; ++j)
            {
                for (k=0; k < TAPE_SIZE; ++k)
                {
                    // count the memory used by L1[i]
                    if (L1[i]->m_tapes[j].m_content[k] != ' ') ++mem;  
                }
            }
            
            // Record the max amount of used memory
            if (mem > max_mem) max_mem = mem;
        }
        // If the machine is non-deterministic, we count only one step for all the
        // parallel steps
        ++steps;
		
    }
    
    // Print separator
    simulation.tmprintsep(display);
	
    if (verbose) printf("%s: Computed %d steps\n", argv[0], steps);
    if (verbose) printf("%s: Used %d memory cells\n", argv[0], max_mem);
	
    if (L1[0] == NULL)
    {
        if (verbose) printf("%s: Machine deadlocked without reaching a decision\n", argv[0]);
    } else {
        if (simulation.conf_contains(1))
            if (verbose) printf("%s: Input %s is ACCEPTED\n", argv[0], input);
		
        if (simulation.tmisall(2))
            if (verbose) printf("%s: Input %s is REJECTED\n", argv[0], input);
    }
	
    if (plot)
    {
        printf("%d\t%d\t%d\n", input_size, steps, max_mem);
    }
	
	
    return 0;
}


