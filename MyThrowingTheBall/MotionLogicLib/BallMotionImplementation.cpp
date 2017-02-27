#include "stdafx.h"

#include "BallMotionInterface.h"
#include <exception>
#include <limits>

#undef max
#undef min

namespace
{ // visible only here

enum E_AXIS
{
    e_XAxis = 0,
    e_YAxis = 1,
    e_ZAxis = 2,

    e_AXIS_COUNT = 3,
};

union U_SD_VECTOR
{
    SD_VECTOR m_vector;
    decltype(SD_VECTOR::x_axis) m_axis[E_AXIS::e_AXIS_COUNT];

    U_SD_VECTOR() // default values 0.
    {
        for (auto& value : m_axis)
            value = 0.;
    }

    U_SD_VECTOR& operator=(SD_VECTOR* const a_pSDVector)
    {
        if (nullptr == a_pSDVector)
            return *this;
        for (int i = 0; i < (int)E_AXIS::e_AXIS_COUNT; ++i)
            m_axis[i] = reinterpret_cast<U_SD_VECTOR*>(a_pSDVector)->m_axis[i];

        return *this;
    }

    U_SD_VECTOR& operator+=(SD_VECTOR* const a_pSDVector)
    {
        if (nullptr == a_pSDVector)
            return *this;
        for (int i = 0; i < (int)E_AXIS::e_AXIS_COUNT; ++i)
            m_axis[i] += reinterpret_cast<U_SD_VECTOR*>(a_pSDVector)->m_axis[i];

        return *this;
    }
};


};

class CBallMotion : public IBallMotion
{
protected:

    U_SD_VECTOR m_position;
    U_SD_VECTOR m_speed;
    U_SD_VECTOR m_acceleration;

    double m_FlyTime;

    U_SD_VECTOR m_positionLowLimit;
    U_SD_VECTOR m_positionHighLimit;

    // helper function to get position and speed at time moment for an axis
    void GetPositionSpeed(U_SD_VECTOR& a_rPosition, U_SD_VECTOR& a_rSpeed, const double a_FlyTime, const E_AXIS a_rAxis_CalculationFor)
    {
        const auto t_axis = m_acceleration.m_axis[a_rAxis_CalculationFor] * a_FlyTime + m_speed.m_axis[a_rAxis_CalculationFor]; // speed
        // speed
        a_rSpeed.m_axis[a_rAxis_CalculationFor] = t_axis;
        // motion
        a_rPosition.m_axis[a_rAxis_CalculationFor] = t_axis * a_FlyTime + m_position.m_axis[a_rAxis_CalculationFor];
    }

    // check we are inside the limits
    // return false if we a_LowEdge < a_Value < a_HighEdge
    // a_bExatLimit will become true only if (a_LowEdge == a_Value || a_Value == a_HighEdge)
    //
    bool ReachLimit(const double a_Value, const double a_LowEdge, const double a_HighEdge, bool& a_bExatLimit)
    {
        a_bExatLimit = (a_LowEdge == a_Value || a_Value == a_HighEdge);
        return a_bExatLimit || (! (a_LowEdge < a_Value && a_Value < a_HighEdge));
    }

public:

    CBallMotion(SD_VECTOR* const a_pPosition, SD_VECTOR* const a_pSpeed):m_FlyTime(0.)
    {
        m_position = a_pPosition;
        m_speed = a_pSpeed;

        for (int i = 0; i < (int)E_AXIS::e_AXIS_COUNT; ++i)
        {
            m_positionLowLimit.m_axis[i] = std::numeric_limits<double>::lowest();
            m_positionHighLimit.m_axis[i] = std::numeric_limits<double>::max();
        }
    }
//    input_03) external forses for change speed with time   (do_01)
    virtual void AddForse(SD_VECTOR* const a_pForse)throw() override
    {
        m_acceleration += a_pForse;
    };


