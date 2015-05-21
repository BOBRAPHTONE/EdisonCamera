#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
 
int main() {
 
	int run = 1;
    // Image
     IplImage *image;
    // Capture vidéo
    CvCapture *capture;
 
    capture = cvCreateCameraCapture(CV_CAP_ANY);
 
    // Vérifier si l'ouverture du flux est ok
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
 
 
       // waiting 100ms
	   usleep(100);
 
    }
 
    cvReleaseCapture(&capture);
 
    return 0;
 
}