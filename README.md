# Master Thesis: 04/2016 - 10/2016

The project was part of my Master Thesis, the main goal was to Parallelize an Image Processing
Algorithms For Face Recognition on Multicore Platforms. The code attached refers to the sequential
implementation in order to identify the possible sources of parallelizations. The next step of the
project consisted in applying parallelization techniques which also included the modification of the
OpenCV source code, a further step consisted in applying an emotion recognition algorithm. 

All the theoretical background, design choices, implementation, results and tests are available at JOAO.pdf

Demos of the application can be found at https://youtu.be/rZGfWJrM0FM and https://youtu.be/t1XhhA-DZyE

## Algorithm
The algorithm can be described as:
1. Read Frame
2. Convert Frame to Gray Scale
3. Choose which histogram equalization to apply (equalizeHist or clahe), when a Face is detected, the histogram equalization applied is kept for the next frames.
4. Choose to Detect or to Track a Face, 
if Face was detected on Frame i, Frame i +1 should Track it then keep tracking for next frames
while is still able to, otherwise switch to detection and start again.
5. Detect Face Features (Eyes open/closed, nose, mouth)
6. Display the results
7. Write the results to csv TabularData.csv

## Milestones 
The implemented algorithm was able to overcome the Viola-Jones weakness such as: 
<br> Unable to detect faces that are rotated to a certain degree  
 Failure when the faces are very dark while the background is relatively light 
<br> Failure on significantly occluded faces, if the eyes are occluded, the detector fails  
 
Other important milestones of my thesis were:<br>
a) Development of an algorithm able to determine the best histogram equalization function to apply on each specific scenario.<br> 
b) Optimization of OpenCV object detect function<br> 
c) Improvement of OpenCV parallel implementation<br>
d) Detailed study on the reasons why the Viola-Jones Algorithm may not allow multi-core platforms (CPUs and GPUs) to be exploited at their full capacity and propose solutions able to solve this issue.  

## Requirements
OpenCV 3.1: https://docs.opencv.org/3.3.1/d7/d9f/tutorial_linux_install.html


## Instructions
In the project folder, open CMakeLists.txt and adjust the paths to your OpenCV location
Enter terminal and go to the project directory
Run:
1. cmake CMakeLists.txt
2. make
3. Run the Program
<br/>3.1 ./bin/FaceRec 0 0 to open the webcam
<br/>3.2 ./bin/FaceRec 0 img/vid.mp4 to read from a video
4. Press ESC to exit
5. On the root folder of the project a file named TabularData.csv is created
