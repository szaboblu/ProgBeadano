/***************************************************************
 * Name:      _018_10_04Main.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2018-10-04
 * Copyright:  ()
 * License:
 **************************************************************/

#include "_018_10_04Main.h"
#include <wx/msgdlg.h>
#include <wx/dcclient.h>
#include <wx/brush.h>

//(*InternalHeaders(_018_10_04Frame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(_018_10_04Frame)
const long _018_10_04Frame::ID_SLIDER1 = wxNewId();
const long _018_10_04Frame::ID_SLIDER2 = wxNewId();
const long _018_10_04Frame::ID_SLIDER3 = wxNewId();
const long _018_10_04Frame::idMenuQuit = wxNewId();
const long _018_10_04Frame::idMenuAbout = wxNewId();
const long _018_10_04Frame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(_018_10_04Frame,wxFrame)
    //(*EventTable(_018_10_04Frame)
    //*)
END_EVENT_TABLE()

_018_10_04Frame::_018_10_04Frame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(_018_10_04Frame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    Slider1 = new wxSlider(this, ID_SLIDER1, 0, 0, 100, wxPoint(144,16), wxSize(104,22), 0, wxDefaultValidator, _T("ID_SLIDER1"));
    Slider2 = new wxSlider(this, ID_SLIDER2, 0, 0, 100, wxPoint(24,16), wxSize(104,22), 0, wxDefaultValidator, _T("ID_SLIDER2"));
    Slider3 = new wxSlider(this, ID_SLIDER3, 0, 0, 360, wxPoint(272,16), wxSize(96,22), 0, wxDefaultValidator, _T("ID_SLIDER3"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_SLIDER1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&_018_10_04Frame::OnSlider1CmdScrollThumbTrack);
    Connect(ID_SLIDER1,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&_018_10_04Frame::OnSlider1CmdScrollThumbTrack);
    Connect(ID_SLIDER2,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&_018_10_04Frame::OnSlider1CmdScrollThumbTrack);
    Connect(ID_SLIDER2,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&_018_10_04Frame::OnSlider1CmdScrollThumbTrack);
    Connect(ID_SLIDER3,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&_018_10_04Frame::OnSlider1CmdScrollThumbTrack);
    Connect(ID_SLIDER3,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&_018_10_04Frame::OnSlider1CmdScrollThumbTrack);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&_018_10_04Frame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&_018_10_04Frame::OnAbout);
    Connect(wxEVT_PAINT,(wxObjectEventFunction)&_018_10_04Frame::OnPaint);
    //*)
}

_018_10_04Frame::~_018_10_04Frame()
{
    //(*Destroy(_018_10_04Frame)
    //*)
}

void _018_10_04Frame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void _018_10_04Frame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}


void _018_10_04Frame::OnPaint(wxPaintEvent& event)
{
        wxPaintDC dc(this);
        wxBrush brush;
        //brush.SetStyle(wxCROSS_HATCH);
        dc.DrawEllipticArc(150, 300, Slider1 -> GetValue(), Slider2 -> GetValue(), Slider3 -> GetValue(), 360);
        double ossz = (Slider1->GetValue() + Slider2->GetValue() + Slider3 ->GetValue());
        int szel, mag, szog;
        szel = (Slider1 -> GetValue() * (360 / ossz));
        mag = (Slider2 -> GetValue() * (360 / ossz));
        szog = (Slider3 -> GetValue() * (360 / ossz));

        if(ossz != 0)
        {
            dc.SetBrush(*wxGREEN_BRUSH);
            dc.DrawEllipticArc(100,100,200,200, 0, szel);
            dc.SetBrush(*wxRED_BRUSH);
            dc.DrawEllipticArc(100,100,200,200, szel, szel + mag);
            dc.SetBrush(*wxYELLOW_BRUSH);
            dc.DrawEllipticArc(100,100,200,200, szel + mag, 360);
        }

}

void _018_10_04Frame::OnSlider1CmdScrollThumbTrack(wxScrollEvent& event)
{
    Refresh();
}
