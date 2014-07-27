#ifndef ENCODERDECODER_H
#define ENCODERDECODER_H



/*This is the header of the Encoder/Decoder class
 *It includes all the required functions and image-specific materials
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

#define PI 3.14159265
#define SQRT2 1.41421356237




class EncoderDecoder {
public :

    EncoderDecoder();

    Mat Encode(String Filepath, int request);
    double getv(Point pt);
    void LumaAssign();
    short GetV(Point pt);
    short GetU(Point pt);
    void ChrominanceAssign420();
    Mat ChannelEncodeY(Mat Y);
    Mat MajorSteps ( Mat src, char Channel, int selection);
    Mat Transformation();
    Mat TwoDimDCT (Mat src);
    Mat TwoDimIDCT (Mat src);
    Mat Quantizize (Mat src, Mat Qtable);
    Mat deQuantizize (Mat src, Mat Qtable);
    Mat YUVtoRGB (Mat Y, Mat U, Mat V);
    double round(double x);


private :
    Mat original,encoded,originalY,originalU,originalV;
    int width,height,selection;
    //static const float Yvals[64];
    //static const float UVvals[64];
    //static const Mat YQtable;
    //static const Mat UVQtable;

};

#endif // ENCODERDECODER_H
