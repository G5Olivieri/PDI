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

	// metade imagem
	cv::Mat img_hlf;

	// suave imagem
	cv::Mat img_svz;
	// Nomeando windows
	cv::namedWindow("Exemplo Cinza", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Exemplo Canny", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Exemplo RGB", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Exemplo Metade", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Exemplo Metade Suavizada", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Exemplo Canny Suavizada", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Exemplo Cinza Suavizada", cv::WINDOW_AUTOSIZE);
	// abrindo imagem
	img_rgb = cv::imread(argv[1]);
	if (img_rgb.empty())
	{
		std::cout << "Nao foi possivel abrir imagem <" << argv[1] << ">\n";
		return 1;
	}
	cv::imshow("Exemplo RGB", img_rgb);

	// metade da imagem
	cv::pyrDown(img_rgb, img_hlf);
	cv::imshow("Exemplo Metade", img_hlf);

	// suavidando metade
	cv::GaussianBlur(img_hlf, img_svz, cv::Size(5, 5), 4, 4);
	cv::imshow("Exemplo Metade Suavizada", img_hlf);
	
	// convertendo imagem para tom de cinza
	cv::cvtColor(img_hlf, img_gry, cv::COLOR_BGR2GRAY);
	cv::imshow("Exemplo Cinza", img_gry);
	
	// convertendo para Canny
	cv::Canny(img_gry, img_cny, 10, 100, 3, true);
	cv::imshow("Exemplo Canny", img_cny);

	// novamente só que agora borrado
	cv::cvtColor(img_svz, img_gry, cv::COLOR_BGR2GRAY);
	cv::imshow("Exemplo Cinza Suavizada", img_gry);
	cv::Canny(img_gry, img_cny, 10, 100, 3, true);
	cv::imshow("Exemplo Canny Suavizada", img_cny);

	// setando pixel
	// pixels
	int x = 16, y = 32;
	cv::Vec3b intensity = img_rgb.at< cv::Vec3b >(y, x);
	uchar blue  = intensity[0];
	uchar green = intensity[1];
	uchar red   = intensity[2];

	std::cout << "At (x, y) = (" << x << ", " << y <<
		"): (blue, green, red) = (" << (unsigned int)blue << ", " <<
		(unsigned int)green << ", " << (unsigned int)red << ")\n";
	std::cout << "Gray pixel there is: " <<
		(unsigned int)img_gry.at<uchar>(y, x) << std::endl;
	
	x /= 4; y /= 4;
	std::cout << "Pyramid2 pixel there is: " <<
		(unsigned int)img_hlf.at<uchar>(y, x) << std::endl;
	
	img_cny.at<uchar>(x, y) = 128; 

	cv::waitKey(0);
	return 0;
}