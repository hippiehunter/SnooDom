//
// MarkdownTable.xaml.h
// Declaration of the MarkdownTable class
//

#pragma once

#include "MarkdownTable.g.h"
#include <vector>
namespace SnooDom
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class MarkdownTable sealed
	{
	internal:
		MarkdownTable(const std::vector<Windows::UI::Xaml::UIElement^>& headers, const std::vector<std::vector<Windows::UI::Xaml::UIElement^>>& body);
	};
}
