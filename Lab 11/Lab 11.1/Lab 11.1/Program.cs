using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_11._1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string fullName;

            Console.Write("Enter your full name > ");
            fullName = Console.ReadLine();

            Console.WriteLine("\n" + fullName.Replace(" ", "")
                + "\nNumber of letters: " + fullName.Length 
                + "\nMady by student of SE 21008b group Pashkevych Yurii");

            Console.ReadKey();
        }
    }
}
