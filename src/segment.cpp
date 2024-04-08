#include "segment.h"
#include <fstream>
#include <bits/stdc++.h>
#include <random>
#include <opencv2/opencv.hpp>

using namespace std;

Segment::Segment(){
    kac_tane_bolge_var = 0;
    bolgeler = (int*)malloc(256 * sizeof(int));

};

Segment::~Segment(){

};

int *Segment::segmentation(int *img){
    int idx = 69;

    for(int i = 2; i < 640 - 2; i++)
    {
        for(int j = 2; j < 640 - 2; j++)
        {
            int curr_idx = (i * 640) + j;
            int prev_idx =  (i * 640) + j - 1 ;
            int up_idx = ((i - 1) * 640) + j;
            int left_cross_idx = ((i - 1) * 640) + j - 1;
            int right_cross_idx = ((i - 1)* 640) + j + 1;

            // 0 4 0 2
            int temp[4] = {img[left_cross_idx], img[up_idx], img[right_cross_idx], img[prev_idx]};

            if(img[curr_idx] == 255)
            {
                // ilk defa bir nesneyi görüyorsa ona yeni bir idx atıyoruz.
                if(temp[0]  == 0 && temp[1]  == 0 && temp[2]  == 0 && temp[3]  == 0)
                {
                    ++idx;
                    img[curr_idx] = idx;
                }
                else
                {
                    int _min_val = 1000;

                    if (temp[0] != 0 && temp[0] < _min_val)
                    {
                        _min_val = temp[0];
                    }
                    if (temp[1] != 0 && temp[1] < _min_val)
                    {
                        _min_val = temp[1];
                    }
                    if (temp[2] != 0 && temp[2] < _min_val)
                    {
                        _min_val = temp[2];
                    }
                    if (temp[3] != 0 && temp[3] < _min_val)
                    {
                        _min_val = temp[3];
                    }

                    img[curr_idx] = _min_val;

                    for (int l = 0; l < 6; l++)
                    {
                        if (img[curr_idx - l] > _min_val)
                        {
                            img[curr_idx - l] = _min_val;
                        }
                    }
                }
            }
        }
    }
    return img;
};

void Segment::draw_segments(int *img, int *cimg)
{
    int bolgeler[256] = {0};
    for (int i = 0; i < 256; i++)
    {
        bolgeler[i] = 0;
    }

    for(int i = 0; i < 640; i++)
    {
        for(int j = 0; j < 640; j++)
        {
            bolgeler[img[i * 640 + j]] += 1;
        }
    }

    for (int i = 0; i < 256; i++)
    {
        if (bolgeler[i] != 0 && i != 0 && bolgeler[i] > 100)
        {
        kac_tane_bolge_var += 1;
        }
    }

}

vector<int*> *Segment::count_objects(int *img){
    for (int i = 0; i < 256; i++)
    {
        bolgeler[i] = 0;
    }

    for(int i = 0; i < 640; i++)
    {
        for(int j = 0; j < 640; j++)
        {
            bolgeler[img[i * 640 + j]] += 1;
        }
    }

    cout << "kac_tane_bolge_var : " << kac_tane_bolge_var << endl;
    vector<int*> *obje = new vector<int*>(kac_tane_bolge_var);
    int sirasi = 0;
    for (int i = 0; i < 256; i++)
    {
        if (bolgeler[i] != 0 && bolgeler[i] > 100 && i != 0)
        {
            cout << i << ". bolgedeki beyaz nokta adeti: " << bolgeler[i] << endl;
            (*obje)[sirasi] = new int[bolgeler[i]];
            int count = 0;
            for(int j = 0; j < 640; j++)
            {
                for(int k = 0; k < 640; k++)
                {
                   if (img[j * 640 + k] == i)
                   {
                        (*obje)[sirasi][count] = j * 640 + k;
                        count += 1;
                   }
                }
            }
            ++sirasi;
        }
    }
    return obje;
}

