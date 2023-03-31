#include "matrixFractions.h"
#include "matrixFractions.cpp"
#include <vector>
#include <iostream>
#include <benchmark/benchmark.h>


using namespace std;

static void BM_BenchMarkLUInversion(benchmark::State& state) {
  std::string x = "hello";
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

BENCHMARK(BM_BenchMarkLUInversion)->Iterations(10000);

BENCHMARK_MAIN();