#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat loadImg(String str){
	
	Mat mat = imread(str);

	return mat;
}

void createWindow(){

	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	namedWindow("Settings", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"

}

void showImage(Mat img){
	imshow("MyWindow", img); //display the image which is stored in the 'img' in the "MyWindow" window
}


/// Global variables
Mat src, dst;

int image_size = 100;
int const max_size = 250;
/**  @function Erosion  */
void resizeImage( int, void* )
{
	
	double size = ((double)image_size + 1.0)/100.0;

	/// Apply the erosion operation
	resize( src, dst, Size(), size, size);
	imshow( "MyWindow", dst );
}

void initResize(){
	/// Create Erosion Trackbar

	createTrackbar( "Size:\n", "Settings",
				&image_size, max_size,
				resizeImage );
}

int main( int argc, const char** argv )
{
	
	src = loadImg("img.jpg");

	createWindow();

	initResize();

	showImage(src);

	while(1){

		//showImage(img);

		if( waitKey(30) == 27) //wait infinite time for a keypress
			break;
	}

	destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"

	return 0;
}


