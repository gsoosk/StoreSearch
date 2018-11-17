all : fileDir Worker Search 

fileDir:
	@mkdir -p build
	@mkdir -p bin
# Worker : 
Worker : build/WorkerMain.o build/Worker.o build/Tools.o
	g++ build/WorkerMain.o build/Worker.o build/Tools.o -o bin/Worker
	@echo "Worker executable file maked!"

build/WorkerMain.o : src/WorkerMain.cpp src/Worker.cpp src/Worker.h
	g++ -c src/WorkerMain.cpp -o build/WorkerMain.o

build/Worker.o :  src/Worker.cpp src/Worker.h
	g++ -c src/Worker.cpp -o build/Worker.o

# LoadBalancer
Search :  build/Main.o build/LoadBalancer.o build/Tools.o
	@echo "Linking..."

	g++ build/Main.o build/LoadBalancer.o build/Tools.o -o  Search

build/Main.o : src/Main.cpp src/LoadBalancer.h src/LoadBalancer.cpp
	g++ -c src/Main.cpp -o build/Main.o

build/Tools.o : src/Tools.cpp src/Tools.h
	g++ -c src/Tools.cpp -o build/Tools.o

build/LoadBalancer.o : src/LoadBalancer.cpp src/LoadBalancer.h
	g++ -c src/LoadBalancer.cpp -o build/LoadBalancer.o

clean : 
	rm -f build/*.o
	rm -f bin/Worker
	rm -f Search
