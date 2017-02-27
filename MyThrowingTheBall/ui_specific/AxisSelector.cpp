#include "stdafx.h"
#include "AxisSelector.h"


namespace ttb_thread
{

AxisSelector::~AxisSelector(){}

    // z
double& Z_AxisSelector::Vertical(SD_VECTOR& arVector)throw()
{
    return arVector.z_axis;
}



// class x horizon, z vertical
double& XZ_AxisSelector::Horizontal(SD_VECTOR& arVector)throw()
{
    return arVector.x_axis;
}

    // class y horizon, z vertical
double& YZ_AxisSelector::Horizontal(SD_VECTOR& arVector)throw()
{
    return arVector.y_axis;
}


};