// This file was generated by:
// $Id$

#include "HelloWorld_Impl.h"
#include "cuts/arch/ccm/CCM_Events_T.h"

namespace HelloWorld_Basic_Impl
{
  //
  // HelloWorld
  //
  HelloWorld::HelloWorld (void)
  : eventCount_ (0),
    isActive_ (true)
  {
    this->periodic_sendData_.init (this, &HelloWorld::periodic_sendData);
    this->periodic_sendData_.configure (CUTS_Periodic_Event::PE_CONSTANT, 10);
    this->register_object (&this->periodic_sendData_);
  }

  //
  // ~HelloWorld
  //
  HelloWorld::~HelloWorld (void)
  {
  }

  //
  // sink: handle_message
  //
  void HelloWorld::push_handle_message (::Message * ev)
  {
    CUTS_CCM_Event_T <OBV_Message> __event_100000038__;
    this->ctx_->push_handle_message (__event_100000038__.in ());

    ACE_UNUSED_ARG (ev);
  }

  //
  // PeriodicEvent: sendData
  //
  void HelloWorld::periodic_sendData (void)
  {
    CUTS_CCM_Event_T <OBV_Message> __event_100000040__;
    this->ctx_->push_handle_message_ex (__event_100000040__.in ());
  }

  //
  // attribute setter: message
  //
  void HelloWorld::message (const char * message)
  {
    this->message_ = message;
  }

  //
  // attribute getter: message
  //
  char * HelloWorld::message (void)
  {
    ::CORBA::String_var s =
      ::CORBA::string_dup (this->message_.c_str ());
    return s._retn ();
  }

  //
  // attribute getter: readonly_message
  //
  char * HelloWorld::readonly_message (void)
  {
    ::CORBA::String_var s =
      ::CORBA::string_dup (this->readonly_message_.c_str ());
    return s._retn ();
  }

  void HelloWorld::ccm_activate (void)
  {
    // pass control to the base class
    this->base_type::ccm_activate ();
  }
}

//
// create_HelloWorld_Basic_Impl
//
::Components::EnterpriseComponent_ptr 
create_HelloWorld_Basic_Impl (void)
{
  ::Components::EnterpriseComponent_ptr retval =
    ::Components::EnterpriseComponent::_nil ();

  ACE_NEW_RETURN (retval, 
                  ::HelloWorld_Basic_Impl::HelloWorld (),
                  ::Components::EnterpriseComponent::_nil ());

  return retval;
}


// end of auto-generated file

