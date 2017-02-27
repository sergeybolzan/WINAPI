#include "stdafx.h"
#include "DrawBuffer.h"

namespace ttb_thread
{


DrawBuffer::DrawBuffer(void)
   :m_dc(NULL)
{
   m_sz.cx = 0;
   m_sz.cy = 0;
}

DrawBuffer::~DrawBuffer(void)
{
   ::SelectObject(m_dc, m_oldImage.Detach());
   ::DeleteDC(m_dc);
}

void DrawBuffer::Init(const HDC ahdc, const RECT& arc)
{
   if ( m_sz.cx >= arc.right - arc.left && m_sz.cy >= arc.bottom - arc.top )
      return;

   if ( m_dc == NULL )
   {
      m_dc = ::CreateCompatibleDC(ahdc);
   }
   else
   {
      ::SelectObject(m_dc, m_oldImage.Detach());
      DeleteObject();
   }

   Attach(::CreateCompatibleBitmap(ahdc, arc.right - arc.left, arc.bottom - arc.top));
   m_oldImage.Attach( ::SelectObject(m_dc, HGDIOBJ(*this)) );

   m_sz.cx = arc.right - arc.left;
   m_sz.cy = arc.bottom - arc.top;
}

HDC DrawBuffer::operator *()
{
   return m_dc;
};


};

