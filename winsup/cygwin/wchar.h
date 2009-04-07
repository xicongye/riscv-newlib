/* wchar.h: Extra wchar defs

   Copyright 2007, 2009 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _CYGWIN_WCHAR_H
#define _CYGWIN_WCHAR_H

#include_next <wchar.h>

#define ENCODING_LEN 31

#ifdef __cplusplus
extern "C" {
#endif

typedef int mbtowc_f (struct _reent *, wchar_t *, const char *, size_t,
		      const char *, mbstate_t *);
typedef mbtowc_f *mbtowc_p;

extern mbtowc_p __mbtowc;
extern mbtowc_f __ascii_mbtowc;
extern mbtowc_f __utf8_mbtowc;
extern mbtowc_f __iso_mbtowc;
extern mbtowc_f __cp_mbtowc;

typedef int wctomb_f (struct _reent *, char *, wchar_t, const char *,
		      mbstate_t *);
typedef wctomb_f *wctomb_p;

extern wctomb_p __wctomb;
extern wctomb_f __utf8_wctomb;

extern char *__locale_charset ();

extern mbtowc_p __set_charset_from_codepage (unsigned int cp, char *charset);

#ifdef __cplusplus
}
#endif

size_t __stdcall sys_cp_wcstombs (wctomb_p, char *, char *, size_t,
				  const PWCHAR, size_t = (size_t) -1)
       __attribute__ ((regparm(3)));
inline size_t
__stdcall sys_wcstombs (char *dst, size_t len, const PWCHAR src,
			size_t nwc = (size_t) -1)
{
  return sys_cp_wcstombs (__wctomb, __locale_charset (), dst, len, src, nwc);
}
size_t __stdcall sys_wcstombs_alloc (char **, int, const PWCHAR,
				     size_t = (size_t) -1)
       __attribute__ ((regparm(3)));

size_t __stdcall sys_cp_mbstowcs (mbtowc_p, char *, PWCHAR, size_t,
				  const char *, size_t = (size_t) -1)
       __attribute__ ((regparm(3)));
inline size_t
sys_mbstowcs (PWCHAR dst, size_t dlen, const char *src,
	      size_t nms = (size_t) -1)
{
  return sys_cp_mbstowcs (__mbtowc, __locale_charset (), dst, dlen, src, nms);
}
size_t __stdcall sys_mbstowcs_alloc (PWCHAR *, int, const char *,
				     size_t = (size_t) -1)
       __attribute__ ((regparm(3)));

#endif /* _CYGWIN_WCHAR_H */
