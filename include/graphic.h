#ifndef __GRAPHIC__
#define __GRAPHIC__

#include <MLV/MLV_all.h>
#include "quadtree.h"

#define WINDOW_NAME "qdc"

typedef struct{
	unsigned int height;
	unsigned int width;
	char name;
}Window;

typedef enum input{
	save,
	open,

}Action;

/* Boutons:
-approximation quadtree
-ouvrir une image
-minimisation (graphes etc)
-4 boutons de sauvegarde.
*/

/* Displays the image represented by the quadtree on the current window
 * at the position (x, y). The image size is set to 512x512.  */
void displayQuadtree(Quadtree qd);



InitWindow(Window * f, unsigned int height, unsigned int width, char * name);

CreateWindow(Window f);

CloseWindow(void);

ClearWindow(void);

Button(void);

Action CliqueCoord(void);


#endif