#ifndef _BASE_H
#define _BASE_H

#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

using namespace std;
using namespace cv;

class base
{
public:
	base();
	Mat openImage(char *nome_image);
	void showImage(char* nome, Mat image);
	Mat convertBGR2GRAY(Mat in);
	Mat convertBGR2HSV(Mat in);
	void splitRGB();
	void splitHSV();
	void MediaFilter();
	Mat cannyFilter(Mat in);
	void thresHoldImage();
	void resizeImage();
	void matrixInFile();
	void manualThresHolding();
	void centroIdRectangle();
	void file2Image();
	void sobelFilter();
	void captureFrame();
	void captureFrameAndCanny();
	Mat histograma(Mat in);
	Mat equalizer();
	Mat equalizerManual();
	void laplacianAndEqualizer();
	void sobelAndGradiente();
	FILE* openFileWrite(FILE* file, char* nome);
	FILE* openFileRead(FILE* file, char* nome);
	void closeFile(FILE* file);
	void madianaFilter();
private:
	Mat img_in;
	FILE *file_in;
	FILE *file_out;
};

#endif