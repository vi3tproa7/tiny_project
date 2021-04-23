/*
Derive a class callled PosDefSymLinSystem from the class LinearSystem
that may be used for the solution of positive definite symmetric linear systems.
Make the method Solve a virtual method of the class LinearSystem,
and override this method in the class PosSymLinSystem so that it uses the conjugate gradient method for solving linear systems.
Your class PosDefSymLinSystem should perform a check that the matrix used is symmetric:
Test your class using suitable examples.
*/

#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "Linear_System.h"

class Pos_Def_Sym_Linear_System : public Linear_System
{

};
