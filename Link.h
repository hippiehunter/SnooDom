#pragma once

#include "DomObject.h"
#include "Text.h"
#include <vector>


namespace SnooDom
{
	class Link : public IDomObject
	{
	public:
		Link(const std::string& link, const std::string& title, std::vector<IDomObject*>& expandedDisplay, uint32_t domId) : IDomObject(domId), Display(expandedDisplay)
		{
			Url = link;
			if(title.size() > 0)
				Hover = std::make_shared<Text>(title, 0);
		}

		std::vector<IDomObject*> Display;
		std::shared_ptr<Text> Hover;
		std::string Url;

		virtual void Accept(IDomVisitor* visitor){ visitor->Visit(this);}
	};
}