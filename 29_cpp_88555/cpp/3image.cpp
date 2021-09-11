#include <cv.h>
#include <highgui.h>

using namespace cv;

int main()
{

Mat im = imread("flo.jpg", CV_LOAD_IMAGE_COLOR);
namedWindow("image");
imshow("image", im);
waitKey(0);
}