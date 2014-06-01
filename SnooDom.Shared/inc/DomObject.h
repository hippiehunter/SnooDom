#pragma once

#include <collection.h>
#include <windows.foundation.h>

namespace SnooDom
{
	class Text;
	class Code;
	class Quote;
	class OrderedList;
	class UnorderedList;
	class HorizontalRule;
	class Table;
	class Link;
	class Paragraph;
	class Document;
	class TableRow;
	class TableColumn;
	class LineBreak;
	class IDomVisitor;

	class IDomObject
	{
	public:
		uint32_t DomID;
		IDomObject(uint32_t domId) : DomID(domId) {}
		virtual void Accept(IDomVisitor* visitor) = 0;
		virtual ~IDomObject() {};
		
	};

	class IDomContainer : public IDomObject
	{
	public:
		std::vector<IDomObject*> Children;
		IDomContainer(std::vector<IDomObject*>& children, uint32_t domId) : IDomObject(domId), Children(children) { }
		virtual ~IDomContainer() {};
	};

	class IDomVisitor
	{
	public:
		virtual void Visit(Text* text) = 0;
		virtual void Visit(Code* code) = 0;
		virtual void Visit(Quote* quote) = 0;
		virtual void Visit(OrderedList* orderedList) = 0;
		virtual void Visit(UnorderedList* unorderedList) = 0;
		virtual void Visit(HorizontalRule* horizontalRule) = 0;
		virtual void Visit(Table* table) = 0;
		virtual void Visit(Link* link) = 0;
		virtual void Visit(Paragraph* paragraph) = 0;
		virtual void Visit(Document* document) = 0;
		virtual void Visit(TableRow* tableRow) = 0;
		virtual void Visit(TableColumn* tableColumn) = 0;
		virtual void Visit(LineBreak* lineBreak) = 0;
		virtual ~IDomVisitor() {};
	};
	struct dom_builder_state;

	class Document : public IDomContainer
	{
	public:
		std::unique_ptr<dom_builder_state> State;
		Document();
		~Document();
		virtual void Accept(IDomVisitor* visitor){ visitor->Visit(this); }
	};
}