export {Matrix, Row}

function Row(arr) {
    this.arr = arr;
    this.n = arr.length
}

Row.prototype.DotProduct = function(b) {
    let result = 0
    for (let i = 0; i < this.arr.length; i++) {
        result += this.GetCell(i) * b.GetCell(i);
    }
    return result;
}

Row.prototype.GetCell = function(i) {
    return this.arr[i];
}

Row.prototype.SetCell = function(i,val) {
    this.arr[i] = val;
}

Row.prototype.GetRowSize = function() {
    return this.n;
}

Row.prototype.Print = function() {
    let str = "\n"
    for (let i = 0; i < this.GetRowSize(); i++) {
        str += this.GetCell(i) + " , ";
    }
    str =  str.substring(0,str.length-1) + "\n";
    console.log(str);
}

function Matrix(n, arr=null) {
    this.n = n; //row/col size n
    if (typeof arr === 'undefined' || arr == null) {
        this.arr = Array.apply(null, Array(n*n)).map(Number.prototype.valueOf,0); //internal 1-D array
    } else {
        this.arr = arr; //internal 1-D array
    }
}

Matrix.prototype.GetCell = function(i,j) {
    return this.arr[i*this.GetRowSize() + j];
}

Matrix.prototype.SetCell = function(i, j ,val) {
    this.arr[i*this.GetRowSize() + j] = val;
}
/*
    returns the ith(begins with 0) row as a Row object 
*/
Matrix.prototype.GetRow = function(i) {
    let row = []
    for (let j = 0; j < this.GetRowSize(); j++) {
        row.push(this.arr[i*this.GetRowSize() + j]);
    }
    return new Row(row);
}

/*
    returns the jth(begins with 0) column as a Row object
*/
Matrix.prototype.GetCol = function(j) {
    let col = [];
    for (let i = 0; i < this.GetRowSize(); i++) {
        col.push(this.arr[i*this.GetRowSize() + j]);
    }
    return new Row(col);
}

Matrix.prototype.GetRowSize = function() {
    return this.n;
}

Matrix.prototype.Print = function() {
    let str = "\n"
    for (let i = 0; i < this.GetRowSize(); i++) {
      for (let j = 0; j < this.GetRowSize(); j++) {
        str += this.GetCell(i,j) + " , ";
      }
      str = str.substring(0,str.length-2) + "\n";
    }
    str =  str.substring(0,str.length-2) + "\n";
    console.log(str);
}

Matrix.prototype.GetArr = function() {
    return this.arr;
}

Matrix.prototype.ConvertTo2DArray = function() {
    let twoDArr = Array.apply(null,Array(this.GetRowSize())).map(Array.prototype.valueOf,[]);
    for (let i = 0; i < this.GetRowSize(); i++) {
        twoDArr[i] = Array.apply(null,Array(this.GetRowSize())).map(Number.prototype.valueOf,0);
    }
    
    for (let i = 0; i < this.GetRowSize(); i++) {
        for (let j = 0; j < this.GetRowSize(); j++) {
            twoDArr[i][j] = this.GetCell(i,j);
        }
    }
    return twoDArr;
}

Matrix.prototype.Multiply = function(B) {
    let result = new Matrix(this.GetRowSize(),Array.apply(null, Array(this.GetRowSize()*this.GetRowSize())).map(Number.prototype.valueOf,0));

    for (let i = 0; i < this.GetRowSize(); i++) {
        for (let j = 0; j < B.GetRowSize(); j++) {
            result.SetCell(i,j,this.GetRow(i).DotProduct(B.GetCol(j)))
        }
    }
    return result;
} 

Matrix.prototype.LUDecomposition = function() {
    let lower = new Matrix(this.GetRowSize());
    let upper = new Matrix(this.GetRowSize());
    
    for (let i = 0; i < this.GetRowSize(); i++) {
        //U: Upper Triangular Matrix
        for (let k = i; k < this.GetRowSize(); k++) {
            let sum = 0;
            for (let j = 0; j < i; j++) {
                sum += (lower.GetCell(i,j) * upper.GetCell(j,k));
            }
            upper.SetCell(i,k, this.GetCell(i,k) - sum);
        }

        //L: Lower Triangular Matrix
        for (let k = i; k < this.GetRowSize(); k++) {
            if (i == k) {
                //Diagonals of lower triangular matrix are 1's
                lower.SetCell(i,i,1);
            } else {
                let sum = 0;
                for (let j = 0; j < i; j++) {
                    sum += (lower.GetCell(k,j) * upper.GetCell(j,i));
                }
                lower.SetCell(k,i,(this.GetCell(k,i) - sum) / upper.GetCell(i,i));
            }
        }
    }
    return [lower,upper];
}

