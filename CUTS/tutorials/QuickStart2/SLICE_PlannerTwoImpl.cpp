// This file was generated by:
// $Id$

#include "SLICE_PlannerTwoImpl.h"
#include "cuts/arch/ccm/CCM_Events_T.h"

namespace SLICE_PlannerTwoImpl
{
  //
  // PlannerTwo
  //
  PlannerTwo::PlannerTwo (void)
  {
  }

  //
  // ~PlannerTwo
  //
  PlannerTwo::~PlannerTwo (void)
  {
  }

  //
  // sink: recvEvent
  //
  void PlannerTwo::push_recvEvent (::SLICE::SimpleEvent * ev)
  {
    this->cpuGen_.run (30);
    CUTS_CCM_Event_T <OBV_SLICE::SimpleEvent> __event_100000083__;
    __event_100000083__->content ().eventCount = ev->content ().eventCount;
    this->ctx_->push_pushEvent (__event_100000083__.in ());

    ACE_UNUSED_ARG (ev);
  }
}

//
// create_SLICE_PlannerTwo_Impl
//
::Components::EnterpriseComponent_ptr
create_SLICE_PlannerTwo_Impl (void)
{
  ::Components::EnterpriseComponent_ptr retval =
    ::Components::EnterpriseComponent::_nil ();

  ACE_NEW_RETURN (retval,
                  ::SLICE_PlannerTwoImpl::PlannerTwo (),
                  ::Components::EnterpriseComponent::_nil ());

  return retval;
}


// end of auto-generated file
