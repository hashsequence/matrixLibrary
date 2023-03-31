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
    
        vector<Matrix*> LUDecomposition();
    
        Matrix* LUInversion();
    
        void Transpose();

        static Matrix* Transpose(Matrix& A);
        
        static Matrix* InvertUpperTriangularMatrix(Matrix& M);
    
        static Matrix* InvertLowerTriangularMatrix(Matrix& M);

        void GetCofactor(Matrix& coFactorMatrix, int p, int q, int n);

        double Determinant();
};

#endif