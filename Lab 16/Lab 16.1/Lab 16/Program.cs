using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_16
{
    internal class Program
    {
        public delegate double Function(double x);

        public static double func1(double x) => Math.Cos(x) / x;
        public static double func2(double x) => Math.Sin(x) / Math.Sqrt(x * x);
        public static double func3(double x) => Math.Pow(x, 1.0/3);

        public static double Integral(double underBorder, double upperBorder, Function func)
        {
            int N, i;
            double x, dx, sum;

            sum = 0;
            N = 90;
            dx = (upperBorder - underBorder) / N;

            for (i = 0, x = underBorder; i < N; i++)
            {
                sum += (func(x) + func(x + dx)) / 2 * dx;
                x += dx;
            }

            return sum;
        }

        static void Main(string[] args)
        {
            Console.WriteLine($"First function result: {Integral(1 ,2 , func1)}");
            Console.WriteLine($"Second function result: {Integral(1 ,2 , func2)}");
            Console.WriteLine($"Third function result: {Integral(1 ,2 , func3)}");

            Console.ReadKey();
        }
    }
}
