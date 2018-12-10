/*
 @file component.hpp
 @Author Igor Spiridonov
 @date 09.12.2018
 */

#include "quantization_table.hpp"

/*
@brief Конструктор копирования
@param[in] component Таблица кватования, из которой копируются данные
*/
QuantizationTable::QuantizationTable(const QuantizationTable& qTable)
	: size(qTable.size),
	valueLength(qTable.valueLength),
	tableId(qTable.tableId)
{
	table = new int*[size];

	for (int i(0); i < size; i++)
	{
		table[i] = new int[size];

		for (int j(0); j < size; j++)
		{
			table[i][j] = qTable.table[i][j];
		}
	}
}

/*
@brief Конструктор
@param[in] size Размер квадратной матрицы
@param[in] valueLength Длина каждого элемента матрицы
@param[in] tableId Идентификатор таблицы
@param[in] table Матрица
*/
QuantizationTable::QuantizationTable(const int size, const int valueLength, const int tableId, int** table)
	: size(size),
	valueLength(valueLength),
	tableId(tableId)
{
	this->table = new int*[size];

	for (int i(0); i < size; i++)
	{
		this->table[i] = new int[size];

		for (int j(0); j < size; j++)
		{
			this->table[i][j] = table[i][j];
		}
	}
}

QuantizationTable::~QuantizationTable()
{
	delete[] table;
}

/*
@brief Преобразование матрицы зигзагом
*/
void QuantizationTable::turnTableToZigzagOrder()
{
	int lastValue(size * size - 1);
	int currNum(0);
	int currDiag(0);
	int loopFrom(0);
	int loopTo(0);
	int row(0);
	int col(0);

	int* tempFlatTable = new int[size * size];
	int k(0);
	for (int i(0); i < size; i++)
	{
		for (int j(0); j < size; j++)
		{
			tempFlatTable[k] = table[i][j];
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

			table[row][col] = tempFlatTable[currNum];
			++currNum;
		}

		++currDiag;
	} while (currDiag <= lastValue);
}

/*
@brief Оператор присваивания
@param[in] table Таблица квантования, к которой присваивается текущий объект
@return Новая таблица квантования
*/
QuantizationTable& QuantizationTable::operator=(const QuantizationTable& obj)
{
	if (this != &obj)
	{
		int** newTable(new int*[obj.size]);
		delete[] table;
		table = newTable;
		std::copy(obj.table, obj.table + obj.size, table);

		size = obj.size;
		valueLength = obj.valueLength;
		tableId = obj.tableId;
	}
	return *this;
}

/*
@brief Оператор вывода
@param[out] ostrm Поток вывода
@param[out] rhs Таблица квантования, которая выводится в поток вывода
@return Поток вывода
*/
std::ostream& operator<<(std::ostream& ostrm, const QuantizationTable& rhs)
{
	return rhs.writeTo(ostrm);
}

/*
@brief Вывод данных о компоненте
@param[out] ostrm Поток вывода
@return Поток вывода
*/
std::ostream& QuantizationTable::writeTo(std::ostream& ostrm) const
{
	for (int j(0); j < size; j++)
	{
		for (int k(0); k < size; k++)
		{
			ostrm << table[j][k] << "\t";
		}
		ostrm << std::endl;
	}
	ostrm << std::endl;

	return ostrm;
}
