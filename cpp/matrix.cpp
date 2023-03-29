#include "matrix.h"
#include <iostream>
#include <vector>

using namespace std;

Row::Row(int n) {
    this->n=n;
    arr.resize(n);
}

Row::Row(vector<double>& arr) {
    this->n=arr.size();
    this->arr=arr;
}

Row::Row(int n, vector<double>& arr) {
    this->n=n;
    this->arr = arr;
}

double Row::GetCell(int i) const {
    return arr[i];
}

void Row::SetCell(int i, double val) {
    arr[i] = val;
}

int Row::GetRowSize() const {
    return this->n;
}

void Row::Print() const {
    string str = "";
    for (int i =0; i < this->arr.size(); i++) {
        str += to_string(this->arr[i]) + ",";
    }
    str = str.substr(0,str.length()-1);
    cout << str << endl;
}

double Row::DotProduct(Row& b) const {
    double result = 0;
    for (int i = 0 ; i < GetRowSize(); i++) {
        result += GetCell(i) * b.GetCell(i);
    }
    return result;
}


Matrix::Matrix(int n) {
    this->n=n;
    arr.resize(n*n);
}


Matrix::Matrix(int n, vector<double>& arr) {
    this->n=n;
    this->arr=arr;
}

double Matrix::GetCell(int i, int j) const {
    return arr[i*GetRowSize() + j];
}

void Matrix::SetCell(int i, int j, double val) {
    arr[i*GetRowSize() + j] = val;
}

Row* Matrix::GetRow(int i) const {
    vector<double> row;
    for (int j = 0; j < GetRowSize(); j++) {
        row.push_back(arr[i*GetRowSize() + j]);
    }
    return new Row(row);
}

Row* Matrix::GetCol(int j) const {
    vector<double> col;
    for (int i = 0; i < GetRowSize(); i++) {
        col.push_back(arr[i*GetRowSize() + j]);
    }
    return new Row(col);
}

int Matrix::GetRowSize() const {
    return n;
}

void Matrix::Print() const {
    string str = "";
    for (int i = 0; i < GetRowSize(); i++) {
        for (int j = 0; j < GetRowSize(); j++) {
            str += to_string(GetCell(i,j)) + ",";
        }
        str = str.substr(0,str.length()-1) + "\n";
    }
    str = str.substr(0,str.length()-1) + "\n";
    cout << str << endl;
}

vector<double> Matrix::GetArr() const {
    return arr;
}

vector<vector<double>> Matrix::ConvertTo2DArray() const {
    vector<vector<double>> twoDArr(GetRowSize(),vector<double>(GetRowSize(),0));
    for (int i = 0; i < GetRowSize(); i++) {
        for (int j = 0; j < GetRowSize(); j++) {
            twoDArr[i][j] = GetCell(i,j);
        }
    }
    return twoDArr;
}

Matrix* Matrix::Multiply(Matrix& B) {
    Matrix* result = new Matrix(GetRowSize());

    for (int i = 0;i < GetRowSize(); i++) {
        for (int j = 0; j < B.GetRowSize(); j++) {
            result->SetCell(i,j,GetRow(i)->DotProduct(*(B.GetCol(j))));
        }
    }
    return result;
}

vector<Matrix*> Matrix::LUDecomposition() {
    vector<Matrix*> result(2,nullptr);
    result[0] = new Matrix(GetRowSize());
    result[1] = new Matrix(GetRowSize());
    Matrix* lower = result[0];
    Matrix* upper = result[1];

    for (int i = 0; i < GetRowSize(); i++) {
        //U: Upper Triangular Matrix
        for (int k = i; k < GetRowSize(); k++) {
            double sum = 0;
            for (int j = 0; j < i; j++) {
                sum += lower->GetCell(i,j) * upper->GetCell(j,k);
            }
            upper->SetCell(i,k,GetCell(i,k)-sum);
        }

         //L: Lower Triangular Matrix
         for (int k = i; k < GetRowSize(); k++) {
            if (i == k) {
                //Diagonals of lower triangular matrix are 1's
                lower->SetCell(i,i,1);
            } else {
                double sum = 0;
                for (int j = 0; j < i; j++) {
                    sum += lower->GetCell(k,j) * upper->GetCell(j,i);
                }
                lower->SetCell(k,i,(GetCell(k,i) - sum) / upper->GetCell(i,i));
            }
         }
    }
    return result;
}

//Inversion algorithm
//LU Decomposition time complexity O(n^3)
//since A=LU -> A^-1 = (LU)^-1 ==>  A^-1 = U^-1 * L^-1 (matrix multiplication is not commutative so U^-1 * L^-1)
//so invert U and L which would take O(n^3) 
// multiply U^-1 * L^-1 will tak O(n^3)
Matrix* Matrix::Inversion() {
    vector<Matrix*> LU = LUDecomposition();
    Matrix* InvertedMatrix = InvertUpperTriangularMatrix(*LU[1])->Multiply(*InvertLowerTriangularMatrix(*LU[0]));
    for (int i = 0; i < LU.size(); i++) {
        delete LU[i];
    }
    return InvertedMatrix;
}

//Inverse of an upper triangular matrix is upper triangular
//inverse of lower triangular matrix is lower triangular
//to compute the inverse of a triangular matrix,
//solve Ux = b for all [0,..,e_i,...0] where e_i = 1 for all 0<=i<n with backwards substitution
//solve Lx=b for all [0,..,e_i,...0] where e_i = 1 for all 0<=i<n with forward substitution
Matrix* Matrix::InvertUpperTriangularMatrix(Matrix& M) {
    Matrix* result = new Matrix(M.GetRowSize());
    for (int i = 0; i < result->GetRowSize(); i++) {
        result->SetCell(i,i,1);
    }

    for (int i = 0; i < result->GetRowSize(); i++) {
        for (int j = result->GetRowSize()-1; j>=0; j--) {
            double sum = 0;
            for (int k = result->GetRowSize()-1; k > j; k--) {
                sum += result->GetCell(k,i)*M.GetCell(j,k);
            }
            result->SetCell(j,i,(result->GetCell(j,i)-sum)/M.GetCell(j,j));
        }
    }
    return result;
}

Matrix* Matrix::InvertLowerTriangularMatrix(Matrix& M) {
    Matrix* result = new Matrix(M.GetRowSize());
    for (int i = 0; i < result->GetRowSize(); i++) {
        result->SetCell(i,i,1);
    }

    for (int i = 0; i < result->GetRowSize(); i++) {
        for (int j = 0; j < result->GetRowSize(); j++) {
            double sum = 0;
            for (int k = 0; k < j;  k++) {
                sum += result->GetCell(k,i)*M.GetCell(j,k);
            }
            result->SetCell(j,i,(result->GetCell(j,i)-sum)/M.GetCell(j,j));
        }
    }
    return result;
}