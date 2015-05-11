// -*- C++ -*-

//=============================================================================
/**
 *  @file         CHAOS_Container.h
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

#ifndef _ICCM_CHAOS_CONTAINER_H_
#define _ICCM_CHAOS_CONTAINER_H_

#include "cuts/iccm/deployment/Container_T.h"

#include "../servant/CHAOS_Servant.h"
#include "CHAOS_Container_Strategy.h"

namespace iCCM
{

// Forward decl.
class CHAOS_Component_Instance_Handler;

/**
 * @class CHAOS_Container
 *
 * iCCM container implementation for the CHAOS architecture.
 */
class ICCM_CHAOS_DEPLOYMENT_HANDLERS_Export CHAOS_Container :
  public Container_T <CHAOS_Container,
                      CHAOS_Component_Instance_Handler,
                      CHAOS_Container_Strategy,
                      CHAOS_Servant>
{
public:
  /// Type definition of the base type.
  typedef
    Container_T <CHAOS_Container,
                 CHAOS_Component_Instance_Handler,
                 CHAOS_Container_Strategy,
                 CHAOS_Servant> base_type;

  /**
   * Initializing constructor.
   *
   * @param[in]           handler           Pointer to instance handler
   * @param[in]           poa               PortableServer for container
   */
  CHAOS_Container (
    CHAOS_Component_Instance_Handler * handler,
     ::PortableServer::POA_ptr the_POA);

  /// Destructor.
  virtual ~CHAOS_Container (void);
};

}

#if defined (__CUTS_INLINE__)
#include "CHAOS_Container.inl"
#endif

#endif  // !defined _ICCM_CHAOS_CONTAINER_H_
