#include "../include/graphic.h"

void InitWindow(Window * f, unsigned int height, unsigned int width, char * name){
	assert(f != NULL);

	f->height = height;
	f->width = width;
	f->name = name;
}

void CreateWindow(Window f){
	MLV_create_window(f.name, NULL, f.height, f.height);
}

void CloseWindow(void){
	MLV_free_window();
}

void ClearWindow(void){
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_actualise_window();
}

void Button(void){
	int width = MLV_get_window_width();
	int height = MLV_get_window_height();
	/*premier bouton*/
	MLV_draw_text_box (a,b,c,d,"Name", 1, MLV_COLOR_WHITE, MLV_COLOR_GREEN, MLV_COLOR_BLACK, MLV_TEXT_LEFT,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	/*Deuxième*/
	MLV_draw_text_box (a,b,c,d,"Name", 1, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_GREY, MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
	MLV_draw_text_box (a,b,c,d,"Name", 1, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_GREY, MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
}

void CliqueCoord(void){
	int x, y, i;
	int width = MLV_get_window_width();
	int height = MLV_get_window_height();
	MLV_wait_mouse(&x, &y);
	if (x >= width*0.905 && x <= width*0.905 + 90 && y >= height/1.55 && y <= height/1.55 + 80){ /*position de chaque bouton*/ /*exemple*/
		sauvegarde();/*ce que ca fait*/
	}
	else if (x >= width*0.905 && x <= width*0.905 + 90 && y >= height/1.25 && y <= height/1.25 + 80){ /*exemple 2*/
		MLV_free_window();
		exit(0);
	}
}