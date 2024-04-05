#include "histogram.h"

using namespace std;

Histogram::Histogram(){
    hist_size = 256;
    hist = new int[hist_size];

    for (int i = 0; i < hist_size; i++) {
        hist[i] = 0;
    }
}

Histogram::~Histogram(){
    
}

// Tek katmanlı görüntüde renk değerleri 0-255 arasında ifade edilir.
// Buradaki histogram, gri görüntüde 0-255 arası renk değerlerinin
// her birinden toplamda kaç adet olduğunu ifade eder.
int *Histogram::calculate_histogram(int *img, int row, int col){
    for (int i = 0; i < row * col; i++) {
        hist[img[i]] += 1;
    }
    return hist;
}

void Histogram::print_histogram() {
    for (int i = 0; i < hist_size; i++) {
        cout << i << ". renk değeri: " << hist[i] << endl;
    }
}
