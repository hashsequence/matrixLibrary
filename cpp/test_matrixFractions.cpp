#include "matrixFractions.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

bool CompareFloat(double x, double y, double epsilon = 0.0000001f){
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
        assert(CompareFloat(ansUInverted[i],UVec[i], .001));
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
        assert(CompareFloat(ansInverted[i],IVec[i], .001));
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


void test10() {
    cout << "-----TEST10---\n";
     vector<Fraction<double>> vec1{
       Fraction<double>(5), Fraction<double>(7), Fraction<double>(9), Fraction<double>(4), Fraction<double>(4),  Fraction<double>(2), Fraction<double>(4), Fraction<double>(7), Fraction<double>(1), Fraction<double>(4),
         Fraction<double>(7), Fraction<double>(9), Fraction<double>(3), Fraction<double>(1), Fraction<double>(2), Fraction<double>(5), Fraction<double>(6), Fraction<double>(3), Fraction<double>(6), Fraction<double>(2),
         Fraction<double>(1), Fraction<double>(4), Fraction<double>(2), Fraction<double>(5), Fraction<double>(2), Fraction<double>(6), Fraction<double>(13), Fraction<double>(9), Fraction<double>(2), Fraction<double>(15),
         Fraction<double>(12), Fraction<double>(20), Fraction<double>(7,2), Fraction<double>(5,3), Fraction<double>(2,13), Fraction<double>(6,19), Fraction<double>(13,8), Fraction<double>(9,7), Fraction<double>(2,5), Fraction<double>(13,12),
         Fraction<double>(11,12), Fraction<double>(7,25), Fraction<double>(6,2), Fraction<double>(3,3), Fraction<double>(5,13), Fraction<double>(20,19), Fraction<double>(17,8), Fraction<double>(5,7), Fraction<double>(4,5), Fraction<double>(6,12),
         Fraction<double>(5,15), Fraction<double>(2,30), Fraction<double>(7,5), Fraction<double>(1,3), Fraction<double>(8,13), Fraction<double>(41,19), Fraction<double>(11,9), Fraction<double>(8,7), Fraction<double>(7,9), Fraction<double>(5,17),
         Fraction<double>(2,17), Fraction<double>(7,29), Fraction<double>(9,3), Fraction<double>(5,3), Fraction<double>(9,13), Fraction<double>(71,19), Fraction<double>(13,8), Fraction<double>(15,7), Fraction<double>(3,5), Fraction<double>(14,12),
         Fraction<double>(6,19), Fraction<double>(9,11), Fraction<double>(1,9), Fraction<double>(7,3), Fraction<double>(2,13), Fraction<double>(28,19), Fraction<double>(17,50), Fraction<double>(2,7), Fraction<double>(7,12), Fraction<double>(56,12),
         Fraction<double>(9,10), Fraction<double>(1,24), Fraction<double>(4,2), Fraction<double>(1,3), Fraction<double>(1,13), Fraction<double>(23,19), Fraction<double>(14,8), Fraction<double>(2,70), Fraction<double>(70,5), Fraction<double>(5,19),
         Fraction<double>(3,11), Fraction<double>(33,70), Fraction<double>(9,3), Fraction<double>(9,3), Fraction<double>(7,13), Fraction<double>(25,19), Fraction<double>(11,16), Fraction<double>(2,711), Fraction<double>(7,56), Fraction<double>(59,12)
       };
        Matrix<Fraction<double>> A(10,vec1);
        A.Print();
        Matrix<Fraction<double>>* A_inverted = A.LUInversion();
        A_inverted->Print();
        vector<double> A_Inverted_Ans{ 0.10025795585430151 , -0.5435622693226418 , -0.10009386958098374 , 0.17380273864430737 , 1.4684749296263968 , 2.7775875331369475 , -1.4584640753064706 , 1.791704641869694 , -0.003966276151435191 , -1.263185830467847,
      -0.06402547800024323 , 0.3367050876197583 , 0.05620163769503209 , -0.056621438628152436 , -0.9188270318869798 , -1.6159222761770256 , 0.8443659986761375 , -1.0614865213018867 , -0.002548606460047206 , 0.7535334149877175,
      -0.01827780226005967 , -0.33877067338001043 , 0.035257936046568975 , 0.15348483915824176 , 0.11797587615054408 , 1.3967684551639712 , -0.4699009922595088 , -0.16373148806886398 , 0.07809845700947322 , 0.17846480532505654,
      0.06424945118451697 , 0.7828216666542989 , -0.11613900322378852 , -0.35493829734757293 , -0.03133077409443156 , -4.348605143730334 , 1.7294950653212868 , -0.021775219479870492 , -0.14267788958865701 , -0.05693947930305134,
      0.11432580357016063 , 1.0037542340217454 , -0.07893576125176964 , -0.4347353702660289 , -1.3092871971976148 , -2.8892197114442384 , 0.954413381485344 , -1.21834929646311 , -0.17910913634144812 , 1.0807899480436698,
      -0.07250201042259662 , -0.014140651134392617 , -0.01468981198312847 , 0.031276196672184384 , -0.10342279238241826 , 0.549828542112086 , 0.03440659246469213 , 0.0492932463402651 , -0.015954526890873236 , 0.026191216675674173,
      -0.06479312305320958 , 0.3906960444984191 , 0.03844058269859246 , -0.14602640603064462 , -0.0687940483149333 , -1.6323553646519375 , 0.5561147956074197 , -0.5335914224251218 , -0.07372056377824347 , 0.29177518723681184,
      0.11999801830237819 , -0.5077843214629313 , 0.0312962535473648 , 0.16032816081438916 , 0.487596966859845 , 1.5094959155930645 , -0.5187679777564239 , 0.8179528716820766 , 0.08374387524103329 , -0.8195076407697989,
      0.00854393063742241 , 0.019764391352719058 , -0.0002352089909742671 , -0.010225551311584027 , -0.08659811301630674 , -0.14184883512200935 , 0.05859079671377178 , -0.026490605937445937 , 0.07398321353350042 , 0.012552863149555442,
      -0.01181644441100393 , -0.4340672064615672 , 0.056703561213528896 , 0.17853728789871248 , 0.1363861744780319 , 2.202260848032843 , -0.9613134477173721 , 0.3106408993348222 , 0.07213364632166433 , -0.038968108880582594};

        for (int i =0; i < vec1.size(); i++ ) {
            assert(CompareFloat(A_Inverted_Ans[i], A_inverted->GetArr()[i].GetNumerator()/A_inverted->GetArr()[i].GetDenominator(),.0001));
        }
        delete A_inverted;
    cout << "-----TEST10 PASSED----\n";
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
    test10();
}