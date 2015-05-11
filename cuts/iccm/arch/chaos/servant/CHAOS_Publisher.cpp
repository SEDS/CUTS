// $IdCHAOS_Publisher.cpp 3086 2011-01-22 05:53:51Z hillj $

#include "CHAOS_Publisher.h"

#if !defined (__CUTS_INLINE__)
#include "CHAOS_Publisher.inl"
#endif

namespace iCCM
{

//
// connect
//
void CHAOS_Publisher::
connect (::Components::EventConsumerBase_ptr p)
{
  // Narrow the base consumer to a consumer of our type. This way, we
  // can validate the consumer and make sure we are not working with
  // a consumer type we do not know about.
  ::Components::CHAOS::EventConsumer_var consumer =
    ::Components::CHAOS::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (consumer.in ()))
    throw ::CORBA::INTERNAL ();

  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here should use the <consumer> object
  // to extract information for establishing a connection and sending
  // data to this consumer event point via CHAOS architecture.
  //===========================================================================

  // Store the event consumer since all operations above executed
  // correctly and we need to remember the event consumer for the
  // disconnect operation.
  this->consumer_ = ::Components::CHAOS::EventConsumer::_narrow (p);
}

//
// disconnect
//
::Components::EventConsumerBase_ptr
CHAOS_Publisher::disconnect (void)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code you place here should release all resources required for
  // communicating over CHAOS to the contained consumer.
  //===========================================================================

  // Return ownership to the caller. This will allow the caller
  // to gracefully destroy the event consumer.
  return this->consumer_._retn ();
}

}
