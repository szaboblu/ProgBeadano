/***************************************************************
 * Name:      _018_10_04Main.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2018-10-04
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef _018_10_04MAIN_H
#define _018_10_04MAIN_H

//(*Headers(_018_10_04Frame)
#include <wx/menu.h>
#include <wx/slider.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
//*)

class _018_10_04Frame: public wxFrame
{
    public:

        _018_10_04Frame(wxWindow* parent,wxWindowID id = -1);
        virtual ~_018_10_04Frame();

    private:

        //(*Handlers(_018_10_04Frame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnSlider1CmdScrollThumbTrack(wxScrollEvent& event);
        //*)

        //(*Identifiers(_018_10_04Frame)
        static const long ID_SLIDER1;
        static const long ID_SLIDER2;
        static const long ID_SLIDER3;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(_018_10_04Frame)
        wxSlider* Slider3;
        wxStatusBar* StatusBar1;
        wxSlider* Slider2;
        wxSlider* Slider1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // _018_10_04MAIN_H
