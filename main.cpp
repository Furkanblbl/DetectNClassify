#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <fstream>

using namespace std;

int main() {

    cv::Mat image; //create a matrix to store the image
    image = cv::imread("../nuts.jpg"); //read the image file
    cv::resize(image, image, cv::Size(640,640), cv::INTER_LINEAR); //resize the image

    int *image_data = (int*) malloc(image.rows * image.cols * 3 * sizeof(int)); //create a new image data for color image

    //get the pixel values of the image in one dimensional array
    for(int i = 0; i < image.rows; i++) {
        for(int j = 0; j < image.cols; j++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i,j);
            image_data[i*image.cols*3 + j + 0] = (int)pixel[0]; //r
            image_data[i*image.cols*3 + j + 1] = (int)pixel[1]; //g
            image_data[i*image.cols*3 + j + 2] = (int)pixel[2]; //b

        }
    }


    int *gray_image_data = (int*) malloc(image.rows * image.cols * 1 * sizeof(int)); //create a new image data for gray image
    
    //convert the color image to gray image
    int idx = 0;
    for(int i = 0; i < image.rows; i++) {
        for(int j = 0; j < image.cols; j++) {
            int toplam = (image_data[i * image.cols * 3 + 0] * 0.299) + (image_data[i * image.cols * 3 + 1] * 0.587) + image_data[i * image.cols * 3 + 2] * 0.144;
            gray_image_data[idx] = toplam;
            idx++;
        }
    }

    cv::Mat gray_image(cv::Size(image.rows, image.cols), CV_8UC1); //create a new matrix for gray image

    for(int i = 0; i < image.rows; i++) {
        for(int j = 0; j < image.cols; j++) {
        uchar blue = image.at<cv::Vec3b>(i, j)[0];
        uchar green = image.at<cv::Vec3b>(i, j)[1];
        uchar red = image.at<cv::Vec3b>(i, j)[2];
        gray_image.at<uchar>(i, j) = static_cast<uchar>(0.299 * red + 0.587 * green + 0.114 * blue);
        }
    }


    cv::imshow("gray", gray_image);
    cv::imshow("Lena", image);
    cv::waitKey(0);

    return 0;
}


