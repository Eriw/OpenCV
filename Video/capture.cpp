#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat meanImage, stdDev;
double convSpeed;
double confAmp;

int conv_speed = 10;
int const max_speed = 100;
int conf_amp = 5;
int const max_amp = 10;
/**  @function Erosion  */
void changeSpeed( int, void* )
{
	convSpeed = 1.0 - ((double)conv_speed)/100.0;
}

void changeAmp( int, void* )
{
	confAmp = (double)conf_amp;
}

void initConfig(){
	/// Create Erosion Trackbar
	
	convSpeed = 0.9;
	confAmp = 5.0;

	createTrackbar( "Speed:\n", "Settings",
				&conv_speed, max_speed,
				changeSpeed );
				
	createTrackbar( "Amplitude:\n", "Settings",
				&conf_amp, max_amp,
				changeAmp );
}

Mat processImage(Mat image)
{
	//resize(img,img,Size(),0.5,0.5);
	
	uchar pixValue = 100;
	for (int i = 0; i < image.cols; i++) {
	    for (int j = 0; j < image.rows; j++) {
	        Vec3b &intensity = image.at<Vec3b>(j, i);
	        Vec3b &intensityMean = meanImage.at<Vec3b>(j, i);
	        Vec3b &intensityDev = stdDev.at<Vec3b>(j, i);
	        
	        for(int k = 0; k < image.channels(); k++) {
	            // calculate pixValue
	            intensityMean.val[k] = intensityMean.val[k]*convSpeed + (1-convSpeed)*intensity.val[k];
	            double diff = intensity.val[k] - intensityMean.val[k];
	            intensityDev.val[k] = intensityDev.val[k]*convSpeed + (1-convSpeed)*abs(diff);
	            
	            diff *= confAmp;
	            
	            double thresh = 50.0;
	            if(abs(diff) > thresh) diff = 0;
	           
	           	if(intensity.val[k] + diff < 0 || intensity.val[k] + diff > 255) break;
	            /*
	            if(diff > 0)
	            	intensity.val[k] = diff;
	            else
	            	intensity.val[k] = -diff;*/
	           	
	           	
	            intensity.val[k] += diff;	
	            	
	            //if(k < 2) intensity.val[k] -= diff;
	        }
	     }
	}
	
	imshow("Mean", stdDev);
	
	
	return image;
}

int main(int argc, char* argv[])
{
    Mat frame,result;
    
    namedWindow("Mean",CV_WINDOW_AUTOSIZE);
    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
    
    namedWindow("Settings",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
    
    initConfig();
	
    VideoCapture cap(0); // open the video camera no. 0

    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

   double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
   double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    cout << "Frame size : " << dWidth << " x " << dHeight << endl;
    
	
   	bool bSuccess = cap.read(frame); // read a new frame from video
   	frame.copyTo(meanImage);
   	frame.copyTo(stdDev);

    while (1)
    {

        bool bSuccess = cap.read(frame); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }
        
        result = processImage(frame);

        imshow("MyVideo", result); //show the frame in "MyVideo" window

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
    }
    return 0;

}