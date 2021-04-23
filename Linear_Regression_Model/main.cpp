// Finally, finish today

#include <iostream>
#include <fstream>
#include "Vector.h"
#include "Matrix.h"
#include "Linear_System.h"
using namespace std;

int main()
{
    cout << "Huy" << endl;
    ifstream fin;
    fin.open("machine.data", ifstream::in);

    // Just read 157 instances
    Matrix A(157, 6);
    Vector b(157);
    char cNum[10];

    if(!fin.is_open())
    {
        cout << "Error to open file";
        exit(-1);
    }

    for(int i = 1; i <= 157; i++)
    {
        fin.ignore(100, ',').ignore(100, ',');
        for(int j = 1; j <= 6; j++)
        {
            fin.getline(cNum, 20, ',');
            A(i, j) = atoi(cNum);
        }
        fin.getline(cNum, 20, ',');
        b(i) = atoi(cNum);
        fin.ignore(20, '\n');
    }

    Vector x = A.pseudo_inverse_with_Tikhonov() * b;
    x.display();
    cout << endl;


    // Testing the model
    Matrix A_test(52,6);
    Vector b_test(52);
    for(int i = 1; i <= 52; i++)
    {
        fin.ignore(100, ',').ignore(100, ',');
        for(int j = 1; j <= 6; j++)
        {
            fin.getline(cNum, 20, ',');
            A_test(i, j) = atoi(cNum);
        }
        fin.getline(cNum, 20, ',');
        b_test(i) = atoi(cNum);
        fin.ignore(20, '\n');
    }

    Vector c = A_test * x;
    c.display();

    // Calculate RMSE
    double sum = 0;
    for(int i = 1; i <= 52; i++)
    {
        cout << b_test(i) << " " << c(i) << endl;
        sum += (c(i) - b_test(i)) * (c(i) - b_test(i));
    }
    cout << sum;
    double RMSE = sqrt(sum / 52);
    cout << endl << RMSE;
    fin.close();
    return 0;
}
