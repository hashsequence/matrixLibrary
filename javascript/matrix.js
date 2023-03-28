function Row(arr) {
    this.arr = arr;
    this.n = arr.length
}

Row.prototype.DotProduct = function(b) {
    let result = 0
    for (let i = 0; i < this.arr.length; i++) {
        result += this.arr[i] * b.arr[i];
    }
    return result;
}

Row.prototype.GetCell = function(i) {
    return this.arr[i];
}

Row.prototype.SetCell = function(i,val) {
    this.arr[i] = val;
}

Row.prototype.GetSize = function() {
    return this.n;
}

Row.prototype.Print = function() {
    let str = "\n"
    for (let i = 0; i < this.GetSize(); i++) {
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
    return this.arr[i*this.GetSize() + j];
}

Matrix.prototype.SetCell = function(i, j ,val) {
    this.arr[i*this.GetSize() + j] = val;
}
/*
    returns the ith(begins with 0) row as a Row object 
*/
Matrix.prototype.GetRow = function(i) {
    let row = []
    for (let j = 0; j < this.GetSize(); j++) {
        row.push(this.arr[i*this.GetSize() + j]);
    }
    return new Row(row);
}

/*
    returns the jth(begins with 0) column as a Row object
*/
Matrix.prototype.GetCol = function(j) {
    let col = [];
    for (let i = 0; i < this.GetSize(); i++) {
        col.push(this.arr[i*this.GetSize() + j]);
    }
    return new Row(col);
}

Matrix.prototype.GetSize = function() {
    return this.n;
}

Matrix.prototype.Print = function() {
    let str = "\n"
    for (let i = 0; i < this.GetSize(); i++) {
      for (let j = 0; j < this.GetSize(); j++) {
        str += this.GetCell(i,j) + " , ";
      }
      str = str.substring(0,str.length-2) + "\n";
    }
    str =  str.substring(0,str.length-2) + "\n";
    console.log(str);
}

Matrix.prototype.ConvertTo2DArray = function() {
    let twoDArr = Array.apply(null,Array(this.GetSize())).map(Array.prototype.valueOf,[]);
    for (let i = 0; i < this.GetSize(); i++) {
        twoDArr[i] = Array.apply(null,Array(this.GetSize())).map(Number.prototype.valueOf,0);
    }
    
    for (let i = 0; i < this.GetSize(); i++) {
        for (let j = 0; j < this.GetSize(); j++) {
            twoDArr[i][j] = this.GetCell(i,j);
        }
    }
    return twoDArr;
}

Matrix.prototype.Multiply = function(B) {
    let result = new Matrix(this.GetSize(),Array.apply(null, Array(this.GetSize()*this.GetSize())).map(Number.prototype.valueOf,0));

    for (let i = 0; i < this.GetSize(); i++) {
        for (let j = 0; j < B.GetSize(); j++) {
            result.SetCell(i,j,this.GetRow(i).DotProduct(B.GetCol(j)))
        }
    }
    return result;
} 

Matrix.prototype.LUDecomposition = function() {
    let lower = new Matrix(this.GetSize());
    let upper = new Matrix(this.GetSize());
    
    for (let i = 0; i < this.GetSize(); i++) {
        //U: Upper Triangular Matrix
        for (let k = i; k < this.GetSize(); k++) {
            let sum = 0;
            for (let j = 0; j < i; j++) {
                sum += (lower.GetCell(i,j) * upper.GetCell(j,k));
            }
            upper.SetCell(i,k, this.GetCell(i,k) - sum);
        }

        //L: Lower Triangular Matrix
        for (let k = i; k < this.GetSize(); k++) {
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

//Inverse of an upper triangular matrix is upper triangular
//inverse of lower triangular matrix is lower triangular
//to compute the inverse of a triangular matrix,
//solve Ux = b for all [0,..,e_i,...0] where e_i = 1 for all 0<=i<n with backwards substitution
//solve Lx=b for all [0,..,e_i,...0] where e_i = 1 for all 0<=i<n with forward substitution

function invertUpperTriangularMatrix(M) {
    let result = new Matrix(M.GetSize())
    //create result matrix and intialize to identity matrix
    for (let i = 0; i < result.GetSize(); i++) {
        result.SetCell(i,i,1);
    }

    for (let i = 0; i < result.GetSize(); i++) {
        let x = new Row(Array.apply(null, Array(M.GetSize())).map(Number.prototype.valueOf,0));
        for (let j = result.GetSize()-1; j >= 0; j--) {
            if (j == result.GetSize()-1) {
                result.SetCell(j,i,result.GetCell(j,i)/M.GetCell(j,j));
            } else {
                let sum = 0;
                for (let k = result.GetSize()-1; k > j; k--) {
                    sum += result.GetCell(k,i) * M.GetCell(j,k);
                }
                result.SetCell(j,i,(result.GetCell(j,i)-sum)/M.GetCell(j,j));
            }           
        }
    }
    return result;
}

function invertLowerTriangularMatrix(M) {

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
    invertUpperTriangularMatrix(new Matrix(3,[2,-1,-2,0,4,-1,0,0,3])).Print()
}

//Example1()
//Example2()
Example3()