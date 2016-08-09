// -*- C++ -*-
// $Id$

namespace iCCM
{

CUTS_INLINE
EventConsumer_Listener::EventConsumer_Listener (void)
{

}

CUTS_INLINE
EventConsumer_Listener::~EventConsumer_Listener (void)
{

}

CUTS_INLINE
EventConsumer::EventConsumer (void)
  : task_(0)
{

}

CUTS_INLINE
EventConsumer::EventConsumer (EventConsumer_Task_Base * task)
  : task_(task)
{

}

CUTS_INLINE
EventConsumer::~EventConsumer (void)
{
}

CUTS_INLINE
void EventConsumer::push_event (Components::EventBase * ev)
{
  if (0 != this->listener_)
    this->listener_->handle_event (ev);
}

CUTS_INLINE
void
EventConsumer::activate (void)
{

}

CUTS_INLINE
void
EventConsumer::passivate (void)
{

}

CUTS_INLINE
void EventConsumer::set_task (EventConsumer_Task_Base * task)
{
  task_ = task;
}

CUTS_INLINE
void EventConsumer::configure_task (int max_threads, CPU_Mask * mask)
{
  if (max_threads > 0) 
  {
    task_->set_max_threads (max_threads);
  }
  if (mask)
  {
  task_->set_cpu_mask (mask);
  }

  task_->open ();
}

CUTS_INLINE
void EventConsumer::listener (EventConsumer_Listener * listener)
{
  this->listener_ = listener;
}

}
