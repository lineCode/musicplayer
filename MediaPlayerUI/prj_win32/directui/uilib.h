// Copyright (c) 2012, Xiang Zhai (xiangzhai83@gmail.com) 
// All rights reserved.
//
// Copyright (c) 2010-2011, duilib develop team (www.duilib.com).
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or 
// without modification, are permitted provided that the 
// following conditions are met.
//
// Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// Redistributions in binary form must reproduce the above 
// copyright notice, this list of conditions and the following
// disclaimer in the documentation and/or other materials 
// provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
// CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#if defined( DIRECTUI_EXPORTS )
#if defined(_MSC_VER)
#define DIRECTUI_API __declspec(dllexport)
#else
#define DIRECTUI_API 
#endif
#else
#if defined(_MSC_VER)
#define DIRECTUI_API __declspec(dllimport)
#else
#define DIRECTUI_API 
#endif
#endif

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stddef.h>
#include <richedit.h>
#include <tchar.h>
#include <assert.h>
#include <crtdbg.h>
#include <malloc.h>

#include "uibase.h"
#include "uimessage.h"
#include "uiwindow.h"
#include "uianim.h"
#include "uimanager.h"
#include "uirender.h"
#include "uidelegate.h"
#include "uicontrol.h"
#include "uicontainer.h"
#include "uilist.h"
#include "uicombo.h"
#include "uilabel.h"
#include "uibutton.h"
#include "uioption.h"
#include "uitext.h"
#include "uiprogress.h"
#include "uislider.h"
#include "uiedit.h"
#include "uiscrollbar.h"
#include "uitool.h"
#include "uimenu.h"
#include "uiactiveX.h"
#include "uirichedit.h"
#include "uimarkup.h"
#include "uidlgbuilder.h"
#include "appwindow.h"
#include "uicontrolwnd.h"
#include "uianimctrl.h"
#include "uihotkey.h"
#include "uiwebbrowser.h"
#include "uicalendar.h"
#include "uilistdefinenode.h"
#include "uilistdefinebase.h"
#include "duiimage.h"
#include "uishadow.h"
#include "uisplitter.h"
#include "uiflashctrl.h"
#include "uigif.h"
#include "singtonhandle.h"
#include "sidehidewindow.h"
#include "droptarget.h"
#include "dropsource.h"
#include "dataobject.h"