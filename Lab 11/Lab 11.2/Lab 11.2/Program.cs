using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Lab_11._2
{
    internal class Program
    {
        static string EncodeDecrypt(string str, ushort key)
        {
            string resStr = String.Empty;

            foreach(char i in str)
            {
                resStr += (char)(i ^ key);
            }

            return resStr;
        }

        static void Main(string[] args)
        {
            string str = "hello world";
            ushort key = 0x0088;

            Console.OutputEncoding = Encoding.UTF8;
            Console.InputEncoding = Encoding.UTF8;

            while (true)
            {
                Console.Write("Enter your message to en/decode (0 to exit) > ");
                str = Console.ReadLine();

                if (str == "0")
                    break;

                Console.Write("Enter your key (any number upto 94) > ");
                key = Convert.ToUInt16(Console.ReadLine());

                Console.WriteLine("En/Decoded message: " + EncodeDecrypt(str, key));

                Console.ReadKey();
                Console.Clear();
            }

        }
    }
}
