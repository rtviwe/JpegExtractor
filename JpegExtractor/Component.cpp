#include "stdafx.h"
#include "Component.hpp"

Component::Component(int id, int hor, int ver, int idOfTable)
	: id(id), horizontalThinning(hor), verticalThinning(ver), idOfTableOfQuantization(idOfTable)
{
}

std::ostream& operator<<(std::ostream& ostrm, const Component& rhs)
{
	return rhs.writeTo(ostrm);
}


std::ostream& Component::writeTo(std::ostream& ostrm) const
{
	ostrm << "id: " << id << " horizontal thinning: " << horizontalThinning
		<< " vertical thinning: " << verticalThinning << " id of table quantization: " << idOfTableOfQuantization;
	return ostrm;
}