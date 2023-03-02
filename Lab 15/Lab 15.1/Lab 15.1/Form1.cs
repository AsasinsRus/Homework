using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.ProgressBar;

namespace Lab_15._1
{
    public partial class Form1 : Form
    {
        Graphics graphics;
        Rectangle rect;
        Pen pen;
        Brush brush;
        int radius;
        public Form1()
        {
            InitializeComponent();
            CenterToScreen();

            pen = new Pen(Color.Black, 1);
            rect = new Rectangle(0,0, radius * 2, radius * 2);

            graphics = pictureBox1.CreateGraphics();          
        }

        private void button1_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.Application.Exit();
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
        }

        private void textBox1_KeyUp(object sender, KeyEventArgs e)
        {
            if(textBox1.Text != "" && !Regex.IsMatch(textBox1.Text, "^[^0,1,2,3,4,5,6,7,8,9]+$"))
            {
                graphics.Clear(Color.White);

                radius = Convert.ToInt32(textBox1.Text);

                rect.Width = radius * 2;
                rect.Height = radius * 2;

                graphics.DrawRectangle(pen, rect);
                graphics.DrawEllipse(pen, rect);

                textBox2.Text = Math.Pow(radius * 2, 2).ToString();
                textBox3.Text = (radius * 2 * 4).ToString();
            }
        }
    }
}
