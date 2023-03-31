#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <vector>

using namespace std;

class Row
{
    private:

        vector<double> arr;
        int n;

    public:

        Row(int n);

        Row(vector<double>& arr);

        Row(int n, vector<double>& arr);

        double GetCell(int i) const;

        void SetCell(int i, double val);

        int GetRowSize() const;

        void Print() const;

        double DotProduct(Row& b) const;
};

class Matrix
{
    private:

        vector<double> arr;
        int n;

    public:

        Matrix(int n);
    
        Matrix(int n, vector<double>& arr);
    
        double GetCell(int i, int j) const;
    
        void SetCell(int i, int j, double val);
    
        Row* GetRow(int i) const;
    
        Row* GetCol(int j) const;
    
        int GetRowSize() const;
    
        void Print() const;
    
        vector<double> GetArr() const;
    
        vector<vector<double>> ConvertTo2DArray() const;
    
        Matrix* Multiply(Matrix& B);
    
        vector<Matrix*> LUDecomposition(); // returns [L, U]
    
        Matrix* LUInversion();
    
        void Transpose();

        static Matrix* Transpose(Matrix& A);

        static Matrix* InvertUpperTriangularMatrix(Matrix& M);
    
        static Matrix* InvertLowerTriangularMatrix(Matrix& M);

        void GetCofactor(Matrix& coFactorMatrix, int p, int q, int n);

        double Determinant();

        static void SwapCols(Matrix& A, int j1, int j2);

        static void SwapRows(Matrix& A, int j1, int j2);

        /*
            returns a vector of [P, A_RowSwapped], where P is the permutation Matrix 
            such that PA = A_RowSwapped and A_RowSwapped is A with rows swapped such that
            we are putting the larger element at the top left position, this is called partial pivoting
            because we are only swapping rows
        */
        static vector<Matrix*> PartialPivot(Matrix& A); 
};


#endif