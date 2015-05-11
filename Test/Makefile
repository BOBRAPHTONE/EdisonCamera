CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lm -lopencv_core -lopencv_imgproc -lopencv_highgui
SOURCES=CameraTest.c
EXECUTABLE=CameraTest

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) 
	$(CC) $(LDFLAGS) $(SOURCES) 