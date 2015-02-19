// $Id$

#include "StdAfx.h"
#include "Event_Creator.h"

#if !defined (__CUTS_INLINE__)
#include "Event_Creator.inl"
#endif  // !defined __CUTS_INLINE__

#include "game/mga/Iterator_T.h"
#include "game/mga/modelgen.h"
#include "game/mga/utils/Point.h"

#include "boost/bind.hpp"
#include <algorithm>
#include <functional>

template <typename T>
class scoped_swap
{
public:
  scoped_swap (T & placeholder, T new_value)
    : placeholder_ (placeholder),
      old_value_ (placeholder)
  {
    this->placeholder_ = new_value;
  }

  ~scoped_swap (void)
  {
    this->placeholder_ = this->old_value_;
  }

private:
  T & placeholder_;
  T old_value_;
};

namespace dds2ccm
{
//
// visit_RootFolder
//
void Event_Creator::
visit_RootFolder (PICML::RootFolder_in folder)
{
  // Visit all the InterfaceDefinitions folders in the root folder.
  for (auto item : folder->get_InterfaceDefinitions ())
    item->accept (this);
}

//
// visit_InterfaceDefinitions
//
void Event_Creator::
visit_InterfaceDefinitions (PICML::InterfaceDefinitions_in item)
{
  const std::string name = item->name ();
  static const std::string PREFIX ("dds2ccm_");

  // Make sure the folder is not a dds_ autogenerated folder.
  if (name.find (PREFIX) == 0)
    return;

  // Make sure an equivalent DDS InterfaceDefinitions folder exists.
  static const std::string dds_InterfaceDefinitions (PREFIX + name);
  GAME::Mga::RootFolder parent = GAME::Mga::RootFolder::_narrow (item->parent ());

  if (GAME::create_if_not <GAME::Mga_t> (parent, this->target_folder_,
      GAME::contains <GAME::Mga_t> (boost::bind (std::equal_to <std::string> (),
                                    dds_InterfaceDefinitions,
                                    boost::bind (&PICML::InterfaceDefinitions::impl_type::name,
                                                 boost::bind (&PICML::InterfaceDefinitions::get, _1))))))
  {
    this->target_folder_->name (dds_InterfaceDefinitions);
  }

  // Visit all the Files in the current folder.
  std::vector <PICML::File> files;

  if (item->get_Files (files))
    std::for_each (GAME::Mga::make_impl_iter (files.begin ()),
                   GAME::Mga::make_impl_iter (files.end ()),
                   boost::bind (&PICML::File::impl_type::accept, _1, this));
}

//
// visit_File
//
void Event_Creator::visit_File (PICML::File_in item)
{
  // Make sure the target file of the same name exists.
  const std::string name = item->name () + "Events";

  PICML::File file;
  if (GAME::create_if_not <GAME::Mga_t> (this->target_folder_, file,
      GAME::contains <GAME::Mga_t> (boost::bind (std::equal_to <std::string> (),
                                    name,
                                    boost::bind (&PICML::File::impl_type::name,
                                                 boost::bind (&PICML::File::get, _1))))))
  {
    file->name (name);
  }

  // Make sure the newly created file references the source file.
  PICML::FileRef file_ref;
  if (GAME::create_if_not <GAME::Mga_t> (file, file_ref,
      GAME::contains <GAME::Mga_t> (boost::bind (std::equal_to <PICML::File> (),
                                    PICML::File (item),
                                    boost::bind (&PICML::FileRef::impl_type::refers_to,
                                                 boost::bind (&PICML::FileRef::get, _1))))))
  {
    file_ref->name (item->name ());
    file_ref->refers_to (item);
  }

  scoped_swap <GAME::Mga::Model> swapper (this->target_model_, file);

  // Visit all the Package elements in this file.
  for (auto package : item->get_Packages ())
    package->accept (this);

  // Visit all the Aggregate elmeents in this file.
  for (auto aggr : item->get_Aggregates ())
    aggr->accept (this);
}

//
// visit_Package
//
void Event_Creator::visit_Package (PICML::Package_in item)
{
  // Make sure the target file of the same name exists.
  static const std::string name = item->name ();

  GAME::Mga::Model package;
  if (GAME::create_if_not <GAME::Mga_t> (this->target_model_, PICML::Package::impl_type::metaname, package,
      GAME::contains <GAME::Mga_t> (boost::bind (std::equal_to <std::string> (),
                                    name,
                                    boost::bind (&GAME::Mga::Model::impl_type::name,
                                                 boost::bind (&GAME::Mga::Model::get, _1))))))
  {
    package->name (name);
  }

  // Set the active parent.
  scoped_swap <GAME::Mga::Model> swapper (this->target_model_, package);

  // Visit all the Package elements in this file.
  for (auto package : item->get_Packages ())
    package->accept (this);

  // Visit all the Aggregate elmeents in this file.
  for (auto aggr : item->get_Aggregates ())
    aggr->accept (this);
}

//
// visit_Aggregate
//
void Event_Creator::visit_Aggregate (PICML::Aggregate_in item)
{
  // Make sure the target file of the same name exists.
  static const std::string name = item->name () + "Event";

  GAME::Mga::Model model;

  if (GAME::create_if_not <GAME::Mga_t> (this->target_model_, PICML::Event::impl_type::metaname, model,
      GAME::contains <GAME::Mga_t> (boost::bind (std::equal_to <std::string> (),
                                    name,
                                    boost::bind (&GAME::Mga::Model::impl_type::name,
                                                 boost::bind (&GAME::Mga::Model::get, _1))))))
  {
    model->name (name);
  }

  this->target_event_ = PICML::Event::_narrow (model);
  for (auto member : item->get_Members ())
    member->accept (this);
}

//
// visit_Member
//
void Event_Creator::visit_Member (PICML::Member_in item)
{
  PICML::MemberType member_type = item->refers_to_MemberType ();
  PICML::Member target_member;

  if (GAME::create_if_not <GAME::Mga_t> (this->target_event_, target_member,
      GAME::contains <GAME::Mga_t> (
        [&] (const PICML::Member & m)
        {
          return std::equal_to <PICML::MemberType> () (member_type, m->refers_to_MemberType ());
        })))
  {
    target_member->refers_to_MemberType (member_type);
  }

  target_member->name (item->name ());

  // Update the position of the newly created item to match the position
  // of its origin.
  GAME::Mga::Point pt;
  GAME::Mga::get_position ("InterfaceDefinition", item, pt);
  GAME::Mga::set_position ("InterfaceDefinition", pt, target_member);
}

} // namespace dds2ccm
