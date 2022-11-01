#include"BattleShips.h"
// system("cls")
int GetRandomInt(int min, int max) {
	//srand(time(NULL));
	return min + (rand() % (max - min));
}
Game::Arena::Arena() {
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = 0; j < 10; j++) {
			Arena_arr[i][j] = 0;
		}
	}
	Arena_the_break = 0;
};
bool Game::Arena::Defeat_condition() {
	return (Arena_the_break == 20);
};
Game::Player_stage_1::Player_stage_1(size_t Tactics, Arena& My_flotilla_get) : My_flotilla(My_flotilla_get) {
	Player_tactics = Tactics;
};
void Game::Player_stage_1::Build() {
	Tactics* Gamer = nullptr;
	switch (Player_tactics)
	{
	case (0):
		Gamer = new Tactics_Player;
		break;
	case (1):
		Gamer = new Tactics_Random;
		break;
	case (2):
		Gamer = new Tactics_Smart;
		break;
	default:
		break;
	}
	Gamer->Build(My_flotilla);
};
Game::Player_stage_2::Player_stage_2(size_t Tactics, Arena& Enemy_flotilla_get, Arena& Enemy_flotilla_see_get) : Enemy_flotilla(Enemy_flotilla_get), Enemy_flotilla_see(Enemy_flotilla_see_get) {
	Player_tactics = Tactics;
};
void Game::Player_stage_2::Strike() {
	Tactics* Gamer = nullptr;
	switch (Player_tactics)
	{
	case (0):
		Gamer = new Tactics_Player;
		break;
	case (1):
		Gamer = new Tactics_Random;
		break;
	case (2):
		Gamer = new Tactics_Smart;
		break;
	default:
		break;
	}
	Gamer->Strike(Enemy_flotilla, Enemy_flotilla_see);
};
void Game::Tactics_Player::Build(Arena& flotilla) {
	int x1, y1, x2, y2, k = 0;
	Arena Arena_new;
	Draw1.InitialDraw();
	Draw2.moveField(30, 1);
	Draw2.InitialDraw();
	while (k == 0) {
		Draw1.clearTxt();
		cout << "Enter the start and end coordinates for a size 4 ship (x1 y1 x2 y2)\n";
		std::cin >> x1 >> y1 >> x2 >> y2;
		if ((x1 == x2 || y1 == y2) && ((abs(x2 - x1) == 3) || (abs(y2 - y1) == 3)) && (0 <= x1) && (x1 <= 9) && (0 <= y1) && (y1 <= 9) && (0 <= x2) && (x2 <= 9) && (0 <= y2) && (y2 <= 9)) {
			Ship Ship_4(x1, y1, x2, y2);
			Ship_4.Build(flotilla);
			k = 1;
		}
	}
	Draw1.changeDraw(flotilla.Arena_arr);
	Draw2.changeDraw(Arena_new.Arena_arr);
	for (int t = 0; t < 2; t++) {
		k = 0;
		while (k == 0) {
			Draw1.clearTxt();
			cout << "Enter the start and end coordinates for a size 3 ship (x1 y1 x2 y2)\n";
			std::cin >> x1 >> y1 >> x2 >> y2;
			if ((x1 == x2 || y1 == y2) && ((abs(x2 - x1) == 2) || (abs(y2 - y1) == 2)) && (0 <= x1) && (x1 <= 9) && (0 <= y1) && (y1 <= 9) && (0 <= x2) && (x2 <= 9) && (0 <= y2) && (y2 <= 9) && (flotilla.Arena_arr[x1][y1] != 5) && (flotilla.Arena_arr[x2][y2] != 5) && (flotilla.Arena_arr[x1][y1] != 2) && (flotilla.Arena_arr[x2][y2] != 2)) {
				Ship Ship_3(x1, y1, x2, y2);
				Ship_3.Build(flotilla);
				k = 1;
			}
		}
		Draw1.changeDraw(flotilla.Arena_arr);
		Draw2.changeDraw(Arena_new.Arena_arr);
	}
	for (int t = 0; t < 3; t++) {
		k = 0;
		while (k == 0) {
			Draw1.clearTxt();
			cout << "Enter the start and end coordinates for a size 2 ship (x1 y1 x2 y2)\n";
			std::cin >> x1 >> y1 >> x2 >> y2;
			if ((x1 == x2 || y1 == y2) && ((abs(x2 - x1) == 1) || (abs(y2 - y1) == 1)) && (0 <= x1) && (x1 <= 9) && (0 <= y1) && (y1 <= 9) && (0 <= x2) && (x2 <= 9) && (0 <= y2) && (y2 <= 9) && (flotilla.Arena_arr[x1][y1] != 5) && (flotilla.Arena_arr[x2][y2] != 5) && (flotilla.Arena_arr[x1][y1] != 2) && (flotilla.Arena_arr[x2][y2] != 2)) {
				Ship Ship_2(x1, y1, x2, y2);
				Ship_2.Build(flotilla);
				k = 1;
			}
		}
		Draw1.changeDraw(flotilla.Arena_arr);
		Draw2.changeDraw(Arena_new.Arena_arr);
	}
	for (int t = 0; t < 4; t++) {
		k = 0;
		while (k == 0) {
			Draw1.clearTxt();
			cout << "Enter the start and end coordinates for a size 1 ship (x1 y1)\n";
			std::cin >> x1 >> y1;
			if ((0 <= x1) && (x1 <= 9) && (0 <= y1) && (y1 <= 9) && (flotilla.Arena_arr[x1][y1] != 5) && (flotilla.Arena_arr[x1][y1] != 2)) {
				Ship Ship_1(x1, y1, x1, y1);
				Ship_1.Build(flotilla);
				k = 1;
			}
		}
		Draw1.changeDraw(flotilla.Arena_arr);
		Draw2.changeDraw(Arena_new.Arena_arr);
	}
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = 0; j < 10; j++) {
			if (flotilla.Arena_arr[i][j] == 5)
				flotilla.Arena_arr[i][j] = 0;
		}
	}
};
void Game::Tactics_Player::Strike(Arena& flotilla, Arena& flotilla_see) {
	size_t x1, y1, k = 0, counter_2, counter_3;
	while (k == 0) {
		counter_2 = 0;
		counter_3 = 0;
		Draw1.clearTxt();
		cout << "Enter coordinates for the attack(x1 y1)\n";
		std::cin >> x1 >> y1;
		if (flotilla.Arena_arr[x1][y1] == 0) {
			flotilla.Arena_arr[x1][y1] = 1;
			flotilla_see.Arena_arr[x1][y1] = 1;
			k = 1;
		}
		if (flotilla.Arena_arr[x1][y1] == 2) {
			flotilla.Arena_the_break = flotilla.Arena_the_break + 1;
			flotilla.Arena_arr[x1][y1] = 3;
			flotilla_see.Arena_arr[x1][y1] = 3;
			if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9)) {
				if (flotilla.Arena_arr[x1 - 1][y1] == 2)
					counter_2 = counter_2 + 1;
				if (flotilla.Arena_arr[x1 - 1][y1] == 3) {
					counter_3 = counter_3 + 1;
					if ((0 <= (x1 - 2)) && ((x1 - 2) <= 9)) {
						if (flotilla.Arena_arr[x1 - 2][y1] == 3) {
							if ((0 <= (x1 - 3)) && ((x1 - 3) <= 9)) {
								if (flotilla.Arena_arr[x1 - 3][y1] == 3) {
									Ship Ship_4(x1, y1, (x1 - 3), y1);
									Ship_4.Destruction(flotilla, flotilla_see);
								}
								else {
									if (flotilla.Arena_arr[x1 - 3][y1] != 2) {
										if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9)) {
											if (flotilla.Arena_arr[x1 + 1][y1] == 3) {
												Ship Ship_4((x1 + 1), y1, (x1 - 2), y1);
												Ship_4.Destruction(flotilla, flotilla_see);
											}
											else {
												if (flotilla.Arena_arr[x1 + 1][y1] != 2) {
													Ship Ship_3(x1, y1, (x1 - 2), y1);
													Ship_3.Destruction(flotilla, flotilla_see);
												}
											}
										}
										else {
											Ship Ship_3(x1, y1, (x1 - 2), y1);
											Ship_3.Destruction(flotilla, flotilla_see);
										}
									}
								}
							}
							else {
								if (flotilla.Arena_arr[x1 + 1][y1] == 3) {
									Ship Ship_4((x1 + 1), y1, (x1 - 2), y1);
									Ship_4.Destruction(flotilla, flotilla_see);
								}
								else {
									if (flotilla.Arena_arr[x1 + 1][y1] != 2) {
										Ship Ship_3(x1, y1, (x1 - 2), y1);
										Ship_3.Destruction(flotilla, flotilla_see);
									}
								}
							}
						}
						else {
							if (flotilla.Arena_arr[x1 - 2][y1] != 2) {
								if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9)) {
									if (flotilla.Arena_arr[x1 + 1][y1] == 3) {
										if ((0 <= (x1 + 2)) && ((x1 + 2) <= 9)) {
											if (flotilla.Arena_arr[x1 + 2][y1] == 3) {
												Ship Ship_4((x1 + 2), y1, (x1 - 1), y1);
												Ship_4.Destruction(flotilla, flotilla_see);
											}
											else {
												if (flotilla.Arena_arr[x1 + 2][y1] != 2) {
													Ship Ship_3((x1 + 1), y1, (x1 - 1), y1);
													Ship_3.Destruction(flotilla, flotilla_see);
												}
											}
										}
										else {
											Ship Ship_3((x1 + 1), y1, (x1 - 1), y1);
											Ship_3.Destruction(flotilla, flotilla_see);
										}
									}
									else {
										if (flotilla.Arena_arr[x1 + 1][y1] != 2) {
											Ship Ship_2(x1, y1, (x1 - 1), y1);
											Ship_2.Destruction(flotilla, flotilla_see);
										}
									}
								}
								else {
									Ship Ship_2(x1, y1, (x1 - 1), y1);
									Ship_2.Destruction(flotilla, flotilla_see);
								}
							}
						}
					}
					else {
						if (flotilla.Arena_arr[x1 + 1][y1] == 3) {
							if (flotilla.Arena_arr[x1 + 2][y1] == 3) {
								Ship Ship_4((x1 + 2), y1, (x1 - 1), y1);
								Ship_4.Destruction(flotilla, flotilla_see);
							}
							else {
								if (flotilla.Arena_arr[x1 + 2][y1] != 2) {
									Ship Ship_3((x1 + 1), y1, (x1 - 1), y1);
									Ship_3.Destruction(flotilla, flotilla_see);
								}
							}
						}
						else {
							if (flotilla.Arena_arr[x1 + 1][y1] != 2) {
								Ship Ship_2(x1, y1, (x1 - 1), y1);
								Ship_2.Destruction(flotilla, flotilla_see);
							}
						}
					}
				}
				else {
					if (flotilla.Arena_arr[x1 - 1][y1] != 2) {
						if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9)) {
							if (flotilla.Arena_arr[x1 + 1][y1] == 3) {
								if ((0 <= (x1 + 2)) && ((x1 + 2) <= 9)) {
									if (flotilla.Arena_arr[x1 + 2][y1] == 3) {
										if ((0 <= (x1 + 3)) && ((x1 + 3) <= 9)) {
											if (flotilla.Arena_arr[x1 + 3][y1] == 3) {
												Ship Ship_4((x1 + 3), y1, x1, y1);
												Ship_4.Destruction(flotilla, flotilla_see);
											}
											else {
												if (flotilla.Arena_arr[x1 + 3][y1] != 2) {
													Ship Ship_3((x1 + 2), y1, x1, y1);
													Ship_3.Destruction(flotilla, flotilla_see);
												}
											}
										}
										else {
											Ship Ship_3((x1 + 2), y1, x1, y1);
											Ship_3.Destruction(flotilla, flotilla_see);
										}
									}
									else {
										if (flotilla.Arena_arr[x1 + 2][y1] != 2) {
											Ship Ship_2((x1 + 1), y1, x1, y1);
											Ship_2.Destruction(flotilla, flotilla_see);
										}
									}
								}
								else {
									Ship Ship_2((x1 + 1), y1, x1, y1);
									Ship_2.Destruction(flotilla, flotilla_see);
								}
							}
						}
					}
				}
			}
			if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9)) {
				if (flotilla.Arena_arr[x1 + 1][y1] == 2)
					counter_2 = counter_2 + 1;
				if (flotilla.Arena_arr[x1 + 1][y1] == 3)
					counter_3 = counter_3 + 1;
			}
			if ((0 <= (y1 - 1)) && ((y1 - 1) <= 9)) {
				if (flotilla.Arena_arr[x1][y1 - 1] == 2)
					counter_2 = counter_2 + 1;
				if (flotilla.Arena_arr[x1][y1 - 1] == 3) {
					counter_3 = counter_3 + 1;
					if ((0 <= (y1 - 2)) && ((y1 - 2) <= 9)) {
						if (flotilla.Arena_arr[x1][y1 - 2] == 3) {
							if ((0 <= (y1 - 3)) && ((y1 - 3) <= 9)) {
								if (flotilla.Arena_arr[x1][y1 - 3] == 3) {
									Ship Ship_4(x1, y1, x1, (y1 - 3));
									Ship_4.Destruction(flotilla, flotilla_see);
								}
								else {
									if (flotilla.Arena_arr[x1][y1 - 3] != 2) {
										if ((0 <= (y1 + 1)) && ((y1 + 1) <= 9)) {
											if (flotilla.Arena_arr[x1][y1 + 1] == 3) {
												Ship Ship_4(x1, (y1 + 1), x1, (y1 - 2));
												Ship_4.Destruction(flotilla, flotilla_see);
											}
											else {
												if (flotilla.Arena_arr[x1][y1 + 1] != 2) {
													Ship Ship_3(x1, y1, x1, (y1 - 2));
													Ship_3.Destruction(flotilla, flotilla_see);
												}
											}
										}
										else {
											Ship Ship_3(x1, y1, x1, (y1 - 2));
											Ship_3.Destruction(flotilla, flotilla_see);
										}
									}
								}
							}
							else {
								if (flotilla.Arena_arr[x1][y1 + 1] == 3) {
									Ship Ship_4(x1, (y1 + 1), x1, (y1 - 2));
									Ship_4.Destruction(flotilla, flotilla_see);
								}
								else {
									if (flotilla.Arena_arr[x1][y1 + 1] != 2) {
										Ship Ship_3(x1, y1, x1, (y1 - 2));
										Ship_3.Destruction(flotilla, flotilla_see);
									}
								}
							}
						}
						else {
							if (flotilla.Arena_arr[x1][y1 - 2] != 2) {
								if ((0 <= (y1 + 1)) && ((y1 + 1) <= 9)) {
									if (flotilla.Arena_arr[x1][y1 + 1] == 3) {
										if ((0 <= (y1 + 2)) && ((y1 + 2) <= 9)) {
											if (flotilla.Arena_arr[x1][y1 + 2] == 3) {
												Ship Ship_4(x1, (y1 + 2), x1, (y1 - 1));
												Ship_4.Destruction(flotilla, flotilla_see);
											}
											else {
												if (flotilla.Arena_arr[x1][y1 + 2] != 2) {
													Ship Ship_3(x1, (y1 + 1), x1, (y1 - 1));
													Ship_3.Destruction(flotilla, flotilla_see);
												}
											}
										}
										else {
											Ship Ship_3(x1, (y1 + 1), x1, (y1 - 1));
											Ship_3.Destruction(flotilla, flotilla_see);
										}
									}
									else {
										if (flotilla.Arena_arr[x1][y1 + 1] != 2) {
											Ship Ship_2(x1, y1, x1, (y1 - 1));
											Ship_2.Destruction(flotilla, flotilla_see);
										}
									}
								}
								else {
									Ship Ship_2(x1, y1, x1, (y1 - 1));
									Ship_2.Destruction(flotilla, flotilla_see);
								}
							}
						}
					}
					else {
						if (flotilla.Arena_arr[x1][y1 + 1] == 3) {
							if (flotilla.Arena_arr[x1][y1 + 2] == 3) {
								Ship Ship_4(x1, (y1 + 2), x1, (y1 - 1));
								Ship_4.Destruction(flotilla, flotilla_see);
							}
							else {
								if (flotilla.Arena_arr[x1][y1 + 2] != 2) {
									Ship Ship_3(x1, (y1 + 1), x1, (y1 - 1));
									Ship_3.Destruction(flotilla, flotilla_see);
								}
							}
						}
						else {
							if (flotilla.Arena_arr[x1][y1 + 1] != 2) {
								Ship Ship_2(x1, y1, x1, (y1 - 1));
								Ship_2.Destruction(flotilla, flotilla_see);
							}
						}
					}
				}
				else {
					if (flotilla.Arena_arr[x1][y1 - 1] != 2) {
						if ((0 <= (y1 + 1)) && ((y1 + 1) <= 9)) {
							if (flotilla.Arena_arr[x1][y1 + 1] == 3) {
								if ((0 <= (y1 + 2)) && ((y1 + 2) <= 9)) {
									if (flotilla.Arena_arr[x1][y1 + 2] == 3) {
										if ((0 <= (y1 + 3)) && ((y1 + 3) <= 9)) {
											if (flotilla.Arena_arr[x1][y1 + 3] == 3) {
												Ship Ship_4(x1, (y1 + 3), x1, y1);
												Ship_4.Destruction(flotilla, flotilla_see);
											}
											else {
												if (flotilla.Arena_arr[x1][y1 + 3] != 2) {
													Ship Ship_3(x1, (y1 + 2), x1, y1);
													Ship_3.Destruction(flotilla, flotilla_see);
												}
											}
										}
										else {
											Ship Ship_3(x1, (y1 + 2), x1, y1);
											Ship_3.Destruction(flotilla, flotilla_see);
										}
									}
									else {
										if (flotilla.Arena_arr[x1][y1 + 2] != 2) {
											Ship Ship_2(x1, (y1 + 1), x1, y1);
											Ship_2.Destruction(flotilla, flotilla_see);
										}
									}
								}
								else {
									Ship Ship_2(x1, (y1 + 1), x1, y1);
									Ship_2.Destruction(flotilla, flotilla_see);
								}
							}
						}
					}
				}
			}
			if ((0 <= (y1 + 1)) && ((y1 + 1) <= 9)) {
				if (flotilla.Arena_arr[x1][y1 + 1] == 2)
					counter_2 = counter_2 + 1;
				if (flotilla.Arena_arr[x1][y1 + 1] == 3)
					counter_3 = counter_3 + 1;
			}
		}
		if ((counter_2 == 0) && (counter_3 == 0)) {
			Ship Ship_1(x1, y1, x1, y1);
			Ship_1.Destruction(flotilla, flotilla_see);
		}
		Draw2.changeDraw(flotilla_see.Arena_arr);
	}
};

