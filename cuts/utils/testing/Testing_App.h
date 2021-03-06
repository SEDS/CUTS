// -*- C++ -*-

//=============================================================================
/**
 * @file          CUTS_Testing_App.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TESTING_APP_H_
#define _CUTS_TESTING_APP_H_

#include "Testing_App_Base.h"
#include "Testing_App_Task.h"
#include "Test_Options.h"
#include "Test_Database.h"
#include "cuts/utils/Property_Map.h"
#include "ace/Thread_Mutex.h"
#include "ace/Condition_T.h"
#include "Command_Options_List.h"

namespace CUTS
{
  // Forward decl.
  class serviceDescription;
}

// Forward decl.
class CUTS_Testing_Service_Manager;

/**
 * @class CUTS_Testing_App
 *
 * The main entry point class for the application.
 */
class CUTS_TEST_Export CUTS_Testing_App : public CUTS_Testing_App_Base
{
public:
  /// Default constructor.
  CUTS_Testing_App (void);

  /// Destructor.
  ~CUTS_Testing_App (void);

  /**
   * Run the main part of the application. This method does not return
   * until the shutdown () method is invoked.
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguments
   */
  int run_main (int argc, char * argv []);

  /// Shutdown the testing application. This will stop the ORBs main
  /// event loop and allow the run_main () method to return.
  virtual void shutdown (void);

  /**
   * Get the options for the testing application.
   *
   * @return        Options for the testing application.
   */
  virtual const CUTS_Test_Options & options (void) const;

  /**
   * Get a reference to the test database.
   *
   * @return        Reference to test database.
   */
  virtual CUTS_Test_Database & test_db (void);

protected:
  /**
   * Parse the command-line arguments.
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguments
   * @retval          0           Successfully parsed arguments
   * @retval          -1          Failed to parse arguments
   */
  virtual int parse_args (int argc, char * argv []);

private:
  /// Print the help for this application.
  void print_help (void);

  /// Deploy the current test.
  int deploy_test (ACE_Process_Options & options);

  /// Execute the test.
  int execute_test ();

  /// Teardown the current test.
  int teardown_test (ACE_Process_Options & options);

  /// Load the configuration for the test.
  int load_configuration (CUTS_Testing_Service_Manager & mgr,
                          const ACE_CString & config);

  /// Execute a particular command.
  int execute (CUTS_Command_Options & opts);

  /// Task for the testing application.
  CUTS_Testing_App_Task task_;

  /// Options for the testing application.
  CUTS_Test_Options opts_;

  /// Database for the test.
  CUTS_Test_Database test_db_;

  /// Collection of properties.
  CUTS_Property_Map props_;

  /// Set of commands
  CUTS_Command_Options_List command_list_;

  ACE_Thread_Mutex shutdown_mutex_;

  ACE_Condition <ACE_Thread_Mutex> can_shutdown_;
};

#if defined (__CUTS_INLINE__)
#include "Testing_App.inl"
#endif

#endif  // !defined _CUTS_TESTING_APP_H_
