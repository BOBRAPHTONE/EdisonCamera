CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lm -lopencv_core -lopencv_imgproc -lopencv_highgui
SOURCES=EdisonCamera.c
EXECUTABLE=EdisonCamera

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) 
	$(CC) $(LDFLAGS) $(SOURCES) 