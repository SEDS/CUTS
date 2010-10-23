// $Id$

#include "BE_algorithm.h"
#include "BE_IDL_Node.h"
#include "boost/bind.hpp"

namespace CUTS_BE
{

/**
 * Implementation of the has_component function.
 */
class has_interface_i : public PICML::Visitor
{
public:
  has_interface_i (void)
    : result_ (false)
  {

  }

  bool result (void) const
  {
    return this->result_;
  }

  virtual void Visit_File (const PICML::File & file)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (file);
  }

  virtual void Visit_Package (const PICML::Package & package)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (package);
  }

protected:
  void Visit_FilePackage_i (const Udm::Object & obj)
  {
    std::set <PICML::Object> objects =
      Udm::ChildrenAttr <PICML::Object> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!objects.empty ())
    {
      this->result_ = true;
      return;
    }

    // Visit the remaining packages.
    std::set <PICML::Package> packages =
      Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (packages.begin (),
                   packages.end (),
                   boost::bind (&PICML::Package::Accept,
                                _1,
                                boost::ref (*this)));
  }

private:
  /// Result of the search.
  bool result_;
};

/**
 * Implementation of the has_component function.
 */
class has_component_i : public PICML::Visitor
{
public:
  has_component_i (void)
    : result_ (false)
  {

  }

  bool result (void) const
  {
    return this->result_;
  }

  virtual void Visit_File (const PICML::File & file)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (file);
  }

  virtual void Visit_Package (const PICML::Package & package)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (package);
  }

protected:
  void Visit_FilePackage_i (const Udm::Object & obj)
  {
    std::set <PICML::Component> components =
      Udm::ChildrenAttr <PICML::Component> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!components.empty ())
    {
      this->result_ = true;
      return;
    }

    // Visit the remaining packages.
    std::set <PICML::Package> packages =
      Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (packages.begin (),
                   packages.end (),
                   boost::bind (&PICML::Package::Accept,
                                _1,
                                boost::ref (*this)));
  }

private:
  /// Result of the search.
  bool result_;
};

//
// has_component
//
bool has_component (const PICML::File & file)
{
  has_component_i search;
  PICML::File (file).Accept (search);

  return search.result ();
}

//
// has_component
//
bool has_interface (const PICML::File & file)
{
  has_interface_i search;
  PICML::File (file).Accept (search);

  return search.result ();
}

//
// has_interface
//
bool has_interface (const CUTS_BE_IDL_Node * node)
{
  return has_interface (node->file_);
}

/**
 * Implementation of the has_events function.
 */
class has_events_i : public PICML::Visitor
{
public:
  has_events_i (void)
    : result_ (false)
  {

  }

  bool result (void) const
  {
    return this->result_;
  }

  virtual void Visit_File (const PICML::File & file)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (file);
  }

  virtual void Visit_Package (const PICML::Package & package)
  {
    if (!this->result_)
      this->Visit_FilePackage_i (package);
  }

protected:
  void Visit_FilePackage_i (const Udm::Object & obj)
  {
    // Gather all the necessary elements.
    std::set <PICML::Event> events =
      Udm::ChildrenAttr <PICML::Event> (obj.__impl (), Udm::NULLCHILDROLE);

    if (!events.empty ())
    {
      this->result_ = true;
      return;
    }

    // Visit the remaining packages.
    std::set <PICML::Package> packages =
      Udm::ChildrenAttr <PICML::Package> (obj.__impl (), Udm::NULLCHILDROLE);

    std::for_each (packages.begin (),
                   packages.end (),
                   boost::bind (&PICML::Package::Accept,
                                _1,
                                boost::ref (*this)));
  }

private:
  /// Result of the search.
  bool result_;
};

//
// has_events
//
bool has_events (const PICML::File & file)
{
  has_events_i search;
  PICML::File (file).Accept (search);

  return search.result ();
}

//
// get_pathname
//
std::string get_pathname (const PICML::File & file,
                          const std::string & separator,
                          const std::string & prefix,
                          const std::string & suffix)
{
  // Make sure we add the path to the pathname.
  std::string pathname = file.Path ();

  if (!pathname.empty ())
    pathname += "/";

  // Construct the remaining part of the pathname.
  pathname += prefix + std::string (file.name ()) + suffix;

  return pathname;
}

}
