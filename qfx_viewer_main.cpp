// For compilers that support precompilation, includes "wx/wx.h".

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wx/listctrl.h"
#include "qfx_viewer.hpp"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum
{
    ID_Hello = 1
};

bool MyApp::OnInit()
{
   MyFrame *frame = new MyFrame();
   frame->Show(true);
   return true;
}
MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Hello World")
{
    wxMenu *menuFile = new wxMenu;

    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");

    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

   Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
   Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
   Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

   long int flags = wxLC_REPORT | wxLC_VIRTUAL;

   wxPanel *m_panel;
    MyListCtrl *m_listCtrl;

   m_panel = new wxPanel(this, wxID_ANY);

   m_listCtrl = new MyListCtrl(m_panel, LIST_CTRL,
      wxDefaultPosition, wxDefaultSize,
      flags |
      wxBORDER_THEME | wxLC_EDIT_LABELS);

   m_listCtrl->AppendColumn("Animal");
   m_listCtrl->AppendColumn("Sound");
   m_listCtrl->SetItemCount(10);

   wxBoxSizer* const sizer = new wxBoxSizer(wxVERTICAL);
   sizer->Add(m_listCtrl, wxSizerFlags(2).Expand().Border());
   m_panel->SetSizer(sizer);
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

wxIMPLEMENT_APP(MyApp);

wxBEGIN_EVENT_TABLE(MyListCtrl, wxListCtrl)
wxEND_EVENT_TABLE()

wxString MyListCtrl::OnGetItemText(long item, long column) const
{
   return wxString::Format("Column %ld of item %ld", column, item);
}

void MyListCtrl::CheckItem(long item, bool check)
{

}

bool MyListCtrl::IsItemChecked(long item) const
{
   return false;
}

bool MyListCtrl::OnGetItemIsChecked(long item) const
{
    return IsItemChecked(item);
}

int MyListCtrl::OnGetItemColumnImage(long item, long column) const
{
    return -1;
}

wxItemAttr *MyListCtrl::OnGetItemAttr(long item) const
{
    return wxListCtrl::OnGetItemAttr(item);
}
