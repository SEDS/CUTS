// $Id$

//
// CUTS_Logger_i
//
CUTS_INLINE
CUTS_Logger_i::
CUTS_Logger_i (CUTS_Log_Message_Handler * handler, const ACE_Utils::UUID & uuid)
: handler_ (handler),
  uuid_ (uuid),
  queue_ (50)
{

}

//
// ~CUTS_Logger_i
//
CUTS_INLINE
CUTS_Logger_i::~CUTS_Logger_i (void)
{
  this->flush ();
}

//
// uuid
//
CUTS_INLINE
const ACE_Utils::UUID & CUTS_Logger_i::uuid (void) const
{
  return this->uuid_;
}