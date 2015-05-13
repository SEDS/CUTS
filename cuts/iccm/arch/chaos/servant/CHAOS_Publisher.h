// -*- C++ -*-

//=============================================================================
/**
 *  @file         CHAOS_Publisher.h
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

#ifndef _ICCM_CHAOS_PUBLISHER_H_
#define _ICCM_CHAOS_PUBLISHER_H_

#include "cuts/iccm/servant/Publisher.h"

#include "CHAOS_EventsC.h"
#include "CHAOS_svnt_export.h"

namespace iCCM
{

/**
 * @class CHAOS_Publisher
 *
 * The base class for all CHAOS publishers that are integrated into
 * the iCCM architecture. In essence, this class is an adapter class that
 * allows a CHAOS publisher to integrate with the iCCM architecture.
 *
 * CHAOS does not have its own Publishers.  Instead, it is a proxy
 * to architecture-specific Publishers.
 */
class ICCM_CHAOS_SVNT_Export CHAOS_Publisher :
  public Publisher
{
public:
  /// Default constructor.
  CHAOS_Publisher (void);

  /// Destructor.
  virtual ~CHAOS_Publisher (void);

  /**
   * Connect an event consumer to this publisher. This reference should
   * be narrowed to a ::Components::CHAOS::EventConsumer object.
   *
   * @param[in]           consumer          Referene to event consumer.
   */
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  /// Disconnect the consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

  /// CCM lifecycle events
  virtual void activate (void);
  virtual void passivate (void);

protected:
  /// The underlying publisher
  Publisher * impl_;
};

}

#if defined (__CUTS_INLINE__)
#include "CHAOS_Publisher.inl"
#endif

#endif  // !defined _ICCM_CHAOS_PUBLISHER_H_
