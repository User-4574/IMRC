/*
 * This file was generated automatically by ExtUtils::ParseXS version 2.19 from the
 * contents of Xlib.xs. Do not edit this file, edit Xlib.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#line 1 "Xlib.xs"
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

/* A few sample routines to get at Xlib via perl
   Will eventaually be extended to the point where
   simple pTk widgets can be *implemented* in perl

   Main stumbling block is a clean way of filling in
   a GC.

   The XDraw*() functions may be a bit messy, but
   should be okay via CODE: bodies and variable number
   of args and/or passing in array refs
*/

/* Now we have some sneakyness for Benefit of Win32.
 * As we have tkVMacro.h above any function which exists
 * should be #define'd so we can test for existance.
 */

#ifndef XLoadFont
#define XLoadFont(dpy,name) None
#endif

#ifndef XDrawString
#define XDrawString(dpy,win,gc,x,y,string,len)
#endif

static IV
SvGCIVOBJ(pTHX_ char *class,SV *sv)
{
 if (sv_isa(sv, class))
  return SvIV((SV*)SvRV(sv));
 else
  croak("Not of type %s",class);
 return 0;
}

#define SvGCint(x)           SvIV(x)
#define SvGCBool(x)          SvIV(x)
#define SvGCunsigned_long(x) SvIV(x)
#define SvGCPixmap(x)        (Pixmap) SvGCIVOBJ(aTHX_ "Pixmap",x)
#define SvGCFont(x)          (Font)   SvGCIVOBJ(aTHX_ "Font",x)

#define GCField(name,bit,field,func) \
 if (!strcmp(key,name)) {            \
  values->field = func(value);       \
  valuemask |= bit;                  \
 } else

unsigned long
GCSetValue(pTHX_ unsigned long valuemask,
           XGCValues *values,char *key,SV *value)
{
#include "GC.def"
 croak("Setting GC %s not implemented",key);
 return valuemask;
}

static void
tmpLine(tkwin,x1,y1,x2,y2,flags)
Tk_Window tkwin;
int x1,y1,x2,y2;
int flags;
{
 GC gc = None;
 XGCValues values;
 Window root = Tk_WindowId(tkwin);
 unsigned long valuemask = GCForeground | GCBackground
                           | GCSubwindowMode | GCFunction
#if 0
                           | GCLineStyle
#endif
                           ;
 values.line_style     = LineDoubleDash;

 if (flags & 4)
  {
   Window child;
   root = XRootWindow(Tk_Display(tkwin), Tk_ScreenNumber(tkwin));
   XTranslateCoordinates(Tk_Display(tkwin),Tk_WindowId(tkwin),root,
                         x1, y1, &x1, &y1, &child);
   XTranslateCoordinates(Tk_Display(tkwin),Tk_WindowId(tkwin),root,
                         x2, y2, &x2, &y2, &child);
   values.subwindow_mode = IncludeInferiors;
  }
 else
  {
   values.subwindow_mode = ClipByChildren;
  }

 if (flags & 2)
  {
   values.background     = 0x0a;
   values.foreground     = 0x05;
   values.function       = GXxor;
  }
 else
  {
   values.function       = GXcopy;
   if (flags & 1)
    {
     values.foreground     = BlackPixelOfScreen(Tk_Screen(tkwin));
     values.background     = WhitePixelOfScreen(Tk_Screen(tkwin));
    }
   else
    {
     values.background     = BlackPixelOfScreen(Tk_Screen(tkwin));
     values.foreground     = WhitePixelOfScreen(Tk_Screen(tkwin));
    }
  }
 gc = Tk_GetGC(tkwin, valuemask, &values);
 if (gc != None)
  {
   XDrawLine(Tk_Display(tkwin), root, gc, x1, y1, x2, y2);
   Tk_FreeGC(Tk_Display(tkwin),gc);
  }
 else
  croak("Cannot get graphic context");
}

#if defined(WIN32) || defined(__WIN32__) || defined(__PM__)
/* wrap the naive macro versions of these ... */
static int
pTk_XSync(Display *dpy, int flush)
{
 XSync(dpy,flush);
 return 0;
}

