// $Id$

//
// CUTS_Logging_Server_File
//
CUTS_INLINE
CUTS_Logging_Server_File::CUTS_Logging_Server_File (void)
: reader_type (&CUTS::reader::logging)
{
  this->configure ();
}

//
// ~CUTS_Logging_Server_File
//
CUTS_INLINE
CUTS_Logging_Server_File::~CUTS_Logging_Server_File (void)
{

}