#include "kmean.h"

using namespace std;

Kmean::Kmean() {

}

Kmean::~Kmean() {

}

float *Kmean::calculate_kmean(int *histogram, float k1, float k2) {
    int *k1_group = (int*)malloc(256 * sizeof(int));
    int *k2_group = (int*)malloc(256 * sizeof(int));
    int count_1 = 0;
    int count_2 = 0;

    for (int i = 0; i < 256; i++) {
        int fark_k1 = abs(i - k1);
        int fark_k2 = abs(i - k2);
        if (fark_k1 < fark_k2) {
            k1_group[count_1] = i;
            ++count_1;
        }
        else {
            k2_group[count_2] = i;
            ++count_2;
        }
    }

    float *final_kmeans = (float*)malloc(2 * sizeof(float));

    float k1_new = 0;
    float k1_sum = 0;

    float k2_new = 0;
    float k2_sum = 0;
    
    for(int i = 0; i < count_1; i++ ) {
        k1_new += histogram[k1_group[i]] * k1_group[i];
        k1_sum += histogram[k1_group[i]];
    }
    k1_new = k1_new / k1_sum;

    for(int i = 0; i < count_2 - 1; i++ ) {
        k2_new += histogram[k2_group[i]] * k2_group[i];
        k2_sum += histogram[k2_group[i]];
    }
    k2_new = k2_new / k2_sum;

    cout << "K1 and K2: " << k1_new << ", " << k2_new << endl;

    if (k1 != k1_new || k2 != k2_new) {
        calculate_kmean(histogram, k1_new, k2_new);
    }
    else {
        final_kmeans[0] = k1_new;
        final_kmeans[1] = k2_new;
        return final_kmeans;
    }
}

int *Kmean::convert_binary(int *img, int k1, int k2) {
    for(int i = 0; i < 640; i++) {
        for(int j = 0; j < 640; j++) {
            int indeks = i * 640 + j;
            int mesafe_1 = abs(img[indeks] - k1);
            int mesafe_2 = abs(img[indeks] - k2);

            if (mesafe_1 < mesafe_2) {
                img[indeks] = 255;
            }
            else {
                img[indeks] = 0;
            }
        }
    }
    return img;
}
