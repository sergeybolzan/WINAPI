#ifndef AXISSELECTOR_GLHKS3479346
#define AXISSELECTOR_GLHKS3479346

// selector of axis for DrawField class
//
// we draw XZ and YZ palnes
// so need 2 class

namespace ttb_thread
{
    // pure class
    class AxisSelector
    {

    public:
        virtual ~AxisSelector();
        virtual double& Vertical(SD_VECTOR& arVector)throw() = 0;
        virtual double& Horizontal(SD_VECTOR& arVector)throw() = 0;
    };


    // z
    class Z_AxisSelector : public AxisSelector
    {
        virtual double& Vertical(SD_VECTOR& arVector)throw() override;
    };



    // class x horizon, z vertical

    class XZ_AxisSelector : public Z_AxisSelector
    {
        virtual double& Horizontal(SD_VECTOR& arVector)throw() override;
    };

    // class y horizon, z vertical
    class YZ_AxisSelector : public Z_AxisSelector
    {
        virtual double& Horizontal(SD_VECTOR& arVector)throw() override;
    };
};


#endif