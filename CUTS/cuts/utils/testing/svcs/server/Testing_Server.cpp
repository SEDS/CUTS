// $Id$

#include "Testing_Server.h"
#include "Testing_Server_Task.h"
#include "cuts/utils/testing/Testing_App.h"
#include "tao/TAO_Singleton_Manager.h"
#include "tao/IORTable/IORTable.h"
#include "ace/Thread_Manager.h"
#include "ace/Get_Opt.h"
#include "ace/Guard_T.h"
#include "ace/streams.h"

CUTS_TESTING_SERVICE_IMPL (CUTS_Testing_Server, _make_CUTS_Testing_Server);

//
// CUTS_Testing_Server
//
CUTS_Testing_Server::CUTS_Testing_Server (void)
: register_with_ns_ (false),
  task_ (*this)
{
  CUTS_TESTING_SERVER_TRACE ("CUTS_Testing_Server::CUTS_Testing_Server (void)");
}

//
// CUTS_Testing_Server
//
CUTS_Testing_Server::~CUTS_Testing_Server (void)
{
  CUTS_TESTING_SERVER_TRACE ("CUTS_Testing_Server::~CUTS_Testing_Server (void)");
}

//
// run_main
//
int CUTS_Testing_Server::init (int argc, char * argv [])
{
  CUTS_TESTING_SERVER_TRACE ("CUTS_Testing_Server::init (int, char * [])");

  if (this->parse_args (argc, argv) == -1)
  {
    ACE_ERROR_RETURN  ((LM_ERROR,
                        "%T (%t) - %M - failed to parse command-line options\n"),
                        -1);
  }

  try
  {
    // Get a reference to the <RootPOA>
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - resolving initial reference to RootPOA\n"));
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    this->root_poa_ = PortableServer::POA::_narrow (obj.in ());

    // Activate the RootPOA's manager.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - getting reference to POAManager\n"));

    this->poa_mgr_ = this->root_poa_->the_POAManager ();
    this->poa_mgr_->activate ();

    // Create a new test manager.
    ACE_NEW_THROW_EX (this->test_manager_,
                      CUTS_TestManager_i (*this),
                      CORBA::NO_MEMORY ());

    // Activate the object and transfer ownership.
    PortableServer::ObjectId_var id =
      this->root_poa_->activate_object (this->test_manager_);

    //CORBA::Object_var obj = this->poa_->id_to_reference (id.in ());
    //CUTS::TestManager_var manager = CUTS::TestManager::_narrow (obj.in ());
    this->servant_ = this->test_manager_;

    // Register the test manager with the IORTable for the ORB.
    //if (this->register_with_iortable () == -1)
    //{
    //  ACE_ERROR ((LM_ERROR,
    //              "%T (%t) - %M - failed to register with IOR table\n"));
    //}

    // Register the test manager with the naming service, if applicable.
    if (this->register_with_ns_)
    {
      if (this->register_with_name_service () == -1)
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to register %s with naming service",
                    this->test_app ()->options ().name_.c_str ()));
      }
    }

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating the server's task\n"));

    return this->task_.activate ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// parse_args
