// -*- C++ -*-

//=============================================================================
/**
 *  @file         QpidPB_Publisher_Table_T.h
 *
 *  $Id$
 *
 *  Code generated by iCCM skeleton project generator that is include
 *  in the CUTS (http://cuts.cs.iupui.edu) and developed by:
 *
 *      Software Engineering & Distributed System (SEDS) Group
 *      Indiana Univesity-Purdue University Indianapolis
 *      Indianapolis, IN 46202
 */
//=============================================================================

#ifndef _ICCM_QPIDPB_PUBLISHER_TABLE_T_H_
#define _ICCM_QPIDPB_PUBLISHER_TABLE_T_H_

#include "cuts/iccm/servant/Publisher_Table_T.h"

#include "QpidPB_Publisher_Table.h"
#include "QpidPB_Publisher_T.h"

namespace iCCM
{

/**
 * @class QpidPB_Publisher_Table_T
 */
template <typename EVENT>
class QpidPB_Publisher_Table_T :
  public Publisher_Table_T < QpidPB_Publisher_Table, QpidPB_Publisher_T <EVENT>, true >
{
public:
  /// Type definition of the base type.
  typedef Publisher_Table_T < QpidPB_Publisher_Table,
                              QpidPB_Publisher_T <EVENT>,
                              true > base_type;

  /// Default constructor.
  QpidPB_Publisher_Table_T (void);

  /// Destructor.
  virtual ~QpidPB_Publisher_Table_T (void);

  /**
   * Subscribe an event consumer.
   *
   * @param[in]       consumer          Event consumer object
   * @return          Cookie object
   */
  virtual ::Components::Cookie * subscribe (::Components::EventConsumerBase_ptr);

  /**
   * Unsubscribe an event consumer.
   *
   * @param[in]       consumer         Cookie object
   * @return          Event consumer object
   */
  virtual ::Components::EventConsumerBase_ptr unsubscribe (::Components::Cookie *);

  /// Send an event.
  void send_event (EVENT * ev);

  /// Allocate a new event.
  EVENT * allocate_event (void);

  virtual void activate (void);
  virtual void passivate (void);

private:
  QpidPB_Sender_T <EVENT> sender_;
};

}

#include "QpidPB_Publisher_Table_T.cpp"

#endif  // !defined _ICCM_QPIDPB_PUBLISHER_TABLE_T_H_