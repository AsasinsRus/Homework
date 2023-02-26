using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_9._2
{
    class CircleService
    { 
        public static double Parameter(double radius)
        {
            return 2 * Math.PI * radius;
        }

        public static double Area(double radius)
        {
            return Math.PI * Math.Pow(radius, 2);
        }
        
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            double radius;

            while(true)
            {
                Console.Write("Enter radius of circle > ");
                radius = Convert.ToDouble(Console.ReadLine());

                if (radius == 0)
                    break;

                Console.WriteLine("\nParameter = " + CircleService.Parameter(radius) 
                    + "\nArea = " + CircleService.Area(radius));

                Console.ReadKey();
                Console.Clear();
            }
        }
    }
}
