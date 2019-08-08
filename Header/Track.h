/*
------------------------------------------------------------------------------------------------------------------------------------------
Description : Adaptation of CamShift, a tracking algorithm which includes 3 steps:
1. Back Projection
2. meanShift 	
3. Track	
------------------------------------------------------------------------------------------------------------------------------------------
*/
#pragma once

/*
----------------------------------------------------------------------------------------------------------------------------------------
Includes
----------------------------------------------------------------------------------------------------------------------------------------
*/
#include <opencv2/opencv.hpp>
#include "Util.h"
#include "Feature.h"
/*
--------------------------------------------------------------------------------------------------
Class Declaration
--------------------------------------------------------------------------------------------------
*/
class Track {

public:

	/*
	--------------------------------------------------------------------------------------------------
	Public Function Prototyping
	--------------------------------------------------------------------------------------------------
	*/
	Track();
	
	 void track_object(cv::Mat& frame, int trackObject, cv::Rect selection, int k, cv::Mat& frame_dst, Util* u);  
	 
	std::vector<bool> 	track_face;
	std::vector<bool> 	selectObject;
	std::vector<int >		timer;
	std::vector<int> 		trackObject;
	std::vector<int> 		sleeptime;
	
	cv::Rect 	selection;
	bool 		isFrameImage;
	int 			faces_to_track;
	 
private:

	
};
