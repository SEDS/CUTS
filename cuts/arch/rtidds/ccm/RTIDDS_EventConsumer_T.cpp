// $Id$

#include "ndds/ndds_cpp.h"
#include "RTIDDS_Event_T.h"

//
// CUTS_RTIDDS_CCM_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_RTIDDS_CCM_EventConsumer_T <SERVANT, EVENT>::
CUTS_RTIDDS_CCM_EventConsumer_T (SERVANT * servant, UPCALL_METHOD callback)
  : servant_ (servant),
    callback_ (callback)
{

}

//
// ~CUTS_RTIDDS_CCM_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_RTIDDS_CCM_EventConsumer_T <SERVANT, EVENT>::
~CUTS_RTIDDS_CCM_EventConsumer_T (void)
{

}

//
// configure
//
template <typename SERVANT, typename EVENT>
int CUTS_RTIDDS_CCM_EventConsumer_T <SERVANT, EVENT>::
configure (::DDSSubscriber * subscriber,
           const char * inst,
           const char * topic)
{
  // First, let's create the fully qualified name of the topic.
  ACE_CString topic_name (inst);
  topic_name += ".";
  topic_name += topic;

  // Register the type for with the participant. This should really
  // be done in the servant's code!!

  typedef typename CUTS_RTIDDS_Traits_T <EVENT>::dds_typesupport_type dds_typesupport_type;

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - registering type %s\n"),
              dds_typesupport_type::get_type_name ()));

  // Register the type with the participant.
  ::DDSDomainParticipant * participant = subscriber->get_participant ();
  ::DDS_ReturnCode_t retcode =
    dds_typesupport_type::register_type (participant,
                                         dds_typesupport_type::get_type_name ());

  if (DDS_RETCODE_OK != retcode)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to register type %s\n"),
                dds_typesupport_type::get_type_name ()));

    throw ::CORBA::INTERNAL ();
  }

  // Open the endpoint for this event consumer.
  this->subscriber_ = subscriber;
  int retval = this->open (dds_typesupport_type::get_type_name (),
                           topic_name.c_str ());

  if (0 != retval)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open the consumer\n")),
                       -1);

  this->reader_ = CUTS_RTIDDS_Traits_T <EVENT>::reader_type::narrow (this->abstract_reader_);

  return 0;
}

//
// on_data_available
//
template <typename SERVANT, typename EVENT>
void CUTS_RTIDDS_CCM_EventConsumer_T <SERVANT, EVENT>::
on_data_available (::DDSDataReader_ptr p)
{
  typename traits_type::dds_event_sequence_type event_seq (1);
  ::DDS_SampleInfoSeq sample_info (1);

  //// Get the concrete reader from the generic reader.
  //typedef typename CUTS_RTIDDS_Traits_T <EVENT>::reader_type reader_type;
  //reader_type * reader = reader_type::narrow (p);

  ::DDS_ReturnCode_t status =
      this->reader_->take (event_seq,
                           sample_info,
                           1,
                           DDS_ANY_SAMPLE_STATE,
                           DDS_ANY_VIEW_STATE,
                           DDS_ANY_INSTANCE_STATE);

  if (DDS_RETCODE_OK == status)
  {
    if (0 != this->callback_)
    {
      // Get the length of the sequence.
      int length = event_seq.length ();

      for (int i = 0; i < length; ++ i)
      {
        // Right now, we are going to derive ourselves from the CORBA
        // object-by-value type since we don't want to implement the remaining
        // pure virtual methods on the concrete classes. :-)
        typedef CUTS_RTIDDS_Upcall_Event_T <typename traits_type::corba_obv_event_type,
                                            typename traits_type::dds_event_type>
                                            upcall_event_t;

        upcall_event_t upcall_event (event_seq[i]);
        (*this->callback_) (this->servant_, &upcall_event);
      }
    }
  }
  else
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to read event [retcode=%d]\n"),
                status));
}