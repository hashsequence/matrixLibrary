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
PA = LU --> A = P<sup>-1</sup>LU  --> A = PLU --> A<sup>-1</sup>=(PLU)<sup>-1</sup> --> A<sup>-1</sup> = U<sup>-1</sup>L<sup>-1</sup>P<sup>-1</sup>

The reason why we are using a P matrix to swap rows is that LU Decomposition can fail if the top-left entry of a matrix A is 0, thus with partial swapping we 
can rearrange the rows so the larger elements are on the diagonals.

The time complexity is O(N<sup>3</sup>) 

For LU Decomposition I used [Doolittle's Algorithm](https://en.wikipedia.org/wiki/LU_decomposition#Doolittle_algorithm)
Partial Pivoting is O(N<sup>2</sup>)

The inverse of P is P<sup>T</P> and so Transpose is O(N^<sup>2</sup>)
and I can solve the inverses of U and L by: 

1. solving Ux = b for all [0,..,e_i,...0] where e<sub>i</sub> = 1 for all 0<=i<n with backwards substitution
2. solving Lx=b for all [0,..,e_i,...0] where e<sub>i</sub> = 1 for all 0<=i<n with forward substitution

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
This is the results of the benchmarks for C++ and JavaScript libraries for LU Inversion with a 5x5 matrix:

### C++
```console
foo@bar:~/matrixLibrary/cpp$ make bench-all
rm -rf test_matrix.exe test_matrixFractions.exe bench_matrix.exe bench_matrixFractions.exe
g++ bench_matrix.cc -isystem benchmark/include  -Lbenchmark/build/src -lbenchmark -lpthread -o bench_matrix.exe
./bench_matrix.exe
2023-03-31T14:11:08-07:00
Running ./bench_matrix.exe
Run on (12 X 2592 MHz CPU s)
Load Average: 0.52, 0.58, 0.59
------------------------------------------------------------------------------------------
Benchmark                                                Time             CPU   Iterations
------------------------------------------------------------------------------------------
BM_BenchMarkLUInversionDouble/iterations:100000      0.100 ms        0.100 ms       100000
BM_BenchMarkLUInversionDouble/iterations:100         0.101 ms        0.156 ms          100
BM_BenchMarkLUInversionDouble                        0.102 ms        0.103 ms         7467
rm -rf test_matrix.exe test_matrixFractions.exe bench_matrix.exe bench_matrixFractions.exe
g++ bench_matrixFractions.cc -isystem benchmark/include  -Lbenchmark/build/src -lbenchmark -lpthread -o bench_matrixFractions.exe
./bench_matrixFractions.exe
2023-03-31T14:11:20-07:00
Running ./bench_matrixFractions.exe
Run on (12 X 2592 MHz CPU s)
Load Average: 0.52, 0.58, 0.59
----------------------------------------------------------------------------------------------------------
Benchmark                                                                Time             CPU   Iterations
----------------------------------------------------------------------------------------------------------
BM_BenchMarkMatrixTemplateIntLUInversion/iterations:100000           0.101 ms        0.101 ms       100000
BM_BenchMarkMatrixTemplateDoubleLUInversion/iterations:100000        0.103 ms        0.103 ms       100000
BM_BenchMarkMatrixTemplateFractionLUInversion/iterations:100000      0.232 ms        0.231 ms       100000
BM_BenchMarkMatrixTemplateIntLUInversion/iterations:100              0.122 ms        0.156 ms          100
BM_BenchMarkMatrixTemplateDoubleLUInversion/iterations:100           0.234 ms        0.312 ms          100
BM_BenchMarkMatrixTemplateFractionLUInversion/iterations:100         0.422 ms        0.312 ms          100
BM_BenchMarkMatrixTemplateIntLUInversion                             0.120 ms        0.120 ms         6400
BM_BenchMarkMatrixTemplateDoubleLUInversion                          0.113 ms        0.112 ms         6400
BM_BenchMarkMatrixTemplateFractionLUInversion                        0.229 ms        0.230 ms         2987
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

 PASS  ./matrix.bench.js (7.114 s)
 PASS  ./matrixFractions.bench.js (12.902 s)
Benchmarks:
  Matrix
    inverting 5x5 Matrix of Numbers   0.015 ms ±  2.25 %  (90 runs sampled)
  Matrix using custom Fractions Class instead of Numbers
    inverting 5x5 Matrix of Numbers     0.439 ms ±  2.38 %  (89 runs sampled)
    inverting 5x5 Matrix of Fractions   0.443 ms ±  1.65 %  (80 runs sampled)

Test Suites: 2 passed, 2 total
Tests:       3 passed, 3 total
Snapshots:   0 total
Time:        13.401 s, estimated 14 s
Ran all test suites.
```

### Discussion

For my basic matrix class 

It looks like LUInversion for a Javascript implementation of Matrix of numbers is around .015 ms as oppose to the C++ implementation which is around .100 ms
thus javascript Matrix class for LUInversion is 6 times faster than C++

For my Matrix of Fraction Class

For C++ I implemented a template for Matrix that support double,int, Fraction\<int\> and for Javascript I implemented a Matrix of Fractions or another custom class that implements the same methods of my Fraction class. My Javascript class ran LUInversion at around .439 ms, and my C++ implementation ran LUInversion for around
double, int, Fraction\<int\> .120 ms, 113 ms, and .229 ms, so my Matrix of a Fraction class for C++ is twice as fast as my JavaScript class.

I reason that the basic matrix class for JavaScript was faster due to the way the node engine optimizes and transform my javascript code to an intermediate form which allows the performance close to C, and since in the basic Matrix Class I was working with floating point primitive types it could be the V8 is optimizing floating point arithmetic whenever possible.

For my Matrix of Fraction class, the result to seems make more sense, perhaps because building a custom data type(Fractions) with custom operations does not allow any optimizations to happen, and thus are more comparable. The overhead of javascript being transformed via node is causing the 2x slowness.
