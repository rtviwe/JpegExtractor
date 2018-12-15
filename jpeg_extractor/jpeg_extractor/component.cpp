/*
 @file component.hpp
 @Author Igor Spiridonov
 @version 1.0.0
 @date 09.12.2018
 */

#include "component.hpp"

/*
@brief Конструктор копирования
@param[in] component Цветовой компонент, из которого копируются данные
*/
Component::Component(const Component &component)
        : id(component.id),
          horizontalThinning(component.horizontalThinning),
          verticalThinning(component.verticalThinning),
          idQuantizationTable(component.idQuantizationTable) {
}

/*
@brief Конструктор
@param[in] id Идентификатор компонента
@param[in] horizontalThinning Горизонтальное прореживание
@param[in] verticalThinning Вертикальное прореживание
@param[in] idQuantizationTable Идентификатор таблицы квантования
*/
Component::Component(const int id, const int horizontalThinning, const int verticalThinning, const int idOfTable)
        : id(id),
          horizontalThinning(horizontalThinning),
          verticalThinning(verticalThinning),
          idQuantizationTable(idOfTable) {
}

/*
@brief Оператор вывода
@param[out] ostrm Поток вывода
@param[out] rhs Компонент, который выводится в поток вывода
@return Поток вывода
*/
std::ostream &operator<<(std::ostream &ostrm, const Component &rhs) {
    return rhs.writeTo(ostrm);
}

/*
@brief Вывод данных о компоненте
@param[out] ostrm Поток вывода
@return Поток вывода
*/
std::ostream &Component::writeTo(std::ostream &ostrm) const {
    ostrm << "id: " << id << " horizontal thinning: " << horizontalThinning
          << " vertical thinning: " << verticalThinning << " id of table quantization: " << idQuantizationTable;
    return ostrm;
}
