using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_10._1
{
    internal class Program
    {
        static void randArr(int[] arr, int minRange = -20, int maxRange = 20)
        {
            Random rand = new Random();

            for(int i=0;i<arr.Length;i++)
            {
                arr[i] = rand.Next(-minRange, maxRange);
            }
        }

        static int findNegativByIndex(int[] arr, int index)
        {
            int counter = 0;

            for(int i = 0; i < arr.Length; i++)
            {
                if (arr[i] < 0)
                    counter++;

                if(counter == index)
                    return i;
            }

            return 0;
        }

        static void Main(string[] args)
        {
            const int SIZE = 10;
            int[] arr = new int[SIZE];

            randArr(arr);

            for(int i = 0; i < arr.Length; i++)
            {
                Console.Write(arr[i] + ", ");
            }

            Console.WriteLine("\nNumber of 5 element > " + findNegativByIndex(arr, 5));

            Console.ReadKey();
        }
    }
}
