#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BAUDRATE B115200 
#define MODEMDEVICE "/dev/ttyUSB0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

FILE *file;
int fileLen;
char *tmpbuffer;
void openport(void);
void readport(void);
void sendport(void);
int fd = 0;
struct termios oldtp, newtp;
char buffer[512];


IplImage* reseizeForCam(IplImage* source){
	IplImage *destination = cvCreateImage(cvSize(64, 32), source->depth, source->nChannels);


	cvResize(source, destination);

	return destination;
}



void openport(void)
{
	fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY | O_NDELAY);
	printf("Oviya %d\n", fd);
	if (fd <0)
	{
		perror(MODEMDEVICE);
	}

	fcntl(fd, F_SETFL, 0);
	tcgetattr(fd, &oldtp); /* save current serial port settings */
	// tcgetattr(fd,&newtp); /* save current serial port settings */
	bzero(&newtp, sizeof(newtp));
	// bzero(&oldtp, sizeof(oldtp));

	newtp.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;

	newtp.c_iflag = IGNPAR | ICRNL;

	newtp.c_oflag = 0;

	newtp.c_lflag = ICANON;

	newtp.c_cc[VINTR] = 0;     /* Ctrl-c */
	newtp.c_cc[VQUIT] = 0;     /* Ctrl-\ */
	newtp.c_cc[VERASE] = 0;     /* del */
	newtp.c_cc[VKILL] = 0;     /* @ */
	//newtp.c_cc[VEOF]     = 4;     /* Ctrl-d */
	newtp.c_cc[VEOF] = 0;     /* Ctrl-d */
	newtp.c_cc[VTIME] = 0;     /* inter-character timer unused */
	newtp.c_cc[VMIN] = 1;     /* blocking read until 1 character arrives */
	newtp.c_cc[VSWTC] = 0;     /* '\0' */
	newtp.c_cc[VSTART] = 0;     /* Ctrl-q */
	newtp.c_cc[VSTOP] = 0;     /* Ctrl-s */
	newtp.c_cc[VSUSP] = 0;     /* Ctrl-z */
	newtp.c_cc[VEOL] = 0;     /* '\0' */
	newtp.c_cc[VREPRINT] = 0;     /* Ctrl-r */
	newtp.c_cc[VDISCARD] = 0;     /* Ctrl-u */
	newtp.c_cc[VWERASE] = 0;     /* Ctrl-w */
	newtp.c_cc[VLNEXT] = 0;     /* Ctrl-v */
	newtp.c_cc[VEOL2] = 0;     /* '\0' */


	//     tcflush(fd, TCIFLUSH);
	//	tcsetattr(fd,TCSANOW,&newtp);
}


void closeport(void){
	close(fd);

}


void sendToSerial(char* text, int size){

	printf("Start send\n");

	int n;
	n = write(fd, text, size + 1);

	if (n < 0)
	{
		fputs("write() of bytes failed!\n", stderr);
	}
	else
	{
		printf("Image sent successfully %d\n", n);
	}
}


void sendImageToSerial(IplImage* image){
	int x, y;
	unsigned char b, g, r;
	int value;
	char textToSend[19];
	textToSend[0] = 'X';
	textToSend[3] = 'Y';
	textToSend[6] = 'R';
	textToSend[10] = 'G';
	textToSend[14] = 'B';
	textToSend[18] = '\0';

	for (y = 0; y < image->height; y++)
	{
		for (x = 0; x < image->width; x++)
		{
			value = image->widthStep * y + x * 3;
			b = image->imageData[value];
			g = image->imageData[value + 1];
			r = image->imageData[value + 2];

			textToSend[7] = (char)((int)r / 100);
			textToSend[8] = (char)((int)((r - (r / 100)) / 10));
			textToSend[9] = (char)((int)(r - (r / 100 - r / 10));

			textToSend[11] = (char)((int)g / 100);
			textToSend[12] = (char)((int)((g - (g / 100)) / 10));
			textToSend[13] = (char)((int)(g - (g / 100 - g / 10));

			textToSend[15] = (char)((int)b / 100);
			textToSend[16] = (char)((int)((b - (b / 100)) / 10));
			textToSend[17] = (char)((int)(b - (b / 100 - b / 10));

			sendToSerial(texToSend, 19);
		}
	}
}

int main() {
 
	openport();

	int run = 1;
    // Image
     IplImage *image;
    // Capture video
    CvCapture *capture;
 
    capture = cvCreateCameraCapture(CV_CAP_ANY);
 
    // Check if the video flux is open
    if (!capture) {
 
       printf("Can't open video !\n");
       return -1;
 
    }
	else
	{
		printf("Starting !\n");

	}
 
    while(run) {
 
       // getting image
       image = cvQueryFrame(capture);
	   int x, y;
	   unsigned char b, g, r;
	   int value;
	   int first = 1;
	   
 
	   IplImage *newImage = reseizeForCam(image);
	   first = 1;

	   sendImageToSerial(newImage);

	          // waiting 500ms
	   usleep(5000);
 
    }
 
    cvReleaseCapture(&capture);
 
    return 0;
 
}
