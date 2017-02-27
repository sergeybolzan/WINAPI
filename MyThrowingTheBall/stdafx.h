#pragma once

#define WIN32_LEAN_AND_MEAN
// we need windows system so use this
#define WINCOMMCTRLAPI

#include "targetver.h"

#include <limits>
#include <stdio.h>
#include <tchar.h>

#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex std::lock // synchronization
#include <sstream>        // std::stringstream
#include <vector>         // std::vector
#include <stdint.h>       // standard types
#include <memory>         // std::shared_ptr
#include <queue>          // std::queue

#include <windows.h> // thread priority adjustment
#include <commctrl.h>     // windows creation

#include <math.h> // need round


#include <string>  // std::string
#include <map>  // std::map
#include <windows.h>      // windows defines

#include "sync.h" // our synchronization class
#include "Logger.h" // our log engine


#include ".\MotionLogicLib\BallMotionInterface.h" // our motion engine


#include "GdiObject.h" // use for work with UI objects


// TODO: reference additional headers your program requires here


#define XSDV(a) a.x_axis
#define YSDV(a) a.y_axis
#define ZSDV(a) a.z_axis



