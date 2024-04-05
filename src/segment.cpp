#include "segment.h"
#include <fstream>

using namespace std;

Segment::Segment(){

};

Segment::~Segment(){

};

int *Segment::segmentation(int *img){
    int idx = 70;

    for(int i = 2; i < 640 - 2; i++) {
        for(int j = 2; j < 640 - 2; j++) {
            int curr_idx = (i * 640) + j;
            int prev_idx =  (i * 640) + j - 1 ;
            int up_idx = ((i - 1) * 640) + j;
            int left_cross_idx = ((i - 1) * 640) + j - 1;
            int right_cross_idx = ((i - 1)* 640) + j + 1;
        
            
            if(img[curr_idx] == 255){
             if(img[prev_idx] == 0 && img[up_idx] == 0 && img[left_cross_idx] == 0 && img[right_cross_idx] == 0){ // ilk defa bir nesneyi görüyorsa ona yeni bir idx atıyoruz.
              img[curr_idx] = idx;
              idx++;
             }
             if( img[prev_idx] != 0 || img[up_idx] != 0 || img[left_cross_idx] != 0 || img[right_cross_idx] != 0) 
              img[curr_idx] = idx;
            }
        }
    }

    ofstream file2("veriler2.txt");
    ofstream file("veriler.txt");



    cout << "BASLIYOOO" << endl;
    int idex = 0;
    for(int i = 0; i < 640; i++) {
        for(int j = 0; j < 640; j++) {
            file << img[idex] << endl;
            idex++;
        }
    }
    file.close();
    file2.close();
    return img;
};
