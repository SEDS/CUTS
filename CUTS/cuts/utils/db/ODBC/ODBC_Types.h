// -*- C++ -*-

//=============================================================================
/**
 * @file        ODBC_Types.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ODBC_TYPES_H_
#define _CUTS_ODBC_TYPES_H_

#include "ODBC.h"
#include "cuts/utils/db/DB_Types_Impl.h"

// Forward decl.
class ACE_Date_Time;

//=============================================================================
/**
 * @class ODBC_Date_Time
 *
 * ODBC implementation of the CUTS_DB_Date_Time_Impl class.
 */
//=============================================================================

class CUTS_ODBC_Export ODBC_Date_Time :
  public CUTS_DB_Date_Time
{
public:
  /// Default constructor.
  ODBC_Date_Time (void);

  /// Destructor.
  virtual ~ODBC_Date_Time (void);

  long month (void) const;
  void month (long);

  long day (void) const;
  void day (long);

  long year (void) const;
  void year (long);

  long hour (void) const;
  void hour (long);

  long minute (void) const;
  void minute (long);

  long second (void) const;
  void second (long);

  long fraction (void) const;
  void fraction (long);

  void * value (void);

  void set (const ACE_Date_Time & datetime);

  void set (const ODBC_Date_Time & datetime);

private:
  /// SQL timestamp data value.
  SQL_TIMESTAMP_STRUCT datetime_;
};

#if defined (__CUTS_INLINE__)
#include "ODBC_Types.inl"
#endif

#endif  // !defined _CUTS_ODBC_TYPES_H_