/*
 * This file was generated automatically by ExtUtils::ParseXS version 2.19 from the
 * contents of Win32Site.xs. Do not edit this file, edit Win32Site.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#line 1 "Win32Site.xs"
/*
  Copyright (c) 1995-2003 Nick Ing-Simmons. All rights reserved.
  This program is free software; you can redistribute it and/or
  modify it under the same terms as Perl itself.
*/
#define PERL_NO_GET_CONTEXT
#include <windows.h>
#include <shellapi.h>

#ifdef __CYGWIN__
# undef WIN32
#endif
#include <EXTERN.h>
#include <perl.h>
#include <XSUB.h>

#include "tkGlue.def"

#include "pTk/tkPort.h"
#include "pTk/tkInt.h"
#include "pTk/tixPort.h"
#include "pTk/tixInt.h"
#include "tkGlue.h"
#include "tkGlue.m"
#include "pTk/tkVMacro.h"

DECLARE_VTABLES;

#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#line 43 "Win32Site.c"

XS(XS_Tk__DragDrop__Win32Site_DragAcceptFiles); /* prototype to pass -Wmissing-prototypes */
XS(XS_Tk__DragDrop__Win32Site_DragAcceptFiles)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 2)
       Perl_croak(aTHX_ "Usage: %s(%s)", "Tk::DragDrop::Win32Site::DragAcceptFiles", "win, flag");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	HWND	win = SVtoHWND(ST(0));
	BOOL	flag = (BOOL)SvIV(ST(1));
#line 38 "Win32Site.xs"
 {
  DragAcceptFiles(win,flag);
 }
#line 63 "Win32Site.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_Tk__DragDrop__Win32Site_DropInfo); /* prototype to pass -Wmissing-prototypes */
XS(XS_Tk__DragDrop__Win32Site_DropInfo)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       Perl_croak(aTHX_ "Usage: %s(%s)", "Tk::DragDrop::Win32Site::DropInfo", "drop");
    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	HANDLE	drop = (HANDLE)SvIV(ST(0));
#line 46 "Win32Site.xs"
 {
  UINT count = DragQueryFile(drop, -1, NULL, 0);
  UINT i;
  POINT point;
  SV *x = sv_newmortal();
  SV *y = sv_newmortal();
  int n = 0;
  if (DragQueryPoint(drop,&point))
   {
    sv_setiv(x,point.x);
    sv_setiv(y,point.y);
   }
  XPUSHs(x);
  XPUSHs(y);
  for (i=0; i < count; i++)
   {
    UINT len = DragQueryFile(drop, i, NULL, 0);
    SV *sv = newSVpv("",0);
    SvGROW(sv,len+1);
    len = DragQueryFile(drop,i,SvPVX(sv),SvLEN(sv));
    SvCUR(sv) = len;
    XPUSHs(sv_2mortal(sv));
   }
  DragFinish(drop);
  PUTBACK;
 }
#line 111 "Win32Site.c"
	PUTBACK;
	return;
    }
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_Tk__DragDrop__Win32Site); /* prototype to pass -Wmissing-prototypes */
XS(boot_Tk__DragDrop__Win32Site)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    char* file = __FILE__;

    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
    XS_VERSION_BOOTCHECK ;

        newXS("Tk::DragDrop::Win32Site::DragAcceptFiles", XS_Tk__DragDrop__Win32Site_DragAcceptFiles, file);
        newXS("Tk::DragDrop::Win32Site::DropInfo", XS_Tk__DragDrop__Win32Site_DropInfo, file);

    /* Initialisation Section */

#line 74 "Win32Site.xs"
 {
  IMPORT_VTABLES;
 }

#line 144 "Win32Site.c"

    /* End of Initialisation Section */

    XSRETURN_YES;
}

