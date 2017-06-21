using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace project_gdi_
{
    public partial class Form1 : Form
    {
        public static string defaultFolder = "/page 1_1";
        public static string defaultFileName = "/page 1.html";
        public static string projectPath = Directory.GetCurrentDirectory();
        //public static string picturePath = projectPath + defaultFolder + "/subtitle";

        private Dictionary<string, Font> myFonts;
        private Brush blackBrush, colorBrush;
        //private JsonBuilder builder;

        public Form1()
        {
            InitializeComponent();

            init();
        }

        private void init()
        {
            makeBrush();
            makeFont("Times New Roman", 24);
        }

        private void makeBrush()
        {
            blackBrush = new SolidBrush(Color.Black);
            colorBrush = new SolidBrush(Color.Red);
        }

        private void makeFont(string fontStyle, int size)
        {
            if (myFonts == null)
            {
                myFonts = new Dictionary<string, Font>();
            }
            var nFont = new Font(fontStyle, size);
            myFonts.Add(fontStyle, nFont);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            CreateNewForm(fileNameBox.Text);
        }

        private void CreateNewForm(string newProject)
        {
            if(!CheckSetting())
            {
                return;
            }

            //세팅이 성공적이라면 폴더를 복사한다.
            
            if (!CreateFolder(newProject))
            {
                MessageBox.Show("같은 이름의 프로젝트가 이미 존재합니다. 기존의 프로젝트를 불러옵니다.");
                new Form2(newProject).ShowDialog();
                return;
            }

            //var properties = new string[]{ textBox1.Text, textBox2.Text,
            //        textBox3.Text, textBox4.Text, textBox5.Text, textBox6.Text, textBox7.Text };

            if (!CreateJsonData(projectPath + "/" + newProject + "/js"))
            {
                return;
            }

            //var newForm = new Form2(newProject, properties);
            var newForm = new Form2(newProject);
            newForm.ShowDialog();

        }

        private bool CheckSetting()
        {
            bool ret = true;

            var beats = textBox1.Text.Split(',');
            var beatCount = beats.Length;
            foreach (string str in beats)
            {
                //str.Trim();

                float temp = 0.0f;
                ret &= float.TryParse(str, out temp);
                if(!ret)
                {
                    MessageBox.Show("박자는 ,로 구분합니다.");
                    return ret;
                }
            }

            var texts = textBox2.Text.Split('\n');
            var textCount = 0;
            for (var i = 0; i < texts.Length; i++)
            {
                texts[i] = texts[i].TrimEnd('\r');
                textCount += texts[i].Length;
            }

            ret &= (beatCount == textCount);
            if(!ret)
            {
                MessageBox.Show("박자수랑 글자수가 다릅니다. 가사는 마디가 넘어가면 엔터해야 함");
                return ret;
            }

            float start = 0.0f, end = 0.0f;
            ret &= (float.TryParse(textBox3.Text, out start) && float.TryParse(textBox4.Text, out end));
            if (!ret)
            {
                MessageBox.Show("시작 시간과 끝시간에 제대로된 숫자를 입력하세요.");
                return ret;
            }

            int songCount = 0, groupCount = 0;
            ret &= (int.TryParse(textBox5.Text, out songCount) && int.TryParse(textBox6.Text, out groupCount));
            if (!ret)
            {
                MessageBox.Show("마디와 절 개수에 제대로된 숫자를 입력하세요.");
                return ret;
            }

            ret &= (groupCount == texts.Length);
            if (!ret)
            {
                MessageBox.Show("가사엔터친개수는 마디개수랑 같아야 한단다.");
                return ret;
            }

            ret &= (fileNameBox.Text.Length > 0);
            if(!ret)
            {
                MessageBox.Show("파일명 입력하세요.");
                return ret;
            }

            return ret;
        }
        
        private bool CreateFolder(string newProject)
        {
            DirectoryInfo fi = new DirectoryInfo(projectPath + "/" + fileNameBox.Text);
            if (fi.Exists)
            {
                return false;
            }
            else
            {
                CopyFolder(projectPath + defaultFolder, projectPath + "/" + newProject);
            }

            string picturePath = projectPath + "/" + newProject + "/subtitle";
            if (!CreateTextImages(textBox2.Text, picturePath))
            {
                return false;
            }

            return true;
        }

        private bool CreateTextImages(string subtitleText, string picturePath)
        {
            foreach (char ch in subtitleText)
            {
                if(ch == '\n' || ch == '\r')
                {
                    continue;
                }
                string text = ch.ToString();
                CreateTextImage(blackBrush, text, picturePath);
                CreateTextImage(colorBrush, text + "2", picturePath);
            }

            //check
            string _Filestr = picturePath;
            System.IO.FileInfo fi;
            foreach (char ch in subtitleText)
            {
                if (ch == '\n' || ch == '\r')
                {
                    continue;
                }
                fi = new System.IO.FileInfo(_Filestr + "/" + ch + ".png");
                if (!fi.Exists)
                {
                    MessageBox.Show("글자 생성 실패");
                    return false;
                }
            }

            return true;
        }

        private void CreateTextImage(Brush brush, string text, string picturePath)
        {
            Bitmap bitmap = new Bitmap(25, 25);
            for (int Xcount = 0; Xcount < bitmap.Width; Xcount++)
            {
                for (int Ycount = 0; Ycount < bitmap.Height; Ycount++)
                {
                    bitmap.SetPixel(Xcount, Ycount, Color.White);
                }
            }

            PointF location = new PointF(0f, 0f);
            using (Graphics graphics = Graphics.FromImage(bitmap))
            {
                //graphics.CompositingMode = CompositingMode.SourceCopy;
                graphics.CompositingQuality = CompositingQuality.HighQuality;
                graphics.SmoothingMode = SmoothingMode.HighQuality;
                graphics.InterpolationMode = InterpolationMode.HighQualityBicubic;

                graphics.DrawString(text.TrimEnd(new char[]{ '2' }), new Font("Times New Roman", 16), brush, location);
                //using (Font f = myFonts["Times New Roman"])
                //{
                //    try
                //    {
                //        graphics.DrawString(text, new Font("Times New Roman", 24), brush, location);
                //    }
                //    catch(Exception e) {  }
                //}
            }

            bitmap.Save(picturePath + "/" + text + ".png", System.Drawing.Imaging.ImageFormat.Png);
        }

        private void CopyFolder(string sourceFolder, string destFolder)
        {
            if (!Directory.Exists(destFolder))
                Directory.CreateDirectory(destFolder);

            string[] files = Directory.GetFiles(sourceFolder);
            string[] folders = Directory.GetDirectories(sourceFolder);

            foreach (string file in files)
            {
                string name = Path.GetFileName(file);
                string dest = Path.Combine(destFolder, name);
                File.Copy(file, dest);
            }

            // foreach 안에서 재귀 함수를 통해서 폴더 복사 및 파일 복사 진행 완료  
            foreach (string folder in folders)
            {
                string name = Path.GetFileName(folder);
                string dest = Path.Combine(destFolder, name);
                CopyFolder(folder, dest);
            }
        }

        private bool CreateJsonData(string destFolder)
        {
            var ret = true;

            try
            {
                JsonBuilder.CreateInitJsonData(new string[]{ textBox1.Text, textBox2.Text,
                    textBox3.Text, textBox4.Text, textBox5.Text, textBox6.Text, textBox7.Text }, destFolder);
            }
            catch(Exception e)
            {
                MessageBox.Show(e.Message);
                return false;
            }
            
            return ret;
        }




        //none
        private void button2_Click(object sender, EventArgs e)
        {
            ////Bitmap bitmap = (Bitmap)System.Drawing.Image.FromFile(picturePath + "/1.jpg");
            //Bitmap bitmap = new Bitmap(35, 35);
            //
            //PointF location = new PointF(-5f, 0f);
            //using (Graphics graphics = Graphics.FromImage(bitmap))
            //{
            //    using (Font f = myFonts["Times New Roman"])
            //    {
            //        graphics.DrawString("오", f, blackBrush, location);
            //    }
            //}
            //
            //bitmap.Save(picturePath + "/2.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            var newForm = new Form4();
            newForm.ShowDialog();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
