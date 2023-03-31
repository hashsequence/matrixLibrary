#include "matrixFractions.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

bool compare_float(double x, double y, double epsilon = 0.0000001f){
   if(fabs(x - y) < epsilon)
      return true; //they are same
      return false; //they are not same
}

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
    vector<int> vecR(R->GetArr());
    vector<int> ans{2,7,5,14,1,11,6,9,3};
    assert(vecR == ans);

    delete R;
    cout << "-----TEST1 PASSED----\n";
}

void test2() {
    cout << "-----TEST2----\n"; 
    vector<double> vec1{2,-1,-2,-4,6,3,-4,-2,8};
    Matrix<double> A(3,vec1);
    A.Print();
    vector<Matrix<double>*> LU = A.LUDecomposition();
    vector<double> ansL = {1,0,0,-2,1,0,-2,-1,1};
    vector<double> ansU = {2,-1,-2, 0,4,-1,0,0,3};
    vector<double> L(LU[0]->GetArr());
    vector<double> U(LU[1]->GetArr());

    assert(L == ansL);
    assert(U == ansU);
    for (int i = 0; i < LU.size(); i++) {
        LU[i]->Print();
        delete LU[i];
    }
    cout << "-----TEST2 PASSED----\n";
}

void test3() {
    cout << "-----TEST3----\n"; 
    vector<double> vec1{2,-1,-2,0,4,-1,0,0,3};
    Matrix<double> A(3,vec1);
    A.Print();
    Matrix<double>* U_inverted = Matrix<double>::InvertUpperTriangularMatrix(A);
    U_inverted->Print();
    vector<double> ansUInverted = {0.5,0.125,0.375,0,0.25,0.0833333,0,0,0.333333};
    vector<double> UVec(U_inverted->GetArr());
    for (int i =0; i < UVec.size(); i++ ) {
        assert(compare_float(ansUInverted[i],UVec[i], .001));
    }

    delete U_inverted;
    cout << "-----TEST3 PASSED----\n";
}

void test4() {
    cout << "-----TEST4----\n"; 
    vector<double> vec1{1,0,0,-2,1,0,-2,-1,1};
    Matrix<double> A(3,vec1);
    A.Print();
    Matrix<double>* L_inverted = Matrix<double>::InvertLowerTriangularMatrix(A);
    L_inverted->Print();
    vector<double> LVec(L_inverted->GetArr());
    vector<double> ansLInverted = {1,0,0,2,1,0,4,1,1};
    assert(LVec == ansLInverted);
    delete L_inverted;
    cout << "-----TEST4 PASSED----\n";
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
    Matrix<double>* A_inverted = A.LUInversion();
    A_inverted -> Print();
    vector<double> IVec(A_inverted->GetArr());
    vector<double> ansInverted = {-0.237569,0.243094,-0.0607735,0.519337,-0.469613,
                                    0.232044,-0.29558,0.198895,-0.472376,0.400552,
                                    0.441989,-0.301105,-0.0497238,-0.256906,0.0248619,
                                    0.0441989,-0.0801105,-0.104972,0.124309,0.0524862,
                                    -0.89779,0.970994,-0.0552486,0.631215,-0.222376};
     for (int i =0; i < IVec.size(); i++ ) {
        assert(compare_float(ansInverted[i],IVec[i], .001));
    }
    double detA = A.Determinant();
    cout <<"detA: " << detA << endl;
    assert(detA == 724);    
    delete A_inverted;
    cout << "-----TEST5 PASSED----\n";
}

void test6() {
    cout << "-----TEST6----\n"; 
    Fraction f1(3,7);
    Fraction f2(2,5);
    Fraction f3(7,9);
    Fraction result1 = f1 + f2;
    result1 += f3;

    cout << f1 << " + " << f2 << " + " << f3 << " = " << result1 << endl;
    assert(result1.GetNumerator() == 506 && result1.GetDenominator() == 315);
    Fraction result2 = f1 - f2;
    cout << f1 << " - " << f2 << " = " << result2 << endl;
    assert(result2.GetNumerator() == 1 && result2.GetDenominator() == 35);
    Fraction result3 = f1 * f2;
    cout << f1 << " * " << f2 << " = " << result3 << endl;
    assert(result3.GetNumerator() == 6 && result3.GetDenominator() == 35);
    Fraction result4 = f1 / f2;
    cout << f1 << " / " << f2 << " = " << result4 << endl;
    assert(result4.GetNumerator() == 15 && result4.GetDenominator() == 14);

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

     assert(result7.GetNumerator() == 1);
     assert(result8.GetNumerator() == -1);
     assert(result9.GetNumerator() == 1);
     assert(result11.GetNumerator() == -1);
     assert(result12.GetNumerator() == 0);
     assert(result13.GetNumerator() == 0);
     cout << "-----TEST6 PASSED----\n";
}

