#include <stdio.h>
#include "../include/interface.h"
#include "../include/option.h"





int main(int argc, char * const argv[]){





	


	return EXIT_SUCCESS;

	memory_error: /* if malloc or realloc fail */
		fprintf(stderr, "%s: Insufficient memory to continue the execution of the program\n", argv[0]);
		return EXIT_FAILURE;

}