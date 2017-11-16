all:
	g++ -std=c++11 -Wall -O3 prediction.cpp -lpython3.5m -L/usr/include/python3.5m/ -I/usr/include/python3.5m/ -o pred_test
clean:
	rm pred_test
