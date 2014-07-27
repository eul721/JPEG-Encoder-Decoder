////////////////////////////////////////////////////////////////////////////////////////////////
/* CMPT 365 Assignment 2 - JPEG encoding
 * Creator: Jia Jiu Jacky Chao
 * id: chaojiac
 * Student #: 301164560
 *
 *
 *This is the core of this project.
 *It contains both the encoder and the decoder. Though, they are actually processed together.
 *Some important functions include: RGB->YUV, downsampling, DCT/IDCT, Quantization, deQuantization, and other support functions.
 */



#include "EncoderDecoder.h"
#include <iostream>
using namespace std;


Mat T; //Transform function used for DCT/IDCT
Mat Ttran; //Transform function used for DCT/IDCT

//The following arrays will be used to generate quantization tables for Y and UV channels
float Yvals[]={16.0,11.0,10.0,16.0,24.0,40.0,51.0,61.0,12.0,12.0,14.0,19.0,26.0,58.0,60.0,55.0,14.0,13.0,16.0,24.0,40.0,57.0,69.0,56.0,14.0,17.0,22.0,29.0,51.0,87.0,80.0,62.0,18.0,22.0,37.0,56.0,68.0,109.0,103.0,77.0,24.0,35.0,55.0,64.0,81.0,104.0,113.0,92.0,49.0,64.0,78.0,87.0,103.0,121.0,120.0,101.0,72.0,92.0,95.0,98.0,112.0,100.0,103.0,99.0};
float Yvals2[]={2,3,2,3,2,3,2,4,2,3,2,3,2,3,2,4,2,3,2,3,2,3,2,4,2,3,2,3,2,3,2,4,2,3,2,3,2,3,2,4,2,3,2,3,2,3,2,4,2,3,2,3,2,3,2,4,2,3,2,3,2,3,2,4,};
float UVvals[]={17,18,24,47,99,99,99,99,18,21,26,66,99,99,99,99,24,26,56,99,99,99,99,99,47,66,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99};
float UVvals2[]={5,6,7,5,8,8,7,9,5,6,7,5,8,8,7,9,5,6,7,5,8,8,7,9,5,6,7,5,8,8,7,9,5,6,7,5,8,8,7,9,5,6,7,5,8,8,7,9,5,6,7,5,8,8,7,9,5,6,7,5,8,8,7,9,};
Mat YQtable;
Mat UVQtable;

//constructor
EncoderDecoder::EncoderDecoder(){
    original = NULL;
    height = 0;
    width = 0;
    selection = NULL;

}


//The "toplevel" in this file. It reads an image and an user input, and returns a image matrix according to those specific options.
Mat EncoderDecoder::Encode(String Filepath,int request){
    T = Transformation();
    transpose(T,Ttran);
    selection = request;


    // Reads the file
    original = imread(Filepath);

    //assigning attributes to object variables
    width = original.cols;
    height = original.rows;





    //YUV planes creation
    //the following should be treated as values-based rather than concept-based
    originalY.create((original.size()), CV_16S); //matrix with Y plane
    originalU.create((original.size()), CV_16S); //matrix with U plane
    originalV.create((original.size()), CV_16S); //matrix with V plane

    //Filling up the YUV planes. In other words, color conversion process.
    //Also, downsampling is performed here.
    LumaAssign();
    ChrominanceAssign420();

    //Choosing the encoding function to perform. 0 for Y-channel output, 1 for High Compression JPEG, and 2 for Low Compression JPEG
    if (request == 0){
        encoded = ChannelEncodeY(originalY);
        return encoded;
    }
    else
    {
        if (request == 1){
            originalY = MajorSteps(originalY, 'Y',1);
            originalU = MajorSteps(originalU, 'U',1);
            originalV = MajorSteps(originalV, 'V',1);
        }
        else {
            originalY = MajorSteps(originalY, 'Y',2);
            originalU = MajorSteps(originalU, 'U',2);
            originalV = MajorSteps(originalV, 'V',2);
        }


    //the encoded image will be returned after reversing color conversion.
    encoded = YUVtoRGB(originalY, originalU, originalV);
    return encoded;}
}


//Assigns Yvalues of this particular image to a 8-bit channel plane for encoding usage.
void EncoderDecoder::LumaAssign (){
    for (int x=0; x<width; x++){
        for (int y=0; y<height; y++){
            Vec3b intensity = original.at<Vec3b>(y, x);
            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];


            int temp = ((0.299 * red) + (0.587 * green) + (0.114 * blue));
            if (temp >=255)
                originalY.at<short>(y, x)= 255;

            else
                originalY.at<short>(y, x)= temp;

            ; //Y is assigned to every pixel
            }


        }

    }

