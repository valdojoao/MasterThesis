/*
------------------------------------------------------------------------------------------------------------------------------------------
Description : Detection function
------------------------------------------------------------------------------------------------------------------------------------------
*/

/*
----------------------------------------------------------------------------------------------------------------------------------------
Includes
----------------------------------------------------------------------------------------------------------------------------------------
*/
#include "Detection.h"

/*
--------------------------------------------------------------------------------------------------
Functions definition
--------------------------------------------------------------------------------------------------
*/

Detection::Detection()
{
   //init stuff
   min_face_size 	= 30; 
   bright_contrats	    = 0;
   isClahe 	            = false;
}

/*
  Convert Frame to gray scale, verify which histogram equalization to apply, if equalizeHist or Clahe
*/
void Detection::preProcessing(cv::Mat& frame, cv::Mat& frame_gray, Util* util){
	
struct timespec t_gray, now_gray, t_hist, now_hist, t_clahe, now_clahe;

    clock_gettime(CLOCK_MONOTONIC, &t_gray);
    cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY); // convert frame to gray scale
    clock_gettime(CLOCK_MONOTONIC, &now_gray);
    util->gray = util->diff(t_gray,now_gray).tv_nsec/1000000.0;

    //equalizeHist
    if (bright_contrats < 100) {
        clock_gettime(CLOCK_MONOTONIC, &t_hist);
        cv::equalizeHist(frame_gray, frame_gray); // compute the integral image - equalizeHist(src, dest)
        clock_gettime(CLOCK_MONOTONIC, &now_hist);
		util->equa = util->diff(t_hist,now_hist).tv_nsec/1000000.0;

        isClahe = false;
    }
    else {

        clock_gettime(CLOCK_MONOTONIC, &t_clahe);
        cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
        clahe->setClipLimit(4);		//clahe
        clahe->apply(frame_gray, frame_gray);
        clock_gettime(CLOCK_MONOTONIC, &now_clahe);
        util->clah = util->diff(t_clahe,now_clahe).tv_nsec/1000000.0;

        isClahe = true;
        if (bright_contrats > 150) {
            bright_contrats = 0;
            isClahe = false;
        }
    }
}

//detect or track a face
void Detection::detect(cv::Mat& frame, cv::Mat& frame_gray, Util* util, Track* track){
	
	std::vector<cv::Rect> faces; 			// create a list of rectangles for faces
    struct timespec t_face, now_face; 

    for (size_t k = 0; k < track->faces_to_track; k++) {
        if (!track->track_face[k]) { //if face is not detected, apply haarcascade to detect it

         /************************************************************************
		* detectMultiScale(mat, vector, sf, mn, flag, minsize)	          	        *
		* sf: how much image size is reduced at each image scale 		    * 
		* mn: how many neighbors each candidate rectange should retain *
		* minsize: objects smaller than that are ignored			                    *
		**********************************************************************/

            clock_gettime(CLOCK_MONOTONIC, &t_face);
            util->face_cascade.detectMultiScale(frame_gray, faces, 1.2, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(min_face_size, min_face_size));
            clock_gettime(CLOCK_MONOTONIC, &now_face);
            util->face = util->diff(t_face,now_face).tv_nsec/1000000.0;

            if (!track->isFrameImage && !faces.empty()) { //if it is a stream from a video/camera
                if (!isClahe)
                    bright_contrats = 0;
                else
                    bright_contrats = 100;
            }
            else
                bright_contrats++;

            for (int i = 0; i < faces.size(); i++) {            // for each detected face

                min_face_size = faces[0].width * 0.8; 	//define the size of face to look for

				util->faceFound = 1;	

				//Find features
                bool boolRightEye, boolLeftEye, boolMouth, boolNose;
				
				Feature *features = new Feature();

                boolRightEye	= features->detectRightEye(faces[i], frame, frame_gray, util);
                boolLeftEye 	= features->detectLeftEye(faces[i], frame, frame_gray, util);
                boolMouth 		= features->detectMouth(faces[i],  frame, frame_gray, util);
                boolNose 		= features->detectNose(faces[i], frame, frame_gray, util);
                
                delete features;

                //in order to eliminate false positives, show face only if at least one of the features is found
                if (boolRightEye || boolLeftEye || boolMouth || boolNose) {
                    //variables to track the face so that we dont need to detect it again

                    track->selection.x 			= faces[i].x;
                    track->selection.y 			= faces[i].y;
                    track->selection.width 	= faces[i].width;
                    track->selection.height 	= faces[i].height;

                    track->trackObject[k] 	= -1;
                    track->track_face[k] 	    = true;
                    track->selection &= cv::Rect(0, 0, frame.cols, frame.rows);

                    util->showFace(faces[i], frame);
                }

            }
        }
        else //face was already detected, track it i
            track->track_object(frame, track->trackObject[k], track->selection, k, frame_gray, util);
    }

}

