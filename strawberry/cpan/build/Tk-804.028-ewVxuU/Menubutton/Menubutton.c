/*
 * This file was generated automatically by ExtUtils::ParseXS version 2.19 from the
 * contents of Menubutton.xs. Do not edit this file, edit Menubutton.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#line 1 "Menubutton.xs"
/*
  Copyright (c) 1995-2003 Nick Ing-Simmons. All rights reserved.
  This program is free software; you can redistribute it and/or
  modify it under the same terms as Perl itself.
*/
#define PERL_NO_GET_CONTEXT
#include <EXTERN.h>
#include <perl.h>
#include <XSUB.h>

#include "tkGlue.def"

#include "pTk/tkPort.h"
#include "pTk/tkInt.h"
#include "tkGlue.h"
#include "tkGlue.m"
#include "pTk/tkVMacro.h"

DECLARE_VTABLES;

#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#line 35 "Menubutton.c"

XS(XS_Tk_menubutton); /* prototype to pass -Wmissing-prototypes */
XS(XS_Tk_menubutton)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    PERL_UNUSED_VAR(cv); /* -W */
    {
#line 28 "Menubutton.xs"
 {
  TKXSRETURN(XSTkCommand(cv,0,Tk_MenubuttonObjCmd,items,&ST(0)));
 }
#line 51 "Menubutton.c"
    }
    XSRETURN_EMPTY;
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_Tk__Menubutton); /* prototype to pass -Wmissing-prototypes */
XS(boot_Tk__Menubutton)
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

        newXS("Tk::menubutton", XS_Tk_menubutton, file);

    /* Initialisation Section */

#line 33 "Menubutton.xs"
 {
  IMPORT_VTABLES;
 }

#line 82 "Menubutton.c"

    /* End of Initialisation Section */

    XSRETURN_YES;
}

