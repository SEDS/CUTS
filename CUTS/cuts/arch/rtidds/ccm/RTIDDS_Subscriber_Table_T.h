// -*- C++ -*-

#ifndef _CUTS_RTIDDS_CCM_SUBSCRIBER_TABLE_T_H_
#define _CUTS_RTIDDS_CCM_SUBSCRIBER_TABLE_T_H_

#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/UUID.h"
#include "RTIDDS_Subscriber_T.h"
#include "RTIDDS_Subscriber_Table.h"

/**
 * @class CUTS_RTIDDS_CCM_Subscriber_Table_T
 */
template <typename EVENT>
class CUTS_RTIDDS_CCM_Subscriber_Table_T :
  public CUTS_RTIDDS_CCM_Subscriber_Table
{
public:
  typedef CUTS_RTIDDS_Traits_T <EVENT> traits_type;

  typedef CUTS_RTIDDS_CCM_Subscriber_T <EVENT> subscriber_type;

  CUTS_RTIDDS_CCM_Subscriber_Table_T (void);

  virtual ~CUTS_RTIDDS_CCM_Subscriber_Table_T (void);

  virtual ::Components::Cookie * subscribe (::Components::EventConsumerBase_ptr);

  virtual ::Components::EventConsumerBase_ptr unsubscribe (::Components::Cookie *);

  void send_event (typename traits_type::corba_event_type * ev);

protected:
  typedef ACE_Hash_Map_Manager <ACE_Utils::UUID,
				subscriber_type *,
                                ACE_RW_Thread_Mutex> table_type;

  table_type table_;
};

#include "RTIDDS_Subscriber_Table_T.cpp"

#endif  // !defined _CUTS_RTIDDS_CCM_SUBSCRIBER_TABLE_T_H_