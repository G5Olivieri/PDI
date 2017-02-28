#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Uso: " << argv[0] << " <File_image>\n";
		return 0;
	}
	
	Mat img;
	img = imread(argv[1], -1);
	
	if (img.empty())
	{
		cout << "Erro ao abrir a imagem\n";
		return -1;
	}

	namedWindow("Imagem", WINDOW_AUTOSIZE);
	imshow("Imagem", img);
	waitKey(0);
	destroyWindow("Imagem");
	return 0;
}