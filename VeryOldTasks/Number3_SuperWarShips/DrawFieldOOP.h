#pragma once
#include"console.h"
#include<iostream>

const size_t Arena_size = 10;
class Drawer {
	int field_x = 1;
	int field_y = 1; // top-left corner
	int field_width = 12;
	int field_height = 12;
	int point_x = 0;
	int point_y = 0;


	/* Output char using given color pair at given position. */		//it was static
	void con_charAt(int ch, int color, int x, int y);
	void all_draw();
	void init_colors();
public:	
	enum PointType { FREE_WATER = '-', STRIKED_WATER = '*', UNBROKEN_SHIP = '#', STRIKED_SHIP = 'X' };
	enum Field { CHAR_BORDER = '*', CHAR_FIELD = ' ', FIELD_PADDING = 5 };
	enum COLORS { COLOR_FREE_WATER = 0, COLOR_STRIKED_WATER, COLOR_UNBROKEN_SHIP, COLOR_STRIKED_SHIP, COLOR_BORDER, CHECK, COLOR_FIELD };

	Drawer();
	void InitialDraw();
	void changeDraw(const size_t(&Field)[Arena_size][Arena_size]);
	const size_t size() { return Arena_size; }
	//Drawer& operator=(const Drawer& other);
	void clearTxt(size_t x1 = 0, size_t y1 = 15, size_t x2 = 150, size_t y2 = 20);
	void moveField(size_t x = 1, size_t y = 1);
	//int process_key(int key);
	void is_pressed(int key = CON_KEY_ENTER);
	~Drawer() { con_deinit(); }
};