#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <vector>

using namespace std;

class Row
{
    private:

        vector<int> arr;
        int n;

    public:

        Row(int n);

        Row(vector<int> arr);

        Row(int n, vector<int> arr);

        int GetCell(int i) const;

        void SetCell(int i, int val);

        int GetRowSize() const;

        void Print() const;
};

class Matrix
{
    private:

        vector<int> arr;
        int n;

    public:

        Matrix(int n);
    
        Matrix(int n, vector<int> arr);
    
        int GetCell(int i, int j) const;
    
        void SetCell(int i, int j, int val);
    
        Row* GetRow(int i) const;
    
        Row* GetCol(int j) const;
    
        int GetRowSize() const;
    
        void Print() const;
    
        vector<int> GetArr() const;
    
        vector<vector<int>> ConvertTo2DArray() const;
    
        Matrix* Multiply(Matrix* B);
    
        Matrix* LUDecomposition();
    
        Matrix* Inversion();
    
        static Matrix* InvertUpperTriangularMatrix(Matrix* M);
    
        static Matrix* InvertLowerTriangularMatrix(Matrix* M);


};

#endif