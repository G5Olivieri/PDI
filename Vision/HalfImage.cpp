#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Uso: " << argv[0] << "<image_file_path\n";
		return 0;
	}
	// criando as janelas
	namedWindow("Exemplo1", WINDOW_AUTOSIZE);
	namedWindow("Exemplo2", WINDOW_AUTOSIZE);
	// instanciando objetos
	Mat img, img_down;
	img = imread(argv[1]);

	if (img.empty())
	{
		cout << "Erro ao abrir imagem\n";
		return 1;
	}

	imshow("Exemplo1", img);
	// dividindo altura e larguro por 2
	// metade da tela
	pyrDown(img, img_down);
	imshow("Exemplo2", img_down);

	waitKey(0);
	return 0;
}