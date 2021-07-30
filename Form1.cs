using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Tesseract;

namespace Text_Recognition
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openfile = new OpenFileDialog();

            if (openfile.ShowDialog() == DialogResult.OK)
            {
                string wanted_path = Path.GetDirectoryName(Path.GetDirectoryName(System.IO.Directory.GetCurrentDirectory()));
                wanted_path = System.IO.Directory.GetParent(wanted_path).ToString() + "\\tessdata";

                Bitmap img = new Bitmap(openfile.FileName);
                Pix pix = PixConverter.ToPix(img);
                TesseractEngine ocr = new TesseractEngine(wanted_path, "eng");
                Page page = ocr.Process(pix);
                
                textBox1.Text = page.GetText();
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
