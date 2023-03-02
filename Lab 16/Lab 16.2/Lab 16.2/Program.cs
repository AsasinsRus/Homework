using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_16._2
{
    public delegate void KeyPressedEvent();

    internal class Program
    {

        static void PrintMyName()
        {
            Console.Clear();
            Console.WriteLine("Pashkevych Yurii");
        }

        static void keyPressed(KeyPressedEvent ev, ConsoleKey key)
        {
            if(Console.ReadKey().Key == key)
                ev();
        }

        static void Main(string[] args)
        {
            keyPressed(PrintMyName, ConsoleKey.E);

            Console.ReadKey();
        }
    }
}
