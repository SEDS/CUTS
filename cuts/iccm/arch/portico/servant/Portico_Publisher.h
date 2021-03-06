// -*- C++ -*-

//=============================================================================
/**
 *  @file         Portico_Publisher.h
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

#ifndef _ICCM_PORTICO_PUBLISHER_H_
#define _ICCM_PORTICO_PUBLISHER_H_

#include "cuts/iccm/servant/Publisher.h"

#include "Portico_EventsC.h"
#include "Portico_svnt_export.h"

#include "ace/UUID.h"
#include "Portico_ObjectClass_Factory.h"

namespace iCCM
{

/**
 * @class Portico_Publisher
 *
 * The base class for all Portico publishers that are integrated into
 * the iCCM architecture. In essence, this class is an adapter class that
 * allows a Portico publisher to integrate with the iCCM architecture.
 */
class ICCM_PORTICO_SVNT_Export Portico_Publisher :
  public Publisher
{
public:
  /// Default constructor.
  Portico_Publisher (void);

  /// Destructor.
  virtual ~Portico_Publisher (void);

  /**
   * Connect an event consumer to this publisher. This reference should
   * be narrowed to a ::Components::Portico::EventConsumer object.
   *
   * @param[in]           consumer          Referene to event consumer.
   */
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  /// Disconnect the consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

  /**
   * Initialize this publisher's handle.
   *
   * @param[in]           rtiamb            Pointer to the ambassador
   */
  virtual void init (RTI::RTIambassador * rtiamb) = 0;

  /**
   * Send an event.
   *
   * @param[in]           attrs             Event attributes
   */
  void send_event (const RTI::AttributeHandleValuePairSet & attrs);

  /// Helper method for storing a connection.
  void connect (::Components::Portico::EventConsumer_ptr p);

protected:
  /// The consumer connected to this publisher.
  ::Components::Portico::EventConsumer_var consumer_;

  /// Pointer to the ambassador.
  RTI::RTIambassador * rtiamb_;

  /// Object instance this publisher is managing.
  RTI::ObjectHandle obj_handle_;

  /// Tag for the object instance.
  ACE_Utils::UUID tag_;
};

}

#if defined (__CUTS_INLINE__)
#include "Portico_Publisher.inl"
#endif

#endif  // !defined _ICCM_PORTICO_PUBLISHER_H_
