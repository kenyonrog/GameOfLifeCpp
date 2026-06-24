#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <random>
#include <raylib.h>
#include "Cell.h"
#include "CellsContainer.h"

void gameOfLifeLogic(CellsContainer* currentState, CellsContainer* newState)
{
	for (int i = 0; i < currentState->getColumns(); ++i)
	{
		for (int j = 0; j < currentState->getRows(); ++j)
		{
			int currentCellNeighbors{ currentState->getNumberOfAliveNeighbors(i, j) };
			Cell* cell{ newState->findCell(i, j) };

			if (currentCellNeighbors < 2 || currentCellNeighbors > 3)
				cell->isAlive = false;
			else if (currentCellNeighbors == 3)
				cell->isAlive = true;
		}
	}
}

int main() {
	const char* windowTitle{ "Game of Life" };
	int screenWidth{ 1280 };
	int screenHeight{ 800 };

	int cellSize{ 10 };

	int columns{ screenWidth / cellSize };
	int rows{ screenHeight / cellSize };

	int generations{};

	CellsContainer stateA(columns, rows);
	CellsContainer stateB(columns, rows);
	CellsContainer* currentState = &stateA;
	CellsContainer* newState = &stateB;

	currentState->findCell(20, 20)->isAlive = true;
	currentState->findCell(20, 21)->isAlive = true;
	currentState->findCell(21, 20)->isAlive = true;
	currentState->findCell(20, 19)->isAlive = true;
	currentState->findCell(19, 2)->isAlive = true;

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist100(1, 100);
	std::uniform_int_distribution<std::mt19937::result_type> distColumns(0, columns - 1);
	std::uniform_int_distribution<std::mt19937::result_type> distRows(0, rows - 1);

	InitWindow(screenWidth, screenHeight, windowTitle);
	SetTargetFPS(10);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		// Copy current state into the new buffer
		*newState = *currentState;

		// Randomly make cells alive
		if (dist100(rng) > 1)
		{
			int cx = distColumns(rng);
			int cy = distRows(rng);
			Cell* c = currentState->findCell(cx, cy);
			if (c)
				c->isAlive = true;
		}

		// Draw cells
		for (auto& cell : *currentState->getCells())
		{
			cell.draw(cellSize);
		}

		gameOfLifeLogic(currentState, newState);

		std::swap(currentState, newState);

		DrawText(std::to_string(generations).c_str(), 50, 500, 50, GREEN);
		EndDrawing();

		++generations;
	}


	return 0;
}