// to write Vector class here
#include <iostream>
using namespace std;

class Vector
{
private:
    double* mData;  // pointer point to the 1st element of vector
    int mSize;      // the size of vector
public:
    // parameter constructor, no arg
    Vector(int mSize)
    {
        this->mSize = mSize;
        mData = new double[mSize];
        // initialize right away
        for(int i = 0; i < mSize; i++)
            mData[i] = 0;
        // Should I add cin here ?
    }

    ~Vector()
    {
        delete[] mData;
    }

    // need a copy constructor
    Vector(const Vector & b);

    void setData()
    {
        for(int i = 0; i < mSize; i++)
            cin >> mData[i];
    }
    void print()
    {
        for(int i = 0; i < mSize; i++)
            cout << mData[i] << " ";
        cout << endl;
    }

    // Addition
    Vector operator+(const Vector& b)
    {
        if(this->mSize != b.mSize)
            cout << "Wrong Size";
        else
        {
        Vector v(this->mSize);

        for(int i = 0; i < b.mSize; i++)
            v.mData[i] = this->mData[i] - b.mData[i];
        return v;
        }
    }

    // Substraction
    Vector operator-(const Vector& b)
    {
        if(this->mSize != b.mSize)
            cout << "Wrong Size";
        else
        {
        Vector v(this->mSize);

        for(int i = 0; i < b.mSize; i++)
            v.mData[i] = this->mData[i] - b.mData[i];
        return v;
        }
    }

    // Scalar Multiplication
    Vector operator*(double b)
    {
        Vector v(mSize);

        for(int i = 0; i < mSize; i++)
            v.mData[i] = mData[i] * b;
        return v;
    }

    // Unary -
    Vector operator-()
    {
        Vector v(mSize);

        for(int i = 0; i < mSize; i++)
            v.mData[i] = - mData[i];
        return v;
    }

    // Dot product
//    double operator*(const Vector a, const Vector b)
//    {
//        double dotProduct = 0;
//
//        for(int i = 0; i < a.mSize; i++)
//            dotProduct += a.mData[i] * b.mData[i];
//        return dotProduct;
//    }
};

//Vector::Vector(const Vector &another)
//{
//    mSize = other.mSize;
//    for(int )
//}

int main(void)
{

    Vector v1(5);
    Vector v2(5);


    v1.setData();
    v1.print();
    v2.setData();
    v2.print();

    Vector v3(5);
    v3 = -v2;
    v3.print();

    Vector v4(5);
    v4 = v1 * 2;
    v4.print();

    return 0;
}

// default constructor, no arg
//    Vector()
//    {
//        mSize = 0;
//        mData = new double[mSize];
//    }
    // maybe no need now
