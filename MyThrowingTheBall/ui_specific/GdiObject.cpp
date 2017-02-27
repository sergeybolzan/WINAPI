#include "stdafx.h"

GdiObject::GdiObject(void):m_hObject(NULL)
{
}
GdiObject::GdiObject(HGDIOBJ hObject):m_hObject(hObject)
{
}

GdiObject::~GdiObject(void)
{
   DeleteObject();
}

void GdiObject::Attach(HGDIOBJ hObject)
{
    if (hObject != m_hObject)
    {
        if (m_hObject != NULL)
            DeleteObject();
        m_hObject = hObject;
    }
}
HGDIOBJ GdiObject::Detach()
{
   const HGDIOBJ hObject = m_hObject;
   m_hObject = NULL;
   return hObject;
}

void GdiObject::DeleteObject()
{
   if (m_hObject != NULL)
      ::DeleteObject(Detach());
}

GdiObject::operator HGDIOBJ() const
{
   return m_hObject;
}
GdiObject::operator HBITMAP() const
{
   return (HBITMAP)m_hObject;
}


IconObject::operator HICON() const
{
   return (HICON)m_hObject;
}

void IconObject::DeleteObject()
{
   if (NULL != m_hObject)
      ::DestroyIcon((HICON)m_hObject);
   m_hObject = NULL;
}
