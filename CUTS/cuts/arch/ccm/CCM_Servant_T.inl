// -*- C++ -*-
// $Id$

//
// ~CUTS_CCM_Servant_T
//
template <typename POA_EXEC>
CUTS_INLINE
CUTS_CCM_Servant_T <POA_EXEC>::~CUTS_CCM_Servant_T (void)
{

}

//
// get_all_consumers
//
template <typename POA_EXEC>
CUTS_INLINE
Components::ConsumerDescriptions *
CUTS_CCM_Servant_T <POA_EXEC>::
get_all_consumers (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_named_consumers
//
template <typename POA_EXEC>
CUTS_INLINE
Components::ConsumerDescriptions *
CUTS_CCM_Servant_T <POA_EXEC>::
get_named_consumers (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_all_emitters
//
template <typename POA_EXEC>
CUTS_INLINE
Components::EmitterDescriptions *
CUTS_CCM_Servant_T <POA_EXEC>::get_all_emitters (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_name_emitters
//
template <typename POA_EXEC>
CUTS_INLINE
Components::EmitterDescriptions *
CUTS_CCM_Servant_T <POA_EXEC>::
get_named_emitters (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_all_publishers
//
template <typename POA_EXEC>
CUTS_INLINE
Components::PublisherDescriptions *
CUTS_CCM_Servant_T <POA_EXEC>::
get_all_publishers (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_named_publishers
//
template <typename POA_EXEC>
CUTS_INLINE
Components::PublisherDescriptions *
CUTS_CCM_Servant_T <POA_EXEC>::
get_named_publishers (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE
::CORBA::Object_ptr
CUTS_CCM_Servant_T <POA_EXEC>::provide_facet (const char *)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE
::Components::FacetDescriptions *
CUTS_CCM_Servant_T <POA_EXEC>::get_all_facets (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE
::Components::FacetDescriptions *
CUTS_CCM_Servant_T <POA_EXEC>::
get_named_facets (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE
::Components::Cookie *
CUTS_CCM_Servant_T <POA_EXEC>::
connect (const char *, ::CORBA::Object_ptr)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE
::CORBA::Object_ptr
CUTS_CCM_Servant_T <POA_EXEC>::
disconnect (const char *, ::Components::Cookie *)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE
::Components::ConnectionDescriptions *
CUTS_CCM_Servant_T <POA_EXEC>::get_connections (const char *)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE
::Components::ReceptacleDescriptions *
CUTS_CCM_Servant_T <POA_EXEC>::get_all_receptacles (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE ::Components::ReceptacleDescriptions *
CUTS_CCM_Servant_T <POA_EXEC>::
get_named_receptacles (const Components::NameList &)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE ::CORBA::Boolean
CUTS_CCM_Servant_T <POA_EXEC>::same_component (::CORBA::Object_ptr)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE ::CORBA::IRObject_ptr
CUTS_CCM_Servant_T <POA_EXEC>::get_component_def (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE ::Components::CCMHome_ptr
CUTS_CCM_Servant_T <POA_EXEC>::get_ccm_home (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE ::Components::PrimaryKeyBase *
CUTS_CCM_Servant_T <POA_EXEC>::get_primary_key (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE void
CUTS_CCM_Servant_T <POA_EXEC>::configuration_complete (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

template <typename POA_EXEC>
CUTS_INLINE ::Components::ComponentPortDescription *
CUTS_CCM_Servant_T <POA_EXEC>::get_all_ports (void)
{
  throw CORBA::NO_IMPLEMENT ();
}
