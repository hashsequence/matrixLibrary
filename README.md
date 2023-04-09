# Matrix Library Javascript vs. C++

Comparison of LU Inversion of Matrix class implementation in JavaScript and C++ 

[javascript](javascript/)

[cpp](cpp/)

## Summary

This project is to compare the performance of a Matrix Class implementation in C++ and Javascript that can work with standard numeric data types such as int and doubles as well as custom data classes. We will be implementing LU Inversion of a matrix and comparing the performance of the Matrix library with standard data types as well as with custom Classes.

## Requirements

* Both C++ and Javascript Implementations will implement a Matrix class and a LUInversion() method to invert an invertible matrix A by LU decomposing it into L U, invert them, and take the product U<sup>-1</sup> * L<sup>-1</sup> to get A<sup>-1</sup>. 

* Test and benchmark the C++ and Javascript Matrix Libraries for LUInversion()

* Implement Fractions Class as the sample custom class and allow the instantiation of a Matrix of fractions

### Bonus

* Implement other Matrix operations such as Determinants

## Design Document

### Limitations And Scope

Since the purpose of this project is to compare the same algorithmic calculation (LU Inversion), the project will only focus on performing the operation on a already invertible matrix and comparing the performance between C++ and javascript implementations of a self-implemented LU Inversion algorithm. 

### Mathematical Analysis

The inverse of a Matrix is usually defined as 

A * A<sup>-1</sup> = I where A has to a square matrix so nxn and the determinant of A is 0

There are multiple ways of calculating Inverses of matrix, but I will be using LU Decomposition with partial row swapping, so

Let A be an invertible matrix.
Let P be a permutation Matrix (a permutation matrix is a square matrix with a 1 in each row and column)
Let L be a lower diagonal matrix
Let U be a upper diagonal matrix

so we get PA = LU, we can then so matrix algebra:
PA = LU --> A = P<sup>-1</sup>LU  --> A = P<sup>T</sup>LU --> A<sup>-1</sup>=(P<sup>T</sup>LU)<sup>-1</sup> --> A<sup>-1</sup> = U<sup>-1</sup>L<sup>-1</sup>(P<sup>T</sup>)<sup>-1</sup> = U<sup>-1</sup>L<sup>-1</sup>P because P<sup>T</sup> = P<sup>-1</sup>

The reason why we are using a P matrix to swap rows is that LU Decomposition can fail if the top-left entry of a matrix A is 0, thus with partial swapping we 
can rearrange the rows so the larger elements are on the diagonals.

