// $Id$

#include "Tron_EventConsumer.h"

#if !defined (__CUTS_INLINE__)
#include "Tron_EventConsumer.inl"

namespace iCCM
{

//
// register_channel
//
void Tron_EventConsumer::
register_channel (Reporter * reporter, const ACE_CString & name)
{
  this->channel_ = reporter->getInputEncoding (reporter, name.c_str ());
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Got reporter for EventConsumer [%s, %d]\n"),
              name.c_str (),
              this->channel_));
}

}

#endif