static int
pTk_XFlush(Display *dpy)
{
 XFlush(dpy);
 return 0;
}
#else
#define pTk_XSync  XSync
#define pTk_XFlush XFlush
#endif /* WIN32 or friends */



#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#line 169 "Xlib.c"

XS(XS_Tk__Widget_tmpLine); /* prototype to pass -Wmissing-prototypes */
XS(XS_Tk__Widget_tmpLine)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 5 || items > 6)
       Perl_croak(aTHX_ "Usage: %s(%s)", "Tk::Widget::tmpLine", "win, x1, y1, x2, y2, onroot = 0");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Tk_Window	win = SVtoWindow(ST(0));
	int	x1 = (int)SvIV(ST(1));
	int	y1 = (int)SvIV(ST(2));
	int	x2 = (int)SvIV(ST(3));
	int	y2 = (int)SvIV(ST(4));
	int	onroot;

	if (items < 6)
	    onroot = 0;
	else {
	    onroot = (int)SvIV(ST(5));
	}

	tmpLine(win, x1, y1, x2, y2, onroot);
    }
    XSRETURN_EMPTY;
}


XS(XS_ScreenPtr_WidthOfScreen); /* prototype to pass -Wmissing-prototypes */
XS(XS_ScreenPtr_WidthOfScreen)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       Perl_croak(aTHX_ "Usage: %s(%s)", "ScreenPtr::WidthOfScreen", "s");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Screen *	s;
	int	RETVAL;
	dXSTARG;

	if (sv_isa(ST(0), "ScreenPtr")) {
	    s = INT2PTR(Screen *, SvIV(SvRV(ST(0))));
	}
	else {
	    s = (Screen *) NULL;
	    croak("s is not of type ScreenPtr");
	};

	RETVAL = WidthOfScreen(s);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_ScreenPtr_WidthMMOfScreen); /* prototype to pass -Wmissing-prototypes */
XS(XS_ScreenPtr_WidthMMOfScreen)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       Perl_croak(aTHX_ "Usage: %s(%s)", "ScreenPtr::WidthMMOfScreen", "s");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Screen *	s;
	int	RETVAL;
	dXSTARG;

	if (sv_isa(ST(0), "ScreenPtr")) {
	    s = INT2PTR(Screen *, SvIV(SvRV(ST(0))));
	}
	else {
	    s = (Screen *) NULL;
	    croak("s is not of type ScreenPtr");
	};

	RETVAL = WidthMMOfScreen(s);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_ScreenPtr_HeightOfScreen); /* prototype to pass -Wmissing-prototypes */
XS(XS_ScreenPtr_HeightOfScreen)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       Perl_croak(aTHX_ "Usage: %s(%s)", "ScreenPtr::HeightOfScreen", "s");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Screen *	s;
	int	RETVAL;
	dXSTARG;

	if (sv_isa(ST(0), "ScreenPtr")) {
	    s = INT2PTR(Screen *, SvIV(SvRV(ST(0))));
	}
	else {
	    s = (Screen *) NULL;
	    croak("s is not of type ScreenPtr");
	};

	RETVAL = HeightOfScreen(s);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_ScreenPtr_HeightMMOfScreen); /* prototype to pass -Wmissing-prototypes */
XS(XS_ScreenPtr_HeightMMOfScreen)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       Perl_croak(aTHX_ "Usage: %s(%s)", "ScreenPtr::HeightMMOfScreen", "s");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Screen *	s;
	int	RETVAL;
	dXSTARG;

	if (sv_isa(ST(0), "ScreenPtr")) {
	    s = INT2PTR(Screen *, SvIV(SvRV(ST(0))));
	}
	else {
	    s = (Screen *) NULL;
	    croak("s is not of type ScreenPtr");
	};

	RETVAL = HeightMMOfScreen(s);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_ScreenPtr_DefaultGCOfScreen); /* prototype to pass -Wmissing-prototypes */
