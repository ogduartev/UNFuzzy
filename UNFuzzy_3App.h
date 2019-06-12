/***************************************************************
 * Name:      UNFuzzy_3App.h
 * Purpose:   Defines Application Class
 * Author:    Oscar Duarte (ogduartev@unal.edu.co)
 * Created:   2019-05-20
 * Copyright: Oscar Duarte ()
 * License:
 **************************************************************/

#ifndef UNFUZZY_3APP_H
#define UNFUZZY_3APP_H

#include <wx/app.h>
#include "SistemaLogicaDifusa.h"


class UNFuzzy_3App : public wxApp
{
    public:
        virtual bool OnInit();
 	    	SistemaLogicaDifusa SLD;

};

#endif // UNFUZZY_3APP_H
