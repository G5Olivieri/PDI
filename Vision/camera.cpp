#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
	// mesma coisa de abrir um video só que 0
	// é igual a primeira cam conectada
	VideoCapture capture(0);
	Mat frame;

	if (!capture.isOpened())
		throw "Error when reading steam_avi";

	namedWindow("Live", WINDOW_AUTOSIZE);
	
	do
	{
		capture >> frame;
		if (frame.empty()) break;
		imshow("Live", frame);
	} while (waitKey(30) != 'q');
				
	return 0;
}