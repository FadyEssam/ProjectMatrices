CC=g++
Deps= main.cpp Matrix.cpp
OutputName=output.exe

build: $(Deps)
	$(CC) $(Deps) -o $(OutputName)

run: $(OutputName)
	./$(OutputName)
