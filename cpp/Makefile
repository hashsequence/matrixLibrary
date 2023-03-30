clean: 
	rm -rf test_matrix.exe test_matrixFractions.exe

post-clean:
	rm -rf test_matrix.exe test_matrixFractions.exe

build-test-matrix: clean
	g++ -o test_matrix.exe matrix.h matrix.cpp test_matrix.cpp

build-test-matrix-fractions: clean
	g++ -o test_matrixFractions.exe matrixFractions.h matrixFractions.cpp test_matrixFractions.cpp

test-matrix: 
	./test_matrix.exe

test-matrix-fractions:
	./test_matrixFractions.exe

run-test-matrix: clean build-test-matrix test-matrix post-clean

run-test-matrix-fractions: clean build-test-matrix-fractions test-matrix-fractions post-clean