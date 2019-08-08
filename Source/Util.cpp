/*
------------------------------------------------------------------------------------------------------------------------------------------
Description : Utilities function
------------------------------------------------------------------------------------------------------------------------------------------
*/

/*
----------------------------------------------------------------------------------------------------------------------------------------
Includes
----------------------------------------------------------------------------------------------------------------------------------------
*/
#include "Util.h"

/*
--------------------------------------------------------------------------------------------------
Functions definition
--------------------------------------------------------------------------------------------------
*/

Util::Util()
{
   //init stuff
   	fps 		= 0; gray		= 0; equa 	= 0; clah 			= 0;
	face 	= 0; nose 	= 0; mou 	= 0; tracking 	= 0;
	rEye 	= 0; rEyeO 	= 0; lEye 	= 0; lEyeO 		= 0;

	faceFound 	= 0; noseFound 		= 0; mouFound 	= 0;
	rEyeFound 	= 0; rEyeOFound 	= 0; lEyeFound 	= 0; lEyeOFound = 0;
	
	filename 	= "TabularData.csv";		//csv output file ouptut
	
	face_cascade_name 			= "haarcascade/haarcascade_frontalface_alt.xml";				// get location of face cascade
    mouth_cascade_name 		= "haarcascade/haarcascade_mcs_mouth.xml";					// get location of mouth cascade
	nose_cascade_name 		= "haarcascade/haarcascade_mcs_nose.xml";					// get location of nose cascade
	rEyes_cascade_name 		= "haarcascade/haarcascade_righteye_2splits.xml";			// get location of left eye cascade
	lEyes_cascade_name 		= "haarcascade/haarcascade_lefteye_2splits.xml";				// get location of left eye cascade
	eyesCld_cascade_name 	= "haarcascade/haarcascade_eye_tree_eyeglasses.xml";	// get location of closed eye cascade
	
	//Variables for the CSV columns headers
	csv_1 			= "FPS";
	csv_2 			= "GrayScale_Func [ms]";
	csv_3 			= "EqualizeHist_Func [ms]";
	csv_4 			= "Clahe_Func [ms]";
	csv_5 			= "Face_Func [ms]";
	csv_6 			= "Nose_Func [ms]";
	csv_7 			= "Mouth_Func [ms]";
	csv_8 			= "RightEye_Func [ms]";
	csv_9 			= "REyeOpen_Func [ms]";
	csv_10 		= "LeftEye_Func [ms]";
	csv_11 		= "LEyeopen_Func [ms]";
	csv_12 		= "Tracking_Func [ms]";
	csv_13 		= "FaceFound?";
	csv_14 		= "NoseFound?";
	csv_15 		= "MouthFound?";
	csv_16 		= "RightEyeFound?";
	csv_17 		= "REyeOpenFound?";
	csv_18 		= "LeftEyeFound?";
	csv_19 		= "LEyeopenFound?";
}

//load all the cascades
int Util::loadCascades(){

	struct timespec t, now;
	clock_gettime(CLOCK_MONOTONIC, &t);

	if (!face_cascade.load(face_cascade_name)) 				{ printf("--(!)Error loading face cascade\n"); 				return -1; };
	if (!lEyes_cascade.load(lEyes_cascade_name)) 			{ printf("--(!)Error loading l eyes cascade\n");			return -1; };
	if (!rEyes_cascade.load(rEyes_cascade_name)) 			{ printf("--(!)Error loading r eyes cascade\n");			return -1; };
	if (!mouth_cascade.load(mouth_cascade_name)) 			{ printf("--(!)Error loading mouth cascade\n"); 			return -1; };
	if (!nose_cascade.load(nose_cascade_name)) 				{ printf("--(!)Error loading nose cascade\n"); 			return -1; };
	if (!eyesCld_cascade.load(eyesCld_cascade_name))	{ printf("--(!)Error loading closed eyes cascade\n");	return -1; };

	clock_gettime(CLOCK_MONOTONIC, &now);
	//printf ("cascades loaded in: %4.3f [ms]\n", diff(t,now).tv_nsec/1000000.0);
}

// create and open the .csv file
void Util::openCSV(){
	fs.open(filename);					
	// write the file headers
    	fs 	<< csv_1 << "," << csv_2 << "," << csv_3 << "," << csv_4 << ","
		<< csv_5 << "," << csv_6 << "," << csv_7 << "," << csv_8 << ","
		<< csv_9 << "," << csv_10 << "," << csv_11 <<  "," << csv_12 << ","
		<< csv_13 << "," << csv_14 << "," << csv_15 <<  "," << csv_16 << ","
		<< csv_17 << "," << csv_18 << "," << csv_19 << std::endl;
}

void Util::writeCSV(){					
	// write data
    	fs 	<< fps << "," << gray << "," << equa << "," << clah << ","
		<< face << "," << nose << "," << mou << "," << rEye << ","
		<< rEyeO << "," << lEye << "," << lEyeO <<  "," << tracking << "," 
		<< faceFound << "," << noseFound << "," << mouFound <<  "," << rEyeFound << "," 
		<< rEyeOFound << "," << lEyeFound << "," << lEyeOFound << std::endl;
}

// Find center of faces, Draw ellipse around face
void Util::showFace(cv::Rect faces, cv::Mat& frame){

	cv::Point center(faces.x + faces.width/2, faces.y + faces.height/2);

	//ellipse(frame, center, axes, angle, startAngle, endAngle, color,thickness, lineType, shift) 
	cv::ellipse(frame, center, cv::Size(faces.width/2, faces.height/2), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0); 

}

// Find center of feature, draw rectangle around feature
void Util::showFeatures(std::vector<cv::Rect> feature, cv::Mat& frame, cv::Rect featureROI, int k, int r, int g, int b){

		cv::Point pt1(feature[0].x, feature[0].y);
		cv::Point pt2(pt1.x + feature[0].width, pt1.y + feature[0].height/k);

		//rectangle(frame, point1, point2, color, thickness, lineType, shift)
		cv::rectangle(frame(featureROI), pt1, pt2, cv::Scalar(r, g, b), 2, 8, 0); 
}

void Util::display(cv::Mat& frame)
{
    struct timespec showInit, showEnd;
    clock_gettime(CLOCK_MONOTONIC, &showInit);
    cv::namedWindow("Face detection", cv::WINDOW_NORMAL);
    cv::imshow("Face detection", frame); 	//Show final result
    clock_gettime(CLOCK_MONOTONIC, &showEnd);
    //printf ("Time to show the results: %4.3f [ms]\n", diff(showInit, showEnd).tv_nsec/1000000.0);
}

/* adds a value ms expressed in nanoseconds to the time variable pointed by t */
timespec Util::diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}