XS(XS_ScreenPtr_DefaultGCOfScreen)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       Perl_croak(aTHX_ "Usage: %s(%s)", "ScreenPtr::DefaultGCOfScreen", "s");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Screen *	s;
	GC	RETVAL;

	if (sv_isa(ST(0), "ScreenPtr")) {
	    s = INT2PTR(Screen *, SvIV(SvRV(ST(0))));
	}
	else {
	    s = (Screen *) NULL;
	    croak("s is not of type ScreenPtr");
	};

	RETVAL = DefaultGCOfScreen(s);
	ST(0) = sv_newmortal();
	sv_setref_iv(ST(0), "GC", PTR2IV(RETVAL));

    }
    XSRETURN(1);
}


XS(XS_ScreenPtr_BlackPixelOfScreen); /* prototype to pass -Wmissing-prototypes */
XS(XS_ScreenPtr_BlackPixelOfScreen)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       Perl_croak(aTHX_ "Usage: %s(%s)", "ScreenPtr::BlackPixelOfScreen", "s");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Screen *	s;
	unsigned long	RETVAL;
	dXSTARG;

	if (sv_isa(ST(0), "ScreenPtr")) {
	    s = INT2PTR(Screen *, SvIV(SvRV(ST(0))));
	}
	else {
	    s = (Screen *) NULL;
	    croak("s is not of type ScreenPtr");
	};

	RETVAL = BlackPixelOfScreen(s);
	XSprePUSH; PUSHu((UV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_ScreenPtr_WhitePixelOfScreen); /* prototype to pass -Wmissing-prototypes */
XS(XS_ScreenPtr_WhitePixelOfScreen)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       Perl_croak(aTHX_ "Usage: %s(%s)", "ScreenPtr::WhitePixelOfScreen", "s");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Screen *	s;
	unsigned long	RETVAL;
	dXSTARG;

	if (sv_isa(ST(0), "ScreenPtr")) {
	    s = INT2PTR(Screen *, SvIV(SvRV(ST(0))));
	}
	else {
	    s = (Screen *) NULL;
	    croak("s is not of type ScreenPtr");
	};

	RETVAL = WhitePixelOfScreen(s);
	XSprePUSH; PUSHu((UV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_DisplayPtr_XSync); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_XSync)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 1 || items > 2)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::XSync", "dpy, discard = False");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	int	discard;
	int	RETVAL;
	dXSTARG;

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	if (items < 2)
	    discard = False;
	else {
	    discard = (int)SvIV(ST(1));
	}

	RETVAL = pTk_XSync(dpy, discard);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_DisplayPtr_XFlush); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_XFlush)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::XFlush", "dpy");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	int	RETVAL;
	dXSTARG;

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	RETVAL = pTk_XFlush(dpy);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_DisplayPtr_ConnectionNumber); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_ConnectionNumber)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::ConnectionNumber", "dpy");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	int	RETVAL;
	dXSTARG;

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	RETVAL = ConnectionNumber(dpy);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_DisplayPtr_XLoadFont); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_XLoadFont)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 2)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::XLoadFont", "dpy, name");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	char *	name = (char *)SvPV_nolen(ST(1));
	Font	RETVAL;

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	RETVAL = XLoadFont(dpy, name);
	ST(0) = sv_newmortal();
	sv_setref_iv(ST(0), "Font", PTR2IV(RETVAL));

    }
    XSRETURN(1);
}


XS(XS_DisplayPtr_XListFonts); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_XListFonts)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 3)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::XListFonts", "dpy, pattern, max");
    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	Display *	dpy;
	char *	pattern = (char *)SvPV_nolen(ST(1));
	int	max = (int)SvIV(ST(2));

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};
#line 225 "Xlib.xs"
 {
  int  count = 0;
#if !defined(__WIN32__) && !defined(__PM__)
  char **list = XListFonts(dpy, pattern, max, &count);
  int i;
  EXTEND(sp, count);
  for (i=0; i < count; i++)
   {
    PUSHs(sv_2mortal(newSVpv(list[i],0)));
   }
  XFreeFontNames(list);
#endif
  XSRETURN(count);
 }
#line 593 "Xlib.c"
	PUTBACK;
	return;
    }
}


