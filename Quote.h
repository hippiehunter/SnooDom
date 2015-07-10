#pragma once

#include "DomObject.h"

#include <vector>

namespace SnooDom
{
	class Quote : public IDomContainer
	{
	public:
		Quote(std::vector<IDomObject*>& children, uint32_t domId) : IDomContainer(children, domId) { }

		virtual void Accept(IDomVisitor* visitor){ visitor->Visit(this); }
	};
}