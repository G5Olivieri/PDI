#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void testando(const Mat &image)
{
	// Criando algumas janelas para mostrar no input
	// and saindo imagens de entradas
	// nomeando/criando duas janelas
	namedWindow("Exemplo-in", WINDOW_AUTOSIZE);
	namedWindow("Exemplo-out", WINDOW_AUTOSIZE);
	// Criando uma janela para monstrar sua imagem de entrada
	imshow("Exemplo-in", image);
	// Criando uma imagem para manter saida suavizada
	Mat out;
	// Suavizando
	// Note: poderia usar GaussianBlur(), blur(), medianBlur() ou BilateralFilter().
	GaussianBlur(image, out, Size(5, 5), 3, 3);
	GaussianBlur(out, out, Size(5, 5), 3, 3);
	// mostrar mudanças nas imagens
	imshow("Examplo-out", out);
	// espera o hit do usuario, a janela ira auto destroir
	waitKey(0);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Uso: " << argv[0] << "<image_file_path\n";
		return 0;
	}
	Mat img;
	img = imread(argv[1], -1);
	if (img.empty())
	{
		cout << "Erro ao abrir imagem\n";
		return 1;
	}
	testando(img);
	return 0;
}