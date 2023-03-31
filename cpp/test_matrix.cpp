#include "matrix.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;


bool compare_float(double x, double y, double epsilon = 0.0000001f){
   if(fabs(x - y) < epsilon)
      return true; //they are same
      return false; //they are not same
}

void test1() {
    cout << "-----TEST1----\n";
    vector<double> vec1{1,2,3,7,2,9,3,3,4};
    vector<double> vec2{2,-1,-2,0,4,-1,0,0,3};
    Matrix A(3,vec1);
    Matrix B(3,vec2);
    A.Print();
    B.Print();
    Matrix* R = A.Multiply(B);
    R->Print();
    vector<double> vecR(R->GetArr());
    vector<double> ans{2,7,5,14,1,11,6,9,3};
    assert(vecR == ans);
    delete R;
    cout << "-----TEST1 PASSED----\n";
}

void test2() {
    cout << "-----TEST2----\n"; 
    vector<double> vec1{2,-1,-2,-4,6,3,-4,-2,8};
    Matrix A(3,vec1);
    A.Print();
    vector<Matrix*> LU = A.LUDecomposition();
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
    Matrix A(3,vec1);
    A.Print();
    Matrix* U_inverted = Matrix::InvertUpperTriangularMatrix(A);
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
    Matrix* A_inverted = A.LUInversion();
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
    vector<double> vec1{
       5,	7,	9,	4,   4,
       2,	4,	7,	1,	4,
       7,	9,	3,	1,	2,
       5,	6,	3,	6,	2,
       1,	4,	2,	5,	2
       };
    Matrix A(5,vec1);
    A.Print();
    Matrix* A_T = Matrix::Transpose(A);
    A_T->Print();
    vector<double> A_T_Ans = {
        5,2,7,5,1,
            7,4,9,6,4,
            9,7,3,3,2,
            4,1,1,6,5,
            4,4,2,2,2};

    for (int i =0; i < vec1.size(); i++ ) {
        assert(A_T_Ans[i] == A_T->GetArr()[i]);
    }
    delete A_T;
    cout << "-----TEST6 PASSED----\n";
}

void test7() {
    cout << "-----TEST7----\n"; 
    vector<double> vec1{
       5,7,9,
        2,4,7,
        7,9,3
       };
    vector<double> vec2{
       7,9,3,
       5,7,9,
       2,4,7,
       };
    vector<double> pVec{
       0,0,1,
       1,0,0,
       0,1,0
       };
    Matrix* M = new Matrix(3,vec1);
    Matrix M_ans(3,vec2);
    Matrix P_ans(3,pVec);
    cout << "M\n";
    M->Print();
    vector<Matrix*> PAs = Matrix::PartialPivot(*M);
    cout << "P: permutation matrix\n";
    PAs[0]->Print();
    cout << "As: row swapped\n";
    PAs[1]-> Print();
    Matrix* P_T = Matrix::Transpose(*(PAs[0]));
    cout << "P_T: P transposed\n";
    P_T->Print();
    Matrix* P_TAs = P_T->Multiply(*(PAs[1]));
    cout << "P^T * As\n";
    P_TAs->Print();
    vector<double> P_TAsArr = P_TAs->GetArr();
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
    cout << "-----TEST7 PASSED----\n";
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