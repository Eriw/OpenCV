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
Mat src, erosion_dst, dilation_dst;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;
/**  @function Erosion  */
void Erosion( int, void* )
{
  int erosion_type;
  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( erosion_type,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) );

  /// Apply the erosion operation
  erode( src, erosion_dst, element );
  imshow( "MyWindow", erosion_dst );
}

void initErosion(){
	/// Create Erosion Trackbar
	createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Settings",
				&erosion_elem, max_elem,
				Erosion );

	createTrackbar( "Kernel size:\n 2n +1", "Settings",
				&erosion_size, max_kernel_size,
				Erosion );
}

int main( int argc, const char** argv )
{
	
	Mat img = loadImg("img.jpg");
	resize(img,img,Size(),2.0,2.0);
	src = img;

	createWindow();

	initErosion();

	showImage(img);

	while(1){

		//showImage(img);

		

		if( waitKey(30) == 27) //wait infinite time for a keypress
			break;
		
	}

	destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"

     return 0;
}


