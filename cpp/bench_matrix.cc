#include "matrix.h"
#include "matrix.cpp"
#include <vector>
#include <iostream>
#include <benchmark/benchmark.h>


using namespace std;

static void BM_BenchMarkLUInversionDouble(benchmark::State& state) {
  for (auto _ : state) {
      vector<double> vec1{
       5,	7,	9,	4,   4,
       2,	4,	7,	1,	4,
       7,	9,	3,	1,	2,
       5,	6,	3,	6,	2,
       1,	4,	2,	5,	2
       };
        Matrix A(5,vec1);
        //A.Print();
        Matrix* A_inverted = A.LUInversion();
        //A_inverted -> Print();
        delete A_inverted;
  }
}

BENCHMARK(BM_BenchMarkLUInversionDouble)->Iterations(100000)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_BenchMarkLUInversionDouble)->Iterations(100)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_BenchMarkLUInversionDouble)->Unit(benchmark::kMillisecond);
BENCHMARK_MAIN();