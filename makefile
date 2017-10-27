CC=g++
Deps= main.cpp Matrix.cpp Parser.cpp
OutputName=output.exe

test: $(Deps)
	$(CC) $(Deps) -o $(OutputName)
	./$(OutputName)
	
build: $(Deps)
	$(CC) $(Deps) -o $(OutputName)

run: $(OutputName)
	./$(OutputName)
