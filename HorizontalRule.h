#pragma once

#include "DomObject.h"

namespace SnooDom
{
	class HorizontalRule : public IDomObject
	{
	public:
		HorizontalRule(uint32_t domId) : IDomObject(domId) { }
		virtual void Accept(IDomVisitor* visitor){ visitor->Visit(this); }
	};
}