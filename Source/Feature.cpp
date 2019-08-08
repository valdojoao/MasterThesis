/*
------------------------------------------------------------------------------------------------------------------------------------------
Description : Features function
------------------------------------------------------------------------------------------------------------------------------------------
*/

/*
----------------------------------------------------------------------------------------------------------------------------------------
Includes
----------------------------------------------------------------------------------------------------------------------------------------
*/
#include "Feature.h"

/*
--------------------------------------------------------------------------------------------------
Functions definition
--------------------------------------------------------------------------------------------------
*/

Feature::Feature()
{
   //init stuff
}


bool Feature::detectRightEye(cv::Rect faces, cv::Mat& frame, cv::Mat& frame_gray, Util* util){
	
	struct timespec t, now, open, closed;
    std::vector<cv::Rect> rEyes, rClosedEyes;

    //right eye region of interrest, upper right side of face
    cv::Rect rROI = cv::Rect(faces.x, (faces.y + faces.height / 4), faces.width / 2, faces.height / 2.75);

    //detect open or closed eyes
    clock_gettime(CLOCK_MONOTONIC, &t);
    util->rEyes_cascade.detectMultiScale((frame_gray)(rROI), rEyes, 1.1, 2, cv::CASCADE_FIND_BIGGEST_OBJECT, cv::Size(30, 30));
    clock_gettime(CLOCK_MONOTONIC, &now);
    util->rEye = util->diff(t,now).tv_nsec/1000000.0;

    if (!rEyes.empty()) { //show detected right eye and determine if its opened or closed

        util->showFeatures(rEyes, frame, rROI, 1, 255, 0, 0);

        clock_gettime(CLOCK_MONOTONIC, &open);
        util->eyesCld_cascade.detectMultiScale((frame_gray)(rROI), rClosedEyes, 1.2, 2, cv::CASCADE_FIND_BIGGEST_OBJECT, cv::Size(30, 30));
        clock_gettime(CLOCK_MONOTONIC, &closed);
        util->rEyeO = util->diff(open, closed).tv_nsec/1000000.0;

	    util->rEyeFound = 1;

        if (!rClosedEyes.empty()) { //if eye is open show pupil
            util->rEyeOFound = 1;
            cv::circle(frame(rROI), cv::Point(rEyes[0].x + rEyes[0].width / 2, rEyes[0].y + rEyes[0].height / 1.5), 3, cv::Scalar(0, 255, 0), -1, 8);
        }

        return true;
    }
    else
        return false;

}

bool Feature::detectLeftEye(cv::Rect faces, cv::Mat& frame, cv::Mat& frame_gray, Util* util)
{

	struct timespec t, now, open, closed;
    std::vector<cv::Rect> lEyes,  lClosedEyes;

    //left region of interrest, upper left side of face
    cv::Rect lROI = cv::Rect(faces.x + faces.width / 2.5, (faces.y + faces.height / 4), faces.width / 2, faces.height / 2.75);

    //detect open or closed eyes
    clock_gettime(CLOCK_MONOTONIC, &t);
    util->lEyes_cascade.detectMultiScale((frame_gray)(lROI), lEyes, 1.1, 2, cv::CASCADE_FIND_BIGGEST_OBJECT, cv::Size(30, 30));
    clock_gettime(CLOCK_MONOTONIC, &now);
    util->lEye = util->diff(t,now).tv_nsec/1000000.0;

    if (!lEyes.empty()) { //show detected left eye and determine if its opened or closed
        util->showFeatures(lEyes, frame, lROI, 1, 255, 0, 0);

        clock_gettime(CLOCK_MONOTONIC, &open);
        util->eyesCld_cascade.detectMultiScale((frame_gray)(lROI), lClosedEyes, 1.2, 2, cv::CASCADE_FIND_BIGGEST_OBJECT, cv::Size(30, 30));
        clock_gettime(CLOCK_MONOTONIC, &closed);
        util->lEyeO = util->diff(open, closed).tv_nsec/1000000.0;

        util->lEyeFound = 1;

        if (!lClosedEyes.empty()){
            util->rEyeOFound = 1;
            cv::circle(frame(lROI), cv::Point(lEyes[0].x + lEyes[0].width / 2, lEyes[0].y + lEyes[0].height / 1.5), 3, cv::Scalar(0, 255, 0), -1, 8);
	    }
        return true;
    }
    else
        return false;
}

bool Feature::detectMouth(cv::Rect faces,  cv::Mat& frame, cv::Mat& frame_gray, Util* util){

	struct timespec t, now;
    std::vector<cv::Rect> mouth;

    //mouth region of interrest, lower part of face
    cv::Rect mouthROI = cv::Rect((faces.x + faces.width/4), (faces.y + faces.height/1.5), faces.width/1.8, faces.height/2.75);

    //detect mouth
    clock_gettime(CLOCK_MONOTONIC, &t);
    util->mouth_cascade.detectMultiScale((frame_gray)(mouthROI), mouth, 1.2, 5, cv::CASCADE_FIND_BIGGEST_OBJECT, cv::Size(30, 30));
    clock_gettime(CLOCK_MONOTONIC, &now);
    util->mou = util->diff(t,now).tv_nsec/1000000.0;

    //show detected mouth
    if (!mouth.empty()) {
        util->mouFound = 1;
        util->showFeatures(mouth, frame, mouthROI, 1, 255, 255, 0);
        return true;
    }
    else
        return false;
}

bool Feature::detectNose(cv::Rect faces,cv::Mat& frame, cv::Mat& frame_gray, Util* util){

	struct timespec t, now;
    std::vector<cv::Rect> nose;

    //nose region of interest, central part of face
    cv::Rect noseROI = cv::Rect((faces.x + faces.width / 4), (faces.y + faces.height / 2.2), faces.width / 1.8, faces.height / 3);

    //detect nose
    clock_gettime(CLOCK_MONOTONIC, &t);
    util->nose_cascade.detectMultiScale((frame_gray)(noseROI), nose, 1.20, 5, cv::CASCADE_FIND_BIGGEST_OBJECT, cv::Size(30, 30));
    clock_gettime(CLOCK_MONOTONIC, &now);
    util->nose = util->diff(t,now).tv_nsec/1000000.0;

    //show detected nose
    if (!nose.empty()) {
	    util->noseFound = 1;
        util->showFeatures(nose, frame, noseROI, 2, 0, 0, 255);
        return true;
    }
    else
        return false;
}

