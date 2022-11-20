#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

class Number
{
    protected:
        int number;

    public:

        Number(int number)
        {
            this->number = number;
        }

        virtual void set(string number)
        {
            this->number = stoi(number);
        }

        virtual void set(int number)
        {
            this->number = number;
        }

        virtual string get()
        {
            return to_string(number);
        }

        virtual int getInteger()
        {
            return number;
        }
};

class BinaryNumber : public Number
{
public:
    BinaryNumber(string number) : Number(fromBinary(number)){}

    BinaryNumber(int number) : Number(number){}

    string get() override
    {
        return toBinary();
    }

    void set(string number)
    {
        this->number = fromBinary(number);
    }

    void set(int number)
    {
        this->number = number;
    }

    int fromBinary(string binary)
    {
        int res = 0;

        string buffer = binary;
        int lenght = binary.size();

        for(int i = 0; i<lenght;i++)
        {
            binary[lenght-i-1] = buffer[i];;
        }

        for(int i=0; i<binary.size(); i++)
        {
            res += (binary[i]-48)*pow(2,i);
        }

        return res;
    }

    string toBinary()
    {
        string res = "";
        int divided = number;

        if(number < 0)
            return "-1";

        if(divided == 0)
            return "0";
        else
        {
            while(divided != 1)
            {
                res += to_string(divided%2);
                divided /= 2;
            }

            res += to_string(1);
            string buffer = res;

            int lenght = res.size();

            for(int i = 0; i<lenght;i++)
            {
                res[lenght-i-1] = buffer[i];;
            }
        }

        return res;
    }
};

class UnsignedNumber : public Number
{
public:
    UnsignedNumber(unsigned int number) : Number(number){}

};

class HexadecimalNumber : public Number
{
public:
    HexadecimalNumber(string number) : Number(fromHexadecimal(number)){}
    HexadecimalNumber(int number) : Number(number){}

    virtual void set(string number)
    {
        this->number = fromHexadecimal(number);
    }

    virtual void set(int number)
    {
        this->number = number;
    }

    virtual string get() override
    {
        return toHexadecimal();
    }

    int fromHexadecimal(string hexadecimal)
    {
        int res = 0;

        string buffer = hexadecimal;
        int lenght = hexadecimal.size();

        for(int i = 0; i<lenght;i++)
        {
            hexadecimal[lenght-i-1] = buffer[i];;
        }

        for(int i=0; i<hexadecimal.size(); i++)
        {
            switch(hexadecimal[i])
            {
                case 'A': res += 10*pow(16,i); break;
                case 'B': res += 11*pow(16,i); break;
                case 'C': res += 12*pow(16,i); break;
                case 'D': res += 13*pow(16,i); break;
                case 'E': res += 14*pow(16,i); break;
                case 'F': res += 15*pow(16,i); break;
                default: res += (hexadecimal[i]-48)*pow(16,i); break;
            }
        }

        return res;
    }

    string toHexadecimal()
    {
        string res = "";
        int divided = number;

        if(number < 0)
            return "-1";

        if(divided == 0)
            return "0";
        else
        {
            int buffer;

            while(divided != 0)
            {
                buffer = divided%16;

                if(buffer > 9)
                {
                    switch(buffer)
                    {
                        case 10: res += "A"; break;
                        case 11: res += "B"; break;
                        case 12: res += "C"; break;
                        case 13: res += "D"; break;
                        case 14: res += "E"; break;
                        case 15: res += "F"; break;
                    }
                }
                else res += to_string(divided%16);

                divided /= 16;
            }

            string bufferRes = res;

            int lenght = res.size();

            for(int i = 0; i<lenght;i++)
            {
                res[lenght-i-1] = bufferRes[i];;
            }
        }

        return res;
    }
};


int main()
{
    Number num(2);
    BinaryNumber binary("11000");
    UnsignedNumber unsignedNum(-10);
    HexadecimalNumber hexadecimal("AF10");

    cout << "Number originally: " << num.get() << endl << "Number integer: " << num.getInteger() << endl << endl;
    cout << "Number originally: " << binary.get() << endl << "Number integer: " << binary.getInteger() << endl << endl;
    cout << "Number originally: " << unsignedNum.get() << endl << "Number integer: " << unsignedNum.getInteger() << endl << endl;
    cout << "Number originally: " << hexadecimal.get() << endl << "Number integer: " << hexadecimal.getInteger() << endl << endl;

    Number nums[4] = {num, binary, unsignedNum, hexadecimal};

    cout << "Array of different types of numbers: ";

    for(int i=0;i<3;i++)
    {
        cout << nums[i].get() << ", ";
    }
    cout << nums[3].get() << endl;

    return 0;
}