XS(XS_DisplayPtr_XDrawLine); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_XDrawLine)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 7)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::XDrawLine", "dpy, win, gc, x1, y1, x2, y2");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	Window	win;
	GC	gc;
	int	x1 = (int)SvIV(ST(3));
	int	y1 = (int)SvIV(ST(4));
	int	x2 = (int)SvIV(ST(5));
	int	y2 = (int)SvIV(ST(6));

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	if (sv_isa(ST(1), "Window")) {
	    win = INT2PTR(Window, SvIV(SvRV(ST(1))));
	}
	else {
	    win = (Window) NULL;
	    croak("win is not of type Window");
	};

	if (sv_isa(ST(2), "GC")) {
	    gc = INT2PTR(GC, SvIV(SvRV(ST(2))));
	}
	else {
	    gc = (GC) NULL;
	    croak("gc is not of type GC");
	};

	XDrawLine(dpy, win, gc, x1, y1, x2, y2);
    }
    XSRETURN_EMPTY;
}


XS(XS_DisplayPtr_XDrawRectangle); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_XDrawRectangle)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 7)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::XDrawRectangle", "dpy, win, gc, x, y, width, height");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	Window	win;
	GC	gc;
	int	x = (int)SvIV(ST(3));
	int	y = (int)SvIV(ST(4));
	int	width = (int)SvIV(ST(5));
	int	height = (int)SvIV(ST(6));

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	if (sv_isa(ST(1), "Window")) {
	    win = INT2PTR(Window, SvIV(SvRV(ST(1))));
	}
	else {
	    win = (Window) NULL;
	    croak("win is not of type Window");
	};

	if (sv_isa(ST(2), "GC")) {
	    gc = INT2PTR(GC, SvIV(SvRV(ST(2))));
	}
	else {
	    gc = (GC) NULL;
	    croak("gc is not of type GC");
	};

	XDrawRectangle(dpy, win, gc, x, y, width, height);
    }
    XSRETURN_EMPTY;
}


XS(XS_DisplayPtr_XDrawString); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_XDrawString)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 6)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::XDrawString", "dpy, win, gc, x, y, string");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	Window	win;
	GC	gc;
	int	x = (int)SvIV(ST(3));
	int	y = (int)SvIV(ST(4));
	SV *	string = ST(5);

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	if (sv_isa(ST(1), "Window")) {
	    win = INT2PTR(Window, SvIV(SvRV(ST(1))));
	}
	else {
	    win = (Window) NULL;
	    croak("win is not of type Window");
	};

	if (sv_isa(ST(2), "GC")) {
	    gc = INT2PTR(GC, SvIV(SvRV(ST(2))));
	}
	else {
	    gc = (GC) NULL;
	    croak("gc is not of type GC");
	};
#line 269 "Xlib.xs"
 {
  if (SvOK(string))
   {STRLEN len;
    char *s = SvPV(string,len);
    if (s && len)
     {
      XDrawString(dpy,win,gc,x,y,s,len);
     }
   }
 }
#line 753 "Xlib.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_DisplayPtr_RootWindow); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_RootWindow)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 1 || items > 2)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::RootWindow", "dpy, scr = DefaultScreen(dpy)");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	int	scr;
	Window	RETVAL;

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	if (items < 2)
	    scr = DefaultScreen(dpy);
	else {
	    scr = (int)SvIV(ST(1));
	}

	RETVAL = RootWindow(dpy, scr);
	ST(0) = sv_newmortal();
	sv_setref_iv(ST(0), "Window", PTR2IV(RETVAL));

    }
    XSRETURN(1);
}


XS(XS_DisplayPtr_DisplayString); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_DisplayString)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::DisplayString", "dpy");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	char *	RETVAL;
	dXSTARG;

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	RETVAL = DisplayString(dpy);
	sv_setpv(TARG, RETVAL); XSprePUSH; PUSHTARG;
    }
    XSRETURN(1);
}