for LU Decomposition I used [Doolittle's Algorithm](https://en.wikipedia.org/wiki/LU_decomposition#Doolittle_algorithm) which has a time complexity of O(N<sup>3</sup>) where N is the number of rows/columns.

Partial Pivoting would be O(N<sup>2</sup>).

The inverse of P is P<sup>T</P> and so Transpose is O(N<sup>2</sup>)
and I can solve the inverses of U and L by:

1. solving Ux = b for all [0,..,e_i,...0] where e<sub>i</sub> = 1 for all 0<=i<n with backwards substitution
2. solving Lx=b for all [0,..,e_i,...0] where e<sub>i</sub> = 1 for all 0<=i<n with forward substitution

which would be O(N<sup>3</sup>).

Matrix multiplication of U<sup>-1</sup>L<sup>-1</sup>P would be O(N<sup>3</sup>).

Total time complexity would be O(N<sup>3</sup>).

### Class and Methods

For the both C++ and JavaScript libraries I made versions of the Matrix Library

1. matrix
    * standard matrix of floating point numbers
    
2. matrixFractions
    * matrix of custom class Fractions, with basic arithmetic and comparison operators


Here is the basic structure of the libraries in psuedo-code:

    Class Fraction {
        var numerator;
        var denomiator;
    }
                                                                               
    Class Row {
        var Fractions[] arr;
        DotProduct();
    }

    Class Matrix {
        Fractions[] arr
        LUinversion()  
        Determinant();
        Transpose();
        Multiply();
    }

## Benchmarking LU inverions with partial row swapping

For benching I used google/bench for the c++ library and jest-bench for javascript.

jest-bench and google benchmarks will run each test until they reach a stable average rate per run
This is the results of the benchmarks for C++ and JavaScript libraries for LU Inversion with a 5x5 matrix and for fractions I also tested with an additional 10x10 matrix:

### C++

```console
foo@bar:~/matrixLibrary/cpp$ make bench-all
rm -rf test_matrix.exe test_matrixFractions.exe bench_matrix.exe bench_matrixFractions.exe
g++ bench_matrix.cc -isystem benchmark/include  -Lbenchmark/build/src -lbenchmark -lpthread -o bench_matrix.exe
./bench_matrix.exe
2023-04-03T19:09:58-07:00
Running ./bench_matrix.exe
Run on (12 X 2592 MHz CPU s)
Load Average: 0.52, 0.58, 0.59
------------------------------------------------------------------------------------------
Benchmark                                                Time             CPU   Iterations
------------------------------------------------------------------------------------------
BM_BenchMarkLUInversionDouble/iterations:100000      0.197 ms        0.188 ms       100000
BM_BenchMarkLUInversionDouble/iterations:100         0.282 ms        0.312 ms          100
BM_BenchMarkLUInversionDouble                        0.283 ms        0.285 ms         2635
rm -rf test_matrix.exe test_matrixFractions.exe bench_matrix.exe bench_matrixFractions.exe
g++ bench_matrixFractions.cc -isystem benchmark/include  -Lbenchmark/build/src -lbenchmark -lpthread -o bench_matrixFractions.exe
./bench_matrixFractions.exe
2023-04-03T19:10:21-07:00
Running ./bench_matrixFractions.exe
Run on (12 X 2592 MHz CPU s)
Load Average: 0.52, 0.58, 0.59
-------------------------------------------------------------------------------------------------------------------
Benchmark                                                                         Time             CPU   Iterations
-------------------------------------------------------------------------------------------------------------------
BM_BenchMarkMatrixTemplateIntLUInversionFiveXFive/iterations:100000           0.206 ms        0.200 ms       100000
BM_BenchMarkMatrixTemplateDoubleLUInversionFiveXFive/iterations:100000        0.286 ms        0.282 ms       100000
BM_BenchMarkMatrixTemplateFractionLUInversionFiveXFive/iterations:100000      0.593 ms        0.568 ms       100000
BM_BenchMarkMatrixTemplateIntLUInversionFiveXFive/iterations:100              0.297 ms        0.156 ms          100
BM_BenchMarkMatrixTemplateDoubleLUInversionFiveXFive/iterations:100           0.331 ms        0.312 ms          100
BM_BenchMarkMatrixTemplateFractionLUInversionFiveXFive/iterations:100         0.642 ms        0.625 ms          100
BM_BenchMarkMatrixTemplateIntLUInversionFiveXFive                             0.298 ms        0.298 ms         2358
BM_BenchMarkMatrixTemplateDoubleLUInversionFiveXFive                          0.312 ms        0.314 ms         2240
BM_BenchMarkMatrixTemplateFractionLUInversionFiveXFive                        0.655 ms        0.642 ms         1120
BM_BenchMarkMatrixTemplateFractionLUInversionTenXTen                           7.31 ms         7.29 ms           90

```

### JavaScript

```console
foo@bar:~/matrixLibrary/javascript$ npm run bench

> matrixlibrary@1.0.0 bench
> jest --projects jest-bench.config.json

● Validation Warning:

  Unknown option "reporters" with value ["default", "jest-bench/reporter"] was found.
  This is probably a typing mistake. Fixing it will remove this message.

  Configuration Documentation:
  https://jestjs.io/docs/configuration

 PASS  ./matrix.bench.js (7.057 s)
 PASS  ./matrixFractions.bench.js (18.739 s)
Benchmarks:
  Matrix
    inverting 5x5 Matrix of Numbers   0.040 ms ±  18.42 %  (36 runs sampled)
  Matrix using custom Fractions Class instead of Numbers
    inverting 5x5 Matrix of Numbers        1.15 ms ±  17.58 %  (35 runs sampled)
    inverting 5x5 Matrix of Fractions      1.13 ms ±   2.25 %  (79 runs sampled)
    inverting 10x10 Matrix of Fractions   12.08 ms ±   2.13 %  (66 runs sampled)

Test Suites: 2 passed, 2 total
Tests:       4 passed, 4 total
Snapshots:   0 total
Time:        19.468 s
Ran all test suites.

```

### Discussion

For my basic matrix class 

It looks like LUInversion for a Javascript implementation of Matrix of numbers is around 0.040 ms as oppose to the C++ implementation which is around .280 ms
thus javascript Matrix class for LUInversion is 7 times faster than C++

For my matrix of fractions class

For C++ I implemented a template for Matrix that support double,int, Fraction\<int\> and for Javascript I implemented a Matrix of Fractions or another custom class that implements the same methods of my Fraction class. My Javascript class ran LUInversion for fractions for a 5x5 at around 1.13 ms, and my C++ implementation ran LUInversion for the same 5x5 for double, int, Fraction\<int\> at around .298, .312 ms, and .655 ms respectively, so my Matrix of a Fraction class for C++ is almost twice as fast as my JavaScript class for fractions (1.13 ms for javascript and .655 ms for C++). For the 10x10 matrix of fractions, my C++ version was 7.31 ms and my javascript version was 12.08 ms, so it is also the ratio of (speed of C++)/(speed of Javascript) is still roughly almost 2.

I reason that the basic matrix class for JavaScript was faster due to the way the node engine optimizes and transform my javascript code to an intermediate form which allows the performance close to C, and since in the basic Matrix Class I was working with floating point primitive types it could be the V8 is optimizing floating point arithmetic whenever possible. (EDIT: the real reason why C++ as slower because I am wrapping operations in Get and Set Methos instead of referencing the array directly using indcies, javascript will optimize this for you, but in C++ it won't, unless perhaps we use the optimization flags when compiling C++ programs)

For matrix of fractions class, the result to seems make more sense with Javascript being twice as slow as C++. Perhaps the reason is because building a custom data type(Fractions) with custom operations does not allow for any special floating-point arithmetic optimzations to happen or least to a staggering extent, and thus are more comparable, and the overhead of javascript executed at runtime versus C++ being compiled would then be the main probable cause for why javascript is usually always slower than C++.
