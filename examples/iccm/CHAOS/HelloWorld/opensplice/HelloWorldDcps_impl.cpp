#include "HelloWorldDcps_impl.h"
#include "gapi.h"
#include "gapi_loanRegistry.h"
#include "HelloWorldSplDcps.h"
#include "ccpp_DataReader_impl.h"
#include "ccpp_DataReaderView_impl.h"
#include "../HelloWorld_stub_export.h"

extern c_bool
__Message__copyIn(
    c_base base,
    struct Message *from,
    struct _Message *to);

extern void
__Message__copyOut(
    void *_from,
    void *_to);

// DDS Message TypeSupportFactory Object Body

HELLOWORLD_STUB_Export DDS::DataWriter_ptr 
MessageTypeSupportFactory::create_datawriter (gapi_dataWriter handle)
{
    return new MessageDataWriter_impl(handle);
}

HELLOWORLD_STUB_Export DDS::DataReader_ptr 
MessageTypeSupportFactory::create_datareader (gapi_dataReader handle)
{
    return new MessageDataReader_impl (handle);
}


HELLOWORLD_STUB_Export DDS::DataReaderView_ptr 
MessageTypeSupportFactory::create_view (gapi_dataReaderView handle)
{
    return new MessageDataReaderView_impl (handle);
}

// DDS Message TypeSupport Object Body

HELLOWORLD_STUB_Export MessageTypeSupport::MessageTypeSupport(void) :
    TypeSupport_impl(
        __Message__name(),
        __Message__keys(),
        MessageTypeSupport::metaDescriptor,
        (gapi_copyIn) __Message__copyIn,
        (gapi_copyOut) __Message__copyOut,
        (gapi_readerCopy) DDS::ccpp_DataReaderCopy<MessageSeq, Message>,
        new  MessageTypeSupportFactory())
{
    // Parent constructor takes care of everything.
}

HELLOWORLD_STUB_Export MessageTypeSupport::~MessageTypeSupport(void)
{
    // Parent destructor takes care of everything.
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageTypeSupport::register_type(
    DDS::DomainParticipant_ptr domain,
    const char * type_name) THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::register_type(domain, type_name);
}

HELLOWORLD_STUB_Export char *
MessageTypeSupport::get_type_name() THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::get_type_name();
}

// DDS Message DataWriter_impl Object Body

HELLOWORLD_STUB_Export MessageDataWriter_impl::MessageDataWriter_impl (
    gapi_dataWriter handle
) : DDS::DataWriter_impl(handle)
{
    // Parent constructor takes care of everything.
}

HELLOWORLD_STUB_Export MessageDataWriter_impl::~MessageDataWriter_impl(void)
{
    // Parent destructor takes care of everything.
}

HELLOWORLD_STUB_Export DDS::InstanceHandle_t
MessageDataWriter_impl::register_instance(
    const Message & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance(&instance_data);
}

