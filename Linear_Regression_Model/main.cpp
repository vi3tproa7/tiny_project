// Finally, finish today

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

    // Just read 157 instances
    Matrix A(157, 7);
    Vector b(157);
    char cNum[10];

    if(!fin.is_open())
    {
        cout << "Error to open file";
        exit(-1);
    }

    // Read the training instances
    for(int i = 1; i <= 157; i++)
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
    A.display();

    // Read the testing instances
    Matrix A_test(52, 7);
    Vector b_test(52);
    for(int i = 1; i <= 52; i++)
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


    // Data normalization for A and A_test
    for(int j = 1; j <= 6; j++)
    {
        double A_max = 0, A_min = 10000000;
        for(int i = 1; i <= 157; i++)
        {
            if(A(i, j) > A_max)
                A_max = A(i, j);
            if(A(i, j) < A_min)
                A_min = A(i, j);
        }

        for(int i = 1; i <= 157; i++)
        {
            A(i, j) = (A(i, j) - A_min) / (A_max - A_min);
        }

        for(int i = 1; i <= 52; i++)
        {
            A_test(i, j) = (A_test(i, j) - A_min) / (A_max - A_min);
        }
    }

    // Data normalization for b
    double b_max = 0, b_min = 100000;
    for(int i = 1; i <= 157; i++)
    {
        if(b(i) > b_max)
            b_max = b(i);
        if(b(i) < b_min)
            b_min = b(i);
    }

    for(int i = 1; i <= 157; i++)
    {
        b(i) = (b(i) - b_min) / (b_max - b_min);
    }


    A.display();
    b.display();

    Pos_Def_Sym_Linear_System ls_1((A^'T') * A, (A^'T') * b);
    Vector x = ls_1.solve();
    Vector x_2 = A.pseudo_inverse() * b;


    Vector y_hat = A_test * x;
    Vector y_hat_2 = A_test * x_2;

    // Reverse the normalization
    for(int i = 1; i <= 52; i++)
    {
        y_hat(i) = y_hat(i) * (b_max - b_min) + b_min;
        y_hat_2(i) = y_hat_2(i) * (b_max - b_min) + b_min;
    }

    y_hat_2.display();
    y_hat.display();
    b_test.display();


    // Calculate RMSE
        double sum = 0;
        double sum_2 = 0;
        for(int i = 1; i <= 52; i++)
        {
            // cout << b_test(i) << " " << c(i) << endl;
            sum += (y_hat_2(i) - b_test(i)) * (y_hat_2(i) - b_test(i));
            sum_2 += fabs(y_hat_2(i) - b_test(i)) / b_test(i) * 100;
        }
        // cout << sum;
        double RMSE = sqrt(sum / 52);
        double average_deviation = sum_2 / 52;
        cout << RMSE << " " << average_deviation << endl;


//    // Find best lambda that have the least RMSE
//    for(double lambda = 0; lambda < 1; lambda += 0.11)
//    {
//        Vector x = A.pseudo_inverse_with_Tikhonov(lambda) * b;
//        x.display();
//
//        Vector c = A_test * x;
//        // c.display();
//
//    }

    return 0;
}

//     Read the training instances
//    for(int i = 1; i <= 157; i++)
//    {
//        fin.ignore(100, ',').ignore(100, ',');
//        for(int j = 1; j <= 7; j++)
//        {
//            if(j != 7)
//            {
//                fin.getline(cNum, 20, ',');
//                A(i, j) = atof(cNum);
//            }
//            else
//                A(i, j) = 1;
//             cout << A(i, j) << " ";
//        }
//        fin.getline(cNum, 20, ',');
//        b(i) = atof(cNum);
//        fin.ignore(20, '\n');
//         cout << endl;
//    }
//     A.display();
//
//     Read the testing instances
//    Matrix A_test(52, 7);
//    Vector b_test(52);
//    for(int i = 1; i <= 52; i++)
//    {
//        fin.ignore(100, ',').ignore(100, ',');
//        for(int j = 1; j <= 7; j++)
//        {
//            if(j != 7)
//            {
//                fin.getline(cNum, 20, ',');
//                A_test(i, j) = atof(cNum);
//            }
//            else
//                A_test(i, j) = 1;
//        }
//        fin.getline(cNum, 20, ',');
//        b_test(i) = atof(cNum);
//        fin.ignore(20, '\n');
//         because if I use fin.getline(cNum, 20, ',')
//         I will meet a trouble with the last element
//         due to it will read also '\n' and the 1st element
//         of next line and discard the next 1st element
//    }
//    fin.close();
//
//     Find best lambda that have the least RMSE
//    for(double lambda = 0; lambda < 1; lambda += 0.11)
//    {
//        Vector x = A.pseudo_inverse_with_Tikhonov(lambda) * b;
//        x.display();
//
//        Vector c = A_test * x;
//         c.display();
//
//         Calculate RMSE
//        double sum = 0;
//        double sum_2 = 0;
//        for(int i = 1; i <= 52; i++)
//        {
//             cout << b_test(i) << " " << c(i) << endl;
//            sum += (c(i) - b_test(i)) * (c(i) - b_test(i));
//            sum_2 += fabs(c(i) - b_test(i)) / b_test(i) * 100;
//        }
//         cout << sum;
//        double RMSE = sqrt(sum / 52);
//        double average_deviation = sum_2 / 52;
//        cout << RMSE << " " << average_deviation <<endl << endl;
//    }
