/***************************************************************
 * Name:      _018_10_04App.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2018-10-04
 * Copyright:  ()
 * License:
 **************************************************************/

#include "_018_10_04App.h"

//(*AppHeaders
#include "_018_10_04Main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(_018_10_04App);

bool _018_10_04App::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	_018_10_04Frame* Frame = new _018_10_04Frame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
        