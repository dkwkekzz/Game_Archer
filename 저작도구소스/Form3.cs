using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace project_gdi_
{
    public partial class Form3 : Form
    {
        HtmlElement target;

        public Form3(HtmlElement target)
        {
            InitializeComponent();

            this.target = target;
        }
    }
}
