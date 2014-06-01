//
// MarkdownQuote.xaml.cpp
// Implementation of the MarkdownQuote class
//

#include "MarkdownQuote.xaml.h"

using namespace SnooDom;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The User Control item template is documented at http://go.microsoft.com/fwlink/?LinkId=234236
MarkdownQuote::MarkdownQuote(Platform::String^ contents, Windows::UI::Xaml::Style^ style)
{
	InitializeComponent();

	auto textBlock = ref new TextBlock();
	textBlock->Text = contents;
	textBlock->Style = style;

}
MarkdownQuote::MarkdownQuote(Windows::UI::Xaml::UIElement^ contents)
{
	InitializeComponent();
	Content = contents;
}

