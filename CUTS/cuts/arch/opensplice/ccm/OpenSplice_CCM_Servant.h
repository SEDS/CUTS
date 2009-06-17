// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_CCM_SERVANT_H_
#define _CUTS_OPENSPLICE_CCM_SERVANT_H_

#include "ccpp_dds_dcps.h"
#include "cuts/arch/ccm/CCM_Servant.h"
#include "cuts/arch/opensplice/OpenSplice_Servant.h"
#include "OpenSplice_CCM_export.h"

/**
 * @class CUTS_OpenSplice_CCM_Servant
 *
 * Base class for all OpenSplice servant objects. This class enables
 * the container to send commands to the servant, such as configuration
 * information for each of its topics.
 */
class CUTS_OPENSPLICE_CCM_Export CUTS_OpenSplice_CCM_Servant :
  public CUTS_OpenSplice_Servant,
  public CUTS_CCM_Servant
{
public:
  /// Destructor.
  virtual ~CUTS_OpenSplice_CCM_Servant (void);

protected:
  /// Default constructor.
  CUTS_OpenSplice_CCM_Servant (const char * name);
};

#if defined (__CUTS_INLINE__)
#include "OpenSplice_CCM_Servant.inl"
#endif

#endif  // !defined _CUTS_OPENSPLICE_CCM_SERVANT_H_