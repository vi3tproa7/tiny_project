// Linear System class to solve a linear system

#include <iostream>
#include <cassert>
#include <cmath>
#include "Vector.h"
#include "Matrix.h"
using namespace std;

class Linear_System
{
private:
    // copy constructor is private to prevent its use
    Linear_System(const Linear_System& other);
protected:
    int m_size;
    Matrix* mpA;
    Vector* mpb;
public:
    // Constructor
    Linear_System(const Matrix& A, const Vector& b);

    // Destructor
    virtual ~Linear_System();

    // Virtual method "solve" that return a Vector
    virtual Vector solve();
};

Linear_System::Linear_System(const Linear_System& other){}

Linear_System::Linear_System(const Matrix& A, const Vector& b)
{
    // check if the Matrix and Vector have compatible size
    assert(A.get_number_of_rows() == A.get_number_of_cols());
    assert(A.get_number_of_rows() == b.get_size());
    // these method need "const" qualifer in the end of method's
    // interface so that the compiler is guaranteed that these
    // methods do not change the current object

    // setup the linear system
    m_size = A.get_number_of_rows();
    mpA = new Matrix(A);    // call copy constructor to create new matrix
    mpb = new Vector(b);    // and vector that are similar to the old ones
    // just like mpA = new Student
    // 1 type of initialization
}

Linear_System::~Linear_System()
{
    delete mpA;
    delete mpb;
}

Vector Linear_System::solve()
{
    Vector m(m_size);
    Vector solution(m_size);

    // Use references here to make the syntax readable
    Matrix& rA = *mpA;      // diff from Matrix rA = *mpA
    Vector& rb = *mpb;      // too miracle, need to remember
    // That why we need the return type is reference with return *this;

    // forward phase of Gaussian elimination
    for (int k = 0; k < m_size - 1; k++)
    {
        // see if pivoting is necessary
        double max = 0.0;
        int row = -1;

        for (int i = k; i < m_size; i++)
        {
            if (fabs(rA(i + 1, k + 1)) > max)
            {
                row = i;
                max = fabs(rA(i + 1, k + 1));
            }
        }

        // Make sure that
        assert(row >= 0);

        // pivot if necessary
        // The better thing is, only need to swap 1 time if necessary
        // My old code swap row a lot of time
        if (row != k)
        {
            // swap matrix rows k + 1 with row + 1
            for (int i = 0; i < m_size; i++)
            {
                double temp = rA(k + 1, i + 1);
                rA(k + 1, i + 1) = rA(row + 1, i + 1 );
                rA(row + 1, i + 1) = temp;
            }

            // swap vector entries k+1 with row+1
            double temp = rb(k + 1);
            rb(k + 1) = rb(row + 1);
            rb(row + 1) = temp;
        }

        // create zeros in lower part of column k
        for (int i = k + 1; i < m_size; i++)
        {
            m(i + 1) = rA(i + 1, k + 1)/rA(k + 1, k + 1);
            for (int j = k; j < m_size; j++)
            {
                rA(i + 1,j + 1) -= rA(k + 1, j + 1) * m(i + 1);
            }

            rb(i + 1) -= rb(k + 1) * m(i + 1);
        }
    }

    // back substitution
    for (int i = m_size - 1; i > -1; i--)
    {
        solution(i + 1) = rb(i + 1);
        for (int j = i + 1; j < m_size; j++)
        {
            solution(i + 1) -= rA(i + 1,j + 1)*solution(j + 1);
        }
        solution(i + 1) /= rA(i + 1, i + 1);
    }

    return solution;
}

int main(void)
{
    return 0;
}
