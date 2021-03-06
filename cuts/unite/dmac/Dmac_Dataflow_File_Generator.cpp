#include "Dmac_Dataflow_File_Generator.h"

//
// CUTS_Dmac_Dataflow_File_Generator
//
CUTS_Dmac_Dataflow_File_Generator::CUTS_Dmac_Dataflow_File_Generator (
                        std::vector <CUTS_Dmac_Log_Format *> & log_formats,
                        const char * name)
 : log_formats_ (log_formats),
   name_ (name)
{

}

//
// ~CUTS_Dmac_Dataflow_File_Generator
//
CUTS_Dmac_Dataflow_File_Generator::~CUTS_Dmac_Dataflow_File_Generator (void)
{

}

//
// init_xml
//
void CUTS_Dmac_Dataflow_File_Generator::init_xml (void)
{
  this->ctx_.xml_
    << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?> " << std::endl;
}

//
// generate_xml
//
void CUTS_Dmac_Dataflow_File_Generator::generate_xml ()
{
  // Initial xml declerations and the namespaces
  this->generate_declerations ();

  // Generating the log formats for a particular execution
  this->generate_logformats ();

  // Finalize the generation for a particular execution
  this->generate_close_tag ();
}

//
// open_file
//
void CUTS_Dmac_Dataflow_File_Generator::open_file (void)
{
  // Construct the name of the file.
  std::string file_name (this->name_);
  file_name = this->name_ + ".datagraph";

  // Open all the files for writing.
  this->ctx_.xml_.open (file_name.c_str ());
  this->ctx_.xml_formatter_.reset (new CUTS_DMAC_XML_GEN::Context::formatter_type (
                                   this->ctx_.xml_));

}

//
// close_file
//
void CUTS_Dmac_Dataflow_File_Generator::close_file (void)
{
  this->ctx_.xml_formatter_.reset ();

  if (this->ctx_.xml_.is_open ())
    this->ctx_.xml_.close ();
}

//
// generate_declerations
//
void CUTS_Dmac_Dataflow_File_Generator::generate_declerations ()
{
  this->ctx_.xml_
    << "<cuts:datagraph xmlns=\"http://www.cs.iupui.edu/CUTS/XML\" "
    << "xmlns:cuts=\"http://www.cs.iupui.edu/CUTS/XML\" "
    << "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
    << "xsi:schemaLocation=\"http://www.cs.iupui.edu/CUTS/XML cuts-unite.xsd\"> "
    << std::endl
    << std::endl
    << "<name>" << this->name_ << "</name>" << std::endl;
}

//
// generate_logformats
//
void CUTS_Dmac_Dataflow_File_Generator::generate_logformats ()
{
  this->ctx_.xml_
    << "<logformats>" << std::endl;

  std::vector <CUTS_Dmac_Log_Format *>::iterator it;

  for (it = this->log_formats_.begin ();
       it != this->log_formats_.end (); it++)
    (*it)->serialize (this->ctx_.xml_);

  this->ctx_.xml_
    << "</logformats>" << std::endl;

}

//
// generate_close_tag
//
void CUTS_Dmac_Dataflow_File_Generator::generate_close_tag (void)
{
  this->ctx_.xml_
    << "</cuts:datagraph>" << std::endl;

}