HELLOWORLD_STUB_Export DDS::InstanceHandle_t 
MessageDataWriter_impl::register_instance_w_timestamp(
    const Message & instance_data,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataWriter_impl::unregister_instance(
    const Message & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance(&instance_data, handle);
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataWriter_impl::unregister_instance_w_timestamp(
    const Message & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataWriter_impl::write(
    const Message & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write(&instance_data, handle);
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataWriter_impl::write_w_timestamp(
    const Message & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataWriter_impl::dispose(
    const Message & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose(&instance_data, handle);
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataWriter_impl::dispose_w_timestamp(
    const Message & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataWriter_impl::writedispose(
    const Message & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose(&instance_data, handle);
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataWriter_impl::writedispose_w_timestamp(
    const Message & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataWriter_impl::get_key_value(
    Message & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::get_key_value(&key_holder, handle);
}

HELLOWORLD_STUB_Export DDS::InstanceHandle_t 
MessageDataWriter_impl::lookup_instance(
	const Message & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::lookup_instance(&instance_data);
}

// DDS Message DataReader_impl Object Body

HELLOWORLD_STUB_Export MessageDataReader_impl::MessageDataReader_impl (
    gapi_dataReader handle
) : DDS::DataReader_impl(handle)
{
    // Parent constructor takes care of everything.
}

HELLOWORLD_STUB_Export MessageDataReader_impl::~MessageDataReader_impl(void)
{
    // Parent destructor takes care of everything.
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReader_impl::read(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReader_impl::take(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReader_impl::read_w_condition(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReader_impl::take_w_condition(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataReader_impl::read_next_sample(
    Message & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::read_next_sample(&received_data, sample_info);
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataReader_impl::take_next_sample(
    Message & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::take_next_sample(&received_data, sample_info);
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReader_impl::read_instance(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReader_impl::take_instance(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReader_impl::read_next_instance(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReader_impl::take_next_instance(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataReader_impl::read_next_instance_w_condition(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataReader_impl::take_next_instance_w_condition(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReader_impl::return_loan(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status = DDS::RETCODE_OK;

    if ( received_data.length() > 0 ) {
        if (received_data.length() == info_seq.length() && 
            received_data.release() == info_seq.release() ) {
            if (!received_data.release()) {
                status = DataReader_impl::return_loan( received_data.get_buffer(),
                                                       info_seq.get_buffer() );

                if ( status == DDS::RETCODE_OK ) {
                    if ( !received_data.release() ) {
                        MessageSeq::freebuf( received_data.get_buffer(false) );
                        received_data.replace(0, 0, NULL, false);
                        DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                        info_seq.replace(0, 0, NULL, false);
                    }
                } else if ( status == DDS::RETCODE_NO_DATA ) {
                    if ( received_data.release() ) {
                        status = DDS::RETCODE_OK;
                    } else {
                        status = DDS::RETCODE_PRECONDITION_NOT_MET;
                    }
                }
            }
        } else {
            status = DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }
    return status;
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataReader_impl::get_key_value(
    Message & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::get_key_value(&key_holder, handle);
}

HELLOWORLD_STUB_Export DDS::InstanceHandle_t 
MessageDataReader_impl::lookup_instance(
    const Message & instance) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::lookup_instance(&instance);
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataReader_impl::check_preconditions(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples)
{
    DDS::ReturnCode_t status = DDS::RETCODE_PRECONDITION_NOT_MET;
    
    if ( received_data.length() == info_seq.length() &&
         received_data.maximum() == info_seq.maximum() &&
         received_data.release() == info_seq.release() ) {
        if ( received_data.maximum() == 0 || received_data.release() ) {
            if (received_data.maximum() == 0 ||
				max_samples <= static_cast<CORBA::Long>(received_data.maximum()) ||
				max_samples == DDS::LENGTH_UNLIMITED ) {
                status = DDS::RETCODE_OK;
            }
        }
    }
    return status;
}


// DDS Message DataReaderView_impl Object Body

HELLOWORLD_STUB_Export MessageDataReaderView_impl::MessageDataReaderView_impl (
    gapi_dataReaderView handle
) : DDS::DataReaderView_impl(handle)
{
    // Parent constructor takes care of everything.
}

HELLOWORLD_STUB_Export MessageDataReaderView_impl::~MessageDataReaderView_impl(void)
{
    // Parent destructor takes care of everything.
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReaderView_impl::read(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = MessageDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReaderView_impl::take(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = MessageDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReaderView_impl::read_w_condition(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = MessageDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReaderView_impl::take_w_condition(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = MessageDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataReaderView_impl::read_next_sample(
    Message & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::read_next_sample(&received_data, sample_info);
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataReaderView_impl::take_next_sample(
    Message & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::take_next_sample(&received_data, sample_info);
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReaderView_impl::read_instance(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = MessageDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReaderView_impl::take_instance(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = MessageDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReaderView_impl::read_next_instance(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = MessageDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReaderView_impl::take_next_instance(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = MessageDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataReaderView_impl::read_next_instance_w_condition(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = MessageDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataReaderView_impl::take_next_instance_w_condition(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = MessageDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t
MessageDataReaderView_impl::return_loan(
    MessageSeq & received_data,
    DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status = DDS::RETCODE_OK;

    if ( received_data.length() > 0 ) {
        if (received_data.length() == info_seq.length() && 
            received_data.release() == info_seq.release() ) {
            if (!received_data.release()) {
                status = DataReaderView_impl::return_loan( received_data.get_buffer(),
                                                       info_seq.get_buffer() );

                if ( status == DDS::RETCODE_OK ) {
                    if ( !received_data.release() ) {
                        MessageSeq::freebuf( received_data.get_buffer(false) );
                        received_data.replace(0, 0, NULL, false);
                        DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                        info_seq.replace(0, 0, NULL, false);
                    }
                } else if ( status == DDS::RETCODE_NO_DATA ) {
                    if ( received_data.release() ) {
                        status = DDS::RETCODE_OK;
                    } else {
                        status = DDS::RETCODE_PRECONDITION_NOT_MET;
                    }
                }
            }
        } else {
            status = DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }
    return status;
}


HELLOWORLD_STUB_Export DDS::ReturnCode_t 
MessageDataReaderView_impl::get_key_value(
    Message & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::get_key_value(&key_holder, handle);
}

HELLOWORLD_STUB_Export DDS::InstanceHandle_t 
MessageDataReaderView_impl::lookup_instance(
    const Message & instance) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::lookup_instance(&instance);
}



const char * MessageTypeSupport::metaDescriptor = "<MetaData version=\"1.0.0\"><Struct name=\"Message\"><Member name=\"time\"><Long/></Member><Member name=\"content\">"
"<String/></Member></Struct></MetaData>";
