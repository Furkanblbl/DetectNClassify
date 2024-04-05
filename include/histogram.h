#include <iostream>


class Histogram {
    public:
        Histogram();
        ~Histogram();
        
        int *calculate_histogram(int *img, int row, int col);
        void print_histogram();

    private:
        int hist_size;
        int *hist;

};