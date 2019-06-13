/***************************************************************
 * Name:      UNFuzzy_3App.cpp
 * Purpose:   Code for Application Class
 * Author:    Oscar Duarte (ogduartev@unal.edu.co)
 * Created:   2019-05-20
 * Copyright: Oscar Duarte ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "UNFuzzy_3App.h"
#include "DialogoSLD.h"

IMPLEMENT_APP(UNFuzzy_3App);

bool UNFuzzy_3App::OnInit()
{
  	SLD.crearMinimoSLD(1,1);

    DialogoSLD* dlg = new DialogoSLD(0L, &SLD, _("UNFuzzy 3.0"));

    dlg->Show();
    return true;
}