//Assigns UVvalues of this particular image to 2 DOWNSAMPLED 8-bit channel plane for encoding usage.
void EncoderDecoder::ChrominanceAssign420(){

    for (int x=0;x<width;x=x+2){

        for (int y=0;y<height;y=y+2){
            Point pt1st(x , y);
            Point pt2rd(x+1 , y);
            Point pt3rd(x , y+1);

            Point pt4th(x+1 , y+1);

            if (x+1==width || y+1==height){
                if (x+1==width&&y+1<height){
                    originalU.at<short>(y, x) = (GetU(pt1st) + GetU(pt3rd))/2;
                    originalU.at<short>(y+1, x) = (GetU(pt1st) + GetU(pt3rd))/2;
                    originalV.at<short>(y, x) = (GetV(pt1st) + GetV(pt3rd))/2;
                    originalV.at<short>(y+1, x) = (GetV(pt1st) + GetV(pt3rd))/2;
                }
                else if (x+1<width&&y+1==height){
                    originalU.at<short>(y, x) = (GetU(pt1st) + GetU(pt2rd))/2;
                    originalU.at<short>(y, x+1) = (GetU(pt1st) + GetU(pt2rd))/2;
                    originalV.at<short>(y, x) = (GetV(pt1st) + GetV(pt2rd))/2;
                    originalV.at<short>(y, x+1) = (GetV(pt1st) + GetV(pt2rd))/2;
                }
                else{
                    originalU.at<short>(y, x) = GetU(pt1st);
                    originalV.at<short>(y, x) = GetV(pt1st);
                }
            }
            else{
                originalU.at<short>(y, x) = (GetU(pt1st) + GetU(pt3rd) + GetU(pt2rd) + GetU(pt4th))/4;
                originalU.at<short>(y+1, x) = (GetU(pt1st) + GetU(pt3rd) + GetU(pt2rd) + GetU(pt4th))/4;
                originalU.at<short>(y, x+1) = (GetU(pt1st) + GetU(pt3rd) + GetU(pt2rd) + GetU(pt4th))/4;
                originalU.at<short>(y+1, x+1) = (GetU(pt1st) + GetU(pt3rd) + GetU(pt2rd) + GetU(pt4th))/4;
                originalV.at<short>(y, x) = (GetV(pt1st) + GetV(pt3rd) + GetV(pt2rd) + GetV(pt4th))/4;
                originalV.at<short>(y+1, x) = (GetV(pt1st) + GetV(pt3rd) + GetV(pt2rd) + GetV(pt4th))/4;
                originalV.at<short>(y, x+1) = (GetV(pt1st) + GetV(pt3rd) + GetV(pt2rd) + GetV(pt4th))/4;
                originalV.at<short>(y+1, x+1) = (GetV(pt1st) + GetV(pt3rd) + GetV(pt2rd) + GetV(pt4th))/4;
            }

        }
    }
}

//support function to get U at every pixel
short EncoderDecoder::GetU(Point pt){
    Vec3b intensity = original.at<Vec3b>(pt);
            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];

        return ((-0.14713* red) + (-0.28886 * green) + (0.436 * blue));
}
//support function to get V at every pixel
short EncoderDecoder::GetV(Point pt){
    Vec3b intensity = original.at<Vec3b>(pt);
            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];

        return ((0.615	* red) + (-0.51499 * green) + (-0.1 * blue));

}

//Encodes the image into Y-only output
Mat EncoderDecoder::ChannelEncodeY(Mat Y){
    Mat newimg((original.size()),(original.type()));
    Y.convertTo(Y,CV_32F);


        for (int i=0;i<height;i++){
            for (int j=0;j<width;j++){
                float y = Y.at<float>(i,j);

                Vec3b* newimgpixel = &newimg.at<Vec3b>(i , j);
                newimgpixel->val[0] = y ;
                newimgpixel->val[1] = y ;

                newimgpixel->val[2] = y ;


            }
        }
        return newimg;
}


/*int* EncoderDecoder::OneDimDCT (uchar* arr){ //takes an uchar[8] array and applys DCT to it. This has been abandoned due to the easier implementation of 2DDCT
    int* newarr = new int[8];
    double Cu;
    for (int u=0; u< 8; u++){
        if (u == 0)
            Cu = (SQRT2 /2.0);
        else
            Cu = 0;
        for (int i=0;i<8;i++){
            newarr[u] = cos((2.0*i +1.0)*u*PI/16.0) * arr[i];
        }
        newarr[u] = Cu /2 * newarr[u];
    }
    return newarr;

}*/

