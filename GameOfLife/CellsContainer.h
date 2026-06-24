#pragma once
#include <iostream>
#include <vector>
#include <array>
#include "Cell.h"

class CellsContainer
{
public:
	CellsContainer(int columns, int rows) : m_columns{columns}, m_rows{rows}
	{
		for (int i = 0; i < columns; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				Vector2 position{ (float)i, (float)j };
				Cell cell{ false, position };

				m_cells.push_back(cell);
			}
		}

		//std::cout << "size: " << m_cells.size() << '\n';
	}

	inline bool isPositionValid(int column, int row) {
		if (row < m_rows && row >= 0 && column >= 0 && column < m_columns)
			return true;

		return false;
	}

	inline Cell* findCell(int column, int row) { 
		if (isPositionValid(column, row))
		{
			return &m_cells[(column * m_rows) + row];
		}
		else
			return nullptr;
	}
	inline std::vector<Cell>* getCells() { return &m_cells; }
	inline int getNumberOfAliveNeighbors(int column, int row)
	{
		int aliveNeighbors{};
		
		for (int i = -1; i < 2; ++i)
		{
			for (int j = -1; j < 2; ++j)
			{
				if (!i && !j)
					continue;

				Cell* possibleCell{ findCell(column + i, row + j) };

				if (possibleCell && possibleCell->isAlive)
					++aliveNeighbors;
			}
		}

		return aliveNeighbors;
	}

	inline const int getColumns() { return m_columns; }
	inline const int getRows() { return m_rows; }

private:
	int m_columns;
	int m_rows;
	std::vector<Cell> m_cells;
};