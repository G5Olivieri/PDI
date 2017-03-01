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
	cv::VideoCapture cap(argv[1]);

	std::cout << cap.grab() << std::endl;
	
	int nframes = (int)cap.get(cv::CAP_PROP_FRAME_COUNT);
	int fps = (int)cap.get(cv::CAP_PROP_FPS);
	
	std::cout << "Total frame: " << nframes << "\nfps: " << fps
		<< "\nCurrent Position: " << cap.get(cv::CAP_PROP_POS_MSEC) << std::endl;
	
	int wait_per_millisecond = 1 * 1000 / fps;

	std::cout << "Wait Per Millisecond: " << wait_per_millisecond << std::endl;
	cv::Mat frame;
	for (int i = 0; i < nframes+100; i++)
	{
		cap >> frame;
		cv::imshow("Exemplo", frame);
		std::cout << i << std::endl;
		if (cv::waitKey(fps) == 27) break;
	}
	cv::destroyWindow("Exemplo");
	return 0;
}