//Two Dimension DCT
Mat EncoderDecoder::TwoDimDCT (Mat src){ //mats are 8x8. Does matrix multiplication (Transform * Source * Transform.transpose())
    Mat temp;
    Mat srctemp;
    src.convertTo(srctemp,CV_32F);



    temp = T * srctemp;

    return temp * Ttran;


}
//Two Dimension IDCT
Mat EncoderDecoder::TwoDimIDCT (Mat src){ //mats are 8x8. Does matrix multiplication (Transform.transpose() * Source *Transform )
    Mat temp;
    Mat srctemp;
    src.convertTo(srctemp,CV_32F);

    temp = Ttran * srctemp;

    return temp * T;
}


//The core in this file. It encodes the source channel to jpeg-compressed format.
//applies the following to a plane in order: 2D-DCT, Quantization, deQuantization, IDCT
Mat EncoderDecoder::MajorSteps ( Mat src, char channel, int selection){
    Mat intver;



    src.copyTo(intver);
    intver.convertTo(intver,CV_32F);


    for (int y = 0; y+8 <= height;y = y+8){

        for (int x =0; x+8 <= width; x = x+8){
            //DCT
            Mat subblock=src(Rect(x,y,8,8));
            Mat dstsubblock=intver(Rect(x,y,8,8));
                TwoDimDCT (subblock).copyTo(dstsubblock);
            //Quantization
            if (channel == 'Y'){
                if (selection ==2)
                    YQtable = Mat(8,8, CV_32F, Yvals2).clone();
                else
                    YQtable = Mat(8,8, CV_32F, Yvals).clone();
                Quantizize(dstsubblock, YQtable).copyTo(dstsubblock);}
            else{
                if (selection ==2)
                    UVQtable = Mat(8,8, CV_32F, UVvals2).clone();
                else
                    UVQtable = Mat(8,8, CV_32F, UVvals).clone();
                Quantizize(dstsubblock, UVQtable).copyTo(dstsubblock);}

            //deQuantization
            if (channel == 'Y')
                deQuantizize(dstsubblock, YQtable).copyTo(dstsubblock);
            else
                deQuantizize(dstsubblock, UVQtable).copyTo(dstsubblock);

            //IDCT
            TwoDimIDCT(dstsubblock).copyTo(dstsubblock);



        }
    }
    return intver;
}


//Quantization
Mat EncoderDecoder::Quantizize (Mat src, Mat Qtable){
    Mat temp(8,8,CV_32F);
    for (int y = 0;y<8;y++){
        for (int x=0;x<8;x++){
            temp.at<float>(y, x) = round (src.at<float>(y, x) / Qtable.at<float>(y, x));
        }
    }
    return temp;
}

//deQuantization
Mat EncoderDecoder::deQuantizize (Mat src, Mat Qtable){
    Mat temp(8,8,CV_32F);
    for (int y = 0;y<8;y++){
        for (int x=0;x<8;x++){
            temp.at<float>(y, x) = round (src.at<float>(y, x) * Qtable.at<float>(y, x));
        }
    }
    return temp;
}

//	temp.create(M.size(),CV_16S);

//Transformation matrix for DCT/IDCT
Mat EncoderDecoder::Transformation(){
    Mat temp;
    temp.create(8,8,CV_32F);

    for (int y=0;y<8;y++){
        for (int x=0;x<8;x++){
            if (y==0)
                temp.at<float>(y, x) = (1.0/2.0 / SQRT2);
            else
            temp.at<float>(y, x) = sqrt(float(2.0/8.0))*cos ((2.0*x + 1.0)*y*PI / 2.0 / 8.0);
        }
    }
    return temp;
}

//simple rounding function for Quantization/deQuantization
double EncoderDecoder::round(double x)
{
 return x < 0.0 ? ceil(x - 0.5) : floor(x + 0.5);
}

//Inverse color conversion
Mat EncoderDecoder::YUVtoRGB (Mat Y, Mat U, Mat V){
Mat newimg((original.size()),(original.type()));
Y.convertTo(Y,CV_32F);
U.convertTo(U,CV_32F);
V.convertTo(V,CV_32F);


    for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){
            float y = Y.at<float>(i,j);
            ////cout << "trace" << endl;
            float u =  U.at<float>(i,j);
            float v =  V.at<float>(i,j);

            Vec3b* newimgpixel = &newimg.at<Vec3b>(i , j);
            newimgpixel->val[0] =  (y + (2.032 * (u)));
            newimgpixel->val[1] =  (y - (0.395 * (u)) - (0.580 * (v)));

            newimgpixel->val[2] =  (y + (1.13983 * (v)));


        }
    }
    return newimg;
}
