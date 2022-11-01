#pragma once
#include<iostream>
#include<exception>
#include<stdexcept>
#include"DrawFieldOOP.h"
#include<ctime>
#include<time.h>
#include<math.h>
#include<cstdlib>
//static const size_t Arena_size = 10;
int GetRandomInt(int min = 0, int max = 9);
static Drawer Draw1;
static Drawer Draw2;
using namespace std;
class Game
{
	class Arena
	{
		friend class Game;
		friend class Player_stage_1;
		friend class Player_stage_2;
		friend class Tactics;
		friend class Tactics_Player;
		friend class Tactics_Random;
		friend class Tactics_Smart;
		size_t Arena_arr[Arena_size][Arena_size] = {};
		size_t Arena_the_break = 0;
	public:
		Arena();
		bool Defeat_condition();
	};
	class Player_stage_1
	{
		size_t Player_tactics;
		Arena& My_flotilla;
	public:
		Player_stage_1(size_t Tactics, Arena& My_flotilla_get);
		void Build();
	};
	class Player_stage_2
	{
		size_t Player_tactics;
		Arena& Enemy_flotilla;
		Arena& Enemy_flotilla_see;
	public:
		Player_stage_2(size_t Tactics, Arena& Enemy_flotilla_get, Arena& Enemy_flotilla_see_get);
		void Strike();
	};
	class Tactics
	{
	public:
		virtual void Build(Arena& flotilla) = 0;
		virtual void Strike(Arena& flotilla, Arena& flotilla_see) = 0;
	};
	class Tactics_Player :public Tactics
	{
	public:
		void Build(Arena& flotilla);
		void Strike(Arena& flotilla, Arena& flotilla_see);
	};
	class Tactics_Random :public Tactics
	{
	public:
		void Build(Arena& flotilla);
		void Strike(Arena& flotilla, Arena& flotilla_see);
	};
	//------------------------------------------------------------------------
	class Tactics_Smart :public Tactics
	{
		int firstX = -1;
		int firstY = -1;
		int lastX = -1;
		int lastY = -1;
		bool directions[4] = { 0, 0, 0, 0 };
		int lastDir = 0;
		bool is_last_ship_Stricked = false;
		bool is_last_ship_DIED = false;
	public:
		void Build(Arena& flotilla);
		void Strike(Arena& flotilla, Arena& flotilla_see);
	};
	//----------------------------------------------------------------------------
	class Ship
	{
		friend class Tactics;
		friend class Tactics_Player;
		friend class Tactics_Random;
		friend class Tactics_Smart;
		size_t Ship_size;
		size_t x1, y1, x2, y2;
	public:
		Ship(size_t x1_in, size_t y1_in, size_t x2_in, size_t y2_in);
		void Build(Arena& flotilla);
		void Destruction(Arena& flotilla, Arena& flotilla_see);
	};
public:
	void Start_Game();
};