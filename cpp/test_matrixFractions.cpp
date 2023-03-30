#include "matrixFractions.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

void test1() {
    cout << "-----TEST1----\n";
    vector<int> vec1{1,2,3,7,2,9,3,3,4};
    vector<int> vec2{2,-1,-2,0,4,-1,0,0,3};
    Matrix<int> A(3,vec1);
    Matrix<int> B(3,vec2);
    A.Print();
    B.Print();
    Matrix<int>* R = A.Multiply(B);
    R->Print();
    delete R;
}

void test2() {
    cout << "-----TEST2----\n"; 
    vector<double> vec1{2,-1,-2,-4,6,3,-4,-2,8};
    Matrix<double> A(3,vec1);
    A.Print();
    vector<Matrix<double>*> LU = A.LUDecomposition();
    for (int i = 0; i < LU.size(); i++) {
        LU[i]->Print();
        delete LU[i];
    }

}

void test3() {
    cout << "-----TEST3----\n"; 
    vector<double> vec1{2,-1,-2,0,4,-1,0,0,3};
    Matrix<double> A(3,vec1);
    A.Print();
    Matrix<double>* U_inverted = Matrix<double>::InvertUpperTriangularMatrix(A);
    U_inverted->Print();
    delete U_inverted;
}

void test4() {
    cout << "-----TEST4----\n"; 
    vector<double> vec1{1,0,0,-2,1,0,-2,-1,1};
    Matrix<double> A(3,vec1);
    A.Print();
    Matrix<double>* L_inverted = Matrix<double>::InvertLowerTriangularMatrix(A);
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
    Matrix<double> A(5,vec1);
    A.Print();
    Matrix<double>* A_inverted = A.Inversion();
    A_inverted -> Print();
    delete A_inverted;
}

void test6() {
    cout << "-----TEST6----\n"; 
    Fraction f1(3,7);
    Fraction f2(2,5);
    Fraction f3(7,9);
    Fraction result = f1 + f2;
    result += f3;
    cout << f1 << " + " << f2 << " + " << f3 << " = " << result << endl;
    Fraction result2 = f1 - f2;
    cout << f1 << " - " << f2 << " = " << result2 << endl;
    Fraction result3 = f1 * f2;
    cout << f1 << " * " << f2 << " = " << result3 << endl;
    Fraction result4 = f1 / f2;
    cout << f1 << " / " << f2 << " = " << result4 << endl;
    vector<Fraction<int>> fracIntVec(5);
    for (int i = 0; i < fracIntVec.size(); i++) {
        Fraction f4(-i,11);
        cout << f4 << endl;
        fracIntVec[i] = f4;
        cout << fracIntVec[i] << endl;
    }

    //modulo tests
    Fraction<int> f9(13,1);
    Fraction<int> f10(-13,1);
    Fraction<int> f11(3,1);
    Fraction<int> f12(-3,1);

    Fraction<int> result7 = f9 % f11;
    Fraction<int> result8 = f10 % f11;
    Fraction<int> result9 = f9 % f12;
    Fraction<int> result11 = f10 % f12;
    Fraction<int> result12 = f9 % f9;
    Fraction<int> result13 = f10 % f10;

    cout << "(" << f9 << ") % (" << f11 << ") = " << result7 << endl;
    cout << "(" << f10 << ") % (" << f11 << ") = " << result8 << endl;
    cout << "(" << f9 << ") % (" << f12 << ") = " << result9 << endl;
    cout << "(" << f10<< ") % (" << f12 << ") = " << result11 << endl;
    cout << "(" << f9 << ") % (" << f9 << ") = " << result12 << endl;
     cout << "(" << f10 << ") % (" << f10 << ") = " << result13 << endl;
}

void test7() {

    cout << "-----TEST7----\n"; 

    vector<Fraction<int>> vec1{
       Fraction<int>(5),Fraction<int>(7),Fraction(9),Fraction<int>(4),Fraction<int>(4),
       Fraction<int>(2),Fraction<int>(4),Fraction(7),Fraction<int>(1),Fraction<int>(4),
       Fraction<int>(7),Fraction<int>(9),Fraction(3),Fraction<int>(1),Fraction<int>(2),
       Fraction<int>(5),Fraction<int>(6),Fraction(3),Fraction<int>(6),Fraction<int>(2),
       Fraction<int>(1),Fraction<int>(4),Fraction(2),Fraction<int>(5),Fraction<int>(2),
       };
    Matrix<Fraction<int>> A(5,vec1);
    A.Print();
    Matrix<Fraction<int>>* A_inverted = A.Inversion();
    A_inverted -> Print();
    delete A_inverted;
}


int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
}