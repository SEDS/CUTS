#ifndef PUBAPPDDSCONTEXT_H
#define PUBAPPDDSCONTEXT_H

#include "DSTO_ContextBase.h"

#include "DDS_Utility.h"
#include "DummyEventC.h"

#include "ModelDDSDataDcps_impl.h"
#include "AppData.h"

#include "PubAppDDS_export.h"

using namespace DDS;

namespace DSTO_AppSpace_Impl
{
  class PubAppDDS_Export PubAppDDSContext
    : public virtual ::CUTS_DSTO::ContextBase
  {
  public:
    PubAppDDSContext ( ::CUTS_DDS::DDS_Utility & dds_utility_);
    virtual ~PubAppDDSContext (void);
    
    virtual void
    push_app_op_send ( ::Outer::TestData * ev);
    
    virtual ::Components::Cookie *
    subscribe_app_op_send ( ::CUTS_DDS::DummyConsumer_ptr c);
    
    virtual ::CUTS_DDS::DummyConsumer_ptr
    unsubscribe_app_op_send ( ::Components::Cookie * ck);
    
    static PubAppDDSContext *
    _narrow ( ::Components::SessionContext_ptr p);
    
  private:
    ::CUTS_DDS::DDS_Utility & dds_utility_;
    
    // Generate this for each publish port.
    ::Outer::TestData_DDSDataWriter_var app_op_send_writer_;
  };
}

#endif // PUBAPPDDSCONTEXT_H

