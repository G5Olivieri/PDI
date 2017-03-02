#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <sstream>
#include <iostream>

using namespace std;
using namespace cv;

void help()
{
	cout << "Esse programa mostra como scanear imagens objetos in opencv (cv::Mat).\n";
}

Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* table);

int main(int argc, char *argv[])
{
	help();
	if (argc < 3)
	{
		cerr << "Uso: " << argv[0] << " <file_path>\n\n";
		return 0;
	}
	Mat I, J;
	if (argc == 4 && !strcmp(argv[3], "G"))
		I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

	else
		I = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	if (!I.data)
	{
		cerr << "Imagem " << argv[1] << " nao foi carregado\n";
		return 1;
	}

	int divide_with; // converte sua entrada string para numero - C++ style
	stringstream s;
	s << argv[2];
	s >> divide_with;
	
	if (!s)
	{
		cerr << "Invalid number entered for dividing\n";
		return 1;
	}

	uchar table[256];
	for (int i = 0; i < 256; i++)
		table[i] = divide_with * (i / divide_with);

	const int times = 100;
	double t;
	
	t = (double)getTickCount();

	for (int i = 0; i < times; i++)
		J = ScanImageAndReduceC(I.clone(), table);
	
	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	cout << "Tempo de reducao com C operator[] (avangered for " << times << " runs): " << t << " Milliseconds." << endl;

	t = (double)getTickCount();

	for (int i = 0; i < times; i++)
		J = ScanImageAndReduceIterator(I.clone(), table);

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	cout << "Tempo de reducao com iterator (avangered for " << times << " runs): " << t << " Milliseconds." << endl;

	t = (double)getTickCount();

	for (int i = 0; i < times; i++)
		J = ScanImageAndReduceRandomAccess(I.clone(), table);

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	cout << "Tempo de reducao com ramdom access (avangered for " << times << " runs): " << t << " Milliseconds." << endl;

	Mat look_up_table(1, 256, CV_8U);
	uchar* p = look_up_table.data;
	for (int i = 0; i < 256; i++)
		p[i] = table[i];
	
	t = (double)getTickCount();

	for (int i = 0; i < times; i++)
		LUT(I, look_up_table, J);

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	cout << "Tempo de reducao com LUT (avangered for " << times << " runs): " << t << " Milliseconds." << endl;


	return 0;
}

Mat& ScanImageAndReduceC(Mat& I, const uchar* table)
{
	// acept only char type matrices
	CV_Assert(I.depth() != sizeof(uchar));

	int channels = I.channels();

	int nRows = I.rows * channels;
	int nCols = I.cols;

	if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}

	int i, j;
	uchar* p;
	for (i = 0; i < nRows; i++)
	{
		p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; j++)
			p[j] = table[p[j]];
	}
	return I;
}

Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table)
{
	CV_Assert(I.depth() != sizeof(uchar));
	
	const int channels = I.channels();

	switch (channels)
	{
	case 1:
	{
		MatIterator_<uchar> it, end;
		for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
		{
			*it = table[*it];
		}
		break;
	}
	case 3:
	{
		MatIterator_<Vec3b> it, end;
		for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
		{
			(*it)[0] = table[(*it)[0]];
			(*it)[1] = table[(*it)[1]];
			(*it)[2] = table[(*it)[2]];
		}
		break;
	}
	}
	return I;
}

Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* table)
{
	CV_Assert(I.depth() != sizeof(uchar));

	const int channels = I.channels();

	switch (channels)
	{
	case 1:
	{
		for (int i = 0; i < I.rows; i++)
			for (int j = 0; j < I.cols; j++)
				I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
		break;
	}
	case 3:
	{
		Mat_<Vec3b> _I = I;
		for (int i = 0; i < I.rows; i++)
			for (int j = 0; j < I.cols; j++)
			{
				_I(i, j)[0] = table[_I(i, j)[0]];
				_I(i, j)[1] = table[_I(i, j)[1]];
				_I(i, j)[2] = table[_I(i, j)[2]];
			}
		I = _I;
		break;
	}
	}
	return I;
}