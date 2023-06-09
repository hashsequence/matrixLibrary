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
Matrix* Matrix::LUInversion() {
    vector<Matrix*> PAs = PartialPivot(*this);
    vector<Matrix*> LU = PAs[1]->LUDecomposition();
    Matrix* InvertedMatrix = InvertUpperTriangularMatrix(*LU[1])->Multiply(*InvertLowerTriangularMatrix(*LU[0]))->Multiply(*(PAs[0]));
    for (int i = 0; i < LU.size(); i++) {
        delete LU[i];
        delete PAs[i];
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

void Matrix::GetCofactor(Matrix& coFactorMatrix, int p, int q, int n) {
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++) {
        for ( int col = 0; col < n; col++) {
            //  Copying into temporary matrix only those
            //  element which are not in given row and
            //  column
            if (row != p && col != q) {
                double val = this->GetCell(row,col);
                coFactorMatrix.SetCell(i,j,val);
                j++;
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double Matrix::Determinant() {
    double D(0); // Initialize result
    double negOne(-1);
    // Base case : if matrix contains single element
    if (this->GetRowSize() == 1) {
        double A_0_0(this->GetCell(0,0));
        return A_0_0;
    }
   
    Matrix coFactorMatrix(this->GetRowSize()-1);// To store cofactors

   
    double sign(1); // To store sign multiplier
   
    // Iterate for each element of first row
    for (int f = 0; f < this->GetRowSize(); f++)
    {
        // Getting Cofactor of A[0][f]
        this->GetCofactor(coFactorMatrix, 0, f, this->GetRowSize());
        double coFacDet  = coFactorMatrix.Determinant();
        double cell_0_f = this->GetCell(0,f);
        double prod = cell_0_f * coFacDet;
        double termVal = sign * prod ;
        D += termVal;
        // terms are to be added with alternate sign
        sign *= negOne;
    }
    return D;
}

void Matrix::Transpose() {
    for (int i = 0; i < this->GetRowSize(); i++) {
        for (int j = i; j < this->GetRowSize(); j++) {
            int t = this->GetCell(i,j);
            this->SetCell(i,j,this->GetCell(j,i));
            this->SetCell(j,i,t);
        }
    }
}

Matrix* Matrix::Transpose(Matrix& A) {
    Matrix* T = new Matrix(A.GetRowSize());
    for (int i = 0; i < A.GetRowSize(); i++) {
        for (int j = i; j < A.GetRowSize(); j++) {
            T->SetCell(i,j,A.GetCell(j,i));
            T->SetCell(j,i,A.GetCell(i,j));
        }
    }
    return T;
}

void Matrix::SwapCols(Matrix& A, int j1, int j2) {
    for (int i = 0; i < A.GetRowSize(); i++) {
        double t = A.GetCell(i,j1);
        A.SetCell(i,j1,A.GetCell(i,j2));
        A.SetCell(i,j2,t);
    }
}

void Matrix::SwapRows(Matrix&A, int i1, int i2) {
    for (int j = 0; j < A.GetRowSize(); j++) {
        int t = A.GetCell(i1,j);
        A.SetCell(i1,j,A.GetCell(i2,j));
        A.SetCell(i2,j,t);
    }
}

vector<Matrix*> Matrix::PartialPivot(Matrix& A) {
    //create a new Matrix
    vector<double> vecCopy(A.GetArr());
    Matrix* ACopy = new Matrix(A.GetRowSize(),vecCopy);
    //creating identity matrix
    Matrix* P = new Matrix(ACopy->GetRowSize());
    for (int i = 0; i < P->GetRowSize();i++) {
        P->SetCell(i,i,1);
    }
    for (int j = 0; j < ACopy->GetRowSize();j++) {
        double max = ACopy->GetCell(j,j);
        int maxRowNum = j;
        for (int i = j; i < ACopy->GetRowSize();i++) { 
            double curr = ACopy->GetCell(i,j);
            if (max < curr) {
                max = curr;
                maxRowNum = i;
            } 
        }
        Matrix::SwapRows(*P,j,maxRowNum);
        Matrix::SwapRows(*ACopy,j,maxRowNum);
    }
    vector<Matrix*> result{P, ACopy};
    return result;
}
