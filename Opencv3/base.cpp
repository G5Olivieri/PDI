#include "base.h"

Mat gray, hsv;
char *img_name = "Koala.jpg";

base::base()
{
	this->file_in = NULL;
	this->file_out = NULL;
}

Mat base::openImage(char * nome_image)
{
	img_in = imread(nome_image, 1);
	return img_in;
}

void base::showImage(char * nome, Mat image)
{
	imshow(nome, image);
}

Mat base::convertBGR2GRAY(Mat in)
{
	in = openImage(img_name);
	cvtColor(in, gray, CV_BGR2GRAY);
	return gray;
}

Mat base::convertBGR2HSV(Mat in)
{
	in = openImage(img_name);
	cvtColor(in, hsv, CV_BGR2HSV);
	return hsv;
}

void base::splitRGB()
{
	img_in = openImage(img_name);
	vector<Mat> rgb_chanels(3);
	split(img_in, rgb_chanels);

	showImage("Blue", rgb_chanels.at(0));
	showImage("Green", rgb_chanels.at(1));
	showImage("Red", rgb_chanels.at(2));

	imwrite("Blue.jpg", rgb_chanels.at(0));
	imwrite("Green.jpg", rgb_chanels.at(1));
	imwrite("Red.jpg", rgb_chanels.at(2));
	
}

void base::splitHSV()
{
	img_in = openImage(img_name);
	hsv = convertBGR2HSV(img_in);
	vector<Mat> hsv_chanels(3);
	split(hsv, hsv_chanels);

	showImage("HSV", hsv);
	showImage("H", hsv_chanels.at(0));
	showImage("S", hsv_chanels.at(1));
	showImage("V", hsv_chanels.at(2));

	imwrite("H.jpg", hsv_chanels.at(0));
	imwrite("S.jpg", hsv_chanels.at(1));
	imwrite("V.jpg", hsv_chanels.at(2));
}

void base::madianaFilter()
{
	img_in = openImage(img_name);
	gray = convertBGR2GRAY(img_in);

	int start, end, tmili;
	int order, size, ordenador = 1, aux, t;
	float soma;

	Mat_<uchar> media(img_in.rows, img_in.cols, CV_32FC1);
	Mat_<uchar> median(img_in.rows, img_in.cols, CV_8UC3);

	for (int i = 0; i < gray.rows; i++)
		for (int j = 0; j < gray.cols; j++)
		{
			media.at<uchar>(i, j) = 0;
			median.at<uchar>(i, j) = 0;
		}

	printf("Please enter the order: ");
	scanf("%d", &order);

	size = pow(order, 2);
	int *vetor = new int[size];

	start = (int)getTickCount();

	for (int i = order / 2; i < gray.rows - order / 2; i++)
		for (int j = order / 2; j < gray.rows - order / 2; j++)
		{
			soma = 0;
			for (int x = -order / 2; x <= order / 2; x++)
				for (int y = -order / 2; y <= order / 2; y++)
					soma += (float)gray.at<uchar>(i + x, j + y);
			media.at<uchar>(i, j) = (int)(soma / (order*order));
		}
	end = (int)getTickCount();

	tmili = end - start;

	printf("\nO tempo gasto para aplicar o filtro da media foi:\t%d ms\n", tmili);

	imshow("Media Filter", media);
	imwrite("Media-Filter.jpg", media);

	start = (int)GetTickCount();

	for (int i = order / 2; i < gray.rows - order / 2; i++)
		for (int j = order / 2; j < gray.cols; j++)
		{
			t = 0;
			ordenador = 1;
			for (int x = -order / 2; x <= order / 2; x++)
				for (int y = -order / 2; y <= order / 2; y++)
				{
					vetor[t] = gray.at<uchar>(i + x, j + y);
					t++;
				}
			while (ordenador <= size)
			{
				for (t = 0; t < size; t++)
					if (vetor[t] < vetor[t + 1])
					{
						aux = vetor[t];
						vetor[t] = vetor[t + 1];
						vetor[t + 1] = aux;
					}
				ordenador++;
			}
			median.at<uchar>(i, j) = vetor[size / 2];
		}

	end = (int)GetTickCount();

	tmili = end - start;

	printf("\nO tempo gasto para aplicar o filtro da mediana foi:\t%d ms\n", tmili);

	imshow("Mediana", median);
	imwrite("Mediana.jpg", median);

	delete[] vetor;
}

