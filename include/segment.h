#include <iostream>

class Segment {
    public:
        Segment();
        ~Segment();
        int *segmentation(int *img);
        int *draw_segments(int *img, int *cimg);
        int *count_objects(int *img);

    private:
    int kac_tane_bolge_var = 0;
};