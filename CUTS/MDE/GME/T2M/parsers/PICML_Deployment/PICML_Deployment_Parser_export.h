
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl PICML_DEPLOYMENT_PARSER
// ------------------------------
#ifndef PICML_DEPLOYMENT_PARSER_EXPORT_H
#define PICML_DEPLOYMENT_PARSER_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (PICML_DEPLOYMENT_PARSER_HAS_DLL)
#  define PICML_DEPLOYMENT_PARSER_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && PICML_DEPLOYMENT_PARSER_HAS_DLL */

#if !defined (PICML_DEPLOYMENT_PARSER_HAS_DLL)
#  define PICML_DEPLOYMENT_PARSER_HAS_DLL 1
#endif /* ! PICML_DEPLOYMENT_PARSER_HAS_DLL */

#if defined (PICML_DEPLOYMENT_PARSER_HAS_DLL) && (PICML_DEPLOYMENT_PARSER_HAS_DLL == 1)
#  if defined (PICML_DEPLOYMENT_PARSER_BUILD_DLL)
#    define PICML_DEPLOYMENT_PARSER_Export ACE_Proper_Export_Flag
#    define PICML_DEPLOYMENT_PARSER_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define PICML_DEPLOYMENT_PARSER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* PICML_DEPLOYMENT_PARSER_BUILD_DLL */
#    define PICML_DEPLOYMENT_PARSER_Export ACE_Proper_Import_Flag
#    define PICML_DEPLOYMENT_PARSER_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define PICML_DEPLOYMENT_PARSER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* PICML_DEPLOYMENT_PARSER_BUILD_DLL */
#else /* PICML_DEPLOYMENT_PARSER_HAS_DLL == 1 */
#  define PICML_DEPLOYMENT_PARSER_Export
#  define PICML_DEPLOYMENT_PARSER_SINGLETON_DECLARATION(T)
#  define PICML_DEPLOYMENT_PARSER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* PICML_DEPLOYMENT_PARSER_HAS_DLL == 1 */

// Set PICML_DEPLOYMENT_PARSER_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (PICML_DEPLOYMENT_PARSER_NTRACE)
#  if (ACE_NTRACE == 1)
#    define PICML_DEPLOYMENT_PARSER_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define PICML_DEPLOYMENT_PARSER_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !PICML_DEPLOYMENT_PARSER_NTRACE */

#if (PICML_DEPLOYMENT_PARSER_NTRACE == 1)
#  define PICML_DEPLOYMENT_PARSER_TRACE(X)
#else /* (PICML_DEPLOYMENT_PARSER_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define PICML_DEPLOYMENT_PARSER_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (PICML_DEPLOYMENT_PARSER_NTRACE == 1) */

#endif /* PICML_DEPLOYMENT_PARSER_EXPORT_H */

// End of auto generated file.
