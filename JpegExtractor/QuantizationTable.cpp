#include "stdafx.h"
#include "QuantizationTable.hpp"

QuantizationTable::QuantizationTable(int newSize)
{
	size = newSize;
	table = new int*[size];
}

QuantizationTable::QuantizationTable(const QuantizationTable& newTable)
{
	size = newTable.size;
	table = new int*[size];

	for (int i(0); i < size; i++)
	{
		table[i] = new int[size];

		for (int j(0); j < size; j++)
		{
			table[i][j] = newTable.table[i][j];
		}
	}
}

QuantizationTable::QuantizationTable(int** &newTable, int newSize)
{
	size = newSize;
	table = new int*[size];

	for (int i(0); i < size; i++)
	{
		table[i] = new int[size];

		for (int j(0); j < size; j++)
		{
			table[i][j] = newTable[i][j];
		}
	}
}

void QuantizationTable::turnTableToZigzagOrder()
{
	int lastValue(size * size - 1);
	int currNum(0);
	int currDiag(0);
	int loopFrom(0);
	int loopTo(0);
	int row(0);
	int col(0);

	int* temoFlatTable = new int[size * size];
	int k(0);
	for (int i(0); i < size; i++)
	{
		for (int j(0); j < size; j++)
		{
			temoFlatTable[k] = table[i][j];
			++k;
		}
	}

	do
	{
		if (currDiag < size)
		{
			loopFrom = 0;
			loopTo = currDiag;
		}
		else
		{
			loopFrom = currDiag - size + 1;
			loopTo = size - 1;
		}

		for (int i = loopFrom; i <= loopTo; i++)
		{
			if (currDiag % 2 == 0)
			{
				row = loopTo - i + loopFrom;
				col = i;
			}
			else
			{
				row = i;
				col = loopTo - i + loopFrom;
			}

			table[row][col] = temoFlatTable[currNum];
			++currNum;
		}

		++currDiag;
	} while (currDiag <= lastValue);
}
