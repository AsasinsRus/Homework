using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_15._2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string[] strs = textBox1.Text.Split(' ');

            textBox1.Clear();

            for(int i = strs.Length - 1; i >= 0; i--)
            {
                textBox1.Text += strs[i] + " ";
            }

            textBox2.Text = (textBox1.Text.Length - strs.Length).ToString();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if(saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string name = saveFileDialog1.FileName;

                File.WriteAllText(name, textBox1.Text);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string name = openFileDialog1.FileName;

                textBox1.Clear();
                textBox1.Text = File.ReadAllText(name);

                textBox2.Text = (textBox1.Text.Length - textBox1.Text.Split(' ').Length).ToString();
            }
        }
    }
}
