========================================================================
    CONSOLE APPLICATION : ThrowingTheBall Project Overview
========================================================================

mailto:Alexey.Zaytsev@gmx.net
skype: Alexey.Zaytsev1706

parameters:

    std::cout << 
        " next parameters can be specified" << std::endl
        << "" << std::endl
        << " g:-2.5 h:2.3 sx:8 sy:3 sz:2 wx:0 wy:-7.1 wz:0  (default values)"<< std::endl
        << "" << std::endl
        << " g: gravity  (meters / (second*second)) = default acceleration for Z" << std::endl
        << " h: height (will be converted into positive value in any case)  (meters)" << std::endl
        << " height treated as initial Z coordinate, initial x and y are 0 both" << std::endl
        << " sx: speed in x Axis  (meters / second)" << std::endl
        << " sy: speed in y Axis   (meters / second)" << std::endl
        << " sz: speed in z Axis  (meters / second)" << std::endl
        << " wx: wind speed in x Axis  (meters /(second*second))   it's like we are doing acceleration" << std::endl
        << " wy: wind speed in y Axis   (meters / (second*second))  it's like we are doing acceleration" << std::endl
        << " wz: wind speed in z Axis  (meters / (second*second))  it's like we are doing acceleration" << std::endl << std::endl
        << " NOTE: overwrite every parameter to change default values" << std::endl;



for motion interface see comments in 
    #include ".\MotionLogicLib\BallMotionInterface.h" // our motion engine



The common plan Is:
1) this is console application, but we need to create a window
   //
   // so we need to link up comctl32.dll
   // studio link it without our desision
   // but anyway we can link it by own wish - check stdafx.h
   //
   // check thread_with_window.cpp/h for thread function
   // and DrawingDialog.cpp/h for window and thread function

2) we will start single thread for UI:
       in this thread we will present a dialog with our presentation.
       Presentation accumulates the data from the main thread and present it
       in dynamic motion after the data flow complete

       motion data generated inside dynamically loaded library according gravity law // height = gtt + vt +c
	   any axis can be adjusted with wind

3) main thread of the application
    will do all calculations and transfer the results to the UI thread

4) UI thread scale incoming dataand then simulate motion after no more data income

5) restriction for motion established for z coordinate inside 
variables:
    SD_VECTOR t_lowLimit = {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), 0.};
    SD_VECTOR t_highLimit = {std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), 8000.};
	so motion within [0..8000.] meters in Z coordinate will be processed




result 1)	motion during data generation changes the curve as far as we need to scale resultat

result 2)	Real motion time and position simulated inside UI window according calculated data

/////////////////////////////////////////////////////////////////////////////
