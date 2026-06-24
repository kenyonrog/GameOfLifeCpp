#pragma once
#include <raylib.h>
#include <raymath.h>

struct Cell
{
	bool isAlive{ false };
	Vector2 position{};

	void draw(int cellSize) {
		Color cellColor{ BLACK };

		if (isAlive)
			cellColor = RED;

		DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, cellColor);
	}

	void draw(int cellSize, Color color) {
		DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, color);
	}
};