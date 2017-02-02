#include <iostream>
#include <cstdlib>
#include <string.h>
#include <getopt.h>
#include "cblock.h"

/*
********************************************************************************
*
*
* Parses the parameters from argv
* 
* The following command line flags are available
*
*
*	-n    	<integer>	# keys
*
*	-r      <integer>	Max # repetitions run (not used)
*
*	-g      <integer>	Min N that may be subject to mergeSort
*
*	-p			Use a parallel merge (default is serial)
*
*	-w			Worst case input of reverse sorted data
*
*	-b			Best case input of perfectly sorted data
*
*	-s 	<integer>	random number seed (for randomized input only)
*
********************************************************************************
*/

void PrintUsage(char* program, char* option);
extern control_block cb;


int cmdLine(int argc, char **argv)
{

			    /* Fill in default values */
   cb.par_merge = false;
   cb.worst = false;
   cb.best = false;

   cb.N = 67108864;             // 64M Keys
   cb.nreps = 1;
   cb.seedVal = 0;
   cb.minN = 262144;            // Recursion stops at 256K keys
   cb.NT = 1;
   cb.seedVal = 0;

   /* Parse the command line arguments  */
   extern char *optarg;
   int c;
   while ((c=getopt(argc,argv,"pwbn:r:s:g:t:")) != -1) {
        switch (c) {
            //
            // Use parallel Merge Sort
            case 'p':
                cb.par_merge = true; break;

            // worst case input
            case 'w':
                cb.worst = true; break;

            // Best case input
            case 'b':
                cb.best = true; break;

            // Input size
            case 'n':
                cb.N = atoi(optarg); break;

            // Run for multiple repetitions 
            // (useful for timing if using a small problem)
            case 'r':
                cb.nreps = atoi(optarg); break;

            // Random seed
            // When we need to run with the exact same input
            case 's':
                cb.seedVal = atoi(optarg); break;

            // Minimium input size for using mergesort;
            // else, we use a fast sort
            case 'g':
                cb.minN = atoi(optarg); break;

            // # threads
            case 't':
                cb.NT = atoi(optarg); break;
            default:
                std::cerr << "\nUsage: " << argv[0] << " [-n <# keys>] [-r <nreps>] [-s <seed> ] [-p] [-w] [-b] [-t ,threads>]\n\n";
                exit(0);
                return(-1);
        }
    }
   if (cb.N <= 0) {
        std::cerr << "# keys must be > 0 [is " << cb.N << "].\n";
	exit(-1);
   }

   if (cb.minN < 4) {
        std::cerr << "Minimum chunk size in recursion must be >= 4.\n";
	exit(-1);
   }

   return(0);

}

/*
********************************************************************************
*
*
* Prints out the command line options
*
*
********************************************************************************
*/

void PrintUsage(char* program, char* option)
  {
   std::cerr << program << "error in argument " << option << std::endl;
   std::cout << "\t-n <integer> problem size\n";
   std::cout << "\t-r <integer> # of repetitions\n";
   std::cout << "\t-t <integer> # threads\n";
   std::cout << "\t-g           minimum block size for mergeSort\n";
   std::cout << "\t-p           use a parallel merge\n";
   std::cout << "\t-w           worst case (reverse sorted) input\n";
   std::cout << "\t-b           best case (perfectly sorted) input\n";
   exit(-1);
  }
