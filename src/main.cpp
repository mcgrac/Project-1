/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <vector>

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "Player.hpp"
#include "Block.hpp"
#include "Goomba.hpp"
//#include "Draw.hpp"
#include "GameManager.hpp"
//#include "BreakBlock.hpp"
#include "SurpriseBlock.hpp"
#include"NormalBlock.hpp"
#include "PowerUp.hpp"
#include"GameCamera.hpp"

using namespace std;

#define GRAVITY  0.5f    // Gravedad aplicada en cada frame
#define JUMP_FORCE 8.0f // Fuerza del salto
#define TILE_SIZE 16.0f  // Tamaño de cada bloque
#define MAP_ROWS 28   // Filas del mapa
#define MAP_COLS 100   // Columnas del mapa

//definir array 2D mapa
//int map[MAP_ROWS][MAP_COLS] = {
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} // Suelo
//};

int map[MAP_ROWS][MAP_COLS] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} // Suelo
};


//vector<Entity*> entities;




//class Camera {
//
//	//poner esta class en otro arhcivo y las funcionalidades de seguir al personaje
//};

void initBlocks() {

	for (int row = 0; row < MAP_ROWS; row++) {
		for (int col = 0; col < MAP_COLS; col++) {
			if (map[row][col] == 1) {

				printf("Creando bloque en: x = %f, y = %f\n", col * TILE_SIZE, row * TILE_SIZE);

				NormalBlock* b = new NormalBlock(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, 2, 1, 1); //createNormalBlock

				//entities.push_back(b);
				//b->draw();

				//b.drawBlock();
			}
			if (map[row][col] == 2) {

				printf("Creando bloque sorpresa en: x = %f, y = %f\n", col * TILE_SIZE, row * TILE_SIZE);

				SurpriseBlock* s = new SurpriseBlock(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, 2, 1, 2); // create surpirse Block
				//PowerUp* p = new PowerUp(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, 2, 1, 1)

				//Block* b = new Block(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, 2, 1, 1);

				//entities.push_back(b);
				//b->draw();

				//b.drawBlock();
			}
		}
	}

	
}

//void Player::colisionsPlayer(vector<Entity*>& e) {
//
//	for (auto it = e.begin(); it != e.end(); ) {
//		Entity* ent = *it;
//
//		// Colisiones con bloques (id == 2)
//		if (ent->id == 2 && CheckCollisionRecs(hitbox, ent->getHitbox())) {
//			printf("colision con bloque\n");
//
//			if (collidingBottom(ent)) {
//				speed.y = 0;
//				hitbox.y = ent->getHitbox().y - hitbox.height;
//				isJumping = false;
//				onGround = true;
//			}
//
//			if (collidingAbove(ent)) {
//				hitbox.y = ent->getHitbox().y + ent->getHitbox().height;
//				speed.y = 1.0f;
//			}
//
//			if (CheckCollisionPointRec(left, ent->getHitbox())) {
//				hitbox.x = ent->getHitbox().x + ent->getHitbox().width;
//			}
//
//			if (CheckCollisionPointRec(right, ent->getHitbox())) {
//				hitbox.x = ent->getHitbox().x - hitbox.width;
//			}
//
//			colliding = true;
//
//			++it;
//			continue;
//		}
//		else {
//
//			colliding = false;
//			onGround = false;
//		}
//
//		// Colisiones con Goomba (id == 1)
//		if (CheckCollisionRecs(hitbox, ent->getHitbox()) && !immunity && ent->id == 1) {
//			if (CheckCollisionPointRec(bottom, ent->getHitbox()) && ent->state == 1) {
//				printf("COLLISION GOOMBA CON LOS PIES\n");
//
//				PlaySound(jumpGoombaS);
//
//				ent->state = 0;
//
//				jump(8.0f);
//
//				delete ent;          // liberar memoria
//				it = e.erase(it);    // borrar del vector y continuar
//				continue;
//			}
//			else {
//				printf("COLISION CON GOOMBA\n");
//
//				state--;
//				if (state == 0) {
//					// Mario muere
//				}
//				else {
//					immunity = true;
//				}
//			}
//		}
//		else {
//
//			colliding = false;
//		}
//
//		++it;
//	}
//}


