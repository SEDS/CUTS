// $Id$

#include "Trace_Importer_App.h"

#if !defined (__CUTS_INLINE__)
#include "Trace_Importer_App.inl"
#endif

#include "Trace_Importer_Parser.h"
#include "cuts/utils/testing/Test_Database.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"

static const char * __HELP__ =
"Utility for importing an execution trace into a CUTS test database\n"
"\n"
"USAGE: cuts-trace-importer [OPTIONS]\n"
"\n"
"General options:\n"
"  -f, --file=FILE            execution trace for import\n"
"  -t, --test=FILE            test database file\n"
"  --hostname=NAME            host that generated execution trace (required)\n"
"\n"
"Output options:\n"
"  -h, --help                 print this help message\n";

//
// run_main
//
int CUTS_Trace_Importer_App::run_main (int argc, char * argv [])
{
  try
  {
    if (0 != this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T - %M - failed to parse command-line arguments\n")),
                         -1);

    // Open the database for writing.
    CUTS_Test_Database test_db;
    test_db.open (this->test_file_);

    // Now, parse the trace and insert data into the database.
    CUTS_Trace_Importer_Parser trace_parser (test_db);
    bool retval = trace_parser.import_trace (this->input_file_, this->hostname_);

    if (!retval)
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to import trace [file=%s]\n"),
                  this->input_file_.c_str ()));

    // Close the connection to the database.
    test_db.close ();

    return retval ? 0 : -1;
  }
  catch (const ADBC::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.message ().c_str ()));
  }

  return -1;
}

//
// parse_args
//
int CUTS_Trace_Importer_App::parse_args (int argc, char * argv [])
{
  const char * optstr = "hi:t:";
  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("test", 't', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("file", 'f', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("hostname", ACE_Get_Opt::ARG_REQUIRED);

  int opt;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("test", get_opt.long_option ()))
      {
        this->test_file_ = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("file", get_opt.long_option ()))
      {
        this->input_file_ = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("hostname", get_opt.long_option ()))
      {
        this->hostname_ = get_opt.opt_arg ();
      }

      break;

    case 't':
      this->test_file_ = get_opt.opt_arg ();
      break;

    case 'f':
      this->input_file_ = get_opt.opt_arg ();
      break;

    case 'h':
      this->print_help ();
      break;
    }
  }

  if (this->hostname_.empty ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - --hostname is missing\n")),
                       -1);

  return 0;
}

//
// print_help
//
void CUTS_Trace_Importer_App::print_help (void)
{
  std::cerr << ::__HELP__ << std::endl;
  ACE_OS::exit (1);
}
