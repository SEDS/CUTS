// -*- C++ -*-
// $IdCHAOS_Publisher.inl 3086 2011-01-22 05:53:51Z hillj $

namespace iCCM
{

//
// CHAOS_Publisher
//
CUTS_INLINE
CHAOS_Publisher::CHAOS_Publisher (void)
: impl_ (0)
{

}

//
// ~CHAOS_Publisher
//
CUTS_INLINE
CHAOS_Publisher::~CHAOS_Publisher (void)
{

}

//
// impl
//
CUTS_INLINE
void
CHAOS_Publisher::impl (Publisher * impl)
{
  this->impl_ = impl;
}

//
// connect
//
CUTS_INLINE
void
CHAOS_Publisher::connect (::Components::EventConsumerBase_ptr consumer)
{
  this->impl_->connect (consumer);
}

//
// disconnect
//
CUTS_INLINE
::Components::EventConsumerBase_ptr
CHAOS_Publisher::disconnect (void)
{
  return this->impl_->disconnect ();
}

//
// activate
//
CUTS_INLINE
void
CHAOS_Publisher::activate (void)
{
  this->impl_->activate ();
}

//
// passivate
//
CUTS_INLINE
void
CHAOS_Publisher::passivate (void)
{
  this->impl_->passivate ();
}

//
// send_event
//
CUTS_INLINE
void
CHAOS_Publisher::send_event (::Components::EventBase * ev)
{
  this->impl_->send_event (ev);
}

//
// allocate_event
//
CUTS_INLINE
::Components::EventBase *
CHAOS_Publisher::allocate_event (void)
{
  return this->impl_->allocate_event ();
}

}
