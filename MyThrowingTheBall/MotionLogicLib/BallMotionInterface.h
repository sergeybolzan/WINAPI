#ifndef BALLMOTIONINTERFACE_H_239687FLKEF
#define BALLMOTIONINTERFACE_H_239687FLKEF


// structure for 3d vector
// can be treated as
//     speed (m/s), position(m), acceleration(m/[s*s])
//
//  !!!  positive acceleration will increase speed on the axis with time
//  so for the gravity use negative Value!
// 

struct SD_VECTOR
{
    double x_axis;
    double y_axis;
    double z_axis;
};

//  the task is:
//
//   use external library for motion calculation
//
//   we have next start input:
//    input_01) initial position
//    input_02) initial speed
//    input_03) external forses for change speed with time
//
//    input_04) set final position to Acquire
//               (when we need to stop motion)
////      also: about final position to Acquire
//        -- THIS is special case, we can setup this class with another external interface for check - should we continue to move
//                this class can specify the surface function for example
//        but task it just heat the ground or reach the orbit
//
//   todo:
//     do_01) setup ball motion with these data
//     do_02) setup ball motion interface with passed time
//     do_02')  acquire current position and speed
//     do_03)  release ball motion object when no need more
//
//   Note As far as we no need to do more, we will not do more then requested
//   but of course, we can simulate changing of speed or teleportation with new methods

class IBallMotion
{
    public:
//    input_03) external forses for change speed with time   (do_01)
    virtual void AddForse(SD_VECTOR* const a_pForse)throw() = 0;

//     do_02) setup ball motion interface with passed time
//     do_02')  acquire current position and speed
    // time in seconds
    //
    //
    // returns false if you reach the motion limit
    //         true - motion can be continued
    // double* ap_ResultTime - result time of fly - calculated more presizely
    //   will be filled only when BallMotion returns true
    virtual bool BallMotion(const double a_dt, SD_VECTOR* a_pPosition, SD_VECTOR* a_pSpeed, double* ap_ResultTime)throw() = 0;

    // input_04) final position to Acquire
    // nullptr if no need to check for edge
    //    using #include <limits>  std::numeric_limits< double >::max();/lowest() by default
    virtual void BallMotionEdges(SD_VECTOR* a_pLower, SD_VECTOR* a_pUpper)throw() = 0;


};

#ifdef MOTIONLOGICLIB_EXPORTS
// #define MOTIONLOGICLIB_API extern "C" __declspec(dllexport)
#else

// return nullptr in case of no memory
//
// if any of SD_VECTOR*s nullptr - the deafult values are 0
//


// do_03) release ball motion object when no need more
typedef  void (__cdecl *FinalizeMotionForBallF)(IBallMotion const *)throw();
#define FinalizeMotionForBallFUNCTION_NAME "FinalizeMotionForBall"

// create an exemplar
// create an object
//    input_01) initial position  (do_01)
//    input_02) initial speed     (do_01)
// creates new Ball Motion object 
//
// return nullptr in case of no memory
//
// if any of SD_VECTOR*s nullptr - the deafult values are 0
//
//

typedef  IBallMotion* (__cdecl *RequestBallMotionF)(SD_VECTOR* const a_pPosition, SD_VECTOR* const a_pSpeed)throw();
#define RequestBallMotionFUNCTION_NAME "RequestBallMotion"

#endif

#endif