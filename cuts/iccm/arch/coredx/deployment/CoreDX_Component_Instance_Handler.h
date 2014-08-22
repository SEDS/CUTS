// -*- C++ -*-

//=============================================================================
/**
 *  @file CoreDX_Component_Instance_Handler.h
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

#ifndef _ICCM_COREDX_COMPONENT_INSTANCE_HANDLER_H_
#define _ICCM_COREDX_COMPONENT_INSTANCE_HANDLER_H_

#include "cuts/iccm/arch/dds/deployment/DDS_Component_Instance_Handler.h"
#include "CoreDX_Container.h"

#include "CoreDX_Deployment_Handlers_export.h"

namespace iCCM
{

/**
 * @class CoreDX_Component_Instance_Handler
 *
 * CoreDX implementation of the deployment handlers for component
 * instances.
 */
class  ICCM_COREDX_DEPLOYMENT_HANDLERS_Export CoreDX_Component_Instance_Handler :
  public DDS_Component_Instance_Handler <CoreDX_Deployment>
{
public:
  /// Type definition of the base type.
  typedef DDS_Component_Instance_Handler <CoreDX_Deployment> base_type;

  /// Default constructor.
  CoreDX_Component_Instance_Handler (void);

  /// Destructor.
  virtual ~CoreDX_Component_Instance_Handler (void);

  /**
   * Configure the instance handler. The deployment properties passed
   * into this function are the ones attached to the Node in the
   * deployment model.
   *
   * @param[in]           config          Configuration properties
   */
  virtual void configure (const Deployment::Properties & config);

  /// Close the instance handler.
  virtual void close (void);

protected:
  /// Helper method handle the DDSDominQoS property.
  void configure_DDSDomainQoS (const iccm::DomainParticipantFactoryQos & qos);

private:
  /// INSERT YOUR VARIABLES HERE
};

}

extern "C"
ICCM_COREDX_DEPLOYMENT_HANDLERS_Export
::DAnCE::InstanceDeploymentHandler_ptr
create_iCCM_CoreDX_Component_Instance_Handler (void);

#if defined (__CUTS_INLINE__)
#include "CoreDX_Component_Instance_Handler.inl"
#endif

#endif  // !defined _ICCM_CoreDX_COMPONENT_INSTANCE_HANDLER_H_