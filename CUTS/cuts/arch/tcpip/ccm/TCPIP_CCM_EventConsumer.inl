// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_CCM_EventConsumer
//
CUTS_INLINE
CUTS_TCPIP_CCM_EventConsumer::
CUTS_TCPIP_CCM_EventConsumer (CUTS_TCPIP_Servant * parent, long event)
: parent_ (parent),
  event_ (event)
{

}

//
// ~CUTS_TCPIP_CCM_EventConsumer
//
CUTS_INLINE
CUTS_TCPIP_CCM_EventConsumer::~CUTS_TCPIP_CCM_EventConsumer (void)
{

}

//
// push_event
//
CUTS_INLINE
void CUTS_TCPIP_CCM_EventConsumer::push_event (Components::EventBase *)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// ciao_push_event
//
CUTS_INLINE
void CUTS_TCPIP_CCM_EventConsumer::
ciao_push_event (Components::EventBase *, const char *, CORBA::TypeCode_ptr)
{
  throw CORBA::NO_IMPLEMENT ();
}