void Game::Tactics_Random::Build(Arena& flotilla) {
		int x1;
		int y1;
		int x2;
		int y2;
		int k = 0;
		int count = 0;
		srand(time(NULL));
		while (k == 0) {

			x1 = 3 + abs((int)rand() % 4);
			y1 = 3 + abs((int)rand() % 4);
			x2 = x1 + 3 * ((int)rand() % 2);
			if (x2 == x1) {
				y2 = y1 + 3 * ((int)rand() % 2);
			}
			else {
				y2 = y1;
			}
			if ((x1 == x2 || y1 == y2) && ((abs(x2 - x1) == 3) || (abs(y2 - y1) == 3)) && (0 <= x1) && (x1 <= 9) && (0 <= y1) && (y1 <= 9) && (0 <= x2) && (x2 <= 9) && (0 <= y2) && (y2 <= 9)) {
				Ship Ship_4(x1, y1, x2, y2);
				Ship_4.Build(flotilla);
				k = 1;
			}
		}
		for (int t = 0; t < 2; t++) {
			k = 0;
			while (k == 0) {
				x1 = 2 + abs((int)rand() % 6);
				y1 = 2 + abs((int)rand() % 6);
				x2 = x1 + 2 * ((int)rand() % 2);
				if (x2 == x1) {
					y2 = y1 + 2 * ((int)rand() % 2);
				}
				else {
					y2 = y1;
				}
				if ((x1 == x2 || y1 == y2) && ((abs(x2 - x1) == 2) || (abs(y2 - y1) == 2)) && (0 <= x1) && (x1 <= 9) && (0 <= y1) && (y1 <= 9) && (0 <= x2) && (x2 <= 9) && (0 <= y2) && (y2 <= 9) && (flotilla.Arena_arr[x1][y1] != 5) && (flotilla.Arena_arr[x2][y2] != 5) && (flotilla.Arena_arr[x1][y1] != 2) && (flotilla.Arena_arr[x2][y2] != 2)) {
					Ship Ship_3(x1, y1, x2, y2);
					Ship_3.Build(flotilla);
					k = 1;
				}
			}
		}
		for (int t = 0; t < 3; t++) {
			k = 0;
			while (k == 0) {
				x1 = 1 + abs((int)rand() % 8);
				y1 = 1 + abs((int)rand() % 8);
				x2 = x1 + ((int)rand() % 2);
				if (x2 == x1) {
					y2 = y1 + ((int)rand() % 2);
				}
				else {
					y2 = y1;
				}
				if ((x1 == x2 || y1 == y2) && ((abs(x2 - x1) == 1) || (abs(y2 - y1) == 1)) && (0 <= x1) && (x1 <= 9) && (0 <= y1) && (y1 <= 9) && (0 <= x2) && (x2 <= 9) && (0 <= y2) && (y2 <= 9) && (flotilla.Arena_arr[x1][y1] != 5) && (flotilla.Arena_arr[x2][y2] != 5) && (flotilla.Arena_arr[x1][y1] != 2) && (flotilla.Arena_arr[x2][y2] != 2)) {
					Ship Ship_2(x1, y1, x2, y2);
					Ship_2.Build(flotilla);
					k = 1;
				}
			}
		}
		for (int t = 0; t < 4; t++) {
			k = 0;
			while (k == 0) {
				x1 = abs((int)rand() % 10);
				y1 = abs((int)rand() % 10);
				if ((0 <= x1) && (x1 <= 9) && (0 <= y1) && (y1 <= 9) && (flotilla.Arena_arr[x1][y1] != 5) && (flotilla.Arena_arr[x1][y1] != 2)) {
					Ship Ship_1(x1, y1, x1, y1);
					Ship_1.Build(flotilla);
					k = 1;
				}//необходимо подключить cstdlib и ctime
			}
		}
		for (size_t i = 0; i < 10; i++) {
			for (size_t j = 0; j < 10; j++) {
				if (flotilla.Arena_arr[i][j] == 5)
					flotilla.Arena_arr[i][j] = 0;
			}
		}
	
	//***********************************************************************************************************
};
void Game::Tactics_Random::Strike(Arena& flotilla, Arena& flotilla_see) {
	int eosh = 0;//когда закончим стрелять?
	while (eosh == 0) {
		int k = 0;
		while (k == 0) {
			int x = abs((int)rand() % 10);
			int y = abs((int)rand() % 10);
			if (flotilla_see.Arena_arr[x][y] != 1 && flotilla_see.Arena_arr[x][y] != 3) {
				k = 1;

				if (flotilla.Arena_arr[x][y] == 2) {
					flotilla_see.Arena_arr[x][y] = 3;
					flotilla.Arena_arr[x][y] = 3;
					bool was_died = 1;
					int tmpx = x;
					int tmpy = y;
					if (x + 1 <= 9) {//////////////////////////////////////////////////////////////////////////////////////
						if (flotilla.Arena_arr[x + 1][y] == 3) {
							tmpx++;
							while ((flotilla.Arena_arr[tmpx][tmpy] != 0) || (flotilla.Arena_arr[tmpx][tmpy] != 1)) {
								if (flotilla.Arena_arr[tmpx][tmpy] == 2) {
									was_died = 0;
									break;
								}
								if (tmpx + 1 <= 9) {
									tmpx++;
								}
								else {
									break;
								}
							}
							tmpx = x;
							while ((flotilla.Arena_arr[tmpx][tmpy] != 0) || (flotilla.Arena_arr[tmpx][tmpy] != 1)) {
								if (flotilla.Arena_arr[tmpx][tmpy] == 2 || !was_died) {
									was_died = 0;
									break;
								}
								if (tmpx - 1 >= 0) {
									tmpx--;
								}
								else {
									break;
								}
							}
							if (was_died) {
								if (tmpy + 1 <= 9 && tmpx - 1 >= 0) {
									flotilla_see.Arena_arr[tmpx - 1][tmpy + 1] = 1;
									flotilla.Arena_arr[tmpx - 1][tmpy + 1] = 1;
								}
								if (tmpx - 1 >= 0) {
									flotilla_see.Arena_arr[tmpx - 1][tmpy] = 1;
									flotilla.Arena_arr[tmpx - 1][tmpy] = 1;
								}
								if (tmpy - 1 >= 0 && tmpx - 1 >= 0) {
									flotilla_see.Arena_arr[tmpx - 1][tmpy - 1] = 1;
									flotilla.Arena_arr[tmpx - 1][tmpy - 1] = 1;
								}
								while ((flotilla.Arena_arr[tmpx][tmpy] != 0) || (flotilla.Arena_arr[tmpx][tmpy] != 1)) {
									if (tmpy + 1 <= 9) {
										flotilla_see.Arena_arr[tmpx][tmpy + 1] = 1;
										flotilla.Arena_arr[tmpx][tmpy + 1] = 1;
									}
									if (tmpy - 1 >= 0) {
										flotilla_see.Arena_arr[tmpx][tmpy - 1] = 1;
										flotilla.Arena_arr[tmpx][tmpy - 1] = 1;
									}
									if (tmpx + 1 <= 9) {
										tmpx++;
									}
									else {
										break;
									}
									if (tmpy + 1 <= 9 && tmpx + 1 <= 9) {
										flotilla_see.Arena_arr[tmpx + 1][tmpy + 1] = 1;
										flotilla.Arena_arr[tmpx + 1][tmpy + 1] = 1;
									}
									if (tmpx + 1 <= 9) {
										flotilla_see.Arena_arr[tmpx + 1][tmpy] = 1;
										flotilla.Arena_arr[tmpx + 1][tmpy] = 1;
									}
									if (tmpy - 1 >= 0 && tmpx + 1 <= 9) {
										flotilla_see.Arena_arr[tmpx + 1][tmpy - 1] = 1;
										flotilla.Arena_arr[tmpx + 1][tmpy - 1] = 1;
									}
								}
							}
						}
						if (x - 1 >= 0) {//////////////////////////////////////////////////////////////////////////////////////////
							if (flotilla.Arena_arr[x - 1][y] == 3) {
								tmpx--;
								while ((flotilla.Arena_arr[tmpx][tmpy] != 0) || (flotilla.Arena_arr[tmpx][tmpy] != 1)) {
									if (flotilla.Arena_arr[tmpx][tmpy] == 2) {
										was_died = 0;
										break;
									}
									if (tmpx - 1 >= 0) {
										tmpx--;
									}
									else {
										break;
									}
								}
								tmpx = x;
								while ((flotilla.Arena_arr[tmpx][tmpy] != 0) || (flotilla.Arena_arr[tmpx][tmpy] != 1)) {
									if (flotilla.Arena_arr[tmpx][tmpy] == 2 || !was_died) {
										was_died = 0;
										break;
									}
									if (tmpx + 1 <= 9) {
										tmpx++;
									}
									else {
										break;
									}
								}
								if (was_died) {
									if (tmpy + 1 <= 9 && tmpx + 1 <= 9) {
										flotilla_see.Arena_arr[tmpx + 1][tmpy + 1] = 1;
										flotilla.Arena_arr[tmpx + 1][tmpy + 1] = 1;
									}
									if (tmpx + 1 <= 9) {
										flotilla_see.Arena_arr[tmpx + 1][tmpy] = 1;
										flotilla.Arena_arr[tmpx + 1][tmpy] = 1;
									}
									if (tmpy - 1 >= 0 && tmpx + 1 <= 9) {
										flotilla_see.Arena_arr[tmpx + 1][tmpy - 1] = 1;
										flotilla.Arena_arr[tmpx + 1][tmpy - 1] = 1;
									}
									while ((flotilla.Arena_arr[tmpx][tmpy] != 0) || (flotilla.Arena_arr[tmpx][tmpy] != 1)) {
										if (tmpy + 1 <= 9) {
											flotilla_see.Arena_arr[tmpx][tmpy + 1] = 1;
											flotilla.Arena_arr[tmpx][tmpy + 1] = 1;
										}
										if (tmpy - 1 >= 0) {
											flotilla_see.Arena_arr[tmpx][tmpy - 1] = 1;
											flotilla.Arena_arr[tmpx][tmpy - 1] = 1;
										}
										if (tmpx - 1 >= 0) {
											tmpx--;
										}
										else {
											break;
										}
										if (tmpx - 1 >= 0 && tmpy + 1 <= 9) {
											flotilla_see.Arena_arr[tmpx - 1][tmpy + 1] = 1;
											flotilla.Arena_arr[tmpx - 1][tmpy + 1] = 1;
										}
										if (tmpx - 1 >= 0) {
											flotilla_see.Arena_arr[tmpx - 1][tmpy] = 1;
											flotilla.Arena_arr[tmpx - 1][tmpy] = 1;
										}
										if (tmpy - 1 >= 0 && tmpx - 1 >= 0) {
											flotilla_see.Arena_arr[tmpx - 1][tmpy - 1] = 1;
											flotilla.Arena_arr[tmpx - 1][tmpy - 1] = 1;
										}
									}
								}
							}
							if (y - 1 >= 0) {//////////////////////////////////////////////////////////////////////////////////////////
								if (flotilla.Arena_arr[x][y - 1] == 2 || flotilla.Arena_arr[x][y - 1] == 3) {
									tmpy--;
									while ((flotilla.Arena_arr[tmpx][tmpy] != 0) || (flotilla.Arena_arr[tmpx][tmpy] != 1)) {
										if (flotilla.Arena_arr[tmpx][tmpy] == 2) {
											was_died = 0;
											break;
										}
										if (tmpy - 1 >= 0) {
											tmpy--;
										}
										else {
											break;
										}
									}
									tmpy = y;
									while ((flotilla.Arena_arr[tmpx][tmpy] != 0) || (flotilla.Arena_arr[tmpx][tmpy] != 1)) {
										if (flotilla.Arena_arr[tmpx][tmpy] == 2 || !was_died) {
											was_died = 0;
											break;
										}
										if (tmpy + 1 <= 9) {
											tmpy++;
										}
										else {
											break;
										}
									}
									if (was_died) {
										if (tmpy + 1 <= 9 && tmpx - 1 >= 0) {
											flotilla_see.Arena_arr[tmpx - 1][tmpy + 1] = 1;
											flotilla.Arena_arr[tmpx - 1][tmpy + 1] = 1;
										}
										if (tmpy + 1 <= 9) {
											flotilla_see.Arena_arr[tmpx][tmpy + 1] = 1;
											flotilla.Arena_arr[tmpx - 1][tmpy] = 1;
										}
										if (tmpy + 1 <= 9 && tmpx + 1 <= 9) {
											flotilla_see.Arena_arr[tmpx + 1][tmpy + 1] = 1;
											flotilla.Arena_arr[tmpx + 1][tmpy + 1] = 1;
										}
										while ((flotilla.Arena_arr[tmpx][tmpy] != 0) || (flotilla.Arena_arr[tmpx][tmpy] != 1)) {
											if (tmpx + 1 <= 9) {
												flotilla_see.Arena_arr[tmpx + 1][tmpy] = 1;
												flotilla.Arena_arr[tmpx + 1][tmpy] = 1;
											}
											if (tmpx - 1 >= 0) {
												flotilla_see.Arena_arr[tmpx - 1][tmpy] = 1;
												flotilla.Arena_arr[tmpx - 1][tmpy] = 1;
											}
											if (tmpy - 1 >= 0) {
												tmpy--;
											}
											else {
												break;
											}
											if (tmpy - 1 >= 0 && tmpx + 1 <= 9) {
												flotilla_see.Arena_arr[tmpx + 1][tmpy - 1] = 1;
												flotilla.Arena_arr[tmpx + 1][tmpy - 1] = 1;
											}
											if (tmpy - 1 <= 0) {
												flotilla_see.Arena_arr[tmpx][tmpy - 1] = 1;
												flotilla.Arena_arr[tmpx][tmpy - 1] = 1;
											}
											if (tmpy - 1 >= 0 && tmpx - 1 >= 0) {
												flotilla_see.Arena_arr[tmpx - 1][tmpy - 1] = 1;
												flotilla.Arena_arr[tmpx - 1][tmpy - 1] = 1;
											}
										}
									}
								}

							}
							if (y + 1 <= 9) {//////////////////////////////////////////////////////////////////////////////////////////
								if (flotilla.Arena_arr[x][y + 1] == 2 || flotilla.Arena_arr[x][y + 1] == 3) {
									tmpx++;
									while ((flotilla.Arena_arr[tmpx][tmpy]) != 0 || (flotilla.Arena_arr[tmpx][tmpy] != 1)) {
										if (flotilla.Arena_arr[tmpx][tmpy] == 2) {
											was_died = 0;
											break;
										}
										if (tmpy + 1 <= 9) {
											tmpy++;
										}
										else {
											break;
										}
									}
									tmpy = y;
									while ((flotilla.Arena_arr[tmpx][tmpy] != 0) || (flotilla.Arena_arr[tmpx][tmpy] != 1)) {
										if (flotilla.Arena_arr[tmpx][tmpy] == 2 || !was_died) {
											was_died = 0;
											break;
										}
										if (tmpy - 1 >= 0) {
											tmpy--;
										}
										else {
											break;
										}
									}
									if (was_died) {
										if (tmpy - 1 >= 0 && tmpx - 1 >= 0) {
											flotilla_see.Arena_arr[tmpx - 1][tmpy - 1] = 1;
											flotilla.Arena_arr[tmpx - 1][tmpy - 1] = 1;
										}
										if (tmpy - 1 >= 0) {
											flotilla_see.Arena_arr[tmpx][tmpy - 1] = 1;
											flotilla.Arena_arr[tmpx][tmpy - 1] = 1;
										}
										if (tmpy - 1 >= 0 && tmpx + 1 <= 9) {
											flotilla_see.Arena_arr[tmpx][tmpy - 1] = 1;
											flotilla.Arena_arr[tmpx][tmpy - 1] = 1;
										}
										while (flotilla.Arena_arr[tmpy][tmpy] != 0 || flotilla.Arena_arr[tmpy][tmpy] != 1) {
											if (tmpx + 1 <= 9) {
												flotilla_see.Arena_arr[tmpx + 1][tmpy] = 1;
												flotilla.Arena_arr[tmpx + 1][tmpy] = 1;
											}
											if (tmpx - 1 >= 0) {
												flotilla_see.Arena_arr[tmpx - 1][tmpy] = 1;
												flotilla.Arena_arr[tmpx - 1][tmpy] = 1;
											}
											if (tmpy + 1 <= 9) {
												tmpy++;
											}
											else {
												break;
											}
											if (tmpy + 1 <= 9 && tmpx + 1 <= 9) {
												flotilla_see.Arena_arr[tmpx + 1][tmpy + 1] = 1;
												flotilla.Arena_arr[tmpx + 1][tmpy + 1] = 1;
											}
											if (tmpy + 1 <= 9) {
												flotilla_see.Arena_arr[tmpx][tmpy + 1] = 1;
												flotilla.Arena_arr[tmpx][tmpy + 1] = 1;
											}
											if (tmpy + 1 >= 0 && tmpx - 1 >= 0) {
												flotilla_see.Arena_arr[tmpx][tmpy - 1] = 1;
												flotilla.Arena_arr[tmpx][tmpy - 1] = 1;
											}
										}
									}
								}

							}
						}


					}
				}
				else {
					eosh = 1;
				}
			}

		}
	}
};
void Game::Tactics_Smart::Build(Arena& flotilla) {
	int x1, y1, x2, y2, k = 0, count = 0;
	srand(time(NULL));
	while (k == 0) {
		if (count <= 25) {
			x1 = 4 + abs((int)rand() % 3);
			y1 = 3 + abs((int)rand() % 4);//верхний правый угол
			x2 = x1 + 3 * abs((int)rand() % 2);
			if (x2 == x1) {
				y2 = y1 + 3 * abs((int)rand() % 2);
			}
			else {
				y2 = y1;
			}
			count++;
		}
		else {
			x1 = 3 + abs((int)rand() % 4);
			y1 = 3 + abs((int)rand() % 4);
			x2 = x1 + 3 * ((int)rand() % 2);
			if (x2 == x1) {
				y2 = y1 + 3 * ((int)rand() % 2);
			}
			else {
				y2 = y1;
			}
		}
		if ((x1 == x2 || y1 == y2) && ((abs(x2 - x1) == 3) || (abs(y2 - y1) == 3)) && (0 <= x1) && (x1 <= 9) && (0 <= y1) && (y1 <= 9) && (0 <= x2) && (x2 <= 9) && (0 <= y2) && (y2 <= 9)) {
			Ship Ship_4(x1, y1, x2, y2);
			Ship_4.Build(flotilla);
			k = 1;
		}
	}
	for (int t = 0; t < 2; t++) {
		k = 0;
		count = 0;
		while (k == 0) {
			if (count <= 25) {
				x1 = 4 + abs((int)rand() % 3);
				y1 = abs((int)rand() % 4);//нижний левый угол
				x2 = x1 + 2 * abs((int)rand() % 2);
				if (x2 == x1) {
					y2 = y1 + 2 * abs((int)rand() % 2);
				}
				else {
					y2 = y1;
				}
				count++;
			}
			else {
				x1 = 2 + abs((int)rand() % 6);
				y1 = 2 + abs((int)rand() % 6);
				x2 = x1 + 2 * ((int)rand() % 2);
				if (x2 == x1) {
					y2 = y1 + 2 * ((int)rand() % 2);
				}
				else {
					y2 = y1;
				}
			}
			if ((x1 == x2 || y1 == y2) && ((abs(x2 - x1) == 2) || (abs(y2 - y1) == 2)) && (0 <= x1) && (x1 <= 9) && (0 <= y1) && (y1 <= 9) && (0 <= x2) && (x2 <= 9) && (0 <= y2) && (y2 <= 9) && (flotilla.Arena_arr[x1][y1] != 5) && (flotilla.Arena_arr[x2][y2] != 5) && (flotilla.Arena_arr[x1][y1] != 2) && (flotilla.Arena_arr[x2][y2] != 2)) {
				Ship Ship_3(x1, y1, x2, y2);
				Ship_3.Build(flotilla);
				k = 1;
			}
		}
	}
	for (int t = 0; t < 3; t++) {
		k = 0;
		count = 0;
		while (k == 0) {
			if (count <= 25) {
				if (count <= 25) {
					x1 = 1 + abs((int)rand() % 3);//внизу
					y1 = 1 + abs((int)rand() % 8);
					x2 = x1 + abs((int)rand() % 2);
					if (x2 == x1) {
						y2 = y1 + abs((int)rand() % 2);
					}
					else {
						y2 = y1;
					}
					count++;
				}
				else {
					x1 = 1 + abs((int)rand() % 8);
					y1 = 1 + abs((int)rand() % 8);
					x2 = x1 + ((int)rand() % 2);
					if (x2 == x1) {
						y2 = y1 + ((int)rand() % 2);
					}
					else {
						y2 = y1;
					}
				}
				if ((x1 == x2 || y1 == y2) && ((abs(x2 - x1) == 1) || (abs(y2 - y1) == 1)) && (0 <= x1) && (x1 <= 9) && (0 <= y1) && (y1 <= 9) && (0 <= x2) && (x2 <= 9) && (0 <= y2) && (y2 <= 9) && (flotilla.Arena_arr[x1][y1] != 5) && (flotilla.Arena_arr[x2][y2] != 5) && (flotilla.Arena_arr[x1][y1] != 2) && (flotilla.Arena_arr[x2][y2] != 2)) {
					Ship Ship_2(x1, y1, x2, y2);
					Ship_2.Build(flotilla);
					k = 1;
				}
			}
		}
	}
	for (int t = 0; t < 4; t++) {
		k = 0;
		while (k == 0) {
			x1 = abs((int)rand() % 10);
			y1 = abs((int)rand() % 10);
			if ((0 <= x1) && (x1 <= 9) && (0 <= y1) && (y1 <= 9) && (flotilla.Arena_arr[x1][y1] != 5) && (flotilla.Arena_arr[x1][y1] != 2)) {
				Ship Ship_1(x1, y1, x1, y1);
				Ship_1.Build(flotilla);
				k = 1;
			}//необходимо подключить cstdlib и ctime
		}
	}
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = 0; j < 10; j++) {
			if (flotilla.Arena_arr[i][j] == 5)
				flotilla.Arena_arr[i][j] = 0;
		}
	}
};
//-------------------------------------------------------------------------------------------
void Game::Tactics_Smart::Strike(Arena& flotilla, Arena& flotilla_see) {

	if ((is_last_ship_Stricked == true) && (is_last_ship_DIED == false)) {
		//если в предыдущий или нынешний корабль попал, но не убил
		int dX = 0;
		int dY = 0;

		if ((firstX == lastX) && (lastY == firstY)) {
			//нет направления обстрела
			//найти нужное направление
			srand(time(NULL));
			lastDir = GetRandomInt(0, 3);
			//directions[lastDir] = true;

			//con_gotoXY(50, 2);
			//con_outTxt("in 1st");
			//con_gotoXY(0, 25);

			//цикл и булиановский массив нужны, чтобы направления не повторялись
			while (directions[lastDir]) {
				srand(time(NULL));
				lastDir = GetRandomInt(0, 3);

				//con_gotoXY(50, 2);
				//con_outTxt("in 1st");
				//con_gotoXY(0, 25);
			}
			//lastDir = randInd;
			directions[lastDir] = true;

			switch (lastDir)//по часовой стрелке
			{
			case 0:
				dY = -1;
				break;
			case 1:
				dX = 1;
				break;
			case 2:
				dY = 1;
				break;
			case 3:
				dX = -1;
				break;
			default:
				con_gotoXY(50, 25);
				con_outTxt("ERR IN SMART TACTIC WITH DIRECTION");
				break;
			}

			//lastX += dX;
			//lastY += dY;
			//бьем, пока не дойдем до воды
			while ((flotilla.Arena_arr[lastX][lastY] == Drawer::COLOR_UNBROKEN_SHIP) ||(flotilla.Arena_arr[lastX][lastY] == Drawer::COLOR_STRIKED_SHIP)) {
				flotilla.Arena_arr[lastX][lastY] = Drawer::COLOR_STRIKED_SHIP;
				flotilla_see.Arena_arr[lastX][lastY] = Drawer::COLOR_STRIKED_SHIP;

				lastX += dX;
				lastY += dY;
				if (lastX < 0) {
					lastX = 0;
					break;
				}
				if (lastX > 9) {
					lastX = 9;
					break;
				}
				if (lastY < 0) {
					lastY = 0;
					break;
				}
				if (lastY > 9) {
					lastY = 9;
					break;
				}

				//con_gotoXY(50, 0);
				//con_outTxt("in 2nd");
				//con_gotoXY(0, 25);
			}
			if ((firstY != 0) && (lastY != 9) && (firstX != 0) && (lastX != 9)) {
				lastY -= dY;
				lastX -= dX;
			}
			
			//проверка на подбитость всего корабля: last-d=!ship - ставим флаг подбитости, вызываем уничтожение корабля.
			//мб надо будет изменить "Drawer::COLOR_UNBROKEN_SHIP" на "подбитая или неподбитая вода"---------------!!!!!!!!!!!!!!!!!!!!!!!
			if (((flotilla.Arena_arr[firstX - dX][firstY] == Drawer::COLOR_FREE_WATER) || (flotilla.Arena_arr[firstX - dX][firstY] == Drawer::COLOR_STRIKED_WATER)) &&//trables here!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				((flotilla.Arena_arr[firstX][firstY - dY] == Drawer::COLOR_FREE_WATER) || (flotilla.Arena_arr[firstX][firstY - dY] == Drawer::COLOR_STRIKED_WATER)) &&//debug stopped here
				((flotilla.Arena_arr[lastX + dX][lastY] == Drawer::COLOR_FREE_WATER) || (flotilla.Arena_arr[lastX + dX][lastY] == Drawer::COLOR_STRIKED_WATER)) &&
				((flotilla.Arena_arr[lastX][lastY + dY] == Drawer::COLOR_FREE_WATER) || (flotilla.Arena_arr[lastX][lastY + dY] == Drawer::COLOR_STRIKED_WATER))/*корабль подбитый*/) {
				
				//con_gotoXY(40, 1);
				//con_outTxt("in 1st if");
				//con_gotoXY(0, 17);

				is_last_ship_DIED = true;
				is_last_ship_Stricked = true;
				//Ship tmp(firstX, firstY, lastX, lastY);
				//tmp.Destruction(flotilla, flotilla_see);
				Strike(flotilla, flotilla_see);
			}
			else {//если корабль недобит - шли по кораблю, но прошли не весь и попали в воду
				//con_gotoXY(60, 1);
				//con_outTxt("in 1st else");
				//con_gotoXY(0, 25);
				
				is_last_ship_DIED = false;
				is_last_ship_Stricked = true;

				{
					if (dX == 0) {
						if (dY == 1){
							//directions[2] = 1;
							lastDir = 2;
						}	
						else {
							//directions[0] = 1;
							lastDir = 0;
						}
					}
					else if (dX == 1) {
						//directions[1] = 1;
						lastDir = 1;
					}	
					else {
						//directions[3] = 1;
						lastDir = 3;
					}
				}

				flotilla.Arena_arr[lastX + dX][lastY + dY] = Drawer::COLOR_STRIKED_WATER;
				flotilla_see.Arena_arr[lastX + dX][lastY + dY] = Drawer::COLOR_STRIKED_WATER;
				//lastX -= dX;
				//lastY -= dY;
			}

			//is_last_ship_DIED = false;
			//is_last_ship_Stricked = false;
		} else {//есть направление обстрела
			//con_gotoXY(60, 3);
			//con_outTxt("in 2nd else");
			//con_gotoXY(0, 20);

			for (int i = 0; i < 4; i++) {
				directions[i] = false;
			}
			
			//последнее направление было в 1 сторону, а стреляем - в другую
			switch (lastDir)//по часовой стрелке
			{
			case 0:
				dY = 1;
				break;
			case 1:
				dX = -1;
				break;
			case 2:
				dY = -1;
				break;
			case 3:
				dX = 1;
				break;
			default:
				con_gotoXY(50, 25);
				con_outTxt("ERR IN SMART TACTIC WITH DIRECTION");
				break;
			}
			//стрелять пока не уничтожит корабль
			while ((flotilla.Arena_arr[lastX][lastY] == Drawer::COLOR_UNBROKEN_SHIP) || (flotilla.Arena_arr[lastX][lastY] == Drawer::COLOR_STRIKED_SHIP)) {
				flotilla.Arena_arr[firstX][firstY] = Drawer::COLOR_STRIKED_SHIP;
				flotilla_see.Arena_arr[firstX][firstY] = Drawer::COLOR_STRIKED_SHIP;

				firstX += dX;
				firstY += dY;
			}

			//Ship tmp(firstX, firstY, lastX - 1, lastY - 1);
			//tmp.Destruction(flotilla, flotilla_see);//--------------------------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			lastY = 0;
			lastX = 0;
			lastDir = 0;
			is_last_ship_DIED = true;
			is_last_ship_Stricked = true;
			//перевызвать метод
			Strike(flotilla, flotilla_see);
		}

		////бьем, пока не дойдем до воды
		//while (flotilla.Arena_arr[lastX][lastY] == Drawer::COLOR_UNBROKEN_SHIP) {
		//	flotilla.Arena_arr[lastX][lastY] = Drawer::COLOR_STRIKED_SHIP;
		//	flotilla_see.Arena_arr[lastX][lastY] = Drawer::COLOR_STRIKED_SHIP;
		//	lastX += dX;
		//	lastY += dY;
		//}
		//if ((flotilla.Arena_arr[firstX - dX][firstY] != Drawer::COLOR_UNBROKEN_SHIP ||
		//	flotilla.Arena_arr[firstX][firstY - dY] != Drawer::COLOR_UNBROKEN_SHIP) &&
		//	(flotilla.Arena_arr[lastX + dX][lastY] != Drawer::COLOR_UNBROKEN_SHIP ||
		//		flotilla.Arena_arr[lastX][lastY + dY] != Drawer::COLOR_UNBROKEN_SHIP)/*корабль подбитый*/) {
		//	is_last_ship_DIED = true;
		//	is_last_ship_Stricked = true;
		//	//Ship tmp(firstX, firstY, lastX, lastY);
		//	//tmp.Destruction(flotilla, flotilla_see);
		//	Strike(flotilla, flotilla_see);
		//}
		//else {//если корабль недобит - шли по кораблю, но прошли не весь и попали в воду
		//	is_last_ship_DIED = false;
		//	is_last_ship_Stricked = true;
		//	{
		//		if (dX == 0) {
		//			if (dY == 1)
		//				directions[2] = 1;
		//			else
		//				directions[0] = 1;
		//		}
		//		else if (dX == 1)
		//			directions[1] = 1;
		//		else
		//			directions[3] = 1;
		//	}
		//	flotilla.Arena_arr[lastX][lastY] = Drawer::COLOR_STRIKED_WATER;
		//	flotilla_see.Arena_arr[lastX][lastY] = Drawer::COLOR_STRIKED_WATER;
		//	lastX -= dX;
		//	lastY -= dY;
		//}
	}
	else {//если в предыдущий корабль не было попадания или он был убит
		is_last_ship_DIED = false;
		is_last_ship_Stricked = false;
		lastX = -1;
		lastY = -1;
		srand(time(NULL));
		int X = GetRandomInt(0, 9);
		int Y = GetRandomInt(0, 9);
		//если вдруг это уже что-то подбитое, то ищем рандом, пока не дойдем до неподбитого
		while ((flotilla.Arena_arr[X][Y] == Drawer::COLOR_STRIKED_SHIP) || (flotilla.Arena_arr[X][Y] == Drawer::COLOR_STRIKED_WATER)) {
			srand(time(NULL));
			X = GetRandomInt(0, 9);
			Y = GetRandomInt(0, 9);
			//con_gotoXY(50, 25);
			//con_outTxt("trables here");
			//Drawer tmp;
			//tmp.is_pressed(CON_KEY_DEL);
		}

		//con_gotoXY(50, 25);
		//std::cout << "X: " << X << "Y: " << Y;
		//con_gotoXY(0, 17);

		int dX = 0;
		int dY = 0;
		if (flotilla.Arena_arr[X][Y] == Drawer::COLOR_UNBROKEN_SHIP) {	//1й раз попал//почему-то вызывается, когда не надо(иногда)
			is_last_ship_Stricked = true;								//мб что-то с условием
			firstX = X;
			firstY = Y;
			lastY = Y;
			lastX = X;

			//con_gotoXY(66, 0);
			//con_outTxt("sssss");
			//con_gotoXY(0, 15);

			flotilla.Arena_arr[X][Y] = Drawer::COLOR_STRIKED_SHIP;
			flotilla_see.Arena_arr[X][Y] = Drawer::COLOR_STRIKED_SHIP;

			//если это единичный корабль:
			if ((flotilla.Arena_arr[firstX - 1][firstY] != Drawer::COLOR_UNBROKEN_SHIP) &&	//тут мб траблы, если н-р корабль будет сверху 
				(flotilla.Arena_arr[firstX][firstY - 1] != Drawer::COLOR_UNBROKEN_SHIP) &&	//поля и он чекнет выще, а там - за границей
				(flotilla.Arena_arr[lastX + 1][lastY] != Drawer::COLOR_UNBROKEN_SHIP) &&	//массива - мб снизу корабль быть
				(flotilla.Arena_arr[lastX][lastY + 1] != Drawer::COLOR_UNBROKEN_SHIP)/*корабль подбитый*/) {
				is_last_ship_DIED = true;
				is_last_ship_Stricked = true;
				//Ship tmp(lastX, lastY, lastX, lastY);
				//tmp.Destruction(flotilla, flotilla_see);//-----------------------------------------------!!!!!!!!!!!!!!!!!!
				//Strike(flotilla, flotilla_see);
				firstX = -1;
				firstY = -1;
				lastY = -1;
				lastX = -1;
			}
			else {
				is_last_ship_DIED = false;
			}

			Strike(flotilla, flotilla_see);

		}
		else {//не попал
			flotilla.Arena_arr[X][Y] = Drawer::COLOR_STRIKED_WATER;
			flotilla_see.Arena_arr[X][Y] = Drawer::COLOR_STRIKED_WATER;
			//if (directions != 0)
			//	directions++;
			//directions = directions % 4;
			is_last_ship_DIED = false;
			is_last_ship_Stricked = false;
			firstX = -1;
			firstY = -1;
			lastX = -1;
			lastY = -1;
		}
	}
};
//--------------------------------------------------------------------------------------------------------
Game::Ship::Ship(size_t x1_in, size_t y1_in, size_t x2_in, size_t y2_in) : x1(x1_in), y1(y1_in), x2(x2_in), y2(y2_in) {
	if (x2 != x1)
		if (x2 > x1)
			Ship_size = (x2 - x1 + 1);
		else
			Ship_size = (x1 - x2 + 1);
	else
		if (y2 != y1)
			if (y2 > y1)
				Ship_size = (y2 - y1 + 1);
			else
				Ship_size = (y1 - y2 + 1);
		else
			Ship_size = 1;
	if (y2 < y1) {
		size_t x;
		x = y2;
		y2 = y1;
		y1 = x;
	}
	if (x2 < x1) {
		size_t x;
		x = x2;
		x2 = x1;
		x1 = x;
	}
};
void Game::Ship::Build(Arena& flotilla) {
	if (Ship_size == 4) {
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				flotilla.Arena_arr[i][j] = 2;
				if (x1 == x2) {
					if ((0 <= (i + 1)) && ((i + 1) <= 9)) flotilla.Arena_arr[i + 1][j] = 5;
					if ((0 <= (i - 1)) && ((i - 1) <= 9)) flotilla.Arena_arr[i - 1][j] = 5;
				}
				if (y1 == y2) {
					if ((0 <= (j + 1)) && ((j + 1) <= 9)) flotilla.Arena_arr[i][j + 1] = 5;
					if ((0 <= (j - 1)) && ((j - 1) <= 9)) flotilla.Arena_arr[i][j - 1] = 5;
				}
			}
		}
		if (y1 == y2) {
			if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (flotilla.Arena_arr[x1 - 1][y1] != 2)) flotilla.Arena_arr[x1 - 1][y1] = 5;
			if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (flotilla.Arena_arr[x1 + 1][y1] != 2)) flotilla.Arena_arr[x1 + 1][y1] = 5;
			if ((0 <= (x2 - 1)) && ((x2 - 2) <= 9) && (flotilla.Arena_arr[x2 - 1][y2] != 2)) flotilla.Arena_arr[x2 - 1][y2] = 5;
			if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (flotilla.Arena_arr[x2 + 1][y2] != 2)) flotilla.Arena_arr[x2 + 1][y2] = 5;
		}
		if (x1 == x2) {
			if ((0 <= (y1 - 1)) && ((y1 - 1) <= 9) && (flotilla.Arena_arr[x1][y1 - 1] != 2)) flotilla.Arena_arr[x1][y1 - 1] = 5;
			if ((0 <= (y1 + 1)) && ((y1 + 1) <= 9) && (flotilla.Arena_arr[x1][y1 + 1] != 2)) flotilla.Arena_arr[x1][y1 + 1] = 5;
			if ((0 <= (y2 - 1)) && ((y2 - 1) <= 9) && (flotilla.Arena_arr[x2][y2 - 1] != 2)) flotilla.Arena_arr[x2][y2 - 1] = 5;
			if ((0 <= (y2 + 1)) && ((y2 + 1) <= 9) && (flotilla.Arena_arr[x2][y2 + 1] != 2)) flotilla.Arena_arr[x2][y2 + 1] = 5;
		}
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 - 1] = 5;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 - 1] = 5;
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 + 1] = 5;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 + 1] = 5;
		if ((0 <= (x2 - 1)) && ((x2 - 1) <= 9) && (0 <= (y2 - 1)) && ((y2 - 1) <= 9)) flotilla.Arena_arr[x2 - 1][y2 - 1] = 5;
		if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (0 <= (y2 - 1)) && ((y2 - 1) <= 9)) flotilla.Arena_arr[x2 + 1][y2 - 1] = 5;
		if ((0 <= (x2 - 1)) && ((x2 - 1) <= 9) && (0 <= (y2 + 1)) && ((y2 + 1) <= 9)) flotilla.Arena_arr[x2 - 1][y2 + 1] = 5;
		if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (0 <= (y2 + 1)) && ((y2 + 1) <= 9)) flotilla.Arena_arr[x2 + 1][y2 + 1] = 5;
	}
	if (Ship_size == 3) {
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				flotilla.Arena_arr[i][j] = 2;
				if (x1 == x2) {
					if ((0 <= (i + 1)) && ((i + 1) <= 9)) flotilla.Arena_arr[i + 1][j] = 5;
					if ((0 <= (i - 1)) && ((i - 1) <= 9)) flotilla.Arena_arr[i - 1][j] = 5;
				}
				if (y1 == y2) {
					if ((0 <= (j + 1)) && ((j + 1) <= 9)) flotilla.Arena_arr[i][j + 1] = 5;
					if ((0 <= (j - 1)) && ((j - 1) <= 9)) flotilla.Arena_arr[i][j - 1] = 5;
				}
			}
		}
		if (y1 == y2) {
			if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (flotilla.Arena_arr[x1 - 1][y1] != 2)) flotilla.Arena_arr[x1 - 1][y1] = 5;
			if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (flotilla.Arena_arr[x1 + 1][y1] != 2)) flotilla.Arena_arr[x1 + 1][y1] = 5;
			if ((0 <= (x2 - 1)) && ((x2 - 2) <= 9) && (flotilla.Arena_arr[x2 - 1][y2] != 2)) flotilla.Arena_arr[x2 - 1][y2] = 5;
			if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (flotilla.Arena_arr[x2 + 1][y2] != 2)) flotilla.Arena_arr[x2 + 1][y2] = 5;
		}
		if (x1 == x2) {
			if ((0 <= (y1 - 1)) && ((y1 - 1) <= 9) && (flotilla.Arena_arr[x1][y1 - 1] != 2)) flotilla.Arena_arr[x1][y1 - 1] = 5;
			if ((0 <= (y1 + 1)) && ((y1 + 1) <= 9) && (flotilla.Arena_arr[x1][y1 + 1] != 2)) flotilla.Arena_arr[x1][y1 + 1] = 5;
			if ((0 <= (y2 - 1)) && ((y2 - 1) <= 9) && (flotilla.Arena_arr[x2][y2 - 1] != 2)) flotilla.Arena_arr[x2][y2 - 1] = 5;
			if ((0 <= (y2 + 1)) && ((y2 + 1) <= 9) && (flotilla.Arena_arr[x2][y2 + 1] != 2)) flotilla.Arena_arr[x2][y2 + 1] = 5;
		}
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 - 1] = 5;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 - 1] = 5;
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 + 1] = 5;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 + 1] = 5;
		if ((0 <= (x2 - 1)) && ((x2 - 1) <= 9) && (0 <= (y2 - 1)) && ((y2 - 1) <= 9)) flotilla.Arena_arr[x2 - 1][y2 - 1] = 5;
		if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (0 <= (y2 - 1)) && ((y2 - 1) <= 9)) flotilla.Arena_arr[x2 + 1][y2 - 1] = 5;
		if ((0 <= (x2 - 1)) && ((x2 - 1) <= 9) && (0 <= (y2 + 1)) && ((y2 + 1) <= 9)) flotilla.Arena_arr[x2 - 1][y2 + 1] = 5;
		if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (0 <= (y2 + 1)) && ((y2 + 1) <= 9)) flotilla.Arena_arr[x2 + 1][y2 + 1] = 5;
	}
	if (Ship_size == 2) {
		flotilla.Arena_arr[x1][y1] = 2;
		flotilla.Arena_arr[x2][y2] = 2;
		if (y1 == y2) {
			if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (flotilla.Arena_arr[x1 - 1][y1] != 2)) flotilla.Arena_arr[x1 - 1][y1] = 5;
			if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (flotilla.Arena_arr[x1 + 1][y1] != 2)) flotilla.Arena_arr[x1 + 1][y1] = 5;
			if ((0 <= (x2 - 1)) && ((x2 - 2) <= 9) && (flotilla.Arena_arr[x2 - 1][y2] != 2)) flotilla.Arena_arr[x2 - 1][y2] = 5;
			if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (flotilla.Arena_arr[x2 + 1][y2] != 2)) flotilla.Arena_arr[x2 + 1][y2] = 5;
		}
		if (x1 == x2) {
			if ((0 <= (y1 - 1)) && ((y1 - 1) <= 9) && (flotilla.Arena_arr[x1][y1 - 1] != 2)) flotilla.Arena_arr[x1][y1 - 1] = 5;
			if ((0 <= (y1 + 1)) && ((y1 + 1) <= 9) && (flotilla.Arena_arr[x1][y1 + 1] != 2)) flotilla.Arena_arr[x1][y1 + 1] = 5;
			if ((0 <= (y2 - 1)) && ((y2 - 1) <= 9) && (flotilla.Arena_arr[x2][y2 - 1] != 2)) flotilla.Arena_arr[x2][y2 - 1] = 5;
			if ((0 <= (y2 + 1)) && ((y2 + 1) <= 9) && (flotilla.Arena_arr[x2][y2 + 1] != 2)) flotilla.Arena_arr[x2][y2 + 1] = 5;
		}
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 - 1] = 5;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 - 1] = 5;
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 + 1] = 5;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 + 1] = 5;
		if ((0 <= (x2 - 1)) && ((x2 - 1) <= 9) && (0 <= (y2 - 1)) && ((y2 - 1) <= 9)) flotilla.Arena_arr[x2 - 1][y2 - 1] = 5;
		if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (0 <= (y2 - 1)) && ((y2 - 1) <= 9)) flotilla.Arena_arr[x2 + 1][y2 - 1] = 5;
		if ((0 <= (x2 - 1)) && ((x2 - 1) <= 9) && (0 <= (y2 + 1)) && ((y2 + 1) <= 9)) flotilla.Arena_arr[x2 - 1][y2 + 1] = 5;
		if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (0 <= (y2 + 1)) && ((y2 + 1) <= 9)) flotilla.Arena_arr[x2 + 1][y2 + 1] = 5;
	}
	if (Ship_size == 1) {
		flotilla.Arena_arr[x1][y1] = 2;
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1] = 5;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1] = 5;
		if ((0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1][y1 - 1] = 5;
		if ((0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1][y1 + 1] = 5;
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 - 1] = 5;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 - 1] = 5;
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 + 1] = 5;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 + 1] = 5;
	}
};
void Game::Ship::Destruction(Arena& flotilla, Arena& flotilla_see) {
	if (Ship_size == 4) {
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				if (x1 == x2) {
					if ((0 <= (i + 1)) && ((i + 1) <= 9)) flotilla.Arena_arr[i + 1][j] = 1;
					if ((0 <= (i - 1)) && ((i - 1) <= 9)) flotilla.Arena_arr[i - 1][j] = 1;
				}
				if (y1 == y2) {
					if ((0 <= (j + 1)) && ((j + 1) <= 9)) flotilla.Arena_arr[i][j + 1] = 1;
					if ((0 <= (j - 1)) && ((j - 1) <= 9)) flotilla.Arena_arr[i][j - 1] = 1;
				}
			}
		}
		if (y1 == y2) {
			if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (flotilla.Arena_arr[x1 - 1][y1] != 2)) flotilla.Arena_arr[x1 - 1][y1] = 1;
			if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (flotilla.Arena_arr[x1 + 1][y1] != 2)) flotilla.Arena_arr[x1 + 1][y1] = 1;
			if ((0 <= (x2 - 1)) && ((x2 - 2) <= 9) && (flotilla.Arena_arr[x2 - 1][y2] != 2)) flotilla.Arena_arr[x2 - 1][y2] = 1;
			if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (flotilla.Arena_arr[x2 + 1][y2] != 2)) flotilla.Arena_arr[x2 + 1][y2] = 1;
		}
		if (x1 == x2) {
			if ((0 <= (y1 - 1)) && ((y1 - 1) <= 9) && (flotilla.Arena_arr[x1][y1 - 1] != 2)) flotilla.Arena_arr[x1][y1 - 1] = 1;
			if ((0 <= (y1 + 1)) && ((y1 + 1) <= 9) && (flotilla.Arena_arr[x1][y1 + 1] != 2)) flotilla.Arena_arr[x1][y1 + 1] = 1;
			if ((0 <= (y2 - 1)) && ((y2 - 1) <= 9) && (flotilla.Arena_arr[x2][y2 - 1] != 2)) flotilla.Arena_arr[x2][y2 - 1] = 1;
			if ((0 <= (y2 + 1)) && ((y2 + 1) <= 9) && (flotilla.Arena_arr[x2][y2 + 1] != 2)) flotilla.Arena_arr[x2][y2 + 1] = 1;
		}
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 - 1] = 1;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 - 1] = 1;
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 + 1] = 1;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 + 1] = 1;
		if ((0 <= (x2 - 1)) && ((x2 - 1) <= 9) && (0 <= (y2 - 1)) && ((y2 - 1) <= 9)) flotilla.Arena_arr[x2 - 1][y2 - 1] = 1;
		if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (0 <= (y2 - 1)) && ((y2 - 1) <= 9)) flotilla.Arena_arr[x2 + 1][y2 - 1] = 1;
		if ((0 <= (x2 - 1)) && ((x2 - 1) <= 9) && (0 <= (y2 + 1)) && ((y2 + 1) <= 9)) flotilla.Arena_arr[x2 - 1][y2 + 1] = 1;
		if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (0 <= (y2 + 1)) && ((y2 + 1) <= 9)) flotilla.Arena_arr[x2 + 1][y2 + 1] = 1;
	}
	if (Ship_size == 3) {
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				if (x1 == x2) {
					if ((0 <= (i + 1)) && ((i + 1) <= 9)) flotilla.Arena_arr[i + 1][j] = 1;
					if ((0 <= (i - 1)) && ((i - 1) <= 9)) flotilla.Arena_arr[i - 1][j] = 1;
				}
				if (y1 == y2) {
					if ((0 <= (j + 1)) && ((j + 1) <= 9)) flotilla.Arena_arr[i][j + 1] = 1;
					if ((0 <= (j - 1)) && ((j - 1) <= 9)) flotilla.Arena_arr[i][j - 1] = 1;
				}
			}
		}
		if (y1 == y2) {
			if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (flotilla.Arena_arr[x1 - 1][y1] != 2)) flotilla.Arena_arr[x1 - 1][y1] = 1;
			if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (flotilla.Arena_arr[x1 + 1][y1] != 2)) flotilla.Arena_arr[x1 + 1][y1] = 1;
			if ((0 <= (x2 - 1)) && ((x2 - 2) <= 9) && (flotilla.Arena_arr[x2 - 1][y2] != 2)) flotilla.Arena_arr[x2 - 1][y2] = 1;
			if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (flotilla.Arena_arr[x2 + 1][y2] != 2)) flotilla.Arena_arr[x2 + 1][y2] = 1;
		}
		if (x1 == x2) {
			if ((0 <= (y1 - 1)) && ((y1 - 1) <= 9) && (flotilla.Arena_arr[x1][y1 - 1] != 2)) flotilla.Arena_arr[x1][y1 - 1] = 1;
			if ((0 <= (y1 + 1)) && ((y1 + 1) <= 9) && (flotilla.Arena_arr[x1][y1 + 1] != 2)) flotilla.Arena_arr[x1][y1 + 1] = 1;
			if ((0 <= (y2 - 1)) && ((y2 - 1) <= 9) && (flotilla.Arena_arr[x2][y2 - 1] != 2)) flotilla.Arena_arr[x2][y2 - 1] = 1;
			if ((0 <= (y2 + 1)) && ((y2 + 1) <= 9) && (flotilla.Arena_arr[x2][y2 + 1] != 2)) flotilla.Arena_arr[x2][y2 + 1] = 1;
		}
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 - 1] = 1;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 - 1] = 1;
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 + 1] = 1;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 + 1] = 1;
		if ((0 <= (x2 - 1)) && ((x2 - 1) <= 9) && (0 <= (y2 - 1)) && ((y2 - 1) <= 9)) flotilla.Arena_arr[x2 - 1][y2 - 1] = 1;
		if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (0 <= (y2 - 1)) && ((y2 - 1) <= 9)) flotilla.Arena_arr[x2 + 1][y2 - 1] = 1;
		if ((0 <= (x2 - 1)) && ((x2 - 1) <= 9) && (0 <= (y2 + 1)) && ((y2 + 1) <= 9)) flotilla.Arena_arr[x2 - 1][y2 + 1] = 1;
		if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (0 <= (y2 + 1)) && ((y2 + 1) <= 9)) flotilla.Arena_arr[x2 + 1][y2 + 1] = 1;
	}
	if (Ship_size == 2) {
		if (y1 == y2) {
			if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (flotilla.Arena_arr[x1 - 1][y1] != 2)) flotilla.Arena_arr[x1 - 1][y1] = 1;
			if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (flotilla.Arena_arr[x1 + 1][y1] != 2)) flotilla.Arena_arr[x1 + 1][y1] = 1;
			if ((0 <= (x2 - 1)) && ((x2 - 2) <= 9) && (flotilla.Arena_arr[x2 - 1][y2] != 2)) flotilla.Arena_arr[x2 - 1][y2] = 1;
			if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (flotilla.Arena_arr[x2 + 1][y2] != 2)) flotilla.Arena_arr[x2 + 1][y2] = 1;
		}
		if (x1 == x2) {
			if ((0 <= (y1 - 1)) && ((y1 - 1) <= 9) && (flotilla.Arena_arr[x1][y1 - 1] != 2)) flotilla.Arena_arr[x1][y1 - 1] = 1;
			if ((0 <= (y1 + 1)) && ((y1 + 1) <= 9) && (flotilla.Arena_arr[x1][y1 + 1] != 2)) flotilla.Arena_arr[x1][y1 + 1] = 1;
			if ((0 <= (y2 - 1)) && ((y2 - 1) <= 9) && (flotilla.Arena_arr[x2][y2 - 1] != 2)) flotilla.Arena_arr[x2][y2 - 1] = 1;
			if ((0 <= (y2 + 1)) && ((y2 + 1) <= 9) && (flotilla.Arena_arr[x2][y2 + 1] != 2)) flotilla.Arena_arr[x2][y2 + 1] = 1;
		}
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 - 1] = 1;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 - 1] = 1;
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 + 1] = 1;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 + 1] = 1;
		if ((0 <= (x2 - 1)) && ((x2 - 1) <= 9) && (0 <= (y2 - 1)) && ((y2 - 1) <= 9)) flotilla.Arena_arr[x2 - 1][y2 - 1] = 1;
		if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (0 <= (y2 - 1)) && ((y2 - 1) <= 9)) flotilla.Arena_arr[x2 + 1][y2 - 1] = 1;
		if ((0 <= (x2 - 1)) && ((x2 - 1) <= 9) && (0 <= (y2 + 1)) && ((y2 + 1) <= 9)) flotilla.Arena_arr[x2 - 1][y2 + 1] = 1;
		if ((0 <= (x2 + 1)) && ((x2 + 1) <= 9) && (0 <= (y2 + 1)) && ((y2 + 1) <= 9)) flotilla.Arena_arr[x2 + 1][y2 + 1] = 1;
	}
	if (Ship_size == 1) {
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1] = 1;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1] = 1;
		if ((0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1][y1 - 1] = 1;
		if ((0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1][y1 + 1] = 1;
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 - 1] = 1;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 - 1)) && ((y1 - 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 - 1] = 1;
		if ((0 <= (x1 - 1)) && ((x1 - 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 - 1][y1 + 1] = 1;
		if ((0 <= (x1 + 1)) && ((x1 + 1) <= 9) && (0 <= (y1 + 1)) && ((y1 + 1) <= 9)) flotilla.Arena_arr[x1 + 1][y1 + 1] = 1;
	}
};
void Game::Start_Game() {
	//system("cls");
	Arena Arena_1, Arena_2, Arena_3, Arena_4, Arena_new;
	Draw1.InitialDraw();
	Draw2.moveField(30, 1);
	Draw2.InitialDraw();
	Draw1.changeDraw(Arena_1.Arena_arr);
	Draw2.changeDraw(Arena_4.Arena_arr);
	size_t tactic1 = 2000;
	size_t tactic2 = 2000;
	while (tactic1 != 0 && tactic1 != 1 && tactic1 != 2) {
		cout << "Enter tactics for player 1 for building stage (0, 1, 2)\n";
		cin >> tactic1;
		Draw1.clearTxt();
	}
	Player_stage_1 Player_1(tactic1, Arena_1);
	Player_1.Build();
	Draw1.clearTxt();
	Draw1.changeDraw(Arena_1.Arena_arr);
	Draw2.changeDraw(Arena_4.Arena_arr);
	cout << "Press Enter to continue\n";
	Draw1.is_pressed();
	Draw1.clearTxt();
	Draw1.changeDraw(Arena_2.Arena_arr);
	Draw2.changeDraw(Arena_3.Arena_arr);
	while (tactic2 != 0 && tactic2 != 1 && tactic2 != 2) {
		cout << "Enter tactics for player 2 for building stage (0, 1, 2)\n";
		cin >> tactic2;
		Draw1.clearTxt();
	}
	Player_stage_1 Player_2(tactic2, Arena_2);
	Player_2.Build();
	Draw1.clearTxt();
	Draw1.changeDraw(Arena_2.Arena_arr);
	Draw2.changeDraw(Arena_3.Arena_arr);
	cout << "Press Enter to continue\n";
	Draw1.is_pressed();
	Draw1.clearTxt();
	Draw1.changeDraw(Arena_new.Arena_arr);
	Draw2.changeDraw(Arena_new.Arena_arr);
	tactic1 = 2000;
	tactic2 = 2000;
	while (tactic1 != 0 && tactic1 != 1 && tactic1 != 2) {
		cout << "Enter tactics for player 1 for striking stage (0, 1, 2)\n";
		cin >> tactic1;
		Draw1.clearTxt();
	}
	while (tactic2 != 0 && tactic2 != 1 && tactic2 != 2) {
		cout << "Enter tactics for player 2 for striking stage (0, 1, 2)\n";
		cin >> tactic2;
		Draw1.clearTxt();
	}
	Player_stage_2 player_1(tactic1, Arena_2, Arena_4);
	Player_stage_2 player_2(tactic2, Arena_1, Arena_3);
	cout << "Press Enter to start shooting. (Player 1 starts) and (Arena left - your; Arena right - your enemy)\n";
	Draw1.is_pressed();
	Draw1.clearTxt();
	while ((Arena_1.Arena_the_break != 20) && (Arena_2.Arena_the_break != 20)) {
		Draw1.changeDraw(Arena_1.Arena_arr);
		Draw2.changeDraw(Arena_4.Arena_arr);
		cout << "Player 1's round has started. Press Enter to continue\n";
		Draw1.is_pressed();
		player_1.Strike();
		Draw1.clearTxt();
		if (Arena_2.Arena_the_break == 20) {
			Draw1.changeDraw(Arena_1.Arena_arr);
			Draw2.changeDraw(Arena_2.Arena_arr);
			cout << "Player 1 wins! (Player 1 - left; Player 2 - right)\n";
			break;
		}
		Draw1.changeDraw(Arena_1.Arena_arr);
		Draw2.changeDraw(Arena_4.Arena_arr);
		cout << "Player 1's round is over. Press Enter to continue\n";
		Draw1.is_pressed();
		Draw1.clearTxt();
		Draw1.changeDraw(Arena_new.Arena_arr);
		Draw2.changeDraw(Arena_new.Arena_arr);
		cout << "Press Enter to see player 2's flotilla\n";
		Draw1.is_pressed();
		Draw1.clearTxt();
		Draw1.changeDraw(Arena_2.Arena_arr);
		Draw2.changeDraw(Arena_3.Arena_arr);
		cout << "Player 2's round has started. Press Enter to continue\n";
		Draw1.is_pressed();
		player_2.Strike();
		Draw1.clearTxt();
		if (Arena_1.Arena_the_break == 20) {
			Draw1.changeDraw(Arena_1.Arena_arr);
			Draw2.changeDraw(Arena_2.Arena_arr);
			cout << "Player 2 wins! (Player 1 - left; Player 2 - right)\n";
			break;
		}
		Draw1.changeDraw(Arena_2.Arena_arr);
		Draw2.changeDraw(Arena_3.Arena_arr);
		cout << "Player 2's round is over. Press Enter to continue\n";
		Draw1.is_pressed();
		Draw1.clearTxt();
		Draw1.changeDraw(Arena_new.Arena_arr);
		Draw2.changeDraw(Arena_new.Arena_arr);
		cout << "Press Enter to see player 1's flotilla\n";
		Draw1.is_pressed();
		Draw1.clearTxt();
	}
};