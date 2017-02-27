#ifndef GDI_OBJECTASDT_35897LJKTR
#define GDI_OBJECTASDT_35897LJKTR

// GdiObject and  IconObject
// for easy using HGDIOBJ as bitmap or icon



class GdiObject
{
public:
// Constructors
    GdiObject(void);
    GdiObject(HGDIOBJ hObject);
    virtual ~GdiObject(void);

    void Attach(HGDIOBJ hObject);
    HGDIOBJ Detach();

    virtual void DeleteObject();
public:

// Attributes
    HGDIOBJ m_hObject;                  // must be first data member
    operator HGDIOBJ() const;
    operator HBITMAP() const;
};

class IconObject: public GdiObject
{
public:
    operator HICON()const;
    virtual void DeleteObject() override;
};


#endif


