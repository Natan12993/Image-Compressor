#include "../include/quadtree.h"


static int powOfTwo(int x){
	return x*x; 
}

static Color getPixelAsColor(const MLV_Image * image, Coor coor){
	Color c;
	int red, green, blue, alpha;

	assert(image != NULL);
	assert(coor.x >= 0);
	assert(coor.y >= 0);

	MLV_get_pixel_on_image(image, coor.x, coor.y, &red, &green, &blue, &alpha);

	c.r = (unsigned char) red;
	c.g = (unsigned char) green;
	c.b = (unsigned char) blue;
	c.a = (unsigned char) alpha;

	return c;
}


/* Finds and returns the leaf whose associated average color
 * represents incorrectly its zone the most among other leaves.
 * If two leaves are as incorrect, the last one encountered is returned
 * This also apply when the quadtree matches the image perfectly.
 * The tree CANNOT be non initialized, meaning qd!=NULL. */
static Quadtree findLeastCorrectLeaf(Quadtree qd, const MLV_Image * image){
	Quadtree s1, s2, s3, s4, worse;

	assert(qd != NULL);
	assert(image != NULL);

	/* We check if qd is a leaf or not 
	 * We assume that the quadtree is correctly implemented,
	 * meaning if s1 is NULL then s2,s3,s4 are too. */
	if(qd->s1 == NULL){
		return qd;
	}

	/* if qd isn't a leaf we select the worst leaf in the following tree */

	s1 = findLeastCorrectLeaf(qd->s1, image);
	s2 = findLeastCorrectLeaf(qd->s2, image);
	s3 = findLeastCorrectLeaf(qd->s3, image);
	s4 = findLeastCorrectLeaf(qd->s4, image);
	worse = s1;

	if(s2->error > worse->error)
		worse = s2;
	if(s3->error > worse->error)
		worse = s3;
	if(s4->error > worse->error)
		worse = s4;

	return worse;
}

char isPerfect(Quadtree qd, const MLV_Image * image){
	assert(image != NULL);
	assert(qd != NULL);

	if(NULL == qd->s1){ /* if qd is a leaf */
		return !qd->error;
	}

	return isPerfect(qd->s1, image) 
		&& isPerfect(qd->s2, image) 
		&& isPerfect(qd->s3, image) 
		&& isPerfect(qd->s4, image);
}


Quadtree newNode(Coor coor, int side, Color color, unsigned int error){
	Quadtree ptr = (Quadtree) malloc(sizeof(Node));
	if(ptr != NULL){
		ptr->error = error;
		ptr->color = color;
		ptr->side = side;
		ptr->topLeft = coor;
		ptr->s1 = NULL;
		ptr->s2 = NULL;
		ptr->s3 = NULL;
		ptr->s4 = NULL;
	}
	return ptr;
}


int expandLeaf(const MLV_Image * image, Quadtree qd){
	Color newAvr;
	Coor newCoor;
	int newSide;

	assert(image != NULL);
	assert(qd != NULL);
	/* If the side equals 1, then it means the node
	 * only covers a pixel, in which case this function should
	 * should not have been called */
	assert(qd->side <= 1); 

	newSide = qd->side / 2; 

	/* NORTH WEST (s1) */
	newCoor = qd->topLeft;
	newAvr = averageColor(image, newCoor, newSide);
	qd->s1 = newNode(newCoor, newSide, newAvr, accuracy(image, newAvr, newCoor, newSide));
	if(qd->s1 == NULL)
		return 1;

	/* NORTH EST (s2) */
	newCoor = (Coor) {qd->topLeft.x + qd->side / 2, qd->topLeft.y};
	newAvr = averageColor(image, newCoor , newSide);
	qd->s2 = newNode(newCoor, newSide, newAvr, accuracy(image, newAvr, newCoor, newSide));
	if(qd->s2 == NULL)
		return 1;

	/* SOUTH EST (s3) */
	newCoor = (Coor) {qd->topLeft.x + qd->side / 2, qd->topLeft.y + qd->side / 2};
	newAvr = averageColor(image, newCoor , newSide);
	qd->s3 = newNode(newCoor, newSide, newAvr, accuracy(image, newAvr, newCoor, newSide));
	if(qd->s3 == NULL)
		return 1;

	/* SOUTH WEST (s4) */
	newCoor = (Coor) {qd->topLeft.x, qd->topLeft.y + qd->side / 2};
	newAvr = averageColor(image, newCoor , newSide);
	qd->s4 = newNode(newCoor, newSide, newAvr, accuracy(image, newAvr, newCoor, newSide));
	if(qd->s4 == NULL)
		return 1;

	return 0;
}


int fillQuadtree(Quadtree * qd, const MLV_Image * image){

	Quadtree worst;
	Color avr;

	assert(image != NULL);
	/* We make an assertion that the lenght of the image is equal 
	 * to its height, as the program is only designed to work on 
	 * 512x512 images. */
	assert(MLV_get_image_width(image) == MLV_get_image_height(image));

	/* If the Quadtree is not initialized, we create the root using default values */
	if(qd == NULL){
		avr = averageColor(image, (Coor){0, 0}, IMAGE_SIDE_LENGHT);
		*qd = newNode((Coor){0, 0}, IMAGE_SIDE_LENGHT, avr, accuracy(image, avr, (Coor){0, 0}, IMAGE_SIDE_LENGHT));
	}

	while(!isPerfect(*qd, image)){
		/* we find the worst leaf */
		worst = findLeastCorrectLeaf(*qd, image);

		/* we split it in 4 */
		if(1 == expandLeaf(image, worst))
			return 1;
	}
	return 0;
}

unsigned int distance(const MLV_Image * image, Color average, Coor coor){
	Color c;

	assert(image != NULL);
	assert(coor.x >= 0);
	assert(coor.y >= 0);

	c = getPixelAsColor(image, coor);

	return (unsigned int) sqrt( (double) (powOfTwo(average.r-c.r) + powOfTwo(average.g-c.g) + powOfTwo(average.b-c.b) + powOfTwo(average.a-c.a)) );
}

Color averageColor(const MLV_Image * image, Coor coor, int side){
	Color c, tmp;
	int tred=0, tgreen=0, tblue=0, talpha=0, i, j;

	assert(image != NULL);
	assert(coor.x >= 0);
	assert(coor.y >= 0);
	assert(side > 0);

	for(i = coor.x; i != coor.x+side; i++){
		for(j = coor.y; j != coor.y+side; j++){
			tmp = getPixelAsColor(image, (Coor){i, j});
			tred += tmp.r;
			tgreen += tmp.g;
			tblue += tmp.b;
			talpha += tmp.a;
		}
	}

	c.r = tred / (i * j);
	c.g = tgreen / (i * j);
	c.b = tblue / (i * j);
	c.a = talpha / (i * j);

	return c;
}


unsigned int accuracy(const MLV_Image * image, Color average, Coor coor, int side){
	unsigned int acc = 0;
	int i, j;

	assert(image != NULL);
	assert(coor.x >= 0);	
	assert(coor.y >= 0);
	assert(side > 0);

	for (i = coor.x; i != coor.x+side; ++i){
		for (j = coor.y; j != coor.y+side; ++j){
			acc += distance(image, average, (Coor){i, j});
		}
	}

	return acc;
}

