#ifndef WXEDITORMAIN_H
#define WXEDITORMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wxEditorApp.h"

class wxEditorFrame: public wxFrame
{
    public:
        wxEditorFrame(wxFrame *frame, const wxString& title);
        ~wxEditorFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout,
            ID_TextBox,
            idMenuOpen, 
            idMenuSave 
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOpen (wxCommandEvent& event); 
        void OnSave (wxCommandEvent& event); 
        DECLARE_EVENT_TABLE()
};


#endif // WXEDITORMAIN_H
