EXEC = Lab11

all: $(EXEC)

$(EXEC): Lab11.cpp
	g++ Lab11.cpp -o $(EXEC).exe

clean:
	rm -rf *.exe