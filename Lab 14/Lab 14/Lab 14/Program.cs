using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;

namespace Lab_14
{
    interface ICross
    {
        float a { get; set; }
        float b { get; set; }

        void SetArea(float value);
        float GetArea();
        void print_sqrt();
    }

    class Cross : ICross
    {
        public float a { get; set; }
        public float b { get; set; }

        public Cross(float a, float b)
        {
            this.a = a;
            this.b = b;
        }

        public void SetArea(float value)
        {
            a = b = (float)Math.Sqrt(value / 5);
        }
        public float GetArea()
        {
            return a * a * 3 + b * b * 2;
        }

        public void print_sqrt()
        {
            Console.WriteLine($"Cross area: {GetArea()}");
        }

        public override string ToString()
        {
            return $"Side a: {a}\tArea: {GetArea()}\nSide b: {b}\n";
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            const int SIZE = 10;

            Cross[] cross = new Cross[SIZE];
            int[] keys = new int[SIZE];

            Random rand = new Random();

            for(int i = 0; i < SIZE; i++)
            {
                int a = rand.Next(20);
                int b = rand.Next(20);

                cross[i] = new Cross(a, b);
                keys[i] = a;
            }

            foreach (Cross i in cross)
            {
                Console.WriteLine(i);
            }

            Console.WriteLine("-----------Sort-----------\n");
            Array.Sort(keys, cross);

            foreach(Cross i in cross)
            {
                Console.WriteLine(i);
            }

            Console.ReadKey();
        }
    }
}
