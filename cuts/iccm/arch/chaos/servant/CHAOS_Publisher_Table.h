// -*- C++ -*-

//=============================================================================
/**
 *  @file         CHAOS_Publisher_Table.h
 *
 *  $Id$
 *
 *  Code generated by iCCM skeleton project generator that is include
 *  in the CUTS (http://cuts.cs.iupui.edu) and developed by:
 *
 *      Software Engineering & Distributed System (SEDS) Group
 *      Indiana Univesity-Purdue University Indianapolis
 *      Indianapolis, IN 46202
 */
//=============================================================================

#ifndef _ICCM_CHAOS_PUBLISHER_TABLE_H_
#define _ICCM_CHAOS_PUBLISHER_TABLE_H_

#include "cuts/iccm/servant/Publisher_Table.h"

#include "CHAOS_svnt_export.h"

namespace iCCM
{

/**
 * @class CHAOS_Publisher_Table
 */
class ICCM_CHAOS_SVNT_Export CHAOS_Publisher_Table :
  public Publisher_Table
{
public:
  /// Default constructor.
  CHAOS_Publisher_Table (void);

  /// Destructor.
  virtual ~CHAOS_Publisher_Table (void);

  /// INSERT CODE HERE

private:
  /// INSERT CODE HERE
};

}

#if defined (__CUTS_INLINE__)
#include "CHAOS_Publisher_Table.inl"
#endif

#endif  // !defined _ICCM_CHAOS_PUBLISHER_TABLE_H_