void base::MediaFilter()
{
	img_in = openImage(img_name);
	gray = convertBGR2GRAY(img_in);

	int start, end, tmili;
	int order, size;
	float soma;

	Mat_<uchar> media(img_in.rows, img_in.cols, CV_32FC1);

	for (int i = 0; i < gray.rows; i++)
		for (int j = 0; j < gray.cols; j++)
		{
			media.at<uchar>(i, j) = 0;
		}

	printf("Please enter the order: ");
	scanf("%d", &order);

	start = (int)getTickCount();

	for(int i = order/2; i < gray.rows - order/2; i++)
		for (int j = order / 2; j < gray.cols - order / 2; j++)
		{
			soma = 0;
			for (int x = -order / 2; x <= order / 2; x++)
				for (int y = -order / 2; y <= order / 2; y++)
					soma += (float)gray.at<uchar>(i + x, j + y);
			media.at<uchar>(i, j) = (int)(soma / (order*order));
		}

	end = (int)getTickCount();
	
	tmili = ((end - start)/getTickFrequency());
	
	printf("\nO tempo gasto para aplicar o filtro da media foi:\t%d ms\n", tmili);

	imshow("Media Filter", media);
	imwrite("Media-Filter.jpg", media);

}

Mat base::cannyFilter(Mat in)
{
	Mat result;
	in = openImage(img_name);
	convertBGR2GRAY(in);

	Canny(in, result, 127, 200, 3);
	imwrite("Canny.jpg", result);

	return result;
}

void base::thresHoldImage()
{
	img_in = openImage(img_name);
	convertBGR2GRAY(img_in);

	vector<Mat> limiarizada(5);

	threshold(gray, limiarizada.at(0), 127, 255, CV_THRESH_BINARY);
	threshold(gray, limiarizada.at(1), 127, 255, CV_THRESH_BINARY_INV);
	threshold(gray, limiarizada.at(2), 127, 255, CV_THRESH_TRUNC);
	threshold(gray, limiarizada.at(3), 127, 255, CV_THRESH_TOZERO);
	threshold(gray, limiarizada.at(4), 127, 255, CV_THRESH_TOZERO_INV);

	showImage("LimiarBin", limiarizada.at(0));
	showImage("LimiarBinInv", limiarizada.at(1));
	showImage("LimiarTruncada", limiarizada.at(2));
	showImage("LimiarToZero", limiarizada.at(3));
	showImage("LimiarToZeroInv", limiarizada.at(4));

	imwrite("LimiarBin.jpg", limiarizada.at(0));
	imwrite("LimiarBinInv.jpg", limiarizada.at(1));
	imwrite("LimiarTrunc.jpg", limiarizada.at(2));
	imwrite("LimiarToZero.jpg", limiarizada.at(3));
	imwrite("LimiarToZeroInv.jpg", limiarizada.at(4));

}

void base::resizeImage()
{
	img_in = openImage(img_name);
	convertBGR2GRAY(img_in);

	Mat maior(gray.cols * 2, gray.rows * 2, 1);
	Mat menor(gray.cols / 2, gray.rows / 2, 1);

	resize(gray, maior, Size(maior.rows, maior.cols), 1);
	resize(gray, menor, Size(menor.rows, menor.cols), 1);

	showImage("Maior", maior);
	showImage("Menor", menor);
	imwrite("Maior.jpg", maior);
	imwrite("Menor.jpg", menor);
}

FILE* base::openFileWrite(FILE* file, char* nome) {
	file = fopen(nome, "w");
	return file;
}

FILE* base::openFileRead(FILE* file, char* nome) {
	file = fopen(nome, "r");
	return file;
}

void base::closeFile(FILE* file) {
	fclose(file);
}

void base::matrixInFile()
{
	img_in = openImage(img_name);
	gray = convertBGR2GRAY(img_in);
	file_out = openFileWrite(file_out, "Result.txt");

	for (int i = 0; i < img_in.rows; i++)
	{
		for (int j = 0; j < img_in.cols; j++)
			fprintf(file_out, "%d ", img_in.at<uchar>(i, j));

		fprintf(file_out, "\n");
	}

	closeFile(file_out);
}

void base::manualThresHolding()
{
}

void base::centroIdRectangle()
{
}

void base::file2Image()
{
}

void base::sobelFilter()
{
}

void base::captureFrame()
{
}

void base::captureFrameAndCanny()
{
}

Mat base::histograma(Mat in)
{
	return Mat();
}

Mat base::equalizer()
{
	return Mat();
}

Mat base::equalizerManual()
{
	return Mat();
}

void base::laplacianAndEqualizer()
{
}

void base::sobelAndGradiente()
{
}
