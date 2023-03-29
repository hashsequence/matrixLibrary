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

        Row(vector<double> arr);

        Row(int n, vector<double> arr);

        double GetCell(int i) const;

        void SetCell(int i, double val);

        int GetRowSize() const;

        void Print() const;
};

class Matrix
{
    private:

        vector<double> arr;
        int n;

    public:

        Matrix(int n);
    
        Matrix(int n, vector<double> arr);
    
        double GetCell(int i, int j) const;
    
        void SetCell(int i, int j, double val);
    
        Row* GetRow(int i) const;
    
        Row* GetCol(int j) const;
    
        int GetRowSize() const;
    
        void Print() const;
    
        vector<double> GetArr() const;
    
        vector<vector<double>> ConvertTo2DArray() const;
    
        Matrix* Multiply(Matrix* B);
    
        Matrix* LUDecomposition();
    
        Matrix* Inversion();
    
        static Matrix* InvertUpperTriangularMatrix(Matrix* M);
    
        static Matrix* InvertLowerTriangularMatrix(Matrix* M);


};

#endif