XS(XS_DisplayPtr_DefaultScreen); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_DefaultScreen)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::DefaultScreen", "dpy");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	int	RETVAL;
	dXSTARG;

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	RETVAL = DefaultScreen(dpy);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_DisplayPtr_ScreenOfDisplay); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_ScreenOfDisplay)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 1 || items > 2)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::ScreenOfDisplay", "dpy, scr = DefaultScreen(dpy)");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	int	scr;
	Screen *	RETVAL;

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	if (items < 2)
	    scr = DefaultScreen(dpy);
	else {
	    scr = (int)SvIV(ST(1));
	}

	RETVAL = ScreenOfDisplay(dpy, scr);
	ST(0) = sv_newmortal();
	sv_setref_iv(ST(0), "ScreenPtr", PTR2IV(RETVAL));

    }
    XSRETURN(1);
}


XS(XS_DisplayPtr_DefaultGC); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_DefaultGC)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 2)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::DefaultGC", "dpy, scr");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	int	scr = (int)SvIV(ST(1));
	GC	RETVAL;

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	RETVAL = DefaultGC(dpy, scr);
	ST(0) = sv_newmortal();
	sv_setref_iv(ST(0), "GC", PTR2IV(RETVAL));

    }
    XSRETURN(1);
}


XS(XS_DisplayPtr_XQueryTree); /* prototype to pass -Wmissing-prototypes */
XS(XS_DisplayPtr_XQueryTree)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 2 || items > 4)
       Perl_croak(aTHX_ "Usage: %s(%s)", "DisplayPtr::XQueryTree", "dpy, w, root = NULL, parent = NULL");
    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	Display *	dpy;
	Window	w;
	SV *	root;
	SV *	parent;

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	if (sv_isa(ST(1), "Window")) {
	    w = INT2PTR(Window, SvIV(SvRV(ST(1))));
	}
	else {
	    w = (Window) NULL;
	    croak("w is not of type Window");
	};

	if (items < 3)
	    root = NULL;
	else {
	    root = ST(2);
	}

	if (items < 4)
	    parent = NULL;
	else {
	    parent = ST(3);
	}
#line 310 "Xlib.xs"
 {Window *children = NULL;
  unsigned int count = 0;
  Window pw = None;
  Window rw = None;
  if (XQueryTree(dpy, w, &rw, &pw, &children, &count))
   {
    unsigned int i;
    for (i=0; i < count; i++)
     {
      SV *sv = sv_newmortal();
      sv_setref_iv(sv, "Window", (IV) (children[i]));
      XPUSHs(sv);
     }
    XFree((char *) children);
   }
  else
   {
    count = 0;
    XSRETURN(0);
   }
  if (parent)
   {
    if (pw == None)
     sv_setsv(parent,&PL_sv_undef);
    else
     sv_setref_iv(parent, "Window", (IV) (pw));
   }
  if (root)
   {
    if (rw == None)
     sv_setsv(root,&PL_sv_undef);
    else
     sv_setref_iv(root, "Window", (IV) (rw));
   }
  XSRETURN(count);
 }
#line 1015 "Xlib.c"
	PUTBACK;
	return;
    }
}


XS(XS_GC_new); /* prototype to pass -Wmissing-prototypes */
XS(XS_GC_new)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 3)
       Perl_croak(aTHX_ "Usage: %s(%s)", "GC::new", "CLASS, dpy, win, ...");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	Window	win;
	char *	CLASS = (char *)SvPV_nolen(ST(0));
	GC	RETVAL;

	if (sv_isa(ST(1), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(1))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	if (sv_isa(ST(2), "Window")) {
	    win = INT2PTR(Window, SvIV(SvRV(ST(2))));
	}
	else {
	    win = (Window) NULL;
	    croak("win is not of type Window");
	};
#line 354 "Xlib.xs"
  {unsigned long valuemask = 0;
   XGCValues values;
   STRLEN na;
   int i;
   for (i=3; i < items; i += 2)
    {char *key = SvPV(ST(i),na);
     if (i+1 < items)
      valuemask = GCSetValue(aTHX_ valuemask,&values,key,ST(i+1));
     else
      croak("No value for %s",key);
    }
   RETVAL = XCreateGC(dpy,win,valuemask,&values);
  }
#line 1068 "Xlib.c"
	ST(0) = sv_newmortal();
	sv_setref_iv(ST(0), "GC", PTR2IV(RETVAL));

    }
    XSRETURN(1);
}


