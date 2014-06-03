using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.VisualStudio.TestPlatform.UnitTestFramework;

namespace Test.Windows
{
    [TestClass]
    public class SnuDownTests
    {
        [TestMethod]
        public void DontCrash()
        {
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
