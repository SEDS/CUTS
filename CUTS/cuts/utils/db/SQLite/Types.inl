// $Id$

CUTS_INLINE
CUTS_DB_SQLite_Date_Time::CUTS_DB_SQLite_Date_Time (void)
: out_of_date_ (true)
{

}

CUTS_INLINE
CUTS_DB_SQLite_Date_Time::
CUTS_DB_SQLite_Date_Time (const ACE_Date_Time & dt)
: dt_ (dt),
  out_of_date_ (true)
{

}

CUTS_INLINE
CUTS_DB_SQLite_Date_Time::~CUTS_DB_SQLite_Date_Time (void)
{

}

CUTS_INLINE
long CUTS_DB_SQLite_Date_Time::month (void) const
{
  return this->dt_.month ();
}

CUTS_INLINE
void CUTS_DB_SQLite_Date_Time::month (long val)
{
  this->dt_.month (val);
  this->out_of_date_ = true;
}

CUTS_INLINE
long CUTS_DB_SQLite_Date_Time::day (void) const
{
  return this->dt_.day ();
}

CUTS_INLINE
void CUTS_DB_SQLite_Date_Time::day (long value)
{
  this->dt_.day (value);
  this->out_of_date_ = true;
}

CUTS_INLINE
long CUTS_DB_SQLite_Date_Time::year (void) const
{
  return this->dt_.year ();
}

CUTS_INLINE
void CUTS_DB_SQLite_Date_Time::year (long value)
{
  this->dt_.year (value);
  this->out_of_date_ = true;
}

CUTS_INLINE
long CUTS_DB_SQLite_Date_Time::hour (void) const
{
  return this->dt_.hour ();
}

CUTS_INLINE
void CUTS_DB_SQLite_Date_Time::hour (long value)
{
  this->dt_.hour (value);
  this->out_of_date_ = true;
}

CUTS_INLINE
long CUTS_DB_SQLite_Date_Time::minute (void) const
{
  return this->dt_.minute ();
}

CUTS_INLINE
void CUTS_DB_SQLite_Date_Time::minute (long value)
{
  this->dt_.minute (value);
  this->out_of_date_ = true;
}

CUTS_INLINE
long CUTS_DB_SQLite_Date_Time::second (void) const
{
  return this->dt_.second ();
}

CUTS_INLINE
void CUTS_DB_SQLite_Date_Time::second (long value)
{
  this->dt_.second (value);
  this->out_of_date_ = true;
}

CUTS_INLINE
long CUTS_DB_SQLite_Date_Time::fraction (void) const
{
  return this->dt_.microsec  ();
}

CUTS_INLINE
void CUTS_DB_SQLite_Date_Time::fraction (long val)
{
  this->dt_.microsec (val);
  this->out_of_date_ = true;
}