// $Id$

#include "Event_Traits.h"

#include "be_extern.h"
#include "Context.h"

#include "ast_module.h"
#include "ast_root.h"
#include "ast_eventtype.h"
#include "utl_identifier.h"

#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

namespace iCCM
{

//
// Event_Traits
//
Event_Traits::Event_Traits (std::ofstream & hfile, std::ofstream & sfile)
: hfile_ (hfile),
  sfile_ (sfile)
{

}

//
// ~Event_Traits
//
Event_Traits::~Event_Traits (void)
{

}

//
// visit_root
//
int Event_Traits::visit_root (AST_Root * node)
{
  return this->visit_scope (node);
}

//
// visit_module
//
int Event_Traits::visit_module (AST_Module * node)
{
  ACE_CString local_name (node->local_name ()->get_string ());
  ACE_CString backup (this->scope_);
  this->scope_ += local_name + "::";

  if (0 != this->visit_scope (node))
    return -1;

  this->scope_ = backup;
  return 0;
}

//
// visit_eventtype
//
int Event_Traits::visit_eventtype (AST_EventType * node)
{
  const char * full_name = node->full_name ();
  const char * local_name = node->local_name ()->get_string ();

  this->hfile_
    << "/**" << std::endl
    << " * @struct iCCM::TCPIP_Event_Traits < ::" << full_name << " >" << std::endl
    << " *" << std::endl
    << " * Trait information for " << full_name << "Event event type." << std::endl
    << " */" << std::endl
    << "namespace iCCM {"
    << "template < >" << std::endl
    << "struct TCPIP_Event_Traits < ::" << full_name << " >"
    << "{"
    << "typedef ::OBV_" << this->scope_ << local_name << " tcpip_event_type;"
    << "};"
    << "}";

  return 0;
}

}
