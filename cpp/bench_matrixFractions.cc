#include "matrixFractions.h"
#include "matrixFractions.cpp"
#include <vector>
#include <iostream>
#include <benchmark/benchmark.h>


using namespace std;

static void BM_BenchMarkMatrixTemplateFractionLUInversionFiveXFive(benchmark::State& state) {
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

static void BM_BenchMarkMatrixTemplateIntLUInversionFiveXFive(benchmark::State& state) {
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

static void BM_BenchMarkMatrixTemplateDoubleLUInversionFiveXFive(benchmark::State& state) {
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

static void BM_BenchMarkMatrixTemplateFractionLUInversionTenXTen(benchmark::State& state) {
  for (auto _ : state) {
      vector<Fraction<int>> vec1{
        Fraction<int>(5),Fraction<int>(7),Fraction<int>(9),Fraction<int>(4),Fraction<int>(4), Fraction<int>(2),Fraction<int>(4),Fraction<int>(7),Fraction<int>(1),Fraction<int>(4),
        Fraction<int>(7),Fraction<int>(9),Fraction<int>(3),Fraction<int>(1),Fraction<int>(2),Fraction<int>(5),Fraction<int>(6),Fraction<int>(3),Fraction<int>(6),Fraction<int>(2),
        Fraction<int>(1),Fraction<int>(4),Fraction<int>(2),Fraction<int>(5),Fraction<int>(2),Fraction<int>(6),Fraction<int>(13),Fraction<int>(9),Fraction<int>(2),Fraction<int>(15),
        Fraction<int>(12),Fraction<int>(20),Fraction<int>(7,2),Fraction<int>(5,3),Fraction<int>(2,13),Fraction<int>(6,19),Fraction<int>(13,8),Fraction<int>(9,7),Fraction<int>(2,5),Fraction<int>(13,12),
        Fraction<int>(11,12),Fraction<int>(7,25),Fraction<int>(6,2),Fraction<int>(3,3),Fraction<int>(5,13),Fraction<int>(20,19),Fraction<int>(17,8),Fraction<int>(5,7),Fraction<int>(4,5),Fraction<int>(6,12),
        Fraction<int>(5,15),Fraction<int>(2,30),Fraction<int>(7,5),Fraction<int>(1,3),Fraction<int>(8,13),Fraction<int>(41,19),Fraction<int>(11,9),Fraction<int>(8,7),Fraction<int>(7,9),Fraction<int>(5,17),
        Fraction<int>(2,17),Fraction<int>(7,29),Fraction<int>(9,3),Fraction<int>(5,3),Fraction<int>(9,13),Fraction<int>(71,19),Fraction<int>(13,8),Fraction<int>(15,7),Fraction<int>(3,5),Fraction<int>(14,12),
        Fraction<int>(6,19),Fraction<int>(9,11),Fraction<int>(1,9),Fraction<int>(7,3),Fraction<int>(2,13),Fraction<int>(28,19),Fraction<int>(17,50),Fraction<int>(2,7),Fraction<int>(7,12),Fraction<int>(56,12),
        Fraction<int>(9,10),Fraction<int>(1,24),Fraction<int>(4,2),Fraction<int>(1,3),Fraction<int>(1,13),Fraction<int>(23,19),Fraction<int>(14,8),Fraction<int>(2,70),Fraction<int>(70,5),Fraction<int>(5,19),
        Fraction<int>(3,11),Fraction<int>(33,70),Fraction<int>(9,3),Fraction<int>(9,3),Fraction<int>(7,13),Fraction<int>(25,19),Fraction<int>(11,16),Fraction<int>(2,711),Fraction<int>(7,56),Fraction<int>(59,12)
       };
        Matrix<Fraction<int>> A(10,vec1);
        //A.Print();
        Matrix<Fraction<int>>* A_inverted = A.LUInversion();
        //A_inverted -> Print();
        delete A_inverted;
  }
}

BENCHMARK(BM_BenchMarkMatrixTemplateIntLUInversionFiveXFive)->Iterations(100000)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_BenchMarkMatrixTemplateDoubleLUInversionFiveXFive)->Iterations(100000)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_BenchMarkMatrixTemplateFractionLUInversionFiveXFive)->Iterations(100000)->Unit(benchmark::kMillisecond);

BENCHMARK(BM_BenchMarkMatrixTemplateIntLUInversionFiveXFive)->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_BenchMarkMatrixTemplateDoubleLUInversionFiveXFive)->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_BenchMarkMatrixTemplateFractionLUInversionFiveXFive)->Iterations(100)->Unit(benchmark::kMillisecond);


BENCHMARK(BM_BenchMarkMatrixTemplateIntLUInversionFiveXFive)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_BenchMarkMatrixTemplateDoubleLUInversionFiveXFive)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_BenchMarkMatrixTemplateFractionLUInversionFiveXFive)->Unit(benchmark::kMillisecond);

BENCHMARK(BM_BenchMarkMatrixTemplateFractionLUInversionTenXTen)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();