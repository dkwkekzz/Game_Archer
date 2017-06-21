using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace project_gdi_
{
    public class HTMLPage
    {
        Label targetBox;

        WebBrowser browser;
        HtmlDocument document;
        HtmlElementCollection col;

        HtmlElement selected;

        public HTMLPage(ref TabPage tabPage, string htmlPath, ref Label targetBox)
        {
            this.targetBox = targetBox;
            browser = new System.Windows.Forms.WebBrowser();
            browser.Dock = DockStyle.Fill;
            browser.ObjectForScripting = true;
            browser.Navigate(htmlPath);
            browser.DocumentCompleted += new WebBrowserDocumentCompletedEventHandler(CallHtmlInit);

            tabPage.Controls.Add(browser);

            //html문서 조작
            document = browser.Document;
            document.Click += SelectHtmlElement;
            //html문서에서 자막 객체를 수정하도록 함수 호출
            //ExecJavascript("subtitleSetting", "");
        }

        public HtmlElement GetCurElement()
        {
            return selected;
        }

        public void SetTargetMutable()
        {
            ExecJavascript("setTargetMutable", "");
        }

        public string GetPaperInnerHtml()
        {
            var elements = document.All;
            List<HtmlElement> papers = new List<HtmlElement>();

            //필요없는 속성 제거
            foreach (HtmlElement e in elements)
            {
                //name
                if (e.Name == "sheetFlashPaper" || e.Name == "imageFlashPaper")
                {
                    papers.Add(e);
                }
                if(e.Name == "subtitle" || e.Name == "videoPlayBar")
                {
                    e.InnerHtml = "";
                }
                e.Name = "";

                //style
                if (e.Style == null) continue;

                var nStyle = "";
                var styleStrs = e.Style.Split(';');
                foreach (var s in styleStrs)
                {
                    var style = s.Split(':')[0].ToLower().Trim();
                    if (style == "left" || style == "top" || style == "visibility")
                    {
                        nStyle += s + ";";
                        Console.WriteLine(s);
                    }
                    e.Style = nStyle;
                }
            }

            var ret = "var flashPaper = [";
            foreach(var e in papers)
            {
                ret += "'";
                var inner = e.InnerHtml;

                var removeText = new string[] { "\r\n" , "\t" , "\n" , "\r" ,
                            "ui-draggable", "-handle"};
                foreach (var t in removeText)
                {
                    inner = inner.Replace(t, "");
                }

                ret += inner;
                ret += "',";
                //Console.WriteLine(ret);
            }

            return ret + "];";
        }
        
        private void CallHtmlInit(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            ExecJavascript("subtitleSetting", "");
        }

        private void SelectHtmlElement(object sender, HtmlElementEventArgs e)
        {
            selected = document.ActiveElement;
            targetBox.Text = selected.Name;

        }

        #region HTML_Control 

        //private void ExecJavascript(ref HtmlDocument document, string funcName, string param_1)
        //{
        //    try
        //    {
        //        if(document == null)
        //        {
        //            MessageBox.Show("선택된 문서가 없습니다.");
        //            return;
        //        }
        //        document.InvokeScript("CallScript", new object[] { funcName, param_1 });
        //    }
        //    catch
        //    {
        //        MessageBox.Show("자바스크립트 호출 예외 발생");
        //    }
        //}

        public void ExecJavascript(string funcName, string param_1)
        {
            try
            {
                document.InvokeScript(funcName, new object[] { param_1 });
            }
            catch (Exception e)
            {
                MessageBox.Show("자바스크립트 호출 예외 발생: " + e.Message);
            }
        }

        public void CallForm(object msg)
        {
            string sMsg = (string)msg;
            {
                // 받은 msg 값을 가지고 처리하는 로직.  
            }
        }

        #endregion

    }
}
