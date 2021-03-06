// -*- C++ -*-

//=============================================================================
/**
 * @file        CAPI_Manager.h
 *
 * Defines the CUTS_BE_CAPI_Manager manager object
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CAPI_MANAGER_H_
#define _CUTS_BE_CAPI_MANAGER_H_

#include "CAPI_Generators.h"
#include "../../BE_Manager_T.h"

typedef CUTS_BE_Manager_T <CUTS_BE_Capi::Context>
                           CUTS_BE_CAPI_Manager;

#endif  // !defined _CUTS_BE_CAPI_MANAGER_H_