//
int CUTS_Testing_Server::parse_args (int argc, char * argv [])
{
  CUTS_TESTING_SERVER_TRACE ("CUTS_Testing_Server::parse_args (int, char * [])");

  try
  {
    this->orb_ = ::CORBA::ORB_init (argc, argv, "SERVER");

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// fini
//
int CUTS_Testing_Server::fini (void)
{
  CUTS_TESTING_SERVER_TRACE ("CUTS_Testing_Server::fini (void)");

  try
  {
    // We need to unregister the object with the naming service before we
    // shutdown the ORB.
    if (this->register_with_ns_)
      this->unregister_with_name_service ();

    // Stop the main event loop for the ORB.
    ACE_DEBUG ((LM_DEBUG, "%T (%t) - %M - shutting down the ORB\n"));
    this->orb_->shutdown (1);
    this->task_.wait ();

    // Destroy the RootPOA.
    ACE_DEBUG ((LM_DEBUG, "%T (%t) - %M - destroying the RootPOA\n"));
    this->root_poa_->destroy (1, 1);

    // Destroy the ORB.
    ACE_DEBUG ((LM_DEBUG, "%T (%t) - %M - destroying the ORB\n"));
    this->orb_->destroy ();

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// register_with_iortable
//
int CUTS_Testing_Server::register_with_iortable (void)
{
  try
  {
    // Locate the IORTable for the application.
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("IORTable");
    IORTable::Table_var ior_table = IORTable::Table::_narrow (obj.in ());

    if (::CORBA::is_nil (ior_table.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to resolve IOR table\n"),
                         -1);
    }

    // Construct the name for the test manager.
    ACE_CString manager_name = "CUTS/TestManager/";
    manager_name += this->test_app ()->options ().name_;

    // Get the IOR string for the test manager.
    CUTS::TestManager_var test_mgr = this->test_manager_->_this ();
    CORBA::String_var obj_str  = this->orb_->object_to_string (test_mgr.in ());
    CORBA::String_var name_str = CORBA::string_dup (manager_name.c_str ());

    // Bind the object to the IOR table.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - registering test manager with the IOR table [%s]\n",
                manager_name.c_str ()));

    ior_table->bind (name_str.in (), obj_str.in ());
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// register_with_name_service
//
int CUTS_Testing_Server::register_with_name_service (void)
{
  try
  {
    // Get the root context of the naming service.
    CORBA::Object_var obj =
      this->orb_->resolve_initial_references ("NameService");

    this->root_ctx_ = CosNaming::NamingContextExt::_narrow (obj.in ());

    // Construct all the context we would like to create, then contact
    // the naming service to ensure they all exist.
    const char * ctx_names [] = {"CUTS", "TestManager"};

    CosNaming::Name ns_name (3);
    CosNaming::NamingContext_var ctx;

    for (int i = 0; i < 2; ++ i)
    {
      // Initialize the next id in the name.
      ns_name.length (i + 1);
      ns_name[i].id = CORBA::string_dup (ctx_names[i]);

      try
      {
        ctx = this->root_ctx_->bind_new_context (ns_name);
      }
      catch (const CosNaming::NamingContext::AlreadyBound &)
      {
        // do nothing
      }
    }

    // Update the length so that the test manager's name is visible
    // to the naming service.
    ns_name.length (3);
    ns_name[2].id = CORBA::string_dup (this->test_app ()->options ().name_.c_str ());

    // Bind the actual test manger to the naming service.
    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - binding testing manager to naming service as %s\n",
                this->test_app ()->options ().name_.c_str ()));

    CUTS::TestManager_var tm = this->test_manager_->_this ();
    this->root_ctx_->bind (ns_name, tm);
    return 0;
  }
  catch (const CosNaming::NamingContext::AlreadyBound & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s already registered with naming service (%s)\n",
                this->test_app ()->options ().name_.c_str (),
                ex._info ().c_str ()));
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// register_with_name_service
//
int CUTS_Testing_Server::unregister_with_name_service (void)
{
  if (CORBA::is_nil (this->root_ctx_))
    return 0;

  try
  {
    // Construct the fully qualified name of the test manger for
    // within the naming service.
    CosNaming::Name ns_name (3);
    ns_name.length (3);

    ns_name[0].id = CORBA::string_dup ("CUTS");
    ns_name[1].id = CORBA::string_dup ("TestManager");
    ns_name[2].id = CORBA::string_dup (this->test_app ()->options ().name_.c_str ());

    // Unregister the TestManger with the naming service.
    ACE_DEBUG ((LM_INFO,
                "%T - %M - unregistering test manager with naming service\n"));

    this->root_ctx_->unbind (ns_name);
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// print_help
//
void CUTS_Testing_Server::print_help (void)
{

}

//
// the_ORB
//
CORBA::ORB_ptr CUTS_Testing_Server::the_ORB (void)
{
  return CORBA::ORB::_duplicate (this->orb_.in ());
}

