#include "matrix.h"
#include <iostream>
#include <vector>

using namespace std;

Row::Row(int n) {
    this->n=n;
    arr.resize(n);
}

Row::Row(vector<double> arr) {
    this->n=arr.size();
    this->arr=arr;
}

Row::Row(int n, vector<double> arr) {
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

Matrix::Matrix(int n) {
    this->n=n;
    arr.resize(n*n);
}


Matrix::Matrix(int n, vector<double> arr) {
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

Matrix* Matrix::Multiply(Matrix* B) {
    return nullptr;
}

Matrix* Matrix::LUDecomposition() {
    return nullptr;
}

Matrix* Matrix::Inversion() {
    return nullptr;
}

Matrix* Matrix::InvertUpperTriangularMatrix(Matrix* M) {
   return nullptr;
}

Matrix* Matrix::InvertLowerTriangularMatrix(Matrix* M) {
    return nullptr;
}