// Linear System class to solve a linear system

#include <iostream>
#include <cassert>
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
    ~Linear_System();

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
}

Linear_System::~Linear_System()
{
    delete mpA;
    delete mpb;
}

int main(void)
{
    return 0;
}
