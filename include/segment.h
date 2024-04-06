#include <iostream>
#include <vector>

using namespace std;

class Segment {
    public:
        Segment();
        ~Segment();
        int *segmentation(int *img);
        void draw_segments(int *img, int *cimg);
        vector<int*> *count_objects(int *img);

        int get_kac_tane_bolge_var();

        int *group_by_object(vector<int*> *data, int count, int *cimg);

    private:
        int kac_tane_bolge_var;
        int *bolgeler;

};