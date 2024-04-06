#include "segment.h"
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

Segment::Segment(){

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

int *Segment::draw_segments(int *img, int *cimg)
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


    for (int i = 0; i < 256; i++)
    {
        if (bolgeler[i] != 0 && i != 0)
        {
            for(int j = 0; j < 640; j++)
            {
                for(int k = 0; k < 640; k++)
                {
                    int indeks_1_d = j * 640 + k;
                    int indeks_3_d = ((j * 640) + k) * 3;

                    if (img[indeks_1_d] == i)
                    {
                        cimg[indeks_3_d + 0] = 255;
                        cimg[indeks_3_d + 1] = 0;
                        cimg[indeks_3_d + 2] = 255;
                    }
                }
            }
        }
    }
    return cimg;

}

int *Segment::count_objects(int *img){

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

    cout << "kac_tane_bolge_var : " << kac_tane_bolge_var << endl;
    vector<int*> obje(kac_tane_bolge_var);
    for (int i = 0; i < 256; i++)
    {
        if (bolgeler[i] != 0 && bolgeler[i] > 100 && i != 0)
        {
            cout << i << ". bolgedeki beyaz nokta adeti: " << bolgeler[i] << endl;
            obje[i] = new int[2*bolgeler[i]];
            int count = 0;
            for(int j = 0; j < 640; j++)
            {
                for(int k = 0; k < 640; k++)
                {
                   if (img[j * 640 + k] == i)
                   {
                        obje[i][count] = j * 640 + k;
                        count += 1;
                   }
                }
            }
        }
    }
}