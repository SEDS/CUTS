// $Id$

//=============================================================================
/**
 * @file        cutslog_d.cpp
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#include "Logging_Client.h"
#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"
#include "ace/Signal.h"

#define LOGGING_CLIENT \
  ACE_Singleton <CUTS_Logging_Client, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  LOGGING_CLIENT->shutdown ();
  ACE_UNUSED_ARG (sig);
}

//
// register_sighandler
//
static void register_sighandler (void)
{
  ACE_Sig_Action sa (&server_sighandler);

  sa.register_action (SIGINT);
  sa.register_action (SIGTERM);
}

//
// main
//
int main (int argc, char * argv [])
{
  int retval;

  u_long default_mask =
    LM_EMERGENCY | LM_ALERT | LM_CRITICAL | LM_ERROR | LM_WARNING | LM_NOTICE;

  ACE_Log_Msg::instance ()->priority_mask (default_mask, ACE_Log_Msg::PROCESS);

  try
  {
    // Register the signal handler.
    register_sighandler ();

    // Run the main part of the application.
    retval = LOGGING_CLIENT->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR, "%T - [%M] - caught unknown exception\n"));
    retval = 1;
  }

  return retval;
}