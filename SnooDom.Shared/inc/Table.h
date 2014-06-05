#pragma once

#include "DomObject.h"
#include "Paragraph.h"

#include <vector>

namespace SnooDom
{
	class TableColumn;
	class Table;

	class TableRow : public IDomObject
	{
	public:
		std::vector<TableColumn*> Columns;
		virtual void Accept(IDomVisitor* visitor) { visitor->Visit(this); }
		TableRow(std::vector<IDomObject*>& children, uint32_t domId);
	};

	enum class ColumnAlignment
	{
		Left,
		Right,
		Center
	};

	class TableColumn : public IDomContainer
	{
	public:
		TableColumn(std::vector<IDomObject*>& children, uint32_t domId, int flags);
		ColumnAlignment Alignment;
		virtual void Accept(IDomVisitor* visitor) { visitor->Visit(this); }
	};

	class Table : public IDomObject
	{
	public:
		std::vector<TableRow*> Rows;
		std::vector<TableColumn*> Headers;
		virtual void Accept(IDomVisitor* visitor) { visitor->Visit(this); }
		Table(std::vector<IDomObject*>& header, std::vector<IDomObject*>& children, uint32_t domId) : IDomObject(domId)
		{
			if(header.size() == 1)
			{
				auto headerRow = dynamic_cast<TableRow*>(header[0]);
				if(headerRow != nullptr)
				{
					Headers = headerRow->Columns;
				}
			}

			for(auto obj : children)
			{
				auto objRow = dynamic_cast<TableRow*>(obj);
				if(objRow != nullptr)
					Rows.push_back(objRow);
			}
		}
	public:
		
	};
}