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

        int GetCell(int i);

        void SetCell(int i, int val);

        int GetSize();

        void Print();
}

class Matrix
{
    private:

        vector<int> arr;
        int n;

    public:

        Matrix(int n);
    
        Matrix(vector<int> arr);
    
        Matrix(int n, vector<int> arr);
    
        int GetCell(int i, int j);
    
        void SetCell(int i, int j, int val);
    
        Row GetRow(int i);
    
        Row GetCol(int j);
    
        int GetSize();
    
        void Print();
    
        vector<int> GetArr();
    
        vector<vector<int> ConvertTo2DArray();
    
        Matrix Multiply(Matrix B);
    
        Matrix LUDecomposition();
    
        Matrix Inversion();
    
        static Matrix InvertUpperTriangularMatrix(Matrix M);
    
        static Matrix InvertLowerTriangularMatrix(Matrix M);


}

#endif