all : fileDir Worker Presenter Search 

fileDir:
	@mkdir -p build
	@mkdir -p bin
	@mkdir -p namedPipe
# Worker : 
Worker : build/WorkerMain.o build/Worker.o build/Tools.o
	@echo "Making worker executable file!"
	g++ build/WorkerMain.o build/Worker.o build/Tools.o -o bin/Worker
	
build/WorkerMain.o : src/WorkerMain.cpp src/Worker.cpp src/Worker.h
	g++ -c src/WorkerMain.cpp -o build/WorkerMain.o

build/Worker.o :  src/Worker.cpp src/Worker.h
	g++ -c src/Worker.cpp -o build/Worker.o

# Presenter :
Presenter : build/PresenterMain.o build/Presenter.o build/Tools.o
	@echo "Making Presenter executable file"
	g++ build/PresenterMain.o build/Presenter.o build/Tools.o -o bin/Presenter

build/PresenterMain.o : src/PresenterMain.cpp src/Presenter.cpp src/Presenter.h
	g++ -c src/PresenterMain.cpp -o build/PresenterMain.o 

build/Presenter.o :  src/Presenter.cpp src/Presenter.h
	g++ -c src/Presenter.cpp -o build/Presenter.o

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
	rm -f -r build
	rm -f -r bin
	rm -f -r namedPipe
	rm -f Search