void test7() {

    cout << "-----TEST7----\n"; 

    vector<Fraction<int>> vec1{
       Fraction<int>(5),Fraction<int>(7),Fraction<int>(9),Fraction<int>(4),Fraction<int>(4),
       Fraction<int>(2),Fraction<int>(4),Fraction<int>(7),Fraction<int>(1),Fraction<int>(4),
       Fraction<int>(7),Fraction<int>(9),Fraction<int>(3),Fraction<int>(1),Fraction<int>(2),
       Fraction<int>(5),Fraction<int>(6),Fraction<int>(3),Fraction<int>(6),Fraction<int>(2),
       Fraction<int>(1),Fraction<int>(4),Fraction<int>(2),Fraction<int>(5),Fraction<int>(2),
       };
    Matrix<Fraction<int>> A(5,vec1);
    A.Print();
    Matrix<Fraction<int>>* A_inverted = A.LUInversion();
    A_inverted -> Print();
    vector<Fraction<int>> AIVec(A_inverted->GetArr());
    vector<Fraction<int>> ansInverted = {
        Fraction<int>(-43,181),Fraction<int>(44,181),Fraction<int>(-11,181),Fraction<int>(94,181),Fraction<int>(-85,181),
        Fraction<int>(42,181),Fraction<int>(-107,362),Fraction<int>(36,181),Fraction<int>(-171,362),Fraction<int>(145,362),
        Fraction<int>(80,181),Fraction<int>(-109,362),Fraction<int>(-9,181),Fraction<int>(-93,362),Fraction<int>(9,362),
        Fraction<int>(8,181),Fraction<int>(-29,362),Fraction<int>(-19,181),Fraction<int>(45,362),Fraction<int>(19,362),
        Fraction<int>(-325,362),Fraction<int>(703,724),Fraction<int>(-10,181),Fraction<int>(457,724),Fraction<int>(-161,724)
    };
    delete A_inverted;
    assert(AIVec == ansInverted);
    cout << "-----TEST7 PASSED----\n";
}

void test8() {
    cout << "-----TEST8----\n"; 
    vector<int> vec1{
       5,	7,	9,	4,   4,
       2,	4,	7,	1,	4,
       7,	9,	3,	1,	2,
       5,	6,	3,	6,	2,
       1,	4,	2,	5,	2
       };
    Matrix<int> A(5,vec1);
    A.Print();
    Matrix<int> * A_T = Matrix<int>::Transpose(A);
    A_T->Print();
    vector<int> A_T_Ans = {
        5,2,7,5,1,
            7,4,9,6,4,
            9,7,3,3,2,
            4,1,1,6,5,
            4,4,2,2,2};

    for (int i =0; i < vec1.size(); i++ ) {
        assert(A_T_Ans[i] == A_T->GetArr()[i]);
    }
    delete A_T;
    cout << "-----TEST8 PASSED----\n";
}



void test9() {
    cout << "-----TEST9---\n"; 
    vector<Fraction<int>> vec1{
        Fraction<int>(5),Fraction<int>(7),Fraction<int>(9),
        Fraction<int>(2),Fraction<int>(4),Fraction<int>(7),
        Fraction<int>(7),Fraction<int>(9),Fraction<int>(3)
       };
    vector<Fraction<int>> vec2{
       Fraction<int>(7),Fraction<int>(9),Fraction<int>(3),
       Fraction<int>(5),Fraction<int>(7),Fraction<int>(9),
       Fraction<int>(2),Fraction<int>(4),Fraction<int>(7),
       };
    vector<Fraction<int>> pVec{
       Fraction<int>(0),Fraction<int>(0),Fraction<int>(1),
       Fraction<int>(1),Fraction<int>(0),Fraction<int>(0),
       Fraction<int>(0),Fraction<int>(1),Fraction<int>(0)
       };
    Matrix<Fraction<int>>* M = new Matrix<Fraction<int>>(3,vec1);
    Matrix<Fraction<int>> M_ans(3,vec2);
    Matrix<Fraction<int>> P_ans(3,pVec);
    cout << "M\n";
    M->Print();
    vector<Matrix<Fraction<int>>*> PAs = Matrix<Fraction<int>>::PartialPivot(*M);
    cout << "P: permutation Matrix<Fraction<int>>\n";
    PAs[0]->Print();
    cout << "As: row swapped\n";
    PAs[1]-> Print();
    Matrix<Fraction<int>>* P_T = Matrix<Fraction<int>>::Transpose(*(PAs[0]));
    cout << "P_T: P transposed\n";
    P_T->Print();
    Matrix<Fraction<int>>* P_TAs = P_T->Multiply(*(PAs[1]));
    cout << "P^T * As\n";
    P_TAs->Print();
    vector<Fraction<int>> P_TAsArr = P_TAs->GetArr();
    for (int i = 0; i < P_TAsArr.size();i++) {
        assert(P_TAsArr[i] == vec1[i]);
    }
    for (int i = 0; i < PAs.size();i++) {
        assert(PAs[0]->GetArr()[i] == pVec[i]);
    }
    for (int i = 0; i < PAs.size();i++) {
        assert(PAs[1]->GetArr()[i] == vec2[i]);
    }

    delete M;
    for (int i = 0; i < PAs.size();i++) {
        delete PAs[i];
    }
    delete P_T;
    delete P_TAs;
    cout << "-----TEST9 PASSED----\n";
}




int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
}