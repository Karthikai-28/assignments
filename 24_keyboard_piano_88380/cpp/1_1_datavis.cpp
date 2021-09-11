#include "pbPlots.hpp"
#include "supportLib.hpp"

using namespace std;

int main()
{

    RGBABitmapImageReference  *imageRef = CreateRGBABitmapImageReference();

    vector<double> x{2,3,4,5,6,7};
    vector<double> y{7,6,5,4,3,2};

    DrawScatterPlot(imageRef, 600, 400, &x, &y);

    vector<double> *pngData = ConvertToPNG(imageRef->image);
    WriteToFile(pngData, "plot.png");
    DeleteImage(imageRef->image);
    return 0;
    
        
}