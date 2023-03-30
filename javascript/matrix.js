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

//Inversion algorithm
//LU Decomposition time complexity O(n^3)
//since A=LU -> A^-1 = (LU)^-1 ==>  A^-1 = U^-1 * L^-1 (matrix multiplication is not commutative so U^-1 * L^-1)
//so invert U and L which would take O(n^3) 
// multiply U^-1 * L^-1 will tak O(n^3)
Matrix.prototype.LUInversion = function() {
    let [L,U] = this.LUDecomposition();
    return Matrix.InvertUpperTriangularMatrix(U).Multiply(Matrix.InvertLowerTriangularMatrix(L));
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

function Example1() {
    let mat = new Matrix(3,[2, -1, -2 ,
                 -4, 6, 3 ,
                 -4, -2, 8]);

    let [L,U] = mat.LUDecomposition();
    L.Print();
    U.Print();
}

function Example2() {
    let mat1 = new Matrix(2,[1, 1, 2, 2]);
    let mat2 = new Matrix(2,[1, 1, 2, 2]);

    mat1.Multiply(mat2).Print();
}

function Example3() {
    Matrix.InvertUpperTriangularMatrix(new Matrix(3,[2,-1,-2,0,4,-1,0,0,3])).Print()
}

function Example4() {
    let mat1 = new Matrix(5,[
        5,	7,	9,	4,   4,
        2,	4,	7,	1,	4,
        7,	9,	3,	1,	2,
        5,	6,	3,	6,	2,
        1,	4,	2,	5,	2
    ])
    let [L,U] = mat1.LUDecomposition()
    L.Print()
    Matrix.InvertLowerTriangularMatrix(L).Print()
}

function Example5() {
    let mat = new Matrix(3,[2, -1, -2 ,
                 -4, 6, 3 ,
                 -4, -2, 8]);

    let [L,U] = mat.LUDecomposition();
    L.Print();
    Matrix.InvertLowerTriangularMatrix(L).Print()
}

function Example6() {
    let mat = new Matrix(3,[2, -1, -2 ,
                 -4, 6, 3 ,
                 -4, -2, 8]);
    mat.Print()
    mat.LUInversion().Print()
}
//Example1()
//Example2()
//Example3()
//Example4()
//Example5()
//Example6()
