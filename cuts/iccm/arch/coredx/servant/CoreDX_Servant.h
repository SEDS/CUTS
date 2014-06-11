// -*- C++ -*-

//==============================================================================
/**
 *  @file       CoreDX_Servant.h
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
//==============================================================================

#ifndef _ICCM_COREDX_SERVANT_H_
#define _ICCM_COREDX_SERVANT_H_

#include "cuts/iccm/arch/dds/servant/DDS_Servant.h"
#include "CoreDX.h"

namespace iccm
{
  // Forward decl.
  class TopicQos;

  // Forward decl.
  class PublisherQos;

  // Forward decl.
  class SubscriberQos;

  // Forward decl.
  class DataReaderQos;

  // Forward decl.
  class DataWriterQos;
}

namespace iCCM
{

/**
 * @class CoreDX_Servant
 *
 * Base class for all CoreDX servant objects. This class enables
 * the container to send commands to the servant, such as
 * domain-specific configuration information.
 */
class ICCM_COREDX_SVNT_Export CoreDX_Servant :
  public DDS_Servant <CoreDX>
{
public:
  /// Trait definitions for iCCM::Servant_T object.
  typedef CoreDX_EventConsumer eventconsumer_type;
  typedef CoreDX_Publisher publisher_type;
  typedef CoreDX_Publisher_Table publisher_table_type;

  /// Default constructor.
  CoreDX_Servant (const char * name);

  /// Destructor.
  virtual ~CoreDX_Servant (void);

  /// Default configuration.
  virtual void configure (void);

  /// Initialize Qos configuration.
  virtual void configure (const ::iccm::DomainParticipantQos & qos);

private:
  void configure_topic (const ::iccm::TopicQos & value);
  void configure_publisher (const ::iccm::PublisherQos & value);
  void configure_subscriber (const ::iccm::SubscriberQos & value);
  void configure_datareader (const ::iccm::DataReaderQos & value);
  void configure_datawriter (const ::iccm::DataWriterQos & value);
};

}

#if defined (__CUTS_INLINE__)
#include "CoreDX_Servant.inl"
#endif

#endif  // !defined _ICCM_CoreDX_SERVANT_H_
