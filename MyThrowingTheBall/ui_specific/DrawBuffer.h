#ifndef DRAW_BUFFER_NKWTLHKWER3457890
#define DRAW_BUFFER_NKWTLHKWER3457890

#include "gdiobject.h"
// we will use this class
// to draw into
//   and then bitblt result into control DC

namespace ttb_thread
{

class DrawBuffer : public GdiObject
{
public:
   DrawBuffer(void);
   ~DrawBuffer(void);
   void Init(const HDC ahdc, const RECT& arc);

   HDC m_dc;
   SIZE m_sz; // rectangle of image
   GdiObject m_oldImage;

   HDC operator *();
};

};

#endif

