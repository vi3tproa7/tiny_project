// Vector.h
#ifndef Vector_h
#define Vector_h

#include <iostream>
#include <cassert>
using namespace std;

// need a prototype of class Matrix here for operation
// between 2 distinct classes
class Matrix;

class Vector
{
private:
    double* m_data;  // pointer point to the 1st element of vector
    int m_size;      // the size of vector
public:
    // Parametered constructor
    Vector(int m_size);

    // Destructor
    ~Vector();

    // Copy constructor
    Vector(const Vector &other);

    // Set the data of the vector by key board
    void set_data();

    // Display all element of the vector
    void display();

    // Assignment operation
    Vector& operator=(const Vector& rhs);

    // Unary + operator
    Vector operator+();

    // Unary - operator
    Vector operator-();

    // Addition operation between 2 vectors
    friend Vector operator+(const Vector& a, const Vector& b);

    // Subtraction operation between 2 vector
    friend Vector operator-(const Vector& a, const Vector& b);

    // Scalar multiplication operation 1
    // Vector is the 1st operand
    friend Vector operator*(const Vector& v, const double a);

    // Scalar multiplication operation 2
    // Vector is the 2nd operand
    friend Vector operator*(const double a, const Vector& v);

    // Dot product between 2 vector
    friend double operator*(const Vector& a, const Vector& b);

    // () overloaded to access the entry in the vector
    // the indexing starts from 1
    double operator()(int i);

    // [] overloaded to check whether the index lies
    // within the correct range, indexing starts at 1 ?check
    bool operator[](int i);

    // Matrix Multiplication between Matrix and Vector
    friend Vector operator*(const Matrix& a, const Vector& b);
};

Vector::Vector(int m_size)
{
    this->m_size = m_size;
    m_data = new double[m_size];

    // initialize right away
    for(int i = 0; i < m_size; i++)
        m_data[i] = 0;
}

Vector::~Vector()
{
    delete[] m_data;
}

Vector::Vector(const Vector &other)
{
    m_size = other.m_size;
    m_data = new double[m_size];

    for(int i = 0; i < m_size; i++)
    {
        m_data[i] = other.m_data[i];
    }

    // *this = other;  /* Google's style ? */ => error ?
}

void Vector::set_data()
{
    cout << "Input the data for by key board" << endl;
    for(int i = 0; i < m_size; i++)
    {
        cout << "m_data[" << i << "] = ";
        cin >> m_data[i];
    }
}

void Vector::display()
{
    for(int i = 0; i < m_size; i++)
        cout << m_data[i] << " ";
    cout << endl;
}

Vector& Vector::operator=(Vector const& rhs)
{
    assert(m_size == rhs.m_size);

    for(int i = 0; i < m_size; i++)
        m_data[i] = rhs.m_data[i];

    return *this;
}

Vector Vector::operator-()
{
    Vector c(m_size);

    for(int i = 0; i < m_size; i++)
            c.m_data[i] = -m_data[i];

    return c;
}

Vector Vector::operator+()
{
    Vector c(m_size);

    for(int i = 0; i < m_size; i++)
        c.m_data[i] = m_data[i];

    return c;
}


Vector operator+(const Vector& a, const Vector& b)
{
    assert(a.m_size == b.m_size);

    Vector c(a.m_size);

    for(int i = 0; i < a.m_size; i++)
        c.m_data[i] = a.m_data[i] + b.m_data[i];

    return c;
}

Vector operator-(const Vector& a, const Vector& b)
{
    if(a.m_size != b.m_size)
        cout << "Wrong Size";
    else
    {
        Vector c(a.m_size);

        for(int i = 0; i < a.m_size; i++)
            c.m_data[i] = a.m_data[i] - b.m_data[i];

        return c;
    }
}

Vector operator*(const Vector& v, const double a)
{
    Vector c(v.m_size);

    for(int i = 0; i < v.m_size; i++)
        c.m_data[i] = v.m_data[i] * a;

    return c;
}

Vector operator*(const double a, const Vector& v)
{
    Vector c(v.m_size);

    for(int i = 0; i < v.m_size; i++)
        c.m_data[i] = v.m_data[i] * a;

    return c;
}

double operator*(const Vector& a, const Vector& b)
{
    if(a.m_size != b.m_size)
        cout << "Wrong size";
    else
    {
        double c = 0;

        for(int i = 0; i < a.m_size; i++)
            c += a.m_data[i] * b.m_data[i];

        return c;
    }
}

double Vector::operator()(int i)
{
    if (i < 1 || i > m_size)
        cout << "Wrong index";
    else
        return m_data[i - 1];
}

bool Vector::operator[](int i)
{
    if (i >= 1 && i <= m_size)
        return true;
    else
        return false;
}

#endif // Vector_h


