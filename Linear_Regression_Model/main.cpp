#include <iostream>
#include <fstream>
#include "Vector.h"
#include "Matrix.h"
#include "Linear_System.h"
#include "Pos_Def_Sym_Linear_System.h"
using namespace std;

int main()
{
    cout << "Huy" << endl;
    ifstream fin;
    fin.open("machine.data", ifstream::in);

    // Just read 170 instances
    Matrix A(170, 7);
    Vector b(170);
    char cNum[10];

    if(!fin.is_open())
    {
        cout << "Error to open file";
        exit(-1);
    }

    // Read the training instances
    for(int i = 1; i <= 170; i++)
    {
        fin.ignore(100, ',').ignore(100, ',');
        for(int j = 1; j <= 7; j++)
        {
            if(j != 7)
            {
                fin.getline(cNum, 20, ',');
                A(i, j) = atof(cNum);
            }
            else
                A(i, j) = 1;
            // cout << A(i, j) << " ";
        }
        fin.getline(cNum, 20, ',');
        b(i) = atof(cNum);
        fin.ignore(20, '\n');
        // cout << endl;
    }
    // A.display();

    //  Read the testing instances
    Matrix A_test(39, 7);
    Vector b_test(39);
    for(int i = 1; i <= 39; i++)
    {
        fin.ignore(100, ',').ignore(100, ',');
        for(int j = 1; j <= 7; j++)
        {
            if(j != 7)
            {
                fin.getline(cNum, 20, ',');
                A_test(i, j) = atof(cNum);
            }
            else
                A_test(i, j) = 1;
        }
        fin.getline(cNum, 20, ',');
        b_test(i) = atof(cNum);
        fin.ignore(20, '\n');
        // because if I use fin.getline(cNum, 20, ',')
        // I will meet a trouble with the last element
        // due to it will read also '\n' and the 1st element
        // of next line and discard the next 1st element
    }
    fin.close();

    // Find best lambda that have the least RMSE
    for(double lambda = 120; lambda <= 130; lambda += 1)
    {
        Vector x = A.pseudo_inverse_with_Tikhonov(lambda) * b;
        x.display();
        Vector y_hat = A_test * x;
        y_hat.display();

        // Calculate RMSE and deviation
        double sum = 0;
        double sum_2 = 0;
        for(int i = 1; i <= 39; i++)
        {
            // cout << b_test(i) << " " << c(i) << endl;
            sum += (y_hat(i) - b_test(i)) * (y_hat(i) - b_test(i));
            sum_2 += fabs(y_hat(i) - b_test(i)) / b_test(i) * 100;
        }
        // cout << sum;
        double RMSE = sqrt(sum / 39);
        double average_deviation = sum_2 / 39;
        cout << RMSE << " " << average_deviation << " " << lambda << endl << endl;
    }

    return 0;
}

