/* Conjugate Gradient Method for solving Positive Definite Symmetric Linear System */
#ifndef Pos_Def_Sym_Linear_System_h
#define Pos_Def_Sym_Linear_System_h

#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "Linear_System.h"
const double NEARZERO = 1.0e-10;

class Pos_Def_Sym_Linear_System : public Linear_System
{
public:
    Vector solve();
};

Vector Pos_Def_Sym_Linear_System::solve()
{
    Vector solution(m_size);

    //Use references here to make the syntax readable
    Matrix& A = *mpA;
    Vector& b = *mpb;
    // Reference is so good, make an alternative name for easily using

    // Checking if the system is symmetric
    // Maybe not need because after using pseudo-inverse
    // every matrix will be symmemtric
    int flag = 0;
    for(int i = 1; i <= m_size; i++)
        for(int j = 1; j <= i; j++) // just enough
            if(A(i, j) != A(j, i))
                flag++;
    assert(flag == 0);


    // The benefit of overloading all operator is tangible now, very useful
    double TOLERANCE = 1.0e-10;
    int n = m_size;
    int k = 0;

    Vector R = b;
    Vector P = R;

    while (k < n)
    {
        Vector Rold = R;                                    // Store previous residual
        Vector AP = A * P;

        double alpha = (R * R) / max(P * AP, NEARZERO );
        solution = 1.0 * solution + alpha * P;              // Next estimate of solution
        R = 1.0 * R - alpha * P;                            // Residual

        if (R.vector_norm() < TOLERANCE)                    // Convergence test
            break;

        double beta = (R * R) / max( Rold * Rold, NEARZERO );
        P = 1.0 * R + beta * P;                             // Next gradient

        k++;
   }

   return solution;
}

#endif // Pos_Def_Sym_Linear_System_h
