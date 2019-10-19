#ifndef QFX_VIEWER_H
#define QFX_VIEWER_H

class MyListCtrl: public wxListCtrl
{
public:
    MyListCtrl(wxWindow *parent,
               const wxWindowID id,
               const wxPoint& pos,
               const wxSize& size,
               long style)
        : wxListCtrl(parent, id, pos, size, style)
        {
            m_updated = -1;

        }

    virtual void CheckItem(long item, bool check) wxOVERRIDE;
    virtual bool IsItemChecked(long item) const wxOVERRIDE;

private:

    virtual wxString OnGetItemText(long item, long column) const wxOVERRIDE;
    virtual bool OnGetItemIsChecked(long item) const wxOVERRIDE;
    virtual int OnGetItemColumnImage(long item, long column) const wxOVERRIDE;
    virtual wxItemAttr *OnGetItemAttr(long item) const wxOVERRIDE;

    long m_updated;

    // checked boxes in virtual list

    wxDECLARE_NO_COPY_CLASS(MyListCtrl);
    wxDECLARE_EVENT_TABLE();
};

#endif
