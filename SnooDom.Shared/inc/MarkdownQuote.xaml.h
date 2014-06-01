//
// MarkdownQuote.xaml.h
// Declaration of the MarkdownQuote class
//

#pragma once

#include "MarkdownQuote.g.h"

namespace SnooDom
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class MarkdownQuote sealed
	{
	public:
		MarkdownQuote(Platform::String^ contents, Windows::UI::Xaml::Style^ style);
		MarkdownQuote(Windows::UI::Xaml::UIElement^ contents);
	};
}
