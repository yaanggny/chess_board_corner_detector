/*  Copyright 2017 onlyliu(997737609@qq.com).                             */
/*                                                                        */
/*  Automatic Camera and Range Sensor Calibration using a single Shot     */
/*  this project realize the papar: Automatic Camera and Range Sensor     */
/*  Calibration using a single Shot                                       */



#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "corner_detector.h"
#include "ChessboradStruct.h"

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>

using namespace cv;
using namespace std;
using std::vector;
vector<Point2i> points;

int main(int argc, char* argv[])
{
    cv::Mat src, src1;
    string sr = "02.png";
    if(argc >= 2)
     sr = string(argv[1]);

	int c_w = atoi(argv[2]);
	int c_h = atoi(argv[3]);

    string simage = sr;
	src1 = imread(simage.c_str(), -1);//载入测试图像

	if (src1.channels() == 1)
	{
		src = src1.clone();
	}
	else
	{
		if (src1.channels() == 3)
		{
			cv::cvtColor(src1, src, cv::COLOR_BGR2GRAY);
		}
		else
		{
			if (src1.channels() == 4)
			{
				cv::cvtColor(src1, src, cv::COLOR_BGRA2GRAY);
			}
		}
	}

	if (src.empty())
	{
		printf("Cannot read image file: %s\n", simage.c_str());
		return -1;
	}
	else
	{
		printf("read image file ok\n");
	}
	
	double t = (double)getTickCount();
	std::vector<cv::Mat> chessboards;
	CornerDetAC corner_detector;
	ChessboradStruct chessboardstruct;

	Corners corners_s;
	corner_detector.detectCorners(src, corners_s, 0.01);

	cv::Mat imgc = src.clone();
	cv::Mat imgc2 = src.clone();
	if(src.channels() < 3)
	{
		cv::cvtColor(src, imgc, cv::COLOR_GRAY2BGR);
		imgc2 = imgc.clone();
	}
	int cnt = 0;
	int cb_size = c_h*c_w;
	for(const auto& p: corners_s.p)
	{
		cv::Point c(p.x+0.5, p.y+0.5);
		cv::circle(imgc, c, 3, CV_RGB(255, 0, 0));
		cv::putText(imgc2, std::to_string(cnt), c, cv::FONT_HERSHEY_DUPLEX, 0.3, CV_RGB(0, 0, 255));
		cnt++;
		if(cnt > cb_size) break;
	}

	cv::imwrite("res_pt.png", imgc);
	cv::imwrite("res_pt_order.png", imgc2);

	t = ((double)getTickCount() - t) / getTickFrequency();
	std::cout << "time cost :" << t << std::endl;
     
	// ImageChessesStruct ics;
	// chessboardstruct.chessboardsFromCorners(corners_s, chessboards, 0.6);
	// chessboardstruct.drawchessboard(src1, corners_s, chessboards, "cb", 0);

     return 0;
}

