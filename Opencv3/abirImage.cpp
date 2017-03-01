#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	// se o usuario nao colocar argumento na hora de chamar
	// o programa manual será mostrado e execução acaba
	if (argc < 2)
	{
		cout << "Uso: " << argv[0] << " <File_image>\n";
		return 0;
	}
	
	// instanciando objeto imagem e abrindo uma imagem
	// com o nome do argumento
	Mat img;
	img = imread(argv[1]);

	// testando se imagem foi aberta
	if (img.empty())
	{
		cout << "Erro ao abrir a imagem\n";
		return -1;
	}
	
	// criando janela
	namedWindow("Imagem", WINDOW_AUTOSIZE);
	
	// abrindo janela com imagem
	imshow("Imagem", img);

	// espera hit do teclado
	waitKey(0);
	
	return 0;
}