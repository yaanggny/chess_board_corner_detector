#ifndef __CORNER_DEF_H
#define __CORNER_DEF_H

#include <opencv2/core.hpp>
#include <vector>

struct Corners
{
	std::vector<cv::Point2f> p;
	std::vector<cv::Vec2f> v1;
	std::vector<cv::Vec2f> v2;
	std::vector<float> score;
};

#endif /* __CORNER_DEF_H */