void Player::colisionsPlayer(vector<Entity*>& e) {

	for (auto it = e.begin(); it != e.end(); ) {
		Entity* ent = *it;

		// Colisiones con bloques (id == 2)
		if (ent->id == 2 && CheckCollisionRecs(hitbox, ent->getHitbox())) {
			printf("colision con bloque\n");

			if (collidingBottom(ent)) {
				speed.y = 0;
				hitbox.y = ent->getHitbox().y - hitbox.height;
				isJumping = false;
				onGround = true;
			}

			if (collidingAbove(ent)) {
				hitbox.y = ent->getHitbox().y + ent->getHitbox().height;
				speed.y = 1.0f;

				if (SurpriseBlock* surprise = dynamic_cast<SurpriseBlock*>(ent)) {

					surprise->state = 0;
				}
			}

			if (CheckCollisionPointRec(left, ent->getHitbox())) {
				hitbox.x = ent->getHitbox().x + ent->getHitbox().width;
			}

			if (CheckCollisionPointRec(right, ent->getHitbox())) {
				hitbox.x = ent->getHitbox().x - hitbox.width;
			}

			colliding = true;

			++it;
			continue;
		}
		else {

			colliding = false;
			onGround = false;
		}

		// Colisiones con Goomba (id == 1)
		if (CheckCollisionRecs(hitbox, ent->getHitbox()) && !immunity && ent->id == 1) {
			if (CheckCollisionPointRec(bottom, ent->getHitbox()) && ent->state == 1) {
				printf("COLLISION GOOMBA CON LOS PIES\n");

				PlaySound(jumpGoombaS);

				ent->state = 0;

				jump(8.0f);

				delete ent;          // liberar memoria
				it = e.erase(it);    // borrar del vector y continuar
				continue;
			}
			else {
				printf("COLISION CON GOOMBA\n");

				state--;
				if (state == 0) {
					// Mario muere
				}
				else {
					immunity = true;
				}
			}
		}
		else {

			colliding = false;
		}

		++it;
	}
}

//void drawBlocks (vector<Entity> list) {
//	
//	for (int i = 0; i < entities.size(); ++i) {
//
//		if (entities[i].id == 2) {
//
//			//if it is a block, draw it
//			DrawRectangleRec(list[i].hitbox, RED);
//
//		}
//	}
//}
void moveCamera(Camera2D& c, Player*& p) {

	printf("MOVING CAMERA\n");

	// Mover la cámara para que siga a Mario
	c.target.x = p->getHitbox().x;
	//camera.target.y = mario.getHitbox().y + TILE_SIZE / 2;
}

