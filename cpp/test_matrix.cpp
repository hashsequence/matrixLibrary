#include "matrix.h"
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

void test1() {
    cout << "-----TEST1----\n";
    vector<double> vec1{1,2,3,7,2,9,3,3,4};
    vector<double> vec2{2,-1,-2,0,4,-1,0,0,3};
    Matrix A(3,vec1);
    Matrix B(3,vec2);
    Matrix* R = A.Multiply(B);
    R->Print();
    delete R;
}

void test2() {
    cout << "-----TEST2----\n"; 
    vector<double> vec1{2,-1,-2,-4,6,3,-4,-2,8};
    Matrix A(3,vec1);
    A.Print();
    vector<Matrix*> LU = A.LUDecomposition();
    for (int i = 0; i < LU.size(); i++) {
        LU[i]->Print();
        delete LU[i];
    }

}

void test3() {
    cout << "-----TEST3----\n"; 
    vector<double> vec1{2,-1,-2,0,4,-1,0,0,3};
    Matrix A(3,vec1);
    A.Print();
    Matrix* U_inverted = Matrix::InvertUpperTriangularMatrix(A);
    U_inverted->Print();
    delete U_inverted;
}

void test4() {
    cout << "-----TEST4----\n"; 
    vector<double> vec1{1,0,0,-2,1,0,-2,-1,1};
    Matrix A(3,vec1);
    A.Print();
    Matrix* L_inverted = Matrix::InvertLowerTriangularMatrix(A);
    L_inverted->Print();
    delete L_inverted;
}

void test5() {
    cout << "-----TEST5----\n"; 
    vector<double> vec1{
       5,	7,	9,	4,   4,
       2,	4,	7,	1,	4,
       7,	9,	3,	1,	2,
       5,	6,	3,	6,	2,
       1,	4,	2,	5,	2
       };
    Matrix A(5,vec1);
    A.Print();
    Matrix* A_inverted = A.Inversion();
    A_inverted -> Print();
    delete A_inverted;
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
}