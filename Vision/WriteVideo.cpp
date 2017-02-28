#include <opencv2\opencv.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Uso: " << argv[0] << " <in_video_file_path> <out_video_file_path>\n\n";
		return 0;
	}

	cv::namedWindow("Exemplo", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Log_Polar", cv::WINDOW_AUTOSIZE);

	cv::VideoCapture cap;

	cap.open(argv[1]);

	if (!cap.isOpened())
	{
		std::cerr << "Não foi possivel abrir o video\n";
		return 1;
	}
	
	// GET VIDEO FPS
	double fps = cap.get(cv::CAP_PROP_FPS);

	// QUANTIDADE DE FRAMES TEM NO VIDEO
	cv::Size size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT));

	cv::VideoWriter writer;

	writer.open(argv[2], CV_FOURCC('M', 'J', 'P', 'G'), fps, size);


	cv::Mat logpolar_frame, bgr_frame;

	while (true)
	{
		cap >> bgr_frame;
		if (bgr_frame.empty()) break;
		cv::imshow("Exemplo", bgr_frame);
		cv::logPolar(
			bgr_frame,					// COR DE ENTRADE FRAME
			logpolar_frame,				// LOG_POLAR SAIDA FRAME
			cv::Point2f(				// PONTO CENTRAL PAR LOG-POLAR TRANSFORMAÇÃO
				bgr_frame.cols / 2,		// X
				bgr_frame.rows / 2		// Y
			),	
			40,							// MAGNITUDE (SCALE PARAMETER)
			cv::WARP_FILL_OUTLIERS		// PREENCHER OUTLIERS COM ZERO
		);
		cv::imshow("Log_Polar", logpolar_frame);
		writer << logpolar_frame;

		char c = cv::waitKey(10);
		if (c == 27) break; // ESQ = quit execution
	}

	cap.release();
	return 0;
}