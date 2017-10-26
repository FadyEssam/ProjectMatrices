CC=g++
Deps= main.cpp Matrix.cpp Parser.cpp
OutputName=output.exe

build: $(Deps)
	$(CC) $(Deps) -o $(OutputName)

run: $(OutputName)
	./$(OutputName)
