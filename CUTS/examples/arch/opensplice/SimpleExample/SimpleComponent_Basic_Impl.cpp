// This file was generated by:
// $Id$

#include "SimpleComponent_Basic_Impl.h"
#include "cuts/arch/ccm/CCM_Events_T.h"

namespace SimpleComponent_Basic_Impl
{
  //
  // SimpleComponent
  //
  SimpleComponent::SimpleComponent (void)
  : isActive_ (true),
    eventCount_ (0)
  {
    this->periodic_sendData_.init (this, &SimpleComponent::periodic_sendData);
    this->periodic_sendData_.configure (CUTS_Periodic_Event::PE_CONSTANT, 10);
    this->register_object (&this->periodic_sendData_);
  }

  //
  // ~SimpleComponent
  //
  SimpleComponent::~SimpleComponent (void)
  {
  }

  //
  // sink: corba_read_test_data
  //
  void SimpleComponent::push_corba_read_test_data (::Outer::TestData_DDS * ev)
  {
    ACE_UNUSED_ARG (ev);
  }

  //
  // sink: dds_read_test_data
  //
  void SimpleComponent::push_dds_read_test_data (::Outer::TestData_DDS * ev)
  {
    ACE_UNUSED_ARG (ev);
  }

  //
  // sink: tcpip_read_test_data
  //
  void SimpleComponent::push_tcpip_read_test_data (::Outer::TestData_DDS * ev)
  {
    ACE_UNUSED_ARG (ev);
  }

  //
  // PeriodicEvent: sendData
  //
  void SimpleComponent::periodic_sendData (void)
  {
  }

  void SimpleComponent::ccm_activate (void)
  {
    // pass control to the base class
    this->base_type::ccm_activate ();
  }
}

//
// create_SimpleComponent_Basic_Impl
//
::Components::EnterpriseComponent_ptr 
create_SimpleComponent_Basic_Impl (void)
{
  ::Components::EnterpriseComponent_ptr retval =
    ::Components::EnterpriseComponent::_nil ();

  ACE_NEW_RETURN (retval, 
                  ::SimpleComponent_Basic_Impl::SimpleComponent (),
                  ::Components::EnterpriseComponent::_nil ());

  return retval;
}


// end of auto-generated file

