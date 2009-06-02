// -*- C++ -*-

//=============================================================================
/**
 *  @file         CCM_Container_Strategy_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_CONTAINER_STRATEGY_T_H_
#define _CUTS_CCM_CONTAINER_STRATEGY_T_H_

#include "ccm/CCM_EnterpriseComponentC.h"
#include "ccm/CCM_StandardConfiguratorC.h"
#include "tao/PortableServer/PS_ForwardC.h"
#include "CCM_export.h"

/**
 * @class CUTS_CCM_Container_Strategy_T
 */
template <typename SERVER>
class CUTS_CCM_Container_Strategy_T
{
public:
  /// Type definition of the servant type.
  typedef SERVER server_type;

  CUTS_CCM_Container_Strategy_T (SERVER * server);

  virtual ~CUTS_CCM_Container_Strategy_T (void);

  virtual ::Components::EnterpriseComponent_ptr
    load_executor (const char * location,
                   const char * entrypt);

  virtual ::PortableServer::Servant
    load_servant (const char * name,
                  const char * location,
                  const char * entrypoint,
                  ::Components::EnterpriseComponent_ptr executor);

protected:
  /// Pointer to the component server hosting the container.
  SERVER * server_;
};

#if defined (__CUTS_INLINE__)
#include "CCM_Container_Strategy_T.inl"
#endif

#include "CCM_Container_Strategy_T.cpp"

#endif  // !defined _CUTS_CCM_CONTAINER_STRATEGY_T_H_
