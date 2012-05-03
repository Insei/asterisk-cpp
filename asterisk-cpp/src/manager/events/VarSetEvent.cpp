/*
 * VarSetEvent.cpp
 *
 *  Created on: May 3, 2012
 *      Author: augcampos
 */

#include "asteriskcpp/manager/events/VarSetEvent.h"

namespace asteriskcpp {

	VarSetEvent::VarSetEvent(const std::string & values) :
			ManagerEvent(values) {

	}

	VarSetEvent::~VarSetEvent()
	{
	}

	std::string VarSetEvent::getChannel() const
	{
		return (getGetterValue(__FUNCTION__));
	}

	std::string VarSetEvent::getUniqueId() const
	{
		return (getGetterValue(__FUNCTION__));
	}

	std::string VarSetEvent::getVariable() const
	{
		return (getGetterValue(__FUNCTION__));
	}

	std::string VarSetEvent::getValue() const
	{
		return (getGetterValue(__FUNCTION__));
	}
} /* namespace asteriskcpp */
