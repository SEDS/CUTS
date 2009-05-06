// $Id$

#include "stdafx.h"
#include "CUTE_Dialog.h"

#if !defined (__CUTS_INLINE__)
#include "CUTE_Dialog.inl"
#endif

BEGIN_MESSAGE_MAP (CUTS_CUTE_Dialog, CDialog)
  ON_BN_CLICKED (IDC_BROWSE, on_click_browse)
END_MESSAGE_MAP ()

//
// OnInitDialog
//
BOOL CUTS_CUTE_Dialog::OnInitDialog (void)
{
  // Pass control to the base class first.
  CDialog::OnInitDialog ();

  if (0 != this->list_)
  {
    // Initialize the contents of the interpreter list.
    CUTS_CUTE_Interpreter_List::CONST_ITERATOR iter (*this->list_);

    for ( ; !iter.done (); ++ iter)
      this->interpreter_list_.InsertString (0, iter->key ().c_str ());
  }

  return FALSE;
}

//
// DoDataExchange
//
void CUTS_CUTE_Dialog::DoDataExchange (CDataExchange * pDX)
{
  CDialog::DoDataExchange (pDX);

  DDX_Control (pDX, IDC_INTERPRETER, this->interpreter_list_);
  DDX_Control (pDX, IDC_CONFIG, this->config_);

  DDX_CBString (pDX, IDC_INTERPRETER, this->selected_interpeter_);
  DDX_Text (pDX, IDC_CONFIG, this->config_file_);
}

//
// on_click_browse
//
void CUTS_CUTE_Dialog::on_click_browse (void)
{
  CFileDialog dialog (1,
                      0,
                      0,
                      OFN_PATHMUSTEXIST,
                      0,
                      this,
                      0);

  dialog.GetOFN ().lpstrTitle = "Open template configuration...";

  if (IDOK == dialog.DoModal ())
    this->config_.SetWindowText (dialog.GetPathName ());
}