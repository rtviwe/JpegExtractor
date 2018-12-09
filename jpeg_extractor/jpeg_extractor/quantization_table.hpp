/*
 @file component.hpp
 @Author Igor Spiridonov
 @date 09.12.2018
 */

#pragma once
#ifndef QUANTIZATION_TABLE_HPP
#define QUANTIZATION_TABLE_HPP

#include <iostream>

/*
@author Igor Spiridonov
@version 1.0.0
@date 1.11.2018
@brief Заголовочный файл для таблицы квантования
@detailed Содержит в себе данные о таблице квантования
 */
struct QuantizationTable
{
	/*
	@brief Конструктор
	*/
	QuantizationTable() = default;

	/*
	@brief Конструктор копирования
	@param[in] component Таблица кватования, из которой копируются данные	
	*/
	QuantizationTable(const QuantizationTable& newTable);

	/*
	@brief Конструктор
	@param[in] size Размер квадратной матрицы
	@param[in] valueLength Длина каждого элемента матрицы
	@param[in] tableId Идентификатор таблицы
	@param[in] table Матрица
	*/
	QuantizationTable(const int size, const int valueLength, const int tableId, int** table);

	/*
	@brief Деструктор
	*/
	~QuantizationTable();

	/*
	@brief Оператор присваивания
	@param[in] table Таблица квантования, к которой присваивается текущий объект
	@return Новая таблица квантования
	*/
	QuantizationTable& operator=(const QuantizationTable& table);

	/*
	@brief Преобразование матрицы зигзагом
	*/
	void turnTableToZigzagOrder();

	/*
	@brief Вывод данных о компоненте
	@param[out] ostrm Поток вывода
	@return Поток вывода
	*/
	std::ostream& writeTo(std::ostream& ostrm) const;

	int size{ 0 }; //< Размер квадратной матрицы
	int valueLength{ 0 }; //< Длина каждого элемента матрицы
	int tableId{ 0 }; //< Идентификатор таблицы
	int** table{ nullptr }; //< Матрица
};

/*
@brief Оператор вывода
@param[out] ostrm Поток вывода
@param[out] rhs Таблица квантования, которая выводится в поток вывода
@return Поток вывода
*/
std::ostream& operator<<(std::ostream& ostrm, const QuantizationTable& rhs);

#endif
