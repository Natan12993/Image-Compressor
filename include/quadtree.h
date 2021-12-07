#ifndef __QUADTREE__
#define __QUADTREE__

#include <MLV/MLV_all.h>
#include <assert.h> /* assert */
#include <stdlib.h> /* abs */
#include <math.h>   /* sqrt */

#define IMAGE_SIDE_LENGHT 512 /* We use 512x512 images only */

/* 4 bytes rgba */
typedef struct color{
	unsigned char r; /* red */
	unsigned char g; /* green */
	unsigned char b; /* blue */
	unsigned char a; /* 0=fully transarent, 255=fully opaque */
}Color;
/* Value for black in bi-color mode : 0,0,0,255 */
/* Value for white in bi-color mode : 255,255,255,255 */


typedef struct coordinates {
    int x;
    int y;
}Coor;


/* represents a node in a quadtree */
typedef struct node{
    Coor topLeft;       /* location of topleft corner of the square on the image */
    int side;           /* lenght of the side of the square */
	struct node * s1, * s2, * s3, * s4;
	Color color;        /* average color of the zone covered by the node. */
    unsigned int error; /* how accurate is color (=0 if perfect) */
}Node, *Quadtree;


/* Returns 1 if the quadtree represents perfectly the image. 0 otherwise. */
char isPerfect(Quadtree qd, const MLV_Image * image);

/* Allocates and returns a node with the specified data.
 * Its sons are set to NULL. 
 * Returns NULL if malloc fails. */
Quadtree newNode(Coor coor, int side, Color color, unsigned int error);

/* This is only to be used if qd is a leaf !
 * Adds 4 leaves to qd, with correct data (topLeft, side, color, error)
 * thus spliting the zone covered by qd in 4.
 * Returns 1 if malloc fails, 0 otherwise. */
int expandLeaf(const MLV_Image * image, Quadtree qd);

/* Fills the quadtree with nodes and leaves so that it exactly represents image.
 * The quadtree doesn't have to be initialized with newNode().
 * The nodes are allocated with malloc. See freeQuadtree().
 * Returns 1 if malloc fails, 0 otherwise. */
int fillQuadtree(Quadtree * qd, const MLV_Image * image);


/********* Color Manipulation from image **********/


/* Returns the distance between average and the color of the pixel located at (x,y) */
unsigned int distance(const MLV_Image * image, Color average, Coor coor); 

/* Returns the average color of the zone located at (x,y), specified by height and width. */
Color averageColor(const MLV_Image * image, Coor coor, int side);

/* Returns the accuracy in which average represents (color-wise) the zone located at (x,y),
 * specified by side (of a square). If the value returned is 0, then it means that every pixel
 * in the zone is portrayed by the color average. */
unsigned int accuracy(const MLV_Image * image, Color average, Coor coor, int side);


#endif