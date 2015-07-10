#pragma once

#include "DomObject.h"
#include <vector>

namespace SnooDom
{
	class Text : public IDomObject
	{
	public:
		Text(const std::string& plainText, uint32_t domId) : IDomObject(domId), Contents(plainText), Italic(false), HeaderSize(0), Bold(false), Strike(false), Superscript(false) { }
	
		bool Italic;
		int HeaderSize; //0 for no headerness
		bool Bold;
		bool Strike;
		bool Superscript;
		std::string Contents;
		virtual void Accept(IDomVisitor* visitor){ visitor->Visit(this); }
	};
}