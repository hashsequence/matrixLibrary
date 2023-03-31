clean: 
	rm -rf test_matrix.exe test_matrixFractions.exe bench_matrix.exe bench_matrixFractions.exe

post-clean:
	rm -rf test_matrix.exe test_matrixFractions.exe bench_matrix.exe bench_matrixFractions.exe

build-test-matrix: clean
	g++ -o test_matrix.exe matrix.h matrix.cpp test_matrix.cpp

build-test-matrix-fractions: clean
	g++ -o test_matrixFractions.exe matrixFractions.h matrixFractions.cpp test_matrixFractions.cpp

run-test-matrix: 
	./test_matrix.exe

run-test-matrix-fractions:
	./test_matrixFractions.exe

test-matrix: clean build-test-matrix run-test-matrix post-clean

test-matrix-fractions: clean build-test-matrix-fractions run-test-matrix-fractions post-clean

build-bench-matrix: 
	g++ bench_matrix.cc -isystem benchmark/include  -Lbenchmark/build/src -lbenchmark -lpthread -o bench_matrix.exe

build-bench-matrix-fractions: 
	g++ bench_matrixFractions.cc -isystem benchmark/include  -Lbenchmark/build/src -lbenchmark -lpthread -o bench_matrixFractions.exe

run-bench-matrix: 
	./bench_matrix.exe

run-bench-matrix-fractions: 
	./bench_matrixFractions.exe


bench-matrix : clean build-bench-matrix run-bench-matrix post-clean

bench-matrix-fractions : clean build-bench-matrix-fractions run-bench-matrix-fractions post-clean

test-all: test-matrix test-matrix-fractions

bench-all: bench-matrix bench-matrix-fractions
