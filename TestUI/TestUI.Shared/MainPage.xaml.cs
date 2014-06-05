using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace TestUI
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            this.NavigationCacheMode = NavigationCacheMode.Required;
        }

		class MarkdownHelpers : SnooDom.ICommandFactory, SnooDom.IStyleProvider
		{
			public TypedEventHandler<Windows.UI.Xaml.Documents.Hyperlink, Windows.UI.Xaml.Documents.HyperlinkClickEventArgs> MakeLinkCommand(string url)
			{
				return new TypedEventHandler<Windows.UI.Xaml.Documents.Hyperlink, Windows.UI.Xaml.Documents.HyperlinkClickEventArgs>((link, arg) => { });
			}

			public Style BorderStyle
			{
				get { return new Style(); }
			}

			public Style RichTextBlockStyle
			{
				get { return new Style(); }
			}

			public Style RunStyle
			{
				get { return new Style(); }
			}

			public Style TextBlockStyle
			{
				get { return null; }
			}
		}

        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.
        /// This parameter is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            // TODO: Prepare page for display here.

            // TODO: If your application contains multiple pages, ensure that you are
            // handling the hardware Back button by registering for the
            // Windows.Phone.UI.Input.HardwareButtons.BackPressed event.
            // If you are using the NavigationHelper provided by some templates,
            // this event is handled for you.
			var helper = new MarkdownHelpers();
			var mdControl = new SnooDom.MarkdownControl(helper, helper);
			Content = mdControl;
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("");
			SnooDom.SnooDom.MarkdownToDOM("");
			SnooDom.SnooDom.MarkdownToDOM("http://www.reddit.com");
			SnooDom.SnooDom.MarkdownToDOM("[foo](http://en.wikipedia.org/wiki/Link_(film\\))");
			SnooDom.SnooDom.MarkdownToDOM("(http://tsfr.org)");
			SnooDom.SnooDom.MarkdownToDOM("[A link with a /r/subreddit in it](/lol)");
			SnooDom.SnooDom.MarkdownToDOM("[A link with a http://www.url.com in it](/lol)");
			SnooDom.SnooDom.MarkdownToDOM("[Empty Link]()");
			SnooDom.SnooDom.MarkdownToDOM("http://en.wikipedia.org/wiki/café_racer");
			SnooDom.SnooDom.MarkdownToDOM("#####################################################hi");
			SnooDom.SnooDom.MarkdownToDOM("[foo](http://bar\nbar)");
			SnooDom.SnooDom.MarkdownToDOM("/r/test");
			SnooDom.SnooDom.MarkdownToDOM("Words words /r/test words");
			SnooDom.SnooDom.MarkdownToDOM("/r/");
			SnooDom.SnooDom.MarkdownToDOM("escaped \\/r/test");
			SnooDom.SnooDom.MarkdownToDOM("ampersands http://www.google.com?test&blah");
			SnooDom.SnooDom.MarkdownToDOM("[_regular_ link with nesting](/test)");
			SnooDom.SnooDom.MarkdownToDOM(" www.a.co?with&test");
			SnooDom.SnooDom.MarkdownToDOM("Normal^superscript");
			SnooDom.SnooDom.MarkdownToDOM("Escape\\^superscript");
			SnooDom.SnooDom.MarkdownToDOM("~~normal strikethrough~~");
			SnooDom.SnooDom.MarkdownToDOM("\\~~escaped strikethrough~~");
			SnooDom.SnooDom.MarkdownToDOM("anywhere\\x03, you");
			SnooDom.SnooDom.MarkdownToDOM("[Test](//test)");
			SnooDom.SnooDom.MarkdownToDOM("[Test](//#test)");
			SnooDom.SnooDom.MarkdownToDOM("[Test](#test)");
			SnooDom.SnooDom.MarkdownToDOM("[Test](git://github.com)");
			SnooDom.SnooDom.MarkdownToDOM("[Speculation](//?)");
			SnooDom.SnooDom.MarkdownToDOM("/r/sr_with_underscores");
			SnooDom.SnooDom.MarkdownToDOM("[Test](///#test)");
			SnooDom.SnooDom.MarkdownToDOM("/r/multireddit+test+yay");
			SnooDom.SnooDom.MarkdownToDOM("<test>");
			SnooDom.SnooDom.MarkdownToDOM("words_with_underscores");
			SnooDom.SnooDom.MarkdownToDOM("words*with*asterisks");
			SnooDom.SnooDom.MarkdownToDOM("~test");
			SnooDom.SnooDom.MarkdownToDOM("/u/test");
			SnooDom.SnooDom.MarkdownToDOM("/u/test/m/test test");
			SnooDom.SnooDom.MarkdownToDOM("/U/nope");
			SnooDom.SnooDom.MarkdownToDOM("/r/test/m/test test");
			SnooDom.SnooDom.MarkdownToDOM("/r/test/w/test test");
			SnooDom.SnooDom.MarkdownToDOM("/r/test/comments/test test");
			SnooDom.SnooDom.MarkdownToDOM("/u/test/commentscommentscommentscommentscommentscommentscomments/test test");
			SnooDom.SnooDom.MarkdownToDOM("/r/test/commentscommentscommentscommentscommentscommentscomments/test test");
			SnooDom.SnooDom.MarkdownToDOM("blah \\\\");
			SnooDom.SnooDom.MarkdownToDOM("/r/whatever: fork");
			SnooDom.SnooDom.MarkdownToDOM("/r/t:timereddit");
			SnooDom.SnooDom.MarkdownToDOM("/r/reddit.com");
			SnooDom.SnooDom.MarkdownToDOM("/r/not.cool");
			SnooDom.SnooDom.MarkdownToDOM("/r/very+clever+multireddit+reddit.com+t:fork+yay");
			SnooDom.SnooDom.MarkdownToDOM("/r/t:heatdeathoftheuniverse");
			SnooDom.SnooDom.MarkdownToDOM("/r/all-minus-something");
			SnooDom.SnooDom.MarkdownToDOM("/r/all-minus-something");
			SnooDom.SnooDom.MarkdownToDOM("/r/notall-minus");
			SnooDom.SnooDom.MarkdownToDOM("/R/reddit.com");
        }
    }
}
