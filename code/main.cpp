#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <assert.h>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include "QOpenCVWidget.h"
#include "RogerController.h"

#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>

#define BUFSIZE (64)
#define DEVICE "/dev/ttyUSB0"


void delay(int ms) {
  struct timespec t;
  t.tv_sec = ms/1000;
  t.tv_nsec = (long)(ms%1000) * 1000000;
  nanosleep(&t, NULL);
}

void sendSerialCommand(int argc, char **argv) {
	int ser;
	
  int current_arg = 1;
  ser = open(DEVICE,O_RDWR);
  if (ser == -1)                                   error(EXIT_FAILURE,errno,"open of " DEVICE " failed");
  
	// setup serial port
	struct termios termsettings;
	  if (tcgetattr(ser, &termsettings) == -1)         error(EXIT_FAILURE,errno,"tcgetattr failed");
	  if (cfsetispeed(&termsettings, B57600) == -1)    error(EXIT_FAILURE,errno,"cfsetispeed failed");
	  if (cfsetospeed(&termsettings, B57600) == -1)    error(EXIT_FAILURE,errno,"cfsetospeed failed");;
	  cfmakeraw(&termsettings);
	  if (tcsetattr(ser, TCSANOW, &termsettings) == -1) error(EXIT_FAILURE,errno,"tcsetattr failed");;

  	while (current_arg < argc) {
		switch(argv[current_arg][0]) {
			case 'p' :
				if (tcdrain(ser) == -1 )                  error(EXIT_FAILURE,errno,"tcdrain failed");
		         delay(atoi(argv[current_arg]+1));
			break;
		
			default :
			{
				unsigned char outbyte = (unsigned char)atoi(argv[current_arg]);
			   	if (write(ser,&outbyte,1) != 1)         error(EXIT_FAILURE,errno,"write failed");
			}
			break;
		
		}
		
		current_arg = current_arg + 1;
	}
 
    if (close(ser) == -1)                          error(EXIT_FAILURE,errno,"close failed");;
}



int main(int argc, char **argv) {
	
	sendSerialCommand(argc, argv);
	
    CvCapture * camera = cvCreateCameraCapture(0);
    assert(camera);
    IplImage * image=cvQueryFrame(camera);
    assert(image);

    printf("Image depth=%i\n", image->depth);
    printf("Image nChannels=%i\n", image->nChannels);

    QApplication app(argc, argv);
    RogerController *mainWin = new RogerController(camera);
    mainWin->setWindowTitle("RogerCam");
    mainWin->show();    
    int retval = app.exec();
    
    cvReleaseCapture(&camera);
    
    return retval;
}