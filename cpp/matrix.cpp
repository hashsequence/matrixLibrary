#include "matrix.h"
#include <iostream>
#include <vector>

using namespace std;

Row::Row(int n) {
    this->n=n;
    arr.resize(n);
}

Row::Row(vector<int> arr) {
    this->n=arr.size();
    this->arr=arr;
}

Row::Row(int n, vector<int> arr) {
    this->n=n;
    this->arr = arr;
}

int Row::GetCell(int i) const {
    return arr[i];
}

void Row::SetCell(int i, int val) {
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


Matrix::Matrix(int n, vector<int> arr) {
    this->n=n;
    this->arr=arr;
}

int Matrix::GetCell(int i, int j) const {
    return arr[i*GetRowSize() + j];
}

void Matrix::SetCell(int i, int j, int val) {
    arr[i*GetRowSize() + j] = val;
}

Row* Matrix::GetRow(int i) const {
    vector<int> row;
    for (int j = 0; j < GetRowSize(); j++) {
        row.push_back(arr[i*GetRowSize() + j]);
    }
    return new Row(row);
}

Row* Matrix::GetCol(int j) const {
    vector<int> col;
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

vector<int> Matrix::GetArr() const {
    return arr;
}

vector<vector<int>> Matrix::ConvertTo2DArray() const {
    vector<vector<int>> twoDArr(GetRowSize(),vector<int>(GetRowSize(),0));
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