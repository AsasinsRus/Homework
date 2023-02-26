using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Lab_10._2
{
    internal class Program
    {
        static void randArr(int[] arr, int minRange = -20, int maxRange = 20)
        {
            Random rand = new Random();

            for(int i=0;i<arr.Length;i++)
            {
                arr[i] = rand.Next(minRange, maxRange);
            }
        }

        static int findNegativeElemQuantity(int[] arr)
        {
            int counter = 0;

            for(int i=0;i<arr.Length;i++)
            {
                if (arr[i] < 0)
                    counter++;
            }

            return counter;
        }

        static int sumPosElem(int[] arr)
        {
            int sum = 0;

            for(int i=0;i<arr.Length;i++)
            {
                if (arr[i] >= 0)
                    sum += arr[i];
            }

            return sum;
        }

        static void Main(string[] args)
        {
            const int SIZE = 20;
            int[] arr = new int[SIZE];

            randArr(arr);

            for (int i = 0; i < arr.Length;i++)
            {
                Console.Write(arr[i] + ", ");
            }

            Console.WriteLine("\nQuantity of negative elements = " + findNegativeElemQuantity(arr)
                + "\nSum of positive elements = " + sumPosElem(arr));

            Console.ReadKey();
        }
    }
}
