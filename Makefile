all : Search 

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
	rm build/*.o
