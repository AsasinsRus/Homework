using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace Lab_13
{
    class Stone
    {
        public string Name { get; set; }
        public float Weight { get; set; }
        public float Price { get; set; }
        public string Color { get; set; }

        public Stone(string Name = null, float Weight = 0, float Price = 0, string Color = null)
        {
            this.Name = Name;
            this.Weight = Weight;
            this.Price = Price;
            this.Color = Color;
        }
        public static bool operator==(Stone stone1, Stone stone2)
        {
            if(stone1.Name != stone2.Name)
            {
                return false;
            }
            else if(stone1.Price != stone2.Price)
            {
                return false;
            }
            else if(stone1.Weight != stone2.Weight)
            {
                return false;
            }
            else if(stone1.Color != stone2.Color)
            {
                return false;
            }

            return true;
        }

        public static bool operator !=(Stone stone1, Stone stone2)
        {
            if (stone1.Name != stone2.Name)
            {
                return true;
            }
            else if (stone1.Price != stone2.Price)
            {
                return true;
            }
            else if (stone1.Weight != stone2.Weight)
            {
                return true;
            }
            else if (stone1.Color != stone2.Color)
            {
                return true;
            }

            return false;
        }

        public override int GetHashCode()
        {
            return Name.GetHashCode() + Price.GetHashCode() + Weight.GetHashCode() + Color.GetHashCode();
        }

        public override bool Equals(Object obj)
        {
            if(obj is Stone)
            {
                if((obj as Stone) == this)
                {
                    return true;
                }
            }

            return false;
        }

        public override string ToString()
        {
            return "Name: " + Name + "\nPrice: " + Price 
                + "\nWeight: " + Weight + "\nColor: " + Color + "\n";
        }
    }

    class ValuableStone : Stone
    {
        public float Hardness { get; set; }
        public float Transparency { get; set; }
        public float Size { get; set; }

        public ValuableStone(string Name = null, float Weight = 0, float Price = 0, string Color = null, float Hardness = 0, float Transparency = 0, float Size = 0)
            : base(Name, Weight, Price, Color)
        {
            this.Hardness = Hardness;
            this.Transparency = Transparency;
            this.Size = Size;
        }

        public static bool operator==(ValuableStone stone1, ValuableStone stone2)
        {
            if(stone1 as Stone == stone2 as Stone)
            {
                if (stone1.Hardness != stone2.Hardness)
                    return false;
                if (stone1.Transparency != stone2.Transparency)
                    return false;
                if (stone1.Size != stone2.Size)
                    return false;

                return true;
            }

            return false;
        }

        public static bool operator !=(ValuableStone stone1, ValuableStone stone2)
        {
            if (stone1 as Stone == stone2 as Stone)
            {
                if (stone1.Hardness != stone2.Hardness)
                    return true;
                if (stone1.Transparency != stone2.Transparency)
                    return true;
                if (stone1.Size != stone2.Size)
                    return true;

                return false;
            }

            return true;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode() + Hardness.GetHashCode() + Transparency.GetHashCode() + Size.GetHashCode();
        }

        public override bool Equals(Object obj)
        {
            if (obj is ValuableStone)
            {
                if ((obj as ValuableStone) == this)
                {
                    return true;
                }
            }

            return false;
        }

        public override string ToString()
        {
            return base.ToString() + "Hardness: " + Hardness 
                + "\nTransparency: " + Transparency + "\nSize: " + Size + "\n";
        }
    }

    class SemipreciousStone : Stone
    {
        public string Value { get; set; }

        public SemipreciousStone(string Name = null, float Weight = 0, float Price = 0, string Color = null, string Value = null)
            : base(Name, Weight, Price, Color)
        {
            this.Value = Value;
        }

        public static bool operator ==(SemipreciousStone stone1, SemipreciousStone stone2)
        {
            if (stone1 as Stone == stone2 as Stone)
            {
                if (stone1.Value != stone2.Value)
                    return false;

                return true;
            }

            return false;
        }

        public static bool operator !=(SemipreciousStone stone1, SemipreciousStone stone2)
        {
            if (stone1 as Stone == stone2 as Stone)
            {
                if (stone1.Value != stone2.Value)
                    return true;

                return false;
            }

            return true;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode() + Value.GetHashCode();
        }

        public override bool Equals(Object obj)
        {
            if (obj is SemipreciousStone)
            {
                if ((obj as SemipreciousStone) == this)
                {
                    return true;
                }
            }

            return false;
        }

        public override string ToString()
        {
            return base.ToString() + "Value: " + Value + "\n";
        }
    }

    class StoneService
    {
        public static float GetTotalWeight(Stone[] stones)
        {
            float totalWeight = 0;

            for(int i=0;i<stones.Length;i++)
            {
                totalWeight += stones[i].Weight;
            }

            return totalWeight;
        }

        public static float GetTotalPrice(Stone[] stones)
        {
            float totalPrice = 0;

            for(int i=0; i<stones.Length;i++)
            {
                totalPrice += stones[i].Price;
            }

            return totalPrice;
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            const int SIZE = 8;
            Stone[] necklace = new Stone[SIZE];

            necklace[0] = new ValuableStone("Diamond", 0.1f, 200, "Blue", 10, 0.7f, 10);
            necklace[1] = new SemipreciousStone("Amethyst", 0.1f, 50, "Red", "valuable");
            necklace[2] = new ValuableStone("Emerald", 0.1f, 150, "Green", 10, 0.7f, 10);
            necklace[3] = new SemipreciousStone("Topaz", 0.1f, 40, "Blue", "valuable");
            necklace[4] = new ValuableStone("Ruby", 0.1f, 160, "Red", 10, 0.7f, 10);
            necklace[5] = new SemipreciousStone("Limestone Calcite", 0.1f, 30, "Orange", "valuable");
            necklace[6] = new ValuableStone("Sapphire", 0.1f, 250, "Blue", 10, 0.7f, 10);
            necklace[7] = new SemipreciousStone("Japer", 0.1f, 60, "Green", "valuable");

            foreach(Stone i in necklace)
            {
                Console.WriteLine(i);
            }

            Console.WriteLine("Total price: " + StoneService.GetTotalPrice(necklace) + " dollars" 
                + "\nTotal weight: " + StoneService.GetTotalWeight(necklace) + " carats");

            Console.ReadKey();
        }
    }
}
