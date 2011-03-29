#ifndef ROGERCONTROLLER_H_
#define ROGERCONTROLLER_H_

#include <QWidget>
#include <QVBoxLayout>
#include "QOpenCVWidget.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>


class RogerController : public QWidget
{
    Q_OBJECT
    private:
		QOpenCVWidget *cvwidget;
		CvCapture *camera;
        
    public:
		RogerController(CvCapture *cam, QWidget *parent=0);
 		
    protected:
		void timerEvent(QTimerEvent*);  
		void cameraInput();
};


#endif /*ROGERCONTROLLER_H_*/