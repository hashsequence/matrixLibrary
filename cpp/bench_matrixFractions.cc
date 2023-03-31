#include "matrixFractions.h"
#include "matrixFractions.cpp"
#include <vector>
#include <iostream>
#include <benchmark/benchmark.h>


using namespace std;

static void BM_BenchMarkMatrixTemplateFractionLUInversion(benchmark::State& state) {
  for (auto _ : state) {
      vector<Fraction<int>> vec1{
       Fraction<int>(5),Fraction<int>(7),Fraction<int>(9),Fraction<int>(4),Fraction<int>(4),
       Fraction<int>(2),Fraction<int>(4),Fraction<int>(7),Fraction<int>(1),Fraction<int>(4),
       Fraction<int>(7),Fraction<int>(9),Fraction<int>(3),Fraction<int>(1),Fraction<int>(2),
       Fraction<int>(5),Fraction<int>(6),Fraction<int>(3),Fraction<int>(6),Fraction<int>(2),
       Fraction<int>(1),Fraction<int>(4),Fraction<int>(2),Fraction<int>(5),Fraction<int>(2),
       };
        Matrix<Fraction<int>> A(5,vec1);
        //A.Print();
        Matrix<Fraction<int>>* A_inverted = A.LUInversion();
        //A_inverted -> Print();
        delete A_inverted;
  }
}

static void BM_BenchMarkMatrixTemplateIntLUInversion(benchmark::State& state) {
  for (auto _ : state) {
      vector<int> vec1{
       5,7,9,4,4,
       2,4,7,1,4,
       7,9,3,1,2,
       5,6,3,6,2,
       1,4,2,5,2,
       };
        Matrix<int> A(5,vec1);
        //A.Print();
        Matrix<int>* A_inverted = A.LUInversion();
        //A_inverted -> Print();
        delete A_inverted;
  }
}

static void BM_BenchMarkMatrixTemplateDoubleLUInversion(benchmark::State& state) {
  for (auto _ : state) {
      vector<double> vec1{
       5,7,9,4,4,
       2,4,7,1,4,
       7,9,3,1,2,
       5,6,3,6,2,
       1,4,2,5,2,
       };
        Matrix<double> A(5,vec1);
        //A.Print();
        Matrix<double>* A_inverted = A.LUInversion();
        //A_inverted -> Print();
        delete A_inverted;
  }
}

BENCHMARK(BM_BenchMarkMatrixTemplateIntLUInversion)->Iterations(100000);
BENCHMARK(BM_BenchMarkMatrixTemplateDoubleLUInversion)->Iterations(100000);
BENCHMARK(BM_BenchMarkMatrixTemplateFractionLUInversion)->Iterations(100000);

BENCHMARK_MAIN();