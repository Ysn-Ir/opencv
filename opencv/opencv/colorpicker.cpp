#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>
cv::Mat img,HSVimg,mask;cv::VideoCapture cam(0);
int hmin = 0, smin = 0, vmin = 0,
hmax = 179, smax = 255, vmax = 255;
//getcolors
int main() {
	
	cv::namedWindow("TrackBars", (640, 300));
	cv::createTrackbar("H min", "TrackBars", &hmin, 179);
	cv::createTrackbar("H max", "TrackBars", &hmax, 179); 
	cv::createTrackbar("S min", "TrackBars", &smin, 255);
	cv::createTrackbar("S max", "TrackBars", &smax, 255);
	cv::createTrackbar("V min", "TrackBars", &vmin, 255);
	cv::createTrackbar("V max", "TrackBars", &vmax, 255);
	while (1) {
		cam.read(img);
		cv::cvtColor(img, HSVimg, cv::COLOR_BGR2HSV);
		cv::Scalar low(hmin, smin, vmin);
		cv::Scalar high(hmax, smax, vmax);
		cv::inRange(HSVimg, low, high, mask);
		std::cout << hmin << " ," << hmax << ", " << smin << " , " << smax << ", " << vmin << " ," << vmax << "   " << std::endl;
		/*cv::imshow("video", HSVimg);*/
		cv::imshow("mask", mask);
		cv::waitKey(1);
	}
	return 0;
}
//std::vector<std::vector<int>> colors{
//	{83 ,116, 170 , 255, 186 , 255,}, //blue
//	{0 ,27, 137 , 227, 255 , 255},   //orange
//	{0 ,95, 0 , 54, 120 ,255},    //white
//	{0 ,5, 62 , 170, 213 ,255},//red
//{71 ,88, 106 , 229, 173 ,255},//green
//{0 ,114, 2 , 109, 21 ,165}//black
//};
//std::string name[] = { "blue","orange","white","red","green","black" };
//std::vector<cv::Scalar> bgr{ {0, 0, 255}, {255, 165, 0}, {255, 255, 255},{255,0,0},{0,255,0},{0,0,0} };
//cv::Mat imgHsv, imgauss, imgcanny, imgdialet, img;
//std::vector<std::vector<cv::Point>> contours;
//std::vector<cv::Vec4i> hierarchy;