    // input_04) final position to Acquire
    // nullptr if no need to check for edge
    //    using #include <limits>  std::numeric_limits< double >::max();/min() by default
    virtual void BallMotionEdges(SD_VECTOR* a_pLower, SD_VECTOR* a_pUpper)throw() override
    {
        if (a_pLower != nullptr)
            m_positionLowLimit.m_vector = *a_pLower;

        if (a_pUpper != nullptr)
            m_positionHighLimit.m_vector = *a_pUpper;
    }



//     do_02) setup ball motion interface with passed time
//     do_02')  acquire current position and speed
    // time in seconds
    //
    virtual bool BallMotion(const double a_dt, SD_VECTOR* a_pPosition, SD_VECTOR* a_pSpeed, double* ap_ResultTime)throw() override
    {
        bool b_ret = true; // we can continue motion be default
        // plan:
        // for each axis calculate speed and motion
        // check edge
        //
        // if we reach the edge - split a_dt for 2. and do result more accurate
        // but only 10 times, and for position - not for speed
        // speed should be recalculated in the end

        m_FlyTime += a_dt;


        U_SD_VECTOR t_position; // position - Local
        U_SD_VECTOR t_speed; // speed - Local

        ///////
        // for each axis calculate speed and motion
        int i = 0;
        for (; i < (int)E_AXIS::e_AXIS_COUNT; ++i)
            GetPositionSpeed(t_position, t_speed, m_FlyTime, (E_AXIS)i);


        for (i = 0; i < (int)E_AXIS::e_AXIS_COUNT; ++i)
        {
            // check limits
            bool b_LimitHeat = false;
            if (!ReachLimit(t_position.m_axis[i], m_positionLowLimit.m_axis[i], m_positionHighLimit.m_axis[i], b_LimitHeat))
                continue;

            b_ret = false; // we reach the limit - return value should be false

            if (b_LimitHeat)
                break; // just go to return values

            // we are reach the limit
            // lets get more accurate result for speed and position

            // ACTUALLY:
            // Possible to implement the logic of searching for any of axis for case when 2 or more axes crossed in 1 single dt
            //    but there no task for decide what surface we heat first:
            //      in case of landing for not the ground we need to find closest surface polygons from the time moment before and after.
            //   and then solve the problem according motion law
            //   here is everything clear
            //
            // lets just find closest time moment if possible for this axis (actually z - but define it dynamically)


            // split dt every time on 2
            // find closer and closer
            auto deltaDT = a_dt / 2.;
            auto t_FlyTime = m_FlyTime - deltaDT;
            for (size_t k = 0 ; k < 10; ++k)
            {
                deltaDT /= 2.; // change time more closer - because t_FlyTime now on the splitted value already

                GetPositionSpeed(t_position, t_speed, t_FlyTime, (E_AXIS)i);

                if (k != 9)
                if (ReachLimit(t_position.m_axis[i], m_positionLowLimit.m_axis[i], m_positionHighLimit.m_axis[i], b_LimitHeat))
                {
                    if (b_LimitHeat)
                        break; // just go to return values

                    t_FlyTime -= deltaDT;
                }
                else
                    t_FlyTime += deltaDT;
            }

            if (nullptr != ap_ResultTime)
                *ap_ResultTime = t_FlyTime; // result fly time

            // recalculate exact position for founded time
            for (int jj = 0; jj < (int)E_AXIS::e_AXIS_COUNT; ++jj)
            {
                if (jj != i)
                {
                    GetPositionSpeed(t_position, t_speed, t_FlyTime, (E_AXIS)jj);
                }
                else
                {
                    // specify exact limit value for this axis
                    t_position.m_axis[i] = t_position.m_axis[i] < ((m_positionHighLimit.m_axis[i] + m_positionLowLimit.m_axis[i]) / 2.) ?
                        m_positionLowLimit.m_axis[i] : m_positionHighLimit.m_axis[i];

                }
            }
        }// for (i = 0; i < (int)E_AXIS::e_AXIS_COUNT; ++i)

        // let the data out
        if (nullptr != a_pPosition)
            *a_pPosition = t_position.m_vector;
        if (nullptr != a_pSpeed)
            *a_pSpeed = t_speed.m_vector;

        return b_ret;
    }


};


// do_03)  release ball motion object when no need more
extern "C" __declspec(dllexport) void FinalizeMotionForBall(IBallMotion const* a_pMotion)throw()
{
    CBallMotion* pointer2Delete = reinterpret_cast<CBallMotion*>( const_cast<IBallMotion*>(a_pMotion) );
    delete pointer2Delete;
}



// return nullptr in case of no memory
//
// if any of SD_VECTOR*s nullptr - the deafult values are 0
//

extern "C" __declspec(dllexport) IBallMotion* RequestBallMotion(SD_VECTOR* const a_pPosition, SD_VECTOR* const a_pSpeed)throw()
{
    return new CBallMotion(a_pPosition, a_pSpeed);
}



