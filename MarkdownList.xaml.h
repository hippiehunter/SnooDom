//
// MarkdownList.xaml.h
// Declaration of the MarkdownList class
//

#pragma once

#include "MarkdownList.g.h"
#include <vector>
namespace SnooDom
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class MarkdownList sealed
	{
	internal:
		MarkdownList(bool numbered, const std::vector<Windows::UI::Xaml::UIElement^>& elements);
	};
}
