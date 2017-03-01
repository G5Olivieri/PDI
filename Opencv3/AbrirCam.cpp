#include <opencv2\opencv.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
	cv::namedWindow("Exemplo", cv::WINDOW_AUTOSIZE);
	cv::VideoCapture cap;

	if (argc == 1)
	{
		cap.open(0);
	}

	else
	{
		cap.open(argv[1]);
	}

	if (!cap.isOpened())
	{
		std::cerr << "Não foi possivel abrir o video\n";
		return 1;
	}

	
	return 0;
}