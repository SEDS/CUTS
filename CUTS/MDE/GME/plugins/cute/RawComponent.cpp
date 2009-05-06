// $Id$

#include "stdafx.h"
#include "RawComponent.h"
#include "CUTE_Dialog.h"
#include "ComponentConfig.h"
#include "Model_Interpreter.h"
#include "Model_Interpreter_Action_List.h"
#include "Property_Locator.h"
#include "Windows_Registry.h"
#include "game/be/ComponentDLL.h"
#include "cuts/utils/Config_List_Parser_T.h"
#include <sstream>

GME_RAWCOMPONENT_IMPL (CUTE, COMPONENT_NAME);

//
// CUTS_CUTE
//
CUTS_CUTE::CUTS_CUTE (void)
: GME::Plugin_Impl ("CUTS Template Engine", COCLASS_PROGID, false)
{

}

//
// ~CUTS_CUTE
//
CUTS_CUTE::~CUTS_CUTE (void)
{

}

//
// invoke_ex
//
int CUTS_CUTE::invoke_ex (GME::Project & project,
                          GME::FCO & target,
                          GME::Collection_T <GME::FCO> & selected,
                          long flags)
{
  try
  {
    // Load the interpreters for this paradigm.
    CUTS_CUTE_Interpreter_List interpreters;

    project.begin_transaction ();
    this->get_interpreters (project.paradigm_name ().c_str (), interpreters);
    project.commit_transaction ();

    // Let the user select the configuration and interpreter.
    CUTS_CUTE_Dialog dialog (::AfxGetMainWnd ());
    dialog.interpreter_list (&interpreters);

    if (IDOK == dialog.DoModal ())
    {
      // First, locate all attributes with a template parameter. We are
      // going to cache the elements for later.
      project.begin_transaction ();
      CUTS_CUTE_Model_Interpreter_Action_List actlist;
      CUTS_CUTE_Property_Locator locator (actlist);
      project.root_folder ().accept (locator);
      project.commit_transaction ();

      // Second, parse the configuration file specified by the end-user
      // in the dialog. After parsing each configuration, we will
      // interpret the model using the configuration.
      CUTS_CUTE_Model_Interpreter interpreter (actlist,
                                               project,
                                               target,
                                               selected,
                                               flags);

      // Get the program id for the selected interpreter.
      ACE_CString prog_id;
      interpreters.find (dialog.selected_interpreter ().GetString (), prog_id);
      interpreter.interpreter (prog_id);

      CUTS_Config_List_Parser_T <CUTS_CUTE_Model_Interpreter> parser (interpreter);
      parser.parse (dialog.configuration_filename ().GetString ());
    }

    // Commit the existing transaction.
    project.commit_transaction ();

    return 0;
  }
  catch (const GME::Failed_Result & ex)
  {
    std::ostringstream ostr;
    ostr << "failed result: [0x" << std::hex
         << ex.value () << "]" << std::endl;

    ::AfxMessageBox (ostr.str ().c_str ());
  }
  catch (const GME::Exception & )
  {
  }

  // Abort the current transaction.
  project.abort_transaction ();

  return -1;
}

//
// get_interpreters
//
void CUTS_CUTE::
get_interpreters (const char * paradigm_name, CUTS_CUTE_Interpreter_List & list)
{
  // Open the GME component section in the registry.
  CUTS_Windows_Registry_Key components;

  if (0 != components.open (HKEY_CURRENT_USER, "Software\\GME\\Components"))
    return;

  char description[255];

  // Iterate over all the components.
  CUTS_Windows_Registry_Key component, associated, paradigm;
  CUTS_Windows_Registry_Key_Iterator key_iter (components);

  for ( ; !key_iter.done (); key_iter.advance ())
  {
    // Open the component and its associated paradigms.
    if (0 != component.open (components, key_iter.name ()))
      continue;
    else if (0 != associated.open (component, "Associated"))
      continue;
    else if (0 != associated.get_value (paradigm_name))
      continue;
    else if (0 != component.get_value ("Description",
                                       description,
                                       sizeof (description)))
    {
      continue;
    }
    else
    {
      list.bind (description, key_iter.name ());
    }
  }
}