XS(XS_GC_Foreground); /* prototype to pass -Wmissing-prototypes */
XS(XS_GC_Foreground)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 3)
       Perl_croak(aTHX_ "Usage: %s(%s)", "GC::Foreground", "dpy, gc, val");
    PERL_UNUSED_VAR(cv); /* -W */
    {
	Display *	dpy;
	GC	gc;
	unsigned long	val = (unsigned long)SvUV(ST(2));

	if (sv_isa(ST(0), "DisplayPtr")) {
	    dpy = INT2PTR(Display *, SvIV(SvRV(ST(0))));
	}
	else {
	    dpy = (Display *) NULL;
	    croak("dpy is not of type DisplayPtr");
	};

	if (sv_isa(ST(1), "GC")) {
	    gc = INT2PTR(GC, SvIV(SvRV(ST(1))));
	}
	else {
	    gc = (GC) NULL;
	    croak("gc is not of type GC");
	};

	XSetForeground(dpy, gc, val);
    }
    XSRETURN_EMPTY;
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_Tk__Xlib); /* prototype to pass -Wmissing-prototypes */
XS(boot_Tk__Xlib)
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

        newXS("Tk::Widget::tmpLine", XS_Tk__Widget_tmpLine, file);
        newXS("ScreenPtr::WidthOfScreen", XS_ScreenPtr_WidthOfScreen, file);
        newXS("ScreenPtr::WidthMMOfScreen", XS_ScreenPtr_WidthMMOfScreen, file);
        newXS("ScreenPtr::HeightOfScreen", XS_ScreenPtr_HeightOfScreen, file);
        newXS("ScreenPtr::HeightMMOfScreen", XS_ScreenPtr_HeightMMOfScreen, file);
        newXS("ScreenPtr::DefaultGCOfScreen", XS_ScreenPtr_DefaultGCOfScreen, file);
        newXS("ScreenPtr::BlackPixelOfScreen", XS_ScreenPtr_BlackPixelOfScreen, file);
        newXS("ScreenPtr::WhitePixelOfScreen", XS_ScreenPtr_WhitePixelOfScreen, file);
        newXS("DisplayPtr::XSync", XS_DisplayPtr_XSync, file);
        newXS("DisplayPtr::XFlush", XS_DisplayPtr_XFlush, file);
        newXS("DisplayPtr::ConnectionNumber", XS_DisplayPtr_ConnectionNumber, file);
        newXS("DisplayPtr::XLoadFont", XS_DisplayPtr_XLoadFont, file);
        newXS("DisplayPtr::XListFonts", XS_DisplayPtr_XListFonts, file);
        newXS("DisplayPtr::XDrawLine", XS_DisplayPtr_XDrawLine, file);
        newXS("DisplayPtr::XDrawRectangle", XS_DisplayPtr_XDrawRectangle, file);
        newXS("DisplayPtr::XDrawString", XS_DisplayPtr_XDrawString, file);
        newXS("DisplayPtr::RootWindow", XS_DisplayPtr_RootWindow, file);
        newXS("DisplayPtr::DisplayString", XS_DisplayPtr_DisplayString, file);
        newXS("DisplayPtr::DefaultScreen", XS_DisplayPtr_DefaultScreen, file);
        newXS("DisplayPtr::ScreenOfDisplay", XS_DisplayPtr_ScreenOfDisplay, file);
        newXS("DisplayPtr::DefaultGC", XS_DisplayPtr_DefaultGC, file);
        newXS("DisplayPtr::XQueryTree", XS_DisplayPtr_XQueryTree, file);
        newXS("GC::new", XS_GC_new, file);
        newXS("GC::Foreground", XS_GC_Foreground, file);

    /* Initialisation Section */

#line 377 "Xlib.xs"
 {
  IMPORT_VTABLES;
 }

#line 1163 "Xlib.c"

    /* End of Initialisation Section */

    XSRETURN_YES;
}

