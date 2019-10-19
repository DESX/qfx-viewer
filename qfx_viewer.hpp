#ifndef QFX_VIEWER_H
#define QFX_VIEWER_H

// IDs for the menu commands
enum
{
    LIST_ABOUT = wxID_ABOUT,
    LIST_QUIT = wxID_EXIT,

    LIST_LIST_VIEW = wxID_HIGHEST,
    LIST_ICON_VIEW,
    LIST_ICON_TEXT_VIEW,
    LIST_SMALL_ICON_VIEW,
    LIST_SMALL_ICON_TEXT_VIEW,
    LIST_REPORT_VIEW,
    LIST_VIRTUAL_VIEW,
    LIST_SMALL_VIRTUAL_VIEW,
    LIST_SET_ITEMS_COUNT,

    LIST_DESELECT_ALL,
    LIST_SELECT_ALL,
    LIST_DELETE_ALL,
    LIST_DELETE,
    LIST_ADD,
    LIST_EDIT,
    LIST_SORT,
    LIST_FIND,
    LIST_SET_FG_COL,
    LIST_SET_BG_COL,
    LIST_ROW_LINES,
    LIST_CUSTOM_HEADER_ATTR,
    LIST_TOGGLE_MULTI_SEL,
    LIST_TOGGLE_HEADER,
    LIST_TOGGLE_BELL,
    LIST_TOGGLE_CHECKBOX,
    LIST_GET_CHECKBOX,
    LIST_TOGGLE_CHECKBOXES,
    LIST_TOGGLE_FIRST,
    LIST_SHOW_COL_INFO,
    LIST_SHOW_SEL_INFO,
    LIST_SHOW_VIEW_RECT,
#ifdef wxHAS_LISTCTRL_COLUMN_ORDER
    LIST_SET_COL_ORDER,
    LIST_GET_COL_ORDER,
#endif // wxHAS_LISTCTRL_COLUMN_ORDER
    LIST_GOTO,
    LIST_FOCUS_LAST,
    LIST_FREEZE,
    LIST_THAW,
    LIST_TOGGLE_LINES,
#ifdef __WXOSX__
    LIST_MAC_USE_GENERIC,
#endif
    LIST_CHECKVISIBILITY,
    LIST_CTRL                   = 1000
};
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
