function Row(arr) {
    this.arr = arr;
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

function Matrix(n, arr=null) {
    this.n = n; //row/col size n
    if (typeof arr === 'undefined' || arr == null) {
        this.arr = Array.apply(null, Array(n*n)).map(Number.prototype.valueOf,0); //internal 1-D array
    } else {
        this.arr = arr; //internal 1-D array
    }
}

Matrix.prototype.GetCell = function(i,j) {
    return this.arr[i*this.n + j];
}

Matrix.prototype.SetCell = function(i, j ,val) {
    this.arr[i*this.n + j] = val;
}
/*
    returns the ith(begins with 0) row as a Row object 
*/
Matrix.prototype.GetRow = function(i) {
    let row = []
    for (let j = 0; j < this.n; j++) {
        row.push(this.arr[i*this.n + j]);
    }
    return new Row(row);
}

/*
    returns the jth(begins with 0) column as a Row object
*/
Matrix.prototype.GetCol = function(j) {
    let col = [];
    for (let i = 0; i < this.n; i++) {
        col.push(this.arr[i*this.n + j]);
    }
    return new Row(col);
}

Matrix.prototype.Print = function() {
    let str = "\n"
    for (let i = 0; i < this.n; i++) {
      for (let j = 0; j < this.n; j++) {
        str += this.GetCell(i,j) + ",";
      }
      str = str.substring(0,str.length-1) + "\n";
    }
    str =  str.substring(0,str.length-1) + "\n";
    console.log(str);
}

Matrix.prototype.ConvertTo2DArray = function() {
    let twoDArr = Array.apply(null,Array(this.n)).map(Array.prototype.valueOf,[]);
    for (let i = 0; i < this.n; i++) {
        twoDArr[i] = Array.apply(null,Array(this.n)).map(Number.prototype.valueOf,0);
    }
    
    for (let i = 0; i < this.n; i++) {
        for (let j = 0; j < this.n; j++) {
            twoDArr[i][j] = this.GetCell(i,j);
        }
    }
    return twoDArr;
}

Matrix.prototype.Multiply = function(B) {
    let result = new Matrix(this.n,Array.apply(null, Array(this.n*this.n)).map(Number.prototype.valueOf,0));

    for (let i = 0; i < this.n; i++) {
        for (let j = 0; j < B.n; j++) {
            result.SetCell(i,j,this.GetRow(i).DotProduct(B.GetCol(j)))
        }
    }
    return result;
} 

Matrix.prototype.LUDecomposition = function() {
    let lower = new Matrix(this.n);
    let upper = new Matrix(this.n);
    
    for (let i = 0; i < this.n; i++) {
        //U: Upper Triangular Matrix
        for (let k = i; k < this.n; k++) {
            let sum = 0;
            for (let j = 0; j < i; j++) {
                sum += (lower.GetCell(i,j) * upper.GetCell(j,k));
            }
            upper.SetCell(i,k, this.GetCell(i,k) - sum);
        }

        //L: Lower Triangular Matrix
        for (let k = i; k < this.n; k++) {
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

Example1()
Example2()