#include "CPUAffinity.h"

#include "dance/DAnCE_PropertiesC.h"
#include "dance/Logger/Log_Macros.h"
#include "ace/Tokenizer_T.h"

#include <sstream>

namespace iCCM
{
  CPU_Affinity::CPU_Affinity (void) : Plugin ("edu.vanderbilt.dre.DAnCE.LocalityManager.CPUAffinity")
  {
  }

  CPU_Affinity::~CPU_Affinity (void)
  {
  }
  
  void CPU_Affinity::configure (const ::Deployment::Property & prop)
  {
#if defined (ACE_HAS_PTHREADS) || defined (ACE_WIN32)
    const char * extracted_affinity = 0;

    if (!(prop.value >>= extracted_affinity)) {
      DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR,
        (LM_ERROR, DLINFO
        ACE_TEXT ("iCCM_CPU_Affinity::configure - ")
        ACE_TEXT ("Unable to extract CPU Affinity string")));
      throw ::Deployment::StartError (prop.name.in (), "Unable to extract CPU Affinity string");
    }

    char * affinity = ACE_OS::strdup (extracted_affinity);

    ACE_Tokenizer_T<char> tokenizer (affinity);
    tokenizer.delimiter (',');

    char * token = 0;

#ifdef ACE_HAS_PTHREADS
    // Setup CPU mask
    cpu_set_t mask;

    CPU_ZERO (&mask);

    // Get process ID
    pthread_t thread_id = pthread_self ();
#endif
#ifdef ACE_WIN32
    // Setup CPU mask
    DWORD_PTR mask = 0;

    // Get process ID
    HANDLE thread_id = GetCurrentProcess ();
#endif

    while ((token = tokenizer.next ()))
    {
      int i = ACE_OS::atoi (token);

      if (i >= 0)
      {
        DANCE_DEBUG (DANCE_LOG_MINOR_EVENT,
          (LM_DEBUG, DLINFO
          ACE_TEXT ("iCCM_CPU_Affinity::configure - ")
          ACE_TEXT ("Toggling affinity for CPU %i\n"),
          i));

#ifdef ACE_HAS_PTHREADS
        CPU_SET (i, &mask);
#endif
#ifdef ACE_WIN32
        mask |= (1 << (i - 1));
#endif
      }
      else
      {
        DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR,
          (LM_ERROR, DLINFO
          ACE_TEXT ("iCCM::CPU_Affinity::configure - ")
          ACE_TEXT ("All affinity values should be greater than 0")));
        throw ::Deployment::StartError (prop.name.in (), "All affinity values should be greater than 0");
      }
    }

    ACE_OS::free (affinity);

    // I strongly dislike this and need to fix it later.
    // sched_setaffinity returns 0 on success
    // SetProcessAffinityMask returns 0 on failure
#ifdef ACE_HAS_PTHREADS
    int retval = sched_setaffinity (thread_id, sizeof (cpu_set_t), &mask);
    if (retval != 0)
#endif
#ifdef ACE_WIN32
    int retval = SetProcessAffinityMask (thread_id, mask);
    if (retval == 0)
#endif
    {
      std::stringstream str;
      std::string safe_error (ACE_OS::strerror (ACE_OS::last_error ()));
      
      str << "Unable to set CPU Affinity to <" << extracted_affinity << ">: " << safe_error;
      const char * msg = str.str ().c_str ();
      DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR,
        (LM_ERROR, DLINFO
        ACE_TEXT ("iCCM::CPU_Affinity::configure - %C\n"),
        msg));
      throw ::Deployment::StartError (prop.name.in (), msg);
    }
#else
    throw ::Deployment::StartError (prop.name.in (), "CPU Affinity not supported on this platform");
#endif
  }
}

iCCM::Plugin * create_CPUAffinity_plugin (void)
{
  iCCM::Plugin * retval (0);

  ACE_NEW_RETURN (retval, iCCM::CPU_Affinity (), 0);

  return retval;
}
