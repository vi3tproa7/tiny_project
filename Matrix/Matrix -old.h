// Matrix.h
#ifndef Matrix_h
#define Matrix_h

#include <iostream>
#include "Vector.h"
using namespace std;

class Matrix
{
private:
    double** m_data;
    int m_num_rows;
    int m_num_cols;
public:
    // Constructor
    Matrix(int m_num_rows, int m_num_cols);

    // Copy constructor
    Matrix(Matrix& other);

    // Destructor
    ~Matrix();

    // Method to get the number of rows
    int get_number_of_rows();

    // Method to get the number of columns
    int get_number_of_cols();

    // Display method
    void display();

    // Auto setter, for testing the logic
    void set_data();

    // () overloaded to access entries in the matrix
    // A(i, j) <=> m_data[i - 1][j - 1]
    double operator()(int i, int j);

    // Copy assignment
    Matrix& operator=(const Matrix& rhs);

    // Unary + operator
    Matrix operator+();

    // Unary - operator
    Matrix operator-();

    // Binary + operator
    // Addition operation between 2 matrices
    friend Matrix operator+(const Matrix& a, const Matrix& b);

    // Binary - operator
    // Subtraction operation between 2 matrices
    friend Matrix operator-(const Matrix& a, const Matrix& b);

    // Matrix Multiplication between 2 matrices
    friend Matrix operator*(const Matrix& a, const Matrix& b);

    // Matrix Multiplication between Matrix and Scalar
    friend Matrix operator*(const Matrix& a, const double b);
    friend Matrix operator*(const double b, const Matrix& a);

    // Matrix Multiplication between Matrix and Vector
    friend Vector operator*(const Matrix& a, const Vector& b);
};

// This constructor allocates memory for the matrix
// and initializes all element to 0
Matrix::Matrix(int m_num_rows, int m_num_cols)
{
    this->m_num_rows = m_num_rows;
    this->m_num_cols = m_num_cols;

    // Create an array of pointer to double
    m_data = new double* [m_num_rows];

    // Using each pointer to create an array of double
    for(int i = 0; i < m_num_rows; i++)
        m_data[i] = new double [m_num_cols];

    for(int i = 0; i < m_num_rows; i++)
        for(int j = 0; j < m_num_cols; j++)
            m_data[i][j] = 0;
}

Matrix::Matrix(Matrix& other)
{
    m_num_rows = other.m_num_rows;
    m_num_cols = other.m_num_cols;

    m_data = new double* [m_num_rows];
    for(int i = 0; i < m_num_rows; i++)
        m_data[i] = new double [m_num_cols];

    for(int i = 0; i < m_num_rows; i++)
        for(int j = 0; j < m_num_cols; j++)
            m_data[i][j] = other.m_data[i][j];
}

Matrix::~Matrix()
{
    // Free memory of arrays of double
    for(int i = 0; i < m_num_rows; i++)
        delete[] m_data[i];

    // Free memory of the array of
    // pointers to double
    delete[] m_data;
}

int Matrix::get_number_of_rows()
{
    return m_num_rows;
}

int Matrix::get_number_of_cols()
{
    return m_num_cols;
}

void Matrix::display()
{
    for(int i = 0; i < m_num_rows; i++)
    {
        for(int j = 0; j < m_num_cols; j++)
            cout << m_data[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

void Matrix::set_data()
{
    for(int i = 0; i < m_num_rows; i++)
        for(int j = 0; j < m_num_cols; j++)
            m_data[i][j] = i * m_num_cols + j;
}

double Matrix::operator()(int i, int j)
{
    if(!(i >= 1 && i <= m_num_rows && j >=1 && j <= m_num_cols))
        cout << "Invalid indexing";
    else
        return m_data[i - 1][j - 1];
}

// need to check again this copy assignment p.74/the C++ PL - Bjarne Stroustrup
Matrix& Matrix::operator=(const Matrix& rhs)
{
    if(m_num_rows != rhs.m_num_rows || m_num_cols != rhs.m_num_cols)
        cout << "Wrong Size";
    else
    {
        for(int i = 0; i < m_num_rows; i++)
            for(int j = 0; j < m_num_cols; j++)
                m_data[i][j] = rhs.m_data[i][j];

        return *this;
    }
}

Matrix Matrix::operator+()
{
    Matrix c(m_num_rows, m_num_cols);

    for(int i = 0; i < m_num_rows; i++)
        for(int j = 0; j < m_num_cols; j++)
            c.m_data[i][j] = m_data[i][j];

    return c;
}

Matrix Matrix::operator-()
{
    Matrix c(m_num_rows, m_num_cols);

    for(int i = 0; i < m_num_rows; i++)
        for(int j = 0; j < m_num_cols; j++)
            c.m_data[i][j] = m_data[i][j];

    return c;
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
    if(a.m_num_rows != b.m_num_rows || a.m_num_cols != b.m_num_cols)
        cout << "2 Matrices do not have the same size";
    else
    {
        Matrix c(a.m_num_rows, a.m_num_cols);

        for(int i = 0; i < a.m_num_rows; i++)
            for(int j = 0; j < a.m_num_cols; j++)
                c.m_data[i][j] = a.m_data[i][j] + b.m_data[i][j];

        return c;
    }
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
    if(a.m_num_rows != b.m_num_rows || a.m_num_cols != b.m_num_cols)
        cout << "2 Matrices do not have the same size";
    else
    {
        Matrix c(a.m_num_rows, a.m_num_cols);

        for(int i = 0; i < a.m_num_rows; i++)
            for(int j = 0; j < a.m_num_cols; j++)
                c.m_data[i][j] = a.m_data[i][j] - b.m_data[i][j];

        return c;
    }
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
    assert(a.m_num_cols == b.m_num_rows);   // columns of a must match rows of b

    Matrix c(a.m_num_rows, b.m_num_cols);

    for(int i = 0; i < a.m_num_rows; i++)           // i go along the row of a
        for(int j = 0; j < b.m_num_cols; j++)       // j go along the col of b
            for(int r = 0; r < a.m_num_cols; r++)   // r go along the col of a and row of b
                c.m_data[i][j] += a.m_data[i][r] * b.m_data[r][j];

    return c;
}

// Matrix is the 1st operand
Matrix operator*(const Matrix& a, const double b)
{
    Matrix c(a.m_num_rows, a.m_num_cols);

    for(int i = 0; i < a.m_num_rows; i++)
        for(int j = 0; j < a.m_num_cols; j++)
            c.m_data[i][j] = a.m_data[i][j] * b;

    return c;
}

// Matrix is the 2nd operand
Matrix operator*(const double b, const Matrix& a)
{
    Matrix c(a.m_num_rows, a.m_num_cols);

    for(int i = 0; i < a.m_num_rows; i++)
        for(int j = 0; j < a.m_num_cols; j++)
            c.m_data[i][j] = a.m_data[i][j] * b;

    return c;
}

Vector operator*(const Matrix& a, const Vector& b)
{
    assert(a.m_num_cols == b.m_size);   // #cols of Matrix == # rows of Vector

    Vector c(a.m_num_rows);     // a little confusion here but it's right
                                // a(m*n) * x(n) = b(m)
    for(int i = 0; i < a.m_num_rows; i++)
        for(int j = 0; j < a.m_num_cols; j++)
            c[i] += a.m_data[i][j] * b[j]; // b <=> x[1, 2, .. n]

    return c;
}

#endif  // Matrix_h
