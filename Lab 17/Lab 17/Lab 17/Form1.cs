using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace Lab_17
{
    public partial class Form1 : Form
    {
        Trapez trapez;
        Graphics graphics;
        Pen pen;
        int xShift = 10, yShift = 10;
        public Form1()
        {
            InitializeComponent();

            graphics = pictureBox1.CreateGraphics();
            pen = new Pen(Color.Black, 2);
            trapez = new Trapez();
        }

        public void DrawTrapeze(float topBase, float bottomBase, float height, float xShift = 0, float yShift = 0)
        {
            float topBaseFrom = (bottomBase - topBase) / 2;
            float topBaseTo = topBase + topBaseFrom;

            graphics.DrawLine(pen, topBaseFrom + xShift, yShift, topBaseTo + xShift, yShift);
            graphics.DrawLine(pen, topBaseTo + xShift, yShift, bottomBase + xShift, height + yShift);
            graphics.DrawLine(pen, bottomBase + xShift, height + yShift, xShift, height + yShift);
            graphics.DrawLine(pen, xShift, height + yShift, topBaseFrom + xShift, yShift);
        }
        private void button1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        private void textBox1_KeyUp(object sender, KeyEventArgs e)
        {
            foreach(char i in textBox1.Text)
            {
                if (!Char.IsDigit(i))
                    return;
            }

            if (textBox1.Text != "")
            {
                trapez.TopBase = Convert.ToInt32(textBox1.Text);
                graphics.Clear(Color.White);
                trapez.Draw(graphics, pen, xShift, yShift);
            }

            
        }

        private void textBox2_KeyUp(object sender, KeyEventArgs e)
        {
            foreach (char i in textBox2.Text)
            {
                if (!Char.IsDigit(i))
                    return;
            }

            if (textBox2.Text != "")
            {
                trapez.BottomBase = Convert.ToInt32(textBox2.Text);
                graphics.Clear(Color.White);
                trapez.Draw(graphics, pen, xShift, yShift);
            }
        }

        private void textBox3_KeyUp(object sender, KeyEventArgs e)
        {
            foreach (char i in textBox3.Text)
            {
                if (!Char.IsDigit(i))
                    return;
            }

            if (textBox3.Text != "")
            {
                trapez.Height = Convert.ToInt32(textBox3.Text);
                graphics.Clear(Color.White);
                trapez.Draw(graphics, pen, xShift, yShift);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            var xmlSerializer = new XmlSerializer(typeof(Trapez));
            var fs = new FileStream("TrapezSave.xml", FileMode.OpenOrCreate);

            xmlSerializer.Serialize(fs, trapez);
            fs.Close();
        }

        private void LoadSerializableTrapez()
        {
            if(File.Exists("TrapezSave.xml"))
            {
                var xmlSerializer = new XmlSerializer(typeof(Trapez));
                var fs = new FileStream("TrapezSave.xml", FileMode.Open);

                trapez = (Trapez)xmlSerializer.Deserialize(fs);
                fs.Close();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            LoadSerializableTrapez();

            graphics.Clear(Color.White);

            textBox1.Text = trapez.TopBase.ToString();
            textBox2.Text = trapez.BottomBase.ToString();
            textBox3.Text = trapez.Height.ToString();

            trapez.Draw(graphics, pen, xShift, yShift);
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {

        }
    }

    [Serializable]
    public class Trapez
    {
        public float TopBase { get; set; }
        public float BottomBase { get; set; }
        public float Height { get; set; }

        public Trapez()
        {
            TopBase = 0;
            BottomBase = 0;
            Height = 0;
        }

        public Trapez(float topBase = 0, float bottomBase = 0, float height = 0)
        {
            TopBase = topBase;
            BottomBase = bottomBase;
            Height = height;
        }

        public void Draw(Graphics graphics, Pen pen, float xShift = 0, float yShift = 0)
        {
            float topBaseFrom = (BottomBase - TopBase) / 2;
            float topBaseTo = TopBase + topBaseFrom;

            graphics.DrawLine(pen, topBaseFrom + xShift, yShift, topBaseTo + xShift, yShift);
            graphics.DrawLine(pen, topBaseTo + xShift, yShift, BottomBase + xShift, Height + yShift);
            graphics.DrawLine(pen, BottomBase + xShift, Height + yShift, xShift, Height + yShift);
            graphics.DrawLine(pen, xShift, Height + yShift, topBaseFrom + xShift, yShift);
        }
    }
}