int main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	const int screenWidth = 512;
	const int screenHeight = 448;

	InitWindow(screenWidth, screenHeight, "Mapa en Movimiento");
	InitAudioDevice();

	GameManager gm(1, 0, false);

	Player* mario = new Player(300.0f, 100.0f, TILE_SIZE, TILE_SIZE, 0, 2, 0, 0, 5.0f, 1);

	//Player mario(300.0f, 100.0f, TILE_SIZE, TILE_SIZE, 0, 2, 0, 0, 5.0f, 1);
	//entities.emplace_back(mario);

	//create goomba and add them in the list
	Goomba* goomba = new Goomba(400.0f, 200.0f, TILE_SIZE, TILE_SIZE, 1, 1, 5.0f, 1);
	//entities.push_back(goomba);

	initBlocks(); //poner en la lista de vector los bloques con colisiones
	
	for (int i = 0; i < Entity::getAllEntities().size(); i++) {

		printf("entity size: %d\n", Entity::getAllEntities().size());
		printf("Is the i = %d, the id of this item is: %d\n and x:%f and y:%f ", i, Entity::getAllEntities()[i]->id, Entity::getAllEntities()[i]->getHitbox().x, Entity::getAllEntities()[i]->getHitbox().y);
	}

	GameCamera camera(screenWidth, 0, 1952); // fondo de 1952 px

	////camaras
	//Camera2D camera = { 0 };
	//camera.target = { mario->getHitbox().x, 0};
	//camera.offset = { screenWidth / 2.0f, 0};
	//camera.rotation = 0.0f;
	//camera.zoom = 1.0f;

	// game loop
	while (!WindowShouldClose())// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		gm.playSounds();

		if (mario->getHitbox().x >= 1500) {

			gm.win();

			delete mario;
			mario = new Player(300.0f, 100.0f, TILE_SIZE, TILE_SIZE, 0, 2, 0, 0, 5.0f, 1);

			camera.reset();
		}

		if (mario->state == 0) {

			gm.gameOver();

			delete mario;
			mario = new Player(300.0f, 100.0f, TILE_SIZE, TILE_SIZE, 0, 2, 0, 0, 5.0f, 1);

			camera.reset();
		}

		if (IsKeyPressed(KEY_N)) {

			gm.nextScreen();

		}

		if (gm.GetScreen() == 2) { // if we are in the main menu are we press up/down keys

			gm.opSelector();
		}

		//Game logic. Apply only when we are in the game screen [0]
		
		if (gm.GetScreen() == 0) {

			mario->applyGravity(GRAVITY);

			mario->updateRects();
			goomba->updateRects();

			if (IsKeyDown(KEY_RIGHT)) {

				if (mario->getDir() != 1) {

					printf("chage direction to right");

					mario->changeDirection();
				}

				if (mario->getDir() == 1) { // if I am going right

					mario->move(1, camera.getRawCamera().target.x); //move to the right
				}

			}

			if (IsKeyDown(KEY_LEFT)) {

				if (mario->getDir() == 1) {

					printf("chage direction to left");

					mario->changeDirection();
				}

				if (mario->getDir() != 1) { // if I am going left

					mario->move(-1, camera.getRawCamera().target.x); //move to the left
				}

			}

			mario->colisionsPlayer(Entity::getAllEntities());

			goomba->moveGoomba(Entity::getAllEntities());



			//mario.colisionsPlayerEnemy(entities);

			//goomba.colisionsGoomba(entities);

			//if (CheckCollisionRecs(mario.hitbox, goomba.hitbox) && !mario.immunity && goomba.state == 1) {

			//	printf("COLISION CON GOOMBA\n");

			//	if (CheckCollisionRecs(mario.hitbox, goomba.hitbox) && !mario.immunity) { //enemies

			//		printf("COLISION CON GOOMBA\n");

			//		if (CheckCollisionPointRec(mario.bottom, goomba.hitbox)) { //si los pies de mario colisionan con goomba

			//			goomba.state = 0; //goomba muerto
			//			mario.jump(8.0f); //REVISAR SALTO
			//		}
			//		else { //mario pierde una vida

			//			mario.state--;

			//			if (mario.state == 0) { //si es mario pequeño, mario muere

			//				//mario muere

			//			}
			//			else {

			//				mario.immunity = true;
			//				//mario.immunityVoid(mario);
			//			}
			//		}

			//	}
			//}

			if (mario->retImmunity()) {

				mario->immunityVoid();
			}

			if (IsKeyPressed(KEY_SPACE) && !mario->retJumping()) {

				mario->jump(JUMP_FORCE);
			}


		}
		
		camera.update(mario->getHitbox());

		//CHECK TO DELATE THE MARKED ELEMENTS IN THE VECTOR
		//for (auto it = Entity::getAllEntities().begin(); it != Entity::getAllEntities().end();) {
		//	if ((*it)->retToDelate()) {

		//		//free memory
		//		delete* it;

		//		// delate entoty from the vector and advance to the next one
		//		it = Entity::getAllEntities().erase(it);
		//	}
		//	else {
		//		++it;
		//	}
		//}

		//-------------------------------------------DRAWING-----------------------------------------------------------//

		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		gm.drawScreen(camera.getRawCamera(), screenWidth, screenHeight);

		if (gm.GetScreen() == 2) {

			gm.drawArrow();
		}

		if (gm.GetScreen() == 0) {

			camera.begin();
			//BeginMode2D(camera);
			//moveCamera(camera, mario);

			mario->draw();

			//if (goomba->state != 0) {

			//	goomba->draw();

			//	//entities.erase(goomba)
			//}


			for (int i = 0; i < Entity::getAllEntities().size(); ++i) { 

				Entity::getAllEntities()[i]->draw();
					
				////-------DRAW BLOCKS--------
				//if (Entity::getAllEntities()[i]->id == 2) {

				//	Entity::getAllEntities()[i]->draw();
				//}

				////-------DRAW ENEMIES--------
				//if (Entity::getAllEntities()[i]->id == 1 && Entity::getAllEntities()[i]->state != 0) {

				//	Entity::getAllEntities()[i]->draw();
				//}
			}
			//for (int row = 0; row < MAP_ROWS; row++) {
			//	for (int col = 0; col < MAP_COLS; col++) {
			//		if (map[row][col] == 1) {

			//			printf("Creando bloque en: x = %f, y = %f\n", col * TILE_SIZE, row * TILE_SIZE);


			//			Block* b = new Block(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, 2, 1, 1);

			//			//entities.push_back(b);
			//			b->draw();

			//			//b.drawBlock();
			//		}
			//	}
			//}

			if (!gm.getMapCreated()) {

				//initBlocks();



				gm.mapCreated();

				printf("All BLOCKS PRINTED\n");
			}

		}
		

		

		
		//dibujar mapa
		//Draw::drawMap(entities);

		//drawBlocks(entities);

		//dubujar personaje
		//Draw::drawMario(mario);

		//dibujar enemigos
		//Draw::drawEnemies(goomba);


		////dibujar enemigo
		//if (goomba.state == 1) {

		//	DrawRectangleRec(goomba.hitbox, WHITE);
		//}


		//Vector2 textPosition = { 10 + camera.target.x - camera.offset.x, 300 + camera.target.y - camera.offset.y };

		//DrawText(TextFormat("Posición: (%.1f, %.1f)", mario.hitbox.x, mario.hitbox.y), 200, 10, 20, WHITE);
		DrawText(TextFormat("colliding: (%d)", mario->getDir()), 200, 60, 20, WHITE);
		//DrawText(TextFormat("Vector Camera Pos : (%f x), (%f y)", camera.target.x, camera.target.y), 200, 110, 20, WHITE);
		DrawText(TextFormat("Player immunity %d", mario->retImmunity()), 200, 160, 20, WHITE);
		DrawText(TextFormat("Player time %f", mario->getTime()), 200, 210, 20, WHITE);
		DrawText(TextFormat("Player state %d", mario->state), 200, 260, 20, WHITE);
		DrawText(TextFormat("Goomba state %d", goomba->state), 200, 310, 20, WHITE);
		DrawText(TextFormat("Posición goomba: (%.1f, %.1f)", goomba->getHitbox().x, goomba->getHitbox().y), 200, 360, 20, WHITE);
		DrawText(TextFormat("Screen: %d", gm.GetScreen()), 200, 410, 20, WHITE);
		//DrawText(TextFormat("op: %d", gm.getOp()), 200, 110, 20, WHITE);

		camera.end();
		//EndMode2D();

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	CloseAudioDevice();
	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
