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

Mat edgeSobel(Mat src){

	Mat src_gray;
	Mat grad;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	Mat blur;
	GaussianBlur( src, blur, Size(3,3), 0, 0, BORDER_DEFAULT );

	/// Convert it to gray
	cvtColor( blur, src_gray, CV_RGB2GRAY );

	/// Generate grad_x and grad_y
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel( src_gray, grad_x, ddepth, 2, 0, 3, scale, delta, BORDER_DEFAULT );
	convertScaleAbs( grad_x, abs_grad_x );

	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel( src_gray, grad_y, ddepth, 0, 2, 3, scale, delta, BORDER_DEFAULT );
	convertScaleAbs( grad_y, abs_grad_y );

	/// Total Gradient (approximate)
	addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

	return grad;

}


int main( int argc, const char** argv )
{
	
	Mat img = loadImg("img.jpg");
	//resize(img,img,Size(),2.0,2.0);

	createWindow();

	//showImage(img);

	while(1){

		//showImage(img);
		Mat tmp = edgeSobel(img);

		Mat tmp2;
		cvtColor(tmp,tmp2,CV_GRAY2RGB);

		Mat out;
		addWeighted( tmp2, 0.5, img, 0.5, 0, out );
		//add(tmp2,img, out);

		showImage(out);

		if( waitKey(30) == 27) //wait infinite time for a keypress
			break;
		
	}

	destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"

     return 0;
}


