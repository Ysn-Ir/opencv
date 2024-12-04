#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>
cv::Mat img,grayimg, gaussimg, cannyimg, dialetimg;
std::string path = "shapes.jpg";
//get contours
void get_contours(cv::Mat img, cv::Mat dialetimg) {
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hiarchy;
	cv::findContours(dialetimg, contours, hiarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	std::vector<std::vector<cv::Point>>contPoly(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		float perimetre = cv::arcLength(contours[i], 1);
		cv::approxPolyDP(contours[i], contPoly[i], 0.02 * perimetre, 1);
		cv::drawContours(img, contPoly, i, cv::Scalar(255, 0, 255), 2);
	}
}
int main() {
	//processing
	img = cv::imread(path);
	cv::cvtColor(img, grayimg, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(grayimg, gaussimg, cv::Size(7, 7), 3, 0);
	cv::Canny(gaussimg, cannyimg, 25, 25);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
	cv::dilate(cannyimg, dialetimg, kernel);
	   //contours
	get_contours(img, dialetimg);
	//rendering
	cv::imshow("img", img);
	/*cv::imshow("gray",grayimg);
	cv::imshow("gauss", gaussimg);
	cv::imshow("canny", cannyimg);
	cv::imshow("dialet", dialetimg);*/
	cv::waitKey(0);
		return 0;
}