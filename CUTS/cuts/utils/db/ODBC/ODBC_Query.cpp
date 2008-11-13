// $Id$

#include "ODBC_Query.h"

#if !defined (__CUTS_INLINE__)
#include "ODBC_Query.inl"
#endif

#include "ODBC_Record.h"
#include "ODBC_Parameter.h"
#include "ODBC_Parameter_List.h"
#include "ace/Log_Msg.h"
#include "ace/CORBA_macros.h"

//
// ODBC_Query
//
ODBC_Query::ODBC_Query (HDBC handle)
: stmt_ (SQL_NULL_HSTMT),
  cursor_open_ (0),
  params_ (*this)
{
  SQL_VERIFY (
    ::SQLAllocHandle (SQL_HANDLE_STMT, handle, &this->stmt_),
    ODBC_Conn_Exception (handle));

  // Set the attributes for the statement
  this->return_ = ::SQLSetStmtAttr (this->stmt_, SQL_ATTR_CONCURRENCY,
    (SQLPOINTER) SQL_CONCUR_ROWVER, 0);
  this->return_ = ::SQLSetStmtAttr (this->stmt_, SQL_ATTR_CURSOR_TYPE,
    (SQLPOINTER) SQL_CURSOR_KEYSET_DRIVEN, 0);
}

//
// ~ODBC_Query
//
ODBC_Query::~ODBC_Query (void)
{
  if (this->stmt_ != SQL_NULL_HSTMT)
    ::SQLFreeHandle (SQL_HANDLE_STMT, this->stmt_);
}

//
// execute_no_record
//
void ODBC_Query::execute_no_record (void)
{
  SQL_VERIFY (::SQLExecute (this->stmt_),
              ODBC_Stmt_Exception (this->stmt_));

  this->cursor_open_ = 0;
}

//
// execute_no_record
//
void ODBC_Query::execute_no_record (const char * query)
{
  SQL_VERIFY (::SQLExecDirect (this->stmt_, (SQLCHAR *)query, SQL_NTS),
              ODBC_Stmt_Exception (this->stmt_));

  this->cursor_open_ = 0;
}

//
// last_insert_id
//
long ODBC_Query::last_insert_id (void)
{
  long last_id = 0;

  // Execute the statement and move to the first and only
  // row in the result set.
  CUTS_DB_Record * record = this->execute ("SELECT LAST_INSERT_ID()");

  // Get the data returned from the statement.
  record->advance ();
  record->get_data (1, last_id);

  return last_id;
}

//
// prepare
//
void ODBC_Query::prepare (const char * stmt)
{
  if (this->cursor_open_)
    this->reset_i ();

  SQL_VERIFY (::SQLPrepare (this->stmt_, (SQLCHAR *) stmt, SQL_NTS),
              ODBC_Stmt_Exception (this->stmt_));

  /// Reset the parameters for this statement.
  this->params_.reset ();
}

//
// cancel
//
void ODBC_Query::cancel (void)
{
  SQL_VERIFY (::SQLCancel (this->stmt_),
              ODBC_Stmt_Exception (this->stmt_));
}

//
// execute
//
CUTS_DB_Record * ODBC_Query::execute (const char * query)
{
  // Reset the record just in case we executed a "SELECT" statement.
  if (this->cursor_open_)
    this->reset_i ();

  // Execute the query and set the <cursor_state_> to open.
  this->execute_no_record (query);
  this->cursor_open_ = 1;

  return this->record_i ();
}

//
// execute
//
CUTS_DB_Record * ODBC_Query::execute (void)
{
  this->execute_no_record ();
  this->cursor_open_ = 1;

  return this->record_i ();
}

//
// record_i
//
ODBC_Record * ODBC_Query::record_i (void)
{
  ODBC_Record * record = 0;

  ACE_NEW_THROW_EX (record,
                    ODBC_Record (*this),
                    ACE_bad_alloc ());

  return record;
}

//
// reset
//
void ODBC_Query::reset (void)
{
  if (this->stmt_ != SQL_NULL_HSTMT)
    this->reset_i ();
}

//
// reset_i
//
void ODBC_Query::reset_i (void)
{
  SQL_VERIFY (::SQLFreeStmt (this->stmt_, SQL_CLOSE),
              ODBC_Stmt_Exception (this->stmt_));

  this->params_.reset ();
}
