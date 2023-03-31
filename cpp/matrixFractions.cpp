#include "matrixFractions.h"
#include <iostream>
#include <vector>

using namespace std;

template <class T>
Row<T>::Row(int n) {
    this->n=n;
    arr.resize(n);
}

template <class T>
Row<T>::Row(vector<T>& arr) {
    this->n=arr.size();
    this->arr=arr;
}

template <class T>
Row<T>::Row(int n, vector<T>& arr) {
    this->n=n;
    this->arr = arr;
}

template <class T>
T Row<T>::GetCell(int i) const{
    T iVal(arr[i]);
    return iVal;
}

template <class T>
void Row<T>::SetCell(int i, T val) {
    arr[i] = val;
}

template <class T>
int Row<T>::GetRowSize() const {
    return this->n;
}

template <class T>
void Row<T>::Print() const {
    for (int i =0; i < GetRowSize(); i++) {
        T currCell(GetCell(i));
        cout << currCell;
        if (i != GetRowSize()-1) {
            cout << ",";
        }
    }
    cout << endl;
}

template <class T>
T Row<T>::DotProduct(Row& b) const {
    T result(0);
    for (int i = 0 ; i < GetRowSize(); i++) {
        T aCell = GetCell(i);
        T bCell = b.GetCell(i);
        T currSum = aCell * bCell;
        result += currSum;
    }
    return result;
}

template <class W>
Matrix<W>::Matrix(int n) {
    this->n=n;
    arr.resize(n*n);
}

template <class W>
Matrix<W>::Matrix(int n, vector<W>& arr) {
    this->n=n;
    this->arr=arr;
}

template <class W>
W Matrix<W>::GetCell(int i, int j) const {
    return arr[i*GetRowSize() + j];
}

template <class W>
void Matrix<W>::SetCell(int i, int j, W val) {
    arr[i*GetRowSize() + j] = val;
}

template <class W>
Row<W>* Matrix<W>::GetRow(int i) const {
    vector<W> row;
    for (int j = 0; j < GetRowSize(); j++) {
        row.push_back(arr[i*GetRowSize() + j]);
    }
    return new Row<W>(row);
}

template <class W>
Row<W>* Matrix<W>::GetCol(int j) const {
    vector<W> col;
    for (int i = 0; i < GetRowSize(); i++) {
        col.push_back(arr[i*GetRowSize() + j]);
    }
    return new Row<W>(col);
}

template <class W>
int Matrix<W>::GetRowSize() const {
    return n;
}

template <class W>
void Matrix<W>::Print() const {
    string str = "";
    for (int i = 0; i < GetRowSize(); i++) {
        for (int j = 0; j < GetRowSize(); j++) {
            cout << GetCell(i,j);
            if (j != GetRowSize()-1) {
                cout << ",";
            }
        }
        cout << endl;
    }
    cout << endl;
}

template <class W>
vector<W> Matrix<W>::GetArr() const {
    return arr;
}

template <class W>
vector<vector<W>> Matrix<W>::ConvertTo2DArray() const {
    vector<vector<W>> twoDArr(GetRowSize(),vector<W>(GetRowSize(),0));
    for (int i = 0; i < GetRowSize(); i++) {
        for (int j = 0; j < GetRowSize(); j++) {
            twoDArr[i][j] = GetCell(i,j);
        }
    }
    return twoDArr;
}

template <class W>
Matrix<W>* Matrix<W>::Multiply(Matrix<W>& B) {
    Matrix<W>* result = new Matrix<W>(GetRowSize());

    for (int i = 0;i < GetRowSize(); i++) {
        for (int j = 0; j < B.GetRowSize(); j++) {
            result->SetCell(i,j,GetRow(i)->DotProduct(*(B.GetCol(j))));
        }
    }
    return result;
}

