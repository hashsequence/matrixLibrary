clean: 
	rm -rf test_matrix.exe

post-clean:
	rm -rf test_matrix.exe 
build-test: clean
	g++ -o test_matrix.exe matrix.h matrix.cpp test_matrix.cpp

test: 
	./test_matrix.exe

run-test: clean build-test test post-clean