int Segment::get_kac_tane_bolge_var()
{
    return kac_tane_bolge_var;
}

int *Segment::group_by_object(vector<int*> *data, int count, int *cimg)
{  

    int data_count[count] = {0};
    
    for (int i = 0; i < count; i++)
    {
        data_count[i] = 0;
    }
    
    
    int indeks = 0;
    for (int i = 0; i < 256; i++)
    {
        if (bolgeler[i] != 0 && bolgeler[i] > 100 && i != 0)
        {
            data_count[indeks]  = bolgeler[i];
            ++indeks;
        }
    }

    random_device rd;
    mt19937 gen(rd());

    // for (int i = 0; i < count; i++)
    // {
    //     uniform_int_distribution<> dis1(0, 255);
    //     uniform_int_distribution<> dis2(0, 255);
    //     uniform_int_distribution<> dis3(0, 255);
    //     int r = dis1(gen);
    //     int g = dis2(gen);
    //     int b = dis3(gen);

    //     for (int j = 0; j < data_count[i]; j++)
    //     {
    //         int idx = (*data)[i][j]*3;
    //         cimg[idx + 0] = r;
    //         cimg[idx + 1] = g;
    //         cimg[idx + 2] = b;
    //     }
    // }

    int moments[count][3];
    for (int i = 0; i < count; i++)
    {
        moments[i][0] = 0;
        moments[i][1] = 0;
        moments[i][2] = 0;
    }

    for(int i = 0; i < count; i++)
    {
        for (int j = 0; j < data_count[i]; j++)
        {
            int idx = (*data)[i][j];
            moments[i][0] += int(idx / 640);  // Satir sayilarinin toplamını verir. Yani m10 degerini elde ederiz.
            moments[i][1] += (idx % 640) - 1; // 640 mod 640 = 0 sütun verir. Sutünların toplamı m01 i verir.
            moments[i][2] += 1; // Nesnenin piksel sayısını verir. Yani m00 i verir.
        }
    }

    for(int i = 0; i < count; i++)
    {   
        int indeks = 0 ;
        cout << i + 1 << ". obje : " ;
        for (int j = 0; j < 3; j++)
        {
            cout << moments[i][j] << " ";
        }
        cout << "  m01/m00 : " << moments[i][1] / moments[i][2] << " m10/m00 : " << moments[i][0] / moments[i][2] << " m10/m01 " <<moments[i][0] / moments[i][1] << " m01/m10 " <<moments[i][1] / moments[i][0]<< endl;
        cout << endl;
    }

    cv::Mat img(cv::Size(640, 640), CV_8UC3);
    for(int i = 0; i < 640; i++) {
        for(int j = 0; j < 640; j++) {
            int indeks = ((i * 640) + j) * 3;
            cv::Vec3b pixel;
            pixel[0] = (int)cimg[indeks + 0];
            pixel[1] = (int)cimg[indeks + 1];
            pixel[2] = (int)cimg[indeks + 2];
            img.at<cv::Vec3b>(i, j) = pixel;
        }
    }

    for(int i = 0; i < count; i++)
    {   
        int m00 = moments[i][2];
        if (100 < m00 &&  m00 < 200)
            cv::putText(img, "mercimek", cv::Point(moments[i][1]/moments[i][2], moments[i][0]/moments[i][2]), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 255), 1, cv::LINE_AA);
        if (300 < m00  && m00 < 600)
            cv::putText(img, "misir", cv::Point(moments[i][1]/moments[i][2], moments[i][0]/moments[i][2]), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 255), 1, cv::LINE_AA);      
        if (m00 > 1000 ) 
            cv::putText(img, "cekirdek ya da findik", cv::Point(moments[i][1]/moments[i][2], moments[i][0]/moments[i][2]), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 255), 1, cv::LINE_AA);        

    }

    cv::imshow("img", img);
    cv::waitKey(0);

    return cimg;
}
