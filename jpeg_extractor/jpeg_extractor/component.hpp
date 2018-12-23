/*!
 \file component.hpp
 \Author Igor Spiridonov
 \version 1.0.0
 \date 09.12.2018
 */

#pragma once
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>

/*!
\author Igor Spiridonov
\version 1.0.0
\date 11.11.2018
\brief Заголовочный файл для цветового компонента
\detailed Содержит в себе данные о данном цветовом компоненте
 */
struct Component {
    /*!
    \brief Конструктор
    */
    Component() = default;

    /*!
    \brief Конструктор копирования
    \param[in] component Цветовой компонент, из которого копируются данные
    */
    Component(const Component &component);

    /*!
    \brief Конструктор
    \param[in] id Идентификатор компонента
    \param[in] horizontalThinning Горизонтальное прореживание
    \param[in] verticalThinning Вертикальное прореживание
    \param[in] idQuantizationTable Идентификатор таблицы квантования
    */
    Component(const int id, const int horizontalThinning, const int verticalThinning, const int idQuantizationTable);

    /*!
    \brief Деструктор
    */
    ~Component() = default;

    /*!
    \brief Вывод данных о компоненте
    \param[out] ostrm Поток вывода
    \return Поток вывода
    */
    std::ostream &writeTo(std::ostream &ostrm) const;

    /*!
    \brief Оператор присваивания
    \param[in] table Цветовой компонент, к которому присваивается текущий объект
    \return Новый цветовой компонент
    */
    Component &operator=(const Component &table) = default;

    /*!
    \brief Идентификатор
    */
    int id{0};

    /*!
    \brief Горизонтальное прореживание
    */
    int horizontalThinning{0};

    /*!
    \brief Вертикальное прореживание
    */
    int verticalThinning{0};

    /*!
    \brief Идентификатор таблицы квантования
    */
    int idQuantizationTable{0};
};

/*!
\brief Оператор вывода
\param[out] ostrm Поток вывода
\param[out] rhs Компонент, который выводится в поток вывода
\return Поток вывода
*/
std::ostream &operator<<(std::ostream &ostrm, const Component &rhs);

#endif