Matrix.prototype.GetCofactor = function(coFactorMatrix, p, q, n) {
    let i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (let row = 0; row < n; row++) {
        for ( let col = 0; col < n; col++) {
            //  Copying into temporary matrix only those
            //  element which are not in given row and
            //  column
            if (row != p && col != q) {
                coFactorMatrix.SetCell(i,j,this.GetCell(row,col));
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

Matrix.prototype.Determinant = function()
{
    let D = 0; // Initialize result
    let negOne = -1;
    // Base case : if matrix contains single element
    if (this.GetRowSize() == 1) {
        return this.GetCell(0,0);
    }
   
    let coFactorMatrix = new Matrix(this.GetRowSize()-1);// To store cofactors

   
    let sign = 1; // To store sign multiplier
   
    // Iterate for each element of first row
    for (let f = 0; f < this.GetRowSize(); f++)
    {
        // Getting Cofactor of A[0][f]
        this.GetCofactor(coFactorMatrix, 0, f, this.GetRowSize());
        D = D + (sign * this.GetCell(0,f) * coFactorMatrix.Determinant());
        // terms are to be added with alternate sign
        sign = sign * negOne;
    }
    return D;
}

//Transpose current matrix
Matrix.prototype.Transpose = function() {
    for (let i = 0; i < this.GetRowSize(); i++) {
        for (let j = i; j < this.GetRowSize(); j++) {
            let t = this.GetCell(i,j);
            this.SetCell(i,j,this.GetCell(j,i));
            this.SetCell(j,i,t);
        }
    }
}

//returns the Transpose of a matrix
Matrix.Transpose = function(A) {
    let T = new Matrix(A.GetRowSize());
    for (let i = 0; i < A.GetRowSize(); i++) {
        for (let j = i; j < A.GetRowSize(); j++) {
            T.SetCell(i,j,A.GetCell(j,i));
            T.SetCell(j,i,A.GetCell(i,j));
        }
    }
    return T;
}

//Inversion algorithm
//LU Decomposition time complexity O(n^3)
//since A=LU -> A^-1 = (LU)^-1 ==>  A^-1 = U^-1 * L^-1 (matrix multiplication is not commutative so U^-1 * L^-1)
//so invert U and L which would take O(n^3) 
// multiply U^-1 * L^-1 will tak O(n^3)
Matrix.prototype.LUInversion = function() {
    let [P, As] = Matrix.PartialPivot(this);
    let [L,U] = As.LUDecomposition();
    return Matrix.InvertUpperTriangularMatrix(U).Multiply(Matrix.InvertLowerTriangularMatrix(L)).Multiply(P);
}
//Inverse of an upper triangular matrix is upper triangular
//inverse of lower triangular matrix is lower triangular
//to compute the inverse of a triangular matrix,
//solve Ux = b for all [0,..,e_i,...0] where e_i = 1 for all 0<=i<n with backwards substitution
//solve Lx=b for all [0,..,e_i,...0] where e_i = 1 for all 0<=i<n with forward substitution

Matrix.InvertUpperTriangularMatrix = function(M) {
    let result = new Matrix(M.GetRowSize())
    //create result matrix and intialize to identity matrix
    for (let i = 0; i < result.GetRowSize(); i++) {
        result.SetCell(i,i,1);
    }

    for (let i = 0; i < result.GetRowSize(); i++) {
        for (let j = result.GetRowSize()-1; j >= 0; j--) {
            let sum = 0;
            for (let k = result.GetRowSize()-1; k > j; k--) {
                sum += result.GetCell(k,i) * M.GetCell(j,k);
            }
            result.SetCell(j,i,(result.GetCell(j,i)-sum)/M.GetCell(j,j));         
        }
    }
    return result;
}

Matrix.InvertLowerTriangularMatrix = function(M) {
    let result = new Matrix(M.GetRowSize())
    //create result matrix and intialize to identity matrix
    for (let i = 0; i < result.GetRowSize(); i++) {
        result.SetCell(i,i,1);
    }
    for (let i = 0; i < result.GetRowSize(); i++) {
        for (let j = 0; j < result.GetRowSize(); j++) {
            let sum = 0;
            for (let k = 0; k < j; k++) {
                sum += result.GetCell(k,i) * M.GetCell(j,k);
            }
            result.SetCell(j,i,(result.GetCell(j,i)-sum)/M.GetCell(j,j));         
        }
    }
    return result;
}

Matrix.SwapCols = function(A, j1, j2) {
    for (let i = 0; i < A.GetRowSize(); i++) {
        let t = A.GetCell(i,j1);
        A.SetCell(i,j1,A.GetCell(i,j2));
        A.SetCell(i,j2,t);
    }
}

Matrix.SwapRows = function(A, i1, i2) {
    for (let j = 0; j < A.GetRowSize(); j++) {
        let t = A.GetCell(i1,j);
        A.SetCell(i1,j,A.GetCell(i2,j));
        A.SetCell(i2,j,t);
    }
}

Matrix.PartialPivot = function(A) {
    //create a new Matrix
    let arr = A.GetArr().map(x => x);
    let ACopy = new Matrix(A.GetRowSize(),arr);
    //creating identity matrix
    let P = new Matrix(ACopy.GetRowSize());
    for (let i = 0; i < P.GetRowSize();i++) {
        P.SetCell(i,i,1);
    }
    for (let j = 0; j < ACopy.GetRowSize();j++) {
        let max = ACopy.GetCell(j,j);
        let maxRowNum = j;
        for (let i = j; i < ACopy.GetRowSize();i++) { 
            let curr = ACopy.GetCell(i,j);
            if (max < curr) {
                max = curr;
                maxRowNum = i;
            } 
        }
        Matrix.SwapRows(P,j,maxRowNum);
        Matrix.SwapRows(ACopy,j,maxRowNum);
    }
    return [P, ACopy];
}
