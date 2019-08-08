/*
------------------------------------------------------------------------------------------------------------------------------------------
Description : Utilities function
------------------------------------------------------------------------------------------------------------------------------------------
*/
#pragma once

/*
----------------------------------------------------------------------------------------------------------------------------------------
Includes
----------------------------------------------------------------------------------------------------------------------------------------
*/
#include <fstream>
#include <time.h>
#include <opencv2/opencv.hpp>
/*
--------------------------------------------------------------------------------------------------
Class Declaration
--------------------------------------------------------------------------------------------------
*/
class Util {

public:

	/*
	--------------------------------------------------------------------------------------------------
	Public Function Prototyping
	--------------------------------------------------------------------------------------------------
	*/
	Util();
	
	int loadCascades();
	void openCSV();
	void writeCSV();
	void showFace(cv::Rect faces, cv::Mat& frame);
	void showFeatures(std::vector<cv::Rect> feature, cv::Mat& frame, cv::Rect featureROI, int k, int r, int g, int b);
	void display(cv::Mat& frame);
	timespec diff(timespec start, timespec end);
	
	//variables to store the results in the csv
	float 	fps, gray, equa, clah;
	float 	face, nose, mou, tracking;
	float 	rEye, rEyeO, lEye, lEyeO;
	bool		faceFound, noseFound, mouFound;
	bool		rEyeFound, rEyeOFound, lEyeFound, lEyeOFound;
	
    std::ofstream 					fs;			//ofstream for the csv file output
	
	/** Classifiers */
	cv::CascadeClassifier face_cascade, mouth_cascade, nose_cascade;
	cv::CascadeClassifier rEyes_cascade, lEyes_cascade, eyesCld_cascade;
	
private:

	std::string filename ;		//csv output file ouptut
	
	//Variables for the CSV columns headers
	std::string csv_1, csv_2, csv_3, csv_4, csv_5, csv_6, csv_7, csv_8, csv_9;
	std::string csv_10, csv_11, csv_12, csv_13, csv_14, csv_15, csv_16; 
	std::string csv_17, csv_18, csv_19;	
		
	//location of the cascade of cclassifiers	
	std::string face_cascade_name, mouth_cascade_name, nose_cascade_name;
	std::string rEyes_cascade_name, lEyes_cascade_name, eyesCld_cascade_name; 
};
