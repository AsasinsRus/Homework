#define _USE_MATH_DEFINES

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

class Smiley
{
int rFace, rEyes;

public:
    Smiley(int rFace = 0, int rEyes = 0)
    {
        this->rFace = rFace;
        this->rEyes = rEyes;
    }

    int getRadiusFace()
    {
        return rFace;
    }

    int getRadiusEyes()
    {
        return rEyes;
    }

    void setRadiusFace(int rFace)
    {
        this->rFace = rFace;
    }

    void setRadiusEyes(int rEyes)
    {
        this->rEyes = rEyes;
    }

    double square(double value)
    {
        return M_PI * pow(value, 2);
    }

    Smiley operator+(Smiley &smiley)
    {
        Smiley res(rFace + smiley.rFace, rEyes + smiley.rEyes);
        return res;
    }

    Smiley operator++()
    {
        rFace++;
        rEyes++;
        return *this;
    }

    Smiley operator++(int notused)
    {
        Smiley res = *this;

        rFace++;
        rEyes++;
        return res;
    }

    friend ostream& operator<< (ostream &os, Smiley &smiley);
};

ostream& operator <<(ostream &os, Smiley &smiley)
{
    os << "Face radius: " << smiley.getRadiusFace() << "\nEyes radius: " << smiley.getRadiusEyes() << "\nFace radius square: " << smiley.square(smiley.getRadiusFace()) << endl;
    return os;
}

int main()
{
    Smiley smiley1(2,1);
    Smiley smiley2(4,2);

    cout << "smiley1:\n" << smiley1 << "\nsmiley2:\n" << smiley2 << endl;

    Smiley sum = smiley1 + smiley2;
    smiley1++;

    cout << "smiley1 + smiley2:\n" << sum << endl
    << "smiley1++ :\n" << smiley1 << endl;

    return 0;
}
