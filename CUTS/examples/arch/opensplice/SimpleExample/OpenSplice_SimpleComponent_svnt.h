// -*- C++ -*-

#ifndef _OPENSPLICE_SIMPLECOMPONENT_SVNT_H_
#define _OPENSPLICE_SIMPLECOMPONENT_SVNT_H_

#include "SimpleComponentS.h"
//#include "OpenSplice_HelloWorldC.h"

#include "SimpleComponentEC.h"
#include "cuts/arch/ccm/CCM_Context_T.h"
//#include "cuts/arch/opensplice/ccm/OpenSplice_CCM_Subscriber_Table_T.h"

#include "SimpleComponent_svnt_export.h"

namespace SimpleComponent_Basic_Impl
{
  // Forward decl.
  class HelloWorld_Servant;

  typedef CUTS_CCM_Context_T <::CCM_HelloWorld_Context, HelloWorld_Servant> HelloWorld_Servant_Context_Base;

  /**
   * @class HelloWorld_Servant_Context
   */
  class HelloWorld_Servant_Context : public HelloWorld_Servant_Context_Base
  {
    public:
    // default constructor
    HelloWorld_Servant_Context (HelloWorld_Servant & parent);

    // destructor
    virtual ~HelloWorld_Servant_Context (void);

    public:
    // push method for output event port: handle_message
    virtual void push_app_op_emit (::Outer::TestData_DDS * ev);

    //CUTS_TCPIP_CCM_Remote_Endpoint & endpoint_handle_message (void);

    private:
    //CUTS_TCPIP_CCM_Remote_Endpoint_T < ::Message > handle_message_;

    public:
    // push method for output event port: handle_message_ex
    virtual void push_app_op_send (::Outer::TestData_DDS * ev);

    //CUTS_TCPIP_CCM_Subscriber_Table & endpoints_handle_message_ex (void);

    private:
    //CUTS_TCPIP_CCM_Subscriber_Table_T < ::Message > handle_message_ex_;
  };


  // Type definition of the this->servant_'s base class
  //  typedef CUTS_TCPIP_CCM_Servant_T < 
  //HelloWorld_Servant,
  //HelloWorld_Servant_Context,
  //CIDL_HelloWorld_Basic_Impl::HelloWorld_Exec,
  //::POA_HelloWorld > HelloWorld_Servant_Base;

  /**
   * @class HelloWorld_Servant
   */
  /*class HelloWorld_Servant : public HelloWorld_Servant_Base
  {
    public:
    // default constructor
    HelloWorld_Servant (const char * name, 
                        CUTS_TCPIP_Servant_Manager & svnt_mgr, 
                        CIDL_HelloWorld_Basic_Impl::HelloWorld_Exec_ptr executor);

    // destructor
    virtual ~HelloWorld_Servant (void);

    void connect_handle_message (::MessageConsumer_ptr);

    ::MessageConsumer_ptr disconnect_handle_message (void);

    ::Components::Cookie * subscribe_handle_message_ex (::MessageConsumer_ptr);

    ::MessageConsumer_ptr unsubscribe_handle_message_ex (::Components::Cookie *);

    public:
    ::MessageConsumer_ptr get_consumer_handle_message (void);

    static int tcpip_handle_message (HelloWorld_Servant * svnt,
                                     CUTS_TCPIP_InputCDR & input);

    private:
    CUTS_TCPIP_CCM_EventConsumer handle_message_consumer_;

    public:
    virtual void message (const char * message);

    virtual char * message (void);

    virtual char * readonly_message (void);
  };
}

extern "C" TCPIP_HELLOWORLD_SVNT_Export
::PortableServer::Servant
create_HelloWorld_Servant (const char * name,
                           CUTS_TCPIP_Servant_Manager * svnt_mgr,
                           ::Components::EnterpriseComponent_ptr p);
  */
#endif  // !defined _TCPIP_HELLOWORLD_SVNT_H_
