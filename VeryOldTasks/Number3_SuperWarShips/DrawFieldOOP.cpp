#include "DrawFieldOOP.h"

//int Drawer::field_width = 12;
//int Drawer::field_height = 12;
//int Drawer::field_x = 1;
//int Drawer::field_y = 1;
//int Drawer::point_x = 0;
//int Drawer::point_y = 0;

void Drawer::con_charAt(int ch, int color, int x, int y) {
	con_gotoXY(x, y);
	con_setColor(color);
	con_outTxt("%c", ch);
}

void Drawer::init_colors() {
	con_initPair(COLOR_FREE_WATER, CON_COLOR_BLUE, CON_COLOR_BLACK);
	con_initPair(COLOR_STRIKED_WATER, CON_COLOR_CYAN, CON_COLOR_BLACK);
	con_initPair(COLOR_UNBROKEN_SHIP, CON_COLOR_WHITE, CON_COLOR_BLACK);
	con_initPair(COLOR_STRIKED_SHIP, CON_COLOR_RED, CON_COLOR_BLACK);
	con_initPair(COLOR_BORDER, CON_COLOR_WHITE, CON_COLOR_BLUE);
	con_initPair(CHECK, CON_COLOR_YELLOW, CON_COLOR_BLACK);
	con_initPair(COLOR_FIELD, CON_COLOR_BLACK, CON_COLOR_BLACK);
}

void Drawer::all_draw() {
	//con_clearScr();
	//con_gotoXY(TITLE_X, TITLE_Y);
	//	con_outTxt("Use arrows to move point, use Esc to exit.");
		int ch;
		int color;
		int i, j;
		for (i = 0; i < field_width; ++i) {
			for (j = 0; j < field_height; ++j) {
				if ((i == 0 || i == field_width - 1) && (j == 0 || j == field_height - 1)) {
					ch = CHAR_BORDER;
					color = COLOR_BORDER;
				}
				else if ((j >= 1 || j <= 9) && (i == 0 || i == field_width - 1)) {
					ch = j + 47;
					color = COLOR_BORDER;
				}
				else if ((i >= 1 && i <= 10) && (j == 0 || j == field_height - 1)) {
					ch = i + 47;
					color = COLOR_BORDER;
				}
				else {
					continue;
				}
				con_charAt(ch, color, field_x + i, field_y + j);
			}
		}
}
//---------------------------------------------------------------
Drawer::Drawer() {}

void Drawer::InitialDraw() {
	//system("cls");
	int quit = 0;
	int max_x, max_y;
	//draw frames
	con_init();//setlocale & showCursor
	con_hideCursor();
	init_colors();

	//calculate size of field
	con_getMaxXY(&max_x, &max_y);

//	con_clearScr();
//	con_gotoXY(0, 0);

	all_draw();

	point_x = 0;
	point_y = field_y + field_height + 2;
	con_charAt('\0', COLOR_UNBROKEN_SHIP, point_x, point_y);//установить курсор в положение для ввода координат пользователем
//	con_gotoXY(point_x, point_y);
	con_showCursor();
}

void Drawer::changeDraw(const size_t(&Field)[Arena_size][Arena_size]) {
	//	con_clearScr();
	//con_deinit();
	con_hideCursor();
	int i, j;
	int ch;
	int color;
	{
		for (i = 0; i < field_width - 2; i++) {
			for (j = 0; j < field_height - 2; j++) {
				int pointX = i + field_x + 1;
				int pointY = j + field_y + 1;
				color = COLOR_STRIKED_SHIP;
				ch = 'e';

				switch (Field[i][j])
				{
				case COLOR_FREE_WATER:
					ch = FREE_WATER;
					color = COLOR_FREE_WATER;
					break;
				case COLOR_STRIKED_WATER:
					ch = STRIKED_WATER;
					color = COLOR_STRIKED_WATER;
					break;
				case COLOR_UNBROKEN_SHIP:
					ch = UNBROKEN_SHIP;
					color = COLOR_UNBROKEN_SHIP;
					break;
				case COLOR_STRIKED_SHIP:
					ch = STRIKED_SHIP;
					color = COLOR_STRIKED_SHIP;
					break;
				case CHECK:
					ch = FREE_WATER;
					color = CHECK;
					break;
				default:
					break;
				}
				con_charAt(ch, color, pointX, pointY);
			}
		}

		//draw on coordinates
		con_showCursor();
		con_charAt(' ', COLOR_UNBROKEN_SHIP, point_x, point_y);
		con_gotoXY(point_x, point_y);
	}
}

void Drawer::clearTxt(size_t x1, size_t y1, size_t x2, size_t y2) {
	con_hideCursor();
	for (size_t i = x1; (i <= x2) && (i >= x1); i++) {
		for (size_t j = y1; (j <= y2) && (j >= y1); j++) {
			con_charAt(' ', COLOR_UNBROKEN_SHIP, i, j);
		}
	}
	con_gotoXY(point_x, point_y);
	con_showCursor();
}

void Drawer::moveField(size_t x, size_t y) {
	field_x = x;
	field_y = y;
}
//-----------------------------------------------
void Drawer::is_pressed(int key) {
	bool quite = false;
	while (!quite) {
		if (con_keyPressed()) {
			if (con_getKey() == key) {
				quite = 1;
			}
		}
	}
}