// $Id$

#include "Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "Container_Strategy.inl"
#endif

#include "ace/DLL.h"

#include "ciao/Containers/Container_BaseC.h"

namespace iCCM
{

//
// load_executor
//
::Components::EnterpriseComponent_ptr
Container_Strategy::
load_executor (const char * location, const char * entrypt)
{
  // Load the executor from its shared library.
  ACE_DLL module;

  if (0 != module.open (location, ACE_DEFAULT_SHLIB_MODE, false))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - error loading opening %s; %m\n"),
                location));

    /// @todo Replace this with our own exception handler so we
    /// are not dependent on CIAO.
    throw ::Components::Deployment::InstallationFailure ();
  }

  // Load the symbol from the library.
  void * symbol = module.symbol (entrypt);

  if (0 == symbol)
    throw ::Components::Deployment::ImplEntryPointNotFound ();

  // Load the executor from the executor artifact.
  typedef ::Components::EnterpriseComponent_ptr (*ExecutorFactoryMethod) (void);
  ptrdiff_t tmp_ptr = reinterpret_cast <ptrdiff_t> (symbol);
  ExecutorFactoryMethod factory_method = reinterpret_cast <ExecutorFactoryMethod> (tmp_ptr);

  return (*factory_method) ();
}

//
// load_servant
//
::PortableServer::Servant Container_Strategy::
load_servant (const char * name,
              const char * location,
              const char * entrypt,
              ::PortableServer::POA_ptr poa,
              ::Components::EnterpriseComponent_ptr executor)
{
  // Load the servant from its shared library.
  ACE_DLL module;

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - opening servant module %s\n"),
              location));

  if (0 != module.open (location, ACE_DEFAULT_SHLIB_MODE, false))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to open module %s; %m\n"),
                location));

    throw ::Components::Deployment::InstallationFailure ();
  }

  // Load the symbol from the library.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - loading symbol %s from servant module\n"),
              entrypt));

  void * symbol = module.symbol (entrypt);

  if (0 == symbol)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to locate symbol in module\n")));

    throw ::Components::Deployment::ImplEntryPointNotFound ();
  }

  // Load the executor from the executor artifact.
  typedef ::PortableServer::Servant (*ServantFactoryMethod)
    (const char *,
     ::PortableServer::POA_ptr,
     ::Components::EnterpriseComponent_ptr);

  ptrdiff_t tmp_ptr = reinterpret_cast <ptrdiff_t> (symbol);
  ServantFactoryMethod factory_method = reinterpret_cast <ServantFactoryMethod> (tmp_ptr);

  return (*factory_method) (name, poa, executor);
}

}
