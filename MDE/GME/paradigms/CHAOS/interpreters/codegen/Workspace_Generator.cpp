// $Id$

#include "StdAfx.h"
#include "Workspace_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "Workspace_Generator.inl"
#endif

#include "BE_Impl_Node.h"
#include "BE_IDL_Node.h"
#include "BE_Options.h"

//
// CUTS_BE_Workspace_File_Open_T
//
void
CUTS_BE_Workspace_File_Open_T <CUTS_CHAOS::Context>::
generate (const std::string & name)
{
  // Construct the full pathname of the workspace.
  std::string pathname (CUTS_BE_OPTIONS ()->output_directory_);
  pathname += "/" + name + ".mwc";

  // Open the workspace file for writing.
  this->ctx_.workspace_.open (pathname.c_str ());
}

//
// CUTS_BE_Workspace_Begin_T
//
void CUTS_BE_Workspace_Begin_T <CUTS_CHAOS::Context>::
generate (const std::string & name)
{
  this->ctx_.workspace_
    << "// -*- MWC -*-" << std::endl
    << std::endl
    << "//===================================================================" << std::endl
    << "// Makefile, Project, and Workspace Creator File" << std::endl
    << "//" << std::endl
    << "// Please do not modify the contents of this file under" << std::endl
    << "// any circumstances. Doing so can result in failure to" << std::endl
    << "// successfully build parts of (or the entire) workspace." << std::endl
    << "//===================================================================" << std::endl
    << std::endl
    << "workspace (" << name << ") {" << std::endl
    << "  // -- initialize the includes for the project." << std::endl
    << "  cmdline += -include $CUTS_ROOT/MPC/config \\" << std::endl
    << "             -feature_file $CUTS_ROOT/default.features \\" << std::endl
    << "             -relative PROJECT_ROOT=" << std::endl
    << std::endl;
}

//
// CUTS_BE_Workspace_Project_Include_T <, CUTS_BE_Impl_Node>
//
void
CUTS_BE_Workspace_Project_Include_T <CUTS_CHAOS::Context, CUTS_BE_Impl_Node>::
generate (const CUTS_BE_Impl_Node & node)
{
  this->ctx_.workspace_
    << "  " << node.name_ << ".mpc" << std::endl;
}

//
// CUTS_BE_Workspace_Project_Include_T <, CUTS_BE_IDL_Node>
//
void
CUTS_BE_Workspace_Project_Include_T <CUTS_CHAOS::Context, CUTS_BE_IDL_Node>::
generate (const CUTS_BE_IDL_Node & node)
{
  this->ctx_.workspace_
    << "  " << node.name_ << ".mpc" << std::endl;
}

//
// CUTS_BE_Workspace_End_T
//
void CUTS_BE_Workspace_End_T <CUTS_CHAOS::Context>::
generate (const std::string & name)
{
  this->ctx_.workspace_
    << "}" << std::endl
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("end of auto-generated workspace")
    << std::endl;
}

//
// CUTS_BE_Workspace_File_Close_T
//
void CUTS_BE_Workspace_File_Close_T <CUTS_CHAOS::Context>::generate (void)
{
  if (this->ctx_.workspace_.is_open ())
    this->ctx_.workspace_.close ();
}