using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Contexts;
using System.Text;
using System.Threading.Tasks;

namespace Lab_12
{
    class Point
    {
        public int x { get; set; }
        public int y { get; set; }

        public Point(int x = 0, int y = 0)
        {
            this.x = x;
            this.y = y;
        }

        static public Point operator+(Point p1, Point p2)
        {
            return new Point((p1.x + p2.x) / 2, (p1.y + p2.y)/2);
        }
        static public Point operator+(Point p, int num)
        {
            return new Point(p.x + num, p.y + num);
        }

        public override bool Equals(object obj)
        {
            return base.Equals(obj);
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        public override string ToString()
        {
            return "(" + x + "; " + y + ")";
        }
    }

        internal class Program
    {
        static void Main(string[] args)
        {
            Point p1 = new Point(1, 2);
            Point p2 = new Point(2, 1);

            Console.WriteLine($"new Point(): {new Point()}\nnew Point(1,2): {new Point(1,2)}" +
                $"\nnew Point(1,2) + new Point(2,1) = {p1 + p2}" +
                $"\nPoint(1,2).Equals(Point(1,2)): {p1.Equals(p1)}" +
                $"\nPoint(1,2).Equals(Point(2,1)): {p1.Equals(p2)}");

            Console.ReadKey();
        }
    }
}
