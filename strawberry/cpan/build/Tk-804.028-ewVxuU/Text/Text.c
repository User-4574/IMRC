/*
 * This file was generated automatically by ExtUtils::ParseXS version 2.19 from the
 * contents of Text.xs. Do not edit this file, edit Text.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#line 1 "Text.xs"
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

#line 35 "Text.c"

XS(XS_Tk_text); /* prototype to pass -Wmissing-prototypes */
XS(XS_Tk_text)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    PERL_UNUSED_VAR(cv); /* -W */
    {
#line 28 "Text.xs"
 {
  TKXSRETURN(XSTkCommand(cv,1,Tk_TextCmd,items,&ST(0)));
 }
#line 51 "Text.c"
    }
    XSRETURN_EMPTY;
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_Tk__Text); /* prototype to pass -Wmissing-prototypes */
XS(boot_Tk__Text)
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

        newXS("Tk::text", XS_Tk_text, file);

    /* Initialisation Section */

#line 33 "Text.xs"
 {
  IMPORT_VTABLES;
 }

#line 82 "Text.c"

    /* End of Initialisation Section */

    XSRETURN_YES;
}

