// For compilers that support precompilation, includes "wx/wx.h".

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wx/listctrl.h"
#include "qfx_parser.hpp"
#include "qfx_viewer.hpp"
#include <limits.h>
#include "fix_console.hpp"

#include <vector>

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
   RedirectIOToConsole();

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

   m_listCtrl->AppendColumn("DATE");
   m_listCtrl->AppendColumn("DESCRIPTION");
   m_listCtrl->AppendColumn("AMOUNT");

   //##################################################################

   m_listCtrl->inp_file = qfx_file::read("../qfx-data/transactions.QFX",-5);
   int curr_transaction = 0;

   m_listCtrl->qfx_order.resize(m_listCtrl->inp_file.transactions.size());

   for(auto & i : m_listCtrl->inp_file.transactions)
   {
      m_listCtrl->qfx_order[curr_transaction++] = i.first;
   }

   m_listCtrl->SetItemCount(m_listCtrl->inp_file.transactions.size());

   //##################################################################


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
   if(qfx_order.size() < (size_t)item)  return wxString::Format("ERROR");

   auto key = qfx_order[item];

   auto found = inp_file.transactions.find(key);

   if(found != inp_file.transactions.end())
   {
      auto val = found->second; 
      switch(column)
      {
         case 0: 
         {
            char str[26];
            ctime_s(str, sizeof(str),&val.date_posted.first);
            return wxString::Format("%s", str);
         }
         case 1: 
         {
            return wxString::Format("%s", val.memo.c_str());
         }
         case 2: 
         {
            int64_t r = val.amount%100;
            return wxString::Format("%lld.%ld", val.amount/100,r>0?r:-r);
         }
         default:
            return wxString::Format("NO DATA %ld.%ld", column, item);
      }
   }
   else
   {
      return wxString::Format("ERROR");
   }
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
