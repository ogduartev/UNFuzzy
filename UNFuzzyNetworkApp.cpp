/***************************************************************
 * Name:      UNFuzzyNetworkApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Oscar Duarte (ogduartev@unal.edu.co)
 * Created:   2019-06-09
 * Copyright: Oscar Duarte ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "UNFuzzyNetworkApp.h"
#include "UNFuzzyNetworkMain.h"

IMPLEMENT_APP(UNFuzzyNetworkApp);

bool UNFuzzyNetworkApp::OnInit()
{
	wxInitAllImageHandlers();

	wxFileName f(wxStandardPaths::Get().GetExecutablePath());

  UNFuzzyNetworkFrame* frame = new UNFuzzyNetworkFrame(0L, _T("UNFuzzyNetwork - Diseño de redes de sistemas de Lógica Difusa"));

  frame->Show();

  return true;
}
