using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_9._1
{
    internal class Program
    {
        static double MathFunction(double x, double y, double z)
        {
            return x + y / (z + 1 / Math.Log(y));
        }

        static void Main(string[] args)
        {
            double x = -1, y = 0, z =0;
            
            while(true)
            {
                Console.Write("Enter x > ");
                x = Convert.ToDouble(Console.ReadLine());

                if (x == 0)
                    break;

                Console.Write("Enter y > ");
                y = Convert.ToDouble(Console.ReadLine());

                Console.Write("Enter z > ");
                z = Convert.ToDouble(Console.ReadLine());

                Console.WriteLine("\nResult = " + MathFunction(x, y, z));
                Console.ReadKey();
                Console.Clear();
            }
        }
    }
}
