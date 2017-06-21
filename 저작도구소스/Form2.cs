using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
//using Newtonsoft.Json;
//using Newtonsoft.Json.Linq;
using SHDocVw; // SHDocVw.dll
using mshtml;  // Microsoft.mshtml.dll
using System.IO;
using System.Security.Permissions;
using System.Runtime.InteropServices;
using System.Threading;
using System.Diagnostics;

namespace project_gdi_
{
    public partial class Form2 : Form
    {
        string defaultFolder = Form1.defaultFolder;
        string defaultFileName = Form1.defaultFileName;
        string projectPath = Form1.projectPath;

        //현재 열려있는 페이지
        HTMLPage curPage;

        string[] curDocumentProperties;

        public Form2()
        {
            InitializeComponent();

            //CreateNewPage("newPage");
        }

        //public Form2(string projectName, string beat, string subtitleText,
        //    string start, string end, string songCounter, string group, string beatCount)
        public Form2(string projectName)
        {
            InitializeComponent();

            CreateNewPage(projectName);
            
        }
        public Form2(string projectName, string[] properties)
        {
            InitializeComponent();
            
            CreateNewPage(projectName, properties);

        }
        
        private void CreateNewPage(string projectName)
        {
            projectPath += "/" + projectName;

            TabPage tpage = new TabPage();
            tpage.BorderStyle = BorderStyle.Fixed3D;
            tpage.Text = projectName;
            browserTabControl.TabPages.Add(tpage);
            browserTabControl.SelectTab(tpage);

            InitHtmlPage(ref tpage);

        }

        private void CreateNewPage(string projectName, string[] properties)
        {
            CreateNewPage(projectName);
            curDocumentProperties = properties;
        }

        private void InitHtmlPage(ref TabPage page)
        {
            HTMLPage html = new HTMLPage(ref page, "file://" + projectPath + defaultFileName, ref targetBox);
            curPage = html;
        }

        private void SetMutable()
        {
            var target = curPage.GetCurElement();
            if (target.Name.Length < 1)
            {
                MessageBox.Show("선택된 객체가 없음");
                return;
            }
            //curPage.SetTargetMutable();

            //new Form3(target).ShowDialog();
        }

        private void CreateInnerHTMLData(HTMLPage page)
        {
            try
            {
                JsonBuilder.CreateOutputJsonData(page.GetPaperInnerHtml(), projectPath + "/js");
            }
            catch (Exception e)
            {
                MessageBox.Show("파일쓰는데 문제가 발생: " + e.Data);
            }

            MessageBox.Show("파일쓰기완료");
        }

        #region temp

        #endregion

        //form event
        private void tabPage1_Click(object sender, EventArgs e)
        {
            Console.WriteLine("tab page click!");
        }

        private void browserTabControl_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine("index changed!");
        }

        private void browserTabControl_MouseDown(object sender, MouseEventArgs e)
        {
            Console.WriteLine("tab click!");
        }

        private void Form2_Click(object sender, EventArgs e)
        {
            Console.WriteLine("form click!");
        }

        private void btnModify_Click(object sender, EventArgs e)
        {
            SetMutable();
        }

        private void Form2_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.A)
            {
                SetMutable();
            }
        }

        private void btnOutput_Click(object sender, EventArgs e)
        {
            CreateInnerHTMLData(curPage);
        }
    }
}
