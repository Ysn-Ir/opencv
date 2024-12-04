#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>
//get colors
std::vector<std::vector<int>> colors{
    {106 ,127, 167 , 255, 88 ,210} //blue
};
std::string name[] = {"blue","orange","white","red","green","black"};
std::vector<cv::Scalar> bgr{ {0, 0, 255} };
cv::Mat imgHsv,imgauss,imgcanny,imgdialet ,img;
std::vector<std::vector<cv::Point>> contours;
std::vector<cv::Vec4i> hierarchy;
std::vector<cv::Point> pos;
//get contours
void getcontours(cv::Mat Mask) {
    cv::findContours(Mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    std::vector<cv::Rect> bounder(contours.size()); // Moved outside the loop
    std::vector<std::vector<cv::Point>> count(contours.size());
    for (int i = 0; i < contours.size(); i++) {
        int area = cv::contourArea(contours[i]);
        if (area > 500) {
            float peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], count[i], 0.05 * peri, true);
            bounder[i] = cv::boundingRect(count[i]); // Store bounding rectangle
            cv::drawContours(img, count, i, cv::Scalar(255, 0, 255), 2);
            cv::rectangle(img, bounder[i].tl(), bounder[i].br(), cv::Scalar(255, 0, 5));
            pos.push_back(cv::Point(bounder[i].x + bounder[i].width, bounder[i].y));
        }
    }
}
void render() {
    for (int i = 0; i < pos.size(); i++) {
        cv::circle(img, pos[i], 10, cv::Scalar(0, 0, 0),  cv::FILLED);
    }
}
void getcolors() {
    cv::cvtColor(img, imgHsv, cv::COLOR_BGR2HSV);
    cv::Mat Mask;
    for (int i = 0; i < colors.size(); i++) {
        cv::Scalar low(colors[i][0], colors[i][2], colors[i][4]);
        cv::Scalar high(colors[i][1], colors[i][3], colors[i][5]);
        cv::inRange(imgHsv, low, high, Mask);
        //cv::imshow(name[i], Mask);
        getcontours(Mask);
    }
}
//render
int main() {
    cv::VideoCapture cam(0);
    cam.set(cv::CAP_PROP_FPS,300);
    while (1) {
        cam.read(img);
        getcolors();
        render();
        cv::imshow("detect", img);
        cv::waitKey(1);
    }
    return 0;
}