template <class W>
vector<Matrix<W>*> Matrix<W>::LUDecomposition() {
    vector<Matrix<W>*> result(2,nullptr);
    result[0] = new Matrix<W>(GetRowSize());
    result[1] = new Matrix<W>(GetRowSize());
    Matrix<W>* lower = result[0];
    Matrix<W>* upper = result[1];

    for (int i = 0; i < GetRowSize(); i++) {
        //U: Upper Triangular Matrix
        for (int k = i; k < GetRowSize(); k++) {
            W sum(0);
            for (int j = 0; j < i; j++) {
                W aCell = lower->GetCell(i,j);
                W bCell = upper->GetCell(j,k);
                W productOfCell = aCell * bCell;
                sum += productOfCell;
            }
            W cCell = GetCell(i,k);
            W dCell = cCell-sum;
            upper->SetCell(i,k,dCell);
        }

         //L: Lower Triangular Matrix
         for (int k = i; k < GetRowSize(); k++) {
            if (i == k) {
                //Diagonals of lower triangular matrix are 1's
                W one(1);
                lower->SetCell(i,i,one);
            } else {
                W sum(0);
                for (int j = 0; j < i; j++) {
                    W aCell = lower->GetCell(k,j);
                    W bCell = upper->GetCell(j,i);
                    W productOfCell = aCell * bCell;
                    sum += productOfCell;
                }
                W dCell = GetCell(k,i);
                W eCell = upper->GetCell(i,i);
                W diffDCellAndSum = dCell - sum;
                W quotientOfDiffAndCell = diffDCellAndSum / eCell;
                lower->SetCell(k,i,quotientOfDiffAndCell);
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
template <class W>
Matrix<W>* Matrix<W>::LUInversion() {
    vector<Matrix<W>*> LU = LUDecomposition();
    Matrix<W>* U_inverted = InvertUpperTriangularMatrix(*(LU[1]));
    Matrix<W>* L_inverted = InvertLowerTriangularMatrix(*(LU[0]));
    Matrix<W>* InvertedMatrix = U_inverted->Multiply(*L_inverted);
    for (int i = 0; i < LU.size(); i++) {
        delete LU[i];
    }
    LU.clear();
    delete U_inverted;
    delete L_inverted;
    return InvertedMatrix;
}

//Inverse of an upper triangular matrix is upper triangular
//inverse of lower triangular matrix is lower triangular
//to compute the inverse of a triangular matrix,
//solve Ux = b for all [0,..,e_i,...0] where e_i = 1 for all 0<=i<n with backwards substitution
//solve Lx=b for all [0,..,e_i,...0] where e_i = 1 for all 0<=i<n with forward substitution
template <class W>
Matrix<W>* Matrix<W>::InvertUpperTriangularMatrix(Matrix& M) {
    Matrix<W>* result = new Matrix<W>(M.GetRowSize());
    for (int i = 0; i < result->GetRowSize(); i++) {
        W one(1);
        result->SetCell(i,i,one);
    }

    for (int i = 0; i < result->GetRowSize(); i++) {
        for (int j = result->GetRowSize()-1; j>=0; j--) {
            W sum(0);
            for (int k = result->GetRowSize()-1; k > j; k--) {
                W aCell = result->GetCell(k,i);
                W bCell = M.GetCell(j,k);
                W productOfCell = aCell * bCell;
                sum += productOfCell;
            }
            W cCell = result->GetCell(j,i);
            W dCell = M.GetCell(j,j);
            W diffOfCell = cCell-sum;
            W quotientOfDiffAndCell = diffOfCell/dCell;
            result->SetCell(j,i,quotientOfDiffAndCell);
        }
    }
    return result;
}

template <class W>
Matrix<W>* Matrix<W>::InvertLowerTriangularMatrix(Matrix<W>& M) {
    Matrix<W>* result = new Matrix<W>(M.GetRowSize());
    for (int i = 0; i < result->GetRowSize(); i++) {
        W one(1);
        result->SetCell(i,i,one);
    }

    for (int i = 0; i < result->GetRowSize(); i++) {
        for (int j = 0; j < result->GetRowSize(); j++) {
            W sum(0);
            for (int k = 0; k < j;  k++) {
                W aCell = result->GetCell(k,i);
                W bCell = M.GetCell(j,k);
                W productOfCell = aCell*bCell;
                sum += productOfCell;
            }
            W cCell = result->GetCell(j,i);
            W dCell = M.GetCell(j,j);
            W diffOfCell = cCell-sum;
            W quotientOfDiffAndCell = diffOfCell/dCell;
            result->SetCell(j,i,quotientOfDiffAndCell);
        }
    }
    return result;
}

template <class W>
void Matrix<W>::GetCofactor(Matrix<W>& coFactorMatrix, int p, int q, int n) {
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++) {
        for ( int col = 0; col < n; col++) {
            //  Copying into temporary matrix only those
            //  element which are not in given row and
            //  column
            if (row != p && col != q) {
                W val = this->GetCell(row,col);
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

template <class W>
W Matrix<W>::Determinant() {
    W D(0); // Initialize result
    W negOne(-1);
    // Base case : if matrix contains single element
    if (this->GetRowSize() == 1) {
        W A_0_0(this->GetCell(0,0));
        return A_0_0;
    }
   
    Matrix<W> coFactorMatrix(this->GetRowSize()-1);// To store cofactors

   
    W sign(1); // To store sign multiplier
   
    // Iterate for each element of first row
    for (int f = 0; f < this->GetRowSize(); f++)
    {
        // Getting Cofactor of A[0][f]
        this->GetCofactor(coFactorMatrix, 0, f, this->GetRowSize());
        W coFacDet  = coFactorMatrix.Determinant();
        W cell_0_f = this->GetCell(0,f);
        W prod = cell_0_f * coFacDet;
        W termVal = sign * prod ;
        D += termVal;
        // terms are to be added with alternate sign
        sign *= negOne;
    }
    return D;
}

template <class W>
void Matrix<W>::Transpose() {
    for (int i = 0; i < this->GetRowSize(); i++) {
        for (int j = i; j < this->GetRowSize(); j++) {
            W t = this->GetCell(i,j);
            this->SetCell(i,j,this->GetCell(j,i));
            this->SetCell(j,i,t);
        }
    }
}

template <class W>
Matrix<W>* Matrix<W>::Transpose(Matrix& A) {
    Matrix<W>* T = new Matrix(A.GetRowSize());
    for (int i = 0; i < A.GetRowSize(); i++) {
        for (int j = i; j < A.GetRowSize(); j++) {
            T->SetCell(i,j,A.GetCell(j,i));
            T->SetCell(j,i,A.GetCell(i,j));
        }
    }
    return T;
}


/*
for linking errors there are three ways to solve this:
1) To move the definition to the .h file
2) Add explicit instantiations in the .cpp file.
3) #include the .cpp file defining the template at the .cpp file using the template.

using method 2
*/

template class Fraction<int>;
template class Fraction<double>;
template class Row<double>;
template class Row<int>;
template class Row<Fraction<int>>;
template class Row<Fraction<double>>;
template class Matrix<double>;
template class Matrix<int>;
template class Matrix<Fraction<int>>;
template class Matrix<Fraction<double>>;
