CC=g++
Deps= main.cpp Matrix.cpp Parser.cpp
OutputName=g16mathlab
	
build: $(Deps) #first make command to build 
	$(CC) $(Deps) -o $(OutputName)

run: $(OutputName)
	./$(OutputName)
