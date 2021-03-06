// -*- C++ -*-

//=============================================================================
/**
 * @file        CUTS_i.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_I_H_
#define _CUTS_I_H_

#include "idl/CUTSC.h"
#include "Component_Type.h"
#include "Benchmark_Agent.h"

//=============================================================================
// @@ extraction operations

void CUTS_Export operator >>= (const CUTS::Port_Descriptions & desc,
                               CUTS_Port_Description_Map & map);

//=============================================================================
// @@ insertion operations

void CUTS_Export operator <<= (CUTS::Port_Descriptions & desc,
                               const CUTS_Port_Agent_Set & agents);

void CUTS_Export operator <<= (CUTS::Port_Descriptions & desc,
                               const CUTS_Endpoint_Map & ends);

#endif  // !defined _CUTS_I_H_
