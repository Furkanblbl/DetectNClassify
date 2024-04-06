#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <fstream>

#include "histogram.h"
#include "kmean.h"
#include "segment.h"

using namespace std;

int main() {

    cv::Mat image; //create a matrix to store the image
    image = cv::imread("../new.jpeg"); //read the image file
    cv::resize(image, image, cv::Size(640, 640)); //resize the image to 640x640
    int *image_data = (int*) malloc(image.rows * image.cols * 3 * sizeof(int)); //create a new image data for color image

    //get the pixel values of the image in one dimensional array
    for(int i = 0; i < image.rows; i++) {
        for(int j = 0; j < image.cols; j++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i,j);
            int indeks = (i * 640 + j) * 3;
            image_data[indeks + 0] = (int)pixel[0]; //r
            image_data[indeks + 1] = (int)pixel[1]; //g
            image_data[indeks + 2] = (int)pixel[2]; //b

        }
    }

    int *gray = (int*)malloc(640 * 640 * 1 * sizeof(int));
    int count = 0;

    for(int i = 0; i < 640 ; i++) {
        for(int j = 0; j < 640 ; j++) {
            int idx = (i * 640 + j) * 3; 
            float red   = image_data[idx + 0] * 0.299;
            float green = image_data[idx + 1] * 0.587;
            float blue  = image_data[idx + 2] * 0.114;
            float _sum = red + green + blue;
            gray[count] = (int)_sum;
            ++count;
        }
    }

    cv::Mat gray_image(cv::Size(640, 640), CV_8UC1);

    for(int i = 0; i < 640; i++) {
        for(int j = 0; j < 640; j++) {
            int indeks = ((i * 640) + j) * 1;
            gray_image.at<uchar>(i, j) = static_cast<uchar>(gray[indeks]);
        }
    }

    Histogram hist;
    int *histogram = hist.calculate_histogram(gray, gray_image.rows, gray_image.cols);
    hist.print_histogram();

    Kmean km;
    float *kmeans = km.calculate_kmean(histogram, 52.0, 149.0);
    int *zeroone = km.convert_binary(gray, (int)kmeans[0], (int)kmeans[1]);

    cv::Mat zero_image(cv::Size(640, 640), CV_8UC1);

    for(int i = 0; i < 640; i++) {
        for(int j = 0; j < 640; j++) {
            int indeks = ((i * 640) + j) * 1;
            zero_image.at<uchar>(i, j) = static_cast<uchar>(zeroone[indeks]);
        }
    }

    Segment seg;
    int *segment = seg.segmentation(zeroone);

    int *cimg = seg.draw_segments(segment, image_data);
    int *segmente = seg.count_objects(segment);

    cv::Mat segmented(cv::Size(640, 640), CV_8UC1);

    for(int i = 0; i < 640; i++) {
        for(int j = 0; j < 640; j++) {
            int indeks = ((i * 640) + j) * 1;
            segmented.at<uchar>(i, j) = static_cast<uchar>(segment[indeks]);
        }
    }

    cv::Mat colored(cv::Size(640, 640), CV_8UC3);

    for(int i = 0; i < 640; i++) {
        for(int j = 0; j < 640; j++) {
            int indeks = ((i * 640) + j) * 3;
            cv::Vec3b pixel;
            pixel[0] = (int)cimg[indeks + 0];
            pixel[1] = (int)cimg[indeks + 1];
            pixel[2] = (int)cimg[indeks + 2];

            colored.at<cv::Vec3b>(i, j) = pixel;
        }
    }
    cv::imshow("gray", gray_image);
    cv::imshow("segment", segmented);
    cv::imshow("image", image);
    cv::imshow("zero_image", zero_image);
    cv::imshow("colored", colored);
    cv::waitKey(0);

    return 0;
}


