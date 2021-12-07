#include "../include/option.h"

/*

int initOption(int argc, char * const argv[], Opt * opt){
	int c, option_index = 0;
	char is_x;
	
	assert(argc > 0);
	assert(argv != NULL);
	assert(opt != NULL);

	 /*Paramètres par défaut

	opt->affichage = graphique;
	opt->unique = UNIQUE_PAR_DEFAUT;
	opt->acces = ACCES_PAR_DEFAUT;
	opt->attente = ATTENTE_PAR_DEFAUT;
	opt->graine = GRAINE_PAR_DEFAUT;
	opt->dimensions.x = TAILLE_X_PAR_DEFAUT;
	opt->dimensions.y = TAILLE_Y_PAR_DEFAUT;

	struct option long_options[] = {
		{"mode", required_argument, NULL, 1},
		{"graine", required_argument, NULL, 2},
		{"attente", required_argument, NULL, 3},
		{"taille", required_argument, NULL, 4},
		{"unique", no_argument, NULL, 5},
		{"acces", no_argument, NULL, 6},
		{0, 0, 0, 0}
	};

	while((c = getopt_long_only(argc, argv, "", long_options, &option_index)) != -1){
		switch(c){
			case 1: 
				if(strcmp(optarg, "texte") == 0){
					opt->affichage = texte;
					break;
				}
				fprintf(stderr, "L'argument de l'option mode n'est pas valide\n");
			case 2: opt->graine = atoi(optarg); break;
			case 3: opt->attente = atoi(optarg); break;
			case 4: 
				sscanf(optarg, "%d%c%d", &(opt->dimensions.x), &is_x, &(opt->dimensions.y));
				break;
			case 5: opt->unique = 1;break;
			case 6: opt->acces = 1;break;	
			default:
				break; 
		}
	}


	return 1;
}

*/