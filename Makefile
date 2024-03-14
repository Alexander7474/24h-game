CC = g++
#comment this if you are on macOS
CFLAGS = -std=c++11 -Wall -I/usr/include/freetype2
LIBS = -lbbop -lglfw -lGLEW -lGL -lfreetype 

#Uncomment if you use macOS or if you are gay
#CFLAGS = -std=c++11 -Wall -I/opt/homebrew/Cellar/freetype/2.13.2/include/freetype2 -I/opt/homebrew/Cellar/glew/2.2.0_1/include -I/usr/local/include/GLFW
#LIBS = -L/opt/homebrew/Cellar/freetype/2.13.2/lib -L/opt/homebrew/Cellar/glew/2.2.0_1/lib -framework Cocoa -framework OpenGL -framework IOKit -lfreetype -lglfw3 -lGLEW.2.2.0

SRCS = main.cpp src/Car.cpp

OBJS = $(SRCS:.cpp=.o) 

all: final

final: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f final $(OBJS)
