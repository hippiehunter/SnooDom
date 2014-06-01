//
// MarkdownButton.xaml.cpp
// Implementation of the MarkdownButton class
//

#include "MarkdownButton.xaml.h"

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

Windows::UI::Xaml::DependencyProperty^ MarkdownButton::_realContentProperty;
Windows::UI::Xaml::DependencyProperty^ MarkdownButton::_urlProperty;

MarkdownButton::MarkdownButton(Platform::String^ url, Platform::Object^ content)
{
	InitializeComponent();

	BorderThickness = Thickness(0);
	Url = url;
	RealContent = dynamic_cast<UIElement^>(content);
}


void MarkdownButton::OnUrlChanged(DependencyObject^ d, DependencyPropertyChangedEventArgs^ e)
{
	auto markdownButton = dynamic_cast<MarkdownButton^>(d);
	auto value = dynamic_cast<String^>(e->NewValue);
	if (value != nullptr && MarkdownButton::HistoryResolver != nullptr)
	{
		if (MarkdownButton::HistoryResolver(value))
		{
			markdownButton->Foreground = MarkdownButton::HistoryBrush;
		}
		else
		{
			markdownButton->Foreground = MarkdownButton::NoHistoryBrush;
		}
	}
}