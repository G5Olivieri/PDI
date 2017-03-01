#include <opencv2\opencv.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Uso: " << argv[0] << "<image_file_path\n";
		return 0;
	}
	
	// instanciando imagens
	
	// (Canny edge detector, Canny detector de bordas)
	cv::Mat img_cny;
	
	// RHB image
	cv::Mat img_rgb;
	
	// tom de cinza imagem
	cv::Mat img_gry;
	
	// Nomeando windows
	cv::namedWindow("Exemplo Cinza", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Exemplo Canny", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Exemplo RGB", cv::WINDOW_AUTOSIZE);
	
	// abrindo imagem
	img_rgb = cv::imread(argv[1]);
	cv::imshow("Exemplo RGB", img_rgb);

	// convertendo imagem para tom de cinza
	cv::cvtColor(img_rgb, img_gry, cv::COLOR_BGR2GRAY);
	
	// mostrar na tela
	cv::imshow("Exemplo Cinza", img_gry);
	
	// convertendo para Canny
	cv::Canny(img_gry, img_cny, 10, 100, 3, true);
	cv::imshow("Exemplo Canny", img_cny);
	
	cv::waitKey(0);
	return 0;
}