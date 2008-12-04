// $Id$

#include "streams.h"
#include "ace/Time_Value.h"
#include "ace/OS_NS_time.h"

//
// CUTS_string_time
//
const char * CUTS_string_time (time_t clock, const char * format)
{
  // convert the time to its <local_time>
  const struct tm * local_time = ACE_OS::localtime (&clock);

  // convert the <local_time> to the format specified
  static char timebuf [256];
  ACE_OS::strftime (timebuf, sizeof (timebuf), format , local_time);
  return timebuf;
}

//
// CUTS_string_time
//
const char * CUTS_string_time (const char * format)
{
  // get the current time in milliseconds
  time_t clock;
  ACE_OS::time (&clock);

  return CUTS_string_time (clock, format);
}

//
// CUTS_string_time
//
const char *
CUTS_string_time (const ACE_Time_Value & tv, const char * format)
{
  return CUTS_string_time (tv.sec (), format);
}

//
// operator <<
//
std::ostream & operator << (std::ostream & out, const ACE_Time_Value & tv)
{
  out << CUTS_string_time (tv, "%H:%M:%S %Y-%m-%d");
  return out;
}