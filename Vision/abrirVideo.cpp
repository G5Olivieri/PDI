#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

// status da trackbar
int g_slider_position = 0;
int g_run = 1;
int g_dont_set = 0;
// instanciando obj do tipo VideoCapture
VideoCapture g_cap;

void onTrackBarSlide(int pos, void *)
{
	g_cap.set(CAP_PROP_POS_FRAMES, pos);
	if (!g_dont_set)
	{
		g_run = 1;
		g_dont_set = 0;
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Uso: " << argv[0] << "<File_video>\n";
		return 0;
	}

	namedWindow("Image", WINDOW_AUTOSIZE);
	// abrindo video
	g_cap.open(String(argv[1]));
	
	// status do video
	int frames = (int) g_cap.get(CAP_PROP_FRAME_COUNT);
	int tmpw   = (int) g_cap.get(CAP_PROP_FRAME_WIDTH);
	int tmph   = (int) g_cap.get(CAP_PROP_FRAME_HEIGHT);

	cout << "O video tem:\nframes: " << frames << "\nframes dimensions: " << tmpw << ", " << tmph << endl;

	createTrackbar("Position", "Image", &g_slider_position, frames, onTrackBarSlide);

	Mat frame;

	while (true)
	{
		if (g_run) // se g_run for diferente de zero
		{
			g_cap >> frame;
			if (!frame.data) break; // verifica se foi aberto o video
			int current_pos = (int) g_cap.get(CAP_PROP_POS_FRAMES); // posição/frame atual
			g_dont_set = 1; // atribuindo 1 para que g_run não volte a ser 1
			setTrackbarPos("Position", "Image", current_pos); // atualizando track posiçao
			imshow("Image", frame);
			g_run -= 1; // diminuindo para fazer a barra andar
		}

		// 'r' roda o video, e 's' para 
		char c = (char)waitKey(10);
		if (c == 's')
		{
			g_run = 1;
			cout << "Single step, run = " << g_run << endl;
		}
		if (c == 'r')
		{
			g_run = -1;
			cout << "Run mode, run = " << g_run << endl;
		}
		if (c == 27) break; // <ESQ> termina a execução
	}
	return 0;
}