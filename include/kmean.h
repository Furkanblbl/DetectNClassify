#include <iostream>

class Kmean {
    public:
        Kmean();
        ~Kmean();
        float *calculate_kmean(int *histogram, float k1, float k2);
        int *convert_binary(int *img, int k1, int k2);

    private:
};