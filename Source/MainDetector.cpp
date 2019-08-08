/*
------------------------------------------------------------------------------------------------------------------------------------------
Description   : Main Program
------------------------------------------------------------------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------------------------
Includes
--------------------------------------------------------------------------------------------------
*/
#include "Detection.h"

/*
--------------------------------------------------------------------------------------------------
Main Process
--------------------------------------------------------------------------------------------------
*/
int main(int argc, char * argv[])
{

  /*
	--------------------------------------------------------------------------------------------------
	Class Objects
	--------------------------------------------------------------------------------------------------
	*/
  Util *utils = new Util();
  
  utils->openCSV();												//openCSV file and write header
  
  utils->loadCascades(); 
  
   cv::VideoCapture capture(argv[2]); 					// var to capture video from camera
   cv::Mat frame, frame_gray; 								// n-dimensional array to store frame data
   
   // Read the video stream or image
    if (argv[2]) { 														//go to video stream or camera	
    
	if (!capture.read(frame)) capture.open(-1); 		//no video stream, open camera


        //Start the clock in order to find the FPS
        time_t start, end;
        time(&start);
        int counter = 0;

        Detection *detection = new Detection(); 
		Track *track = new Track();
        
        while (capture.read(frame)) {

            detection->preProcessing(frame, frame_gray, utils);								//verify which histogram equalization to apply

            detection->detect(frame, frame_gray, utils, track); 									//detect Face, detect features then track 

            utils->display(frame);

            //Stop the clock and show FPS
            time(&end);
            ++counter;
            double sec = difftime(end, start);
            double fps = counter / sec;

            utils->fps = fps;
            utils->writeCSV();			                                   //write results to csv

            int c = cv::waitKey(10);
            if ((char)c == 27)
                break; //escape  
        }
            cv::destroyWindow("Face detection");            //deallocate any associated memory usage
            delete detection;
            delete track;  
    }
   
   utils->fs.close(); //close csv   
   delete utils;
  
   frame.release();		
   frame_gray.release();		
   
   return 0;
}
