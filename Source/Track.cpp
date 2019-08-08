/*
------------------------------------------------------------------------------------------------------------------------------------------
Description   : Track
------------------------------------------------------------------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------------------------
*/

#include "Track.h"


/*
--------------------------------------------------------------------------------------------------
Functions definition
--------------------------------------------------------------------------------------------------
*/

Track::Track()
{
   //init stuff
   faces_to_track = 1;
   for (size_t i = 0; i < faces_to_track; i++){ 		
			track_face.push_back(false);
			selectObject.push_back(false);
			timer.push_back(0);
			trackObject.push_back(0);
			sleeptime.push_back(0);
		}
}

/************************************************************************
 * Adaptation of CamShift, a tracking algorithm which includes 3 steps:	*
 * 1. Back Projection							* 
 * 2. meanShift 							*
 * 3. Track								*
 ***********************************************************************/

void Track::track_object(cv::Mat& frame, int trackObject, cv::Rect selection, int k, cv::Mat& frame_dst, Util* util)
{

    cv::Rect trackWindow;
    int hsize = 16;
    float hranges[] = { 0, 180 };
    const float* phranges = hranges;

    cv::Mat hsv, hue, mask, hist, histimg = cv::Mat::zeros(200, 320, CV_8UC3), backproj;
    bool paused = false;

    struct timespec t_track, now_track;

    clock_gettime(CLOCK_MONOTONIC, &t_track);
    cv::cvtColor(frame, hsv, CV_BGR2HSV);

    /****************************************************************************************************************
	* 1 Back Projection uses the histogram of image to show the probabilities of colors may appear in each pixel	*
	* First transform the picture space to HSV space 								* 
	* Secondly split the H channel out, as a single grayscale image, and get its histogram, and normalize it. 	*
	* Thirdly use “calcBackProject()” function to calculate the back projection of the image			*
	***************************************************************************************************************/
   
    int _vmin = 10, _vmax = 100, _smin = 30;
    cv::inRange(hsv, cv::Scalar(0, _smin, MIN(_vmin, _vmax)),
        cv::Scalar(180, 256, MAX(_vmin, _vmax)), mask);

    int ch[] = { 0, 0 };
    hue.create(hsv.size(), hsv.depth());
    mixChannels(&hsv, 1, &hue, 1, ch, 1);

    if (trackObject < 0) {
        cv::Mat roi(hue, selection), maskroi(mask, selection);
        cv::calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
        cv::normalize(hist, hist, 0, 255, CV_MINMAX);
        trackWindow = selection;
        histimg = cv::Scalar::all(0);
        int binW = histimg.cols / hsize;
        cv::Mat buf(1, hsize, CV_8UC3);

        for (int i = 0; i < hsize; i++)
            buf.at<cv::Vec3b>(i) = cv::Vec3b(cv::saturate_cast<uchar>(i * 180. / hsize), 255, 255);

        cv::cvtColor(buf, buf, CV_HSV2BGR);

        for (int i = 0; i < hsize; i++) {
            int val = cv::saturate_cast<int>(hist.at<float>(i) * histimg.rows / 255);
            cv::rectangle(histimg, cv::Point(i * binW, histimg.rows),
                cv::Point((i + 1) * binW, histimg.rows - val),
                cv::Scalar(buf.at<cv::Vec3b>(i)), -1, 8);
        }
        
        roi.release();		
        maskroi.release();		
        buf.release();	
    }
    cv::calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
    backproj &= mask;

    /* 2 Apply meanshift to get the new location and Setup the termination criteria */
    cv::RotatedRect trackBox = cv::CamShift(backproj, trackWindow,
        cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1));

    /* 3 Track frames captured, the initial window of each frame is the output window of the prior frame.*/
    if (trackWindow.area() <= 1) {
        int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5) / 6;
        trackWindow = cv::Rect(trackWindow.x - r, trackWindow.y - r,
                          trackWindow.x + r, trackWindow.y + r) & cv::Rect(0, 0, cols, rows);
    }

    //show tracked face
    cv::Point pt1(trackWindow.x, trackWindow.y - trackWindow.height / 2.5);
    cv::Point pt2(pt1.x + trackWindow.width + trackWindow.width / 2.5, pt1.y + trackWindow.height + trackWindow.height / 5.4);
    cv::rectangle(frame, pt1, pt2, cv::Scalar(150, 150, 255), 2, 8, 0);

    util->faceFound = 1;

    clock_gettime(CLOCK_MONOTONIC, &now_track);
    util->tracking = util->diff(t_track, now_track).tv_nsec / 1000000.0;

    try {
        
        cv::Rect faces_;
        
        faces_.x = trackWindow.x;
        faces_.y = trackWindow.y - trackWindow.height / 2.5;
        faces_.width = trackWindow.width + trackWindow.width / 2.5;
        faces_.height = trackWindow.height + trackWindow.height / 5.4;
  
        //detect features of the tracked face
        bool boolRightEye, boolLeftEye, boolMouth, boolNose;

        Feature *features = new Feature();
		
        boolRightEye 	= features->detectRightEye(faces_,  frame, frame_dst, util);
        boolLeftEye 	= features->detectLeftEye(faces_, frame, frame_dst, util);
        boolMouth 		= features->detectMouth(faces_, frame, frame_dst, util);
        boolNose 		= features->detectNose(faces_, frame, frame_dst, util);

        delete features;
        
        hsv.release();		
        hue.release();		
        mask.release();		
        hist.release();		
        histimg.release();			

        if (boolRightEye || boolLeftEye || boolMouth || boolNose)
            timer[k] = 0;
        else
            timer[k]++; 

        //if no feature is found for a certain number of iterations then disable face tracking, face will have to be detected again
        if (timer[k] > 25)
            track_face[k] = false;
    }
    catch (std::exception& e) {
    }
}

