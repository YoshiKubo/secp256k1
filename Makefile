build:
	g++ -std=c++17 -c math_tools.cpp -o math_tools.o
	g++ -std=c++17 -c ec_group.cpp -o ec_group.o
	g++ -std=c++17 -c field_element.cpp -o field_element.o
	g++ -std=c++17 -c ec_element.cpp -o ec_element.o
	g++ -std=c++17 -c exception.cpp -o exception.o
	g++ -std=c++17 -c secp256k1.cpp -o secp256k1.o

test:
	g++ -std=c++17 -c test.cpp -o test.o
	g++ -std=c++17 -o test.exe math_tools.o ec_group.o field_element.o ec_element.o exception.o secp256k1.o test.o
	./test.exe


clean:
	rm *.o *.exe
