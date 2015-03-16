// -*- C++ -*-
// $Id$

namespace CUTS_BE_CCM
{
namespace Cpp
{

//
// Out_Type_Generator
//
CUTS_INLINE
Out_Type_Generator::Out_Type_Generator (std::ostream & out)
: Type_System (out)
{

}

//
// ~Out_Type_Generator
//
CUTS_INLINE
Out_Type_Generator::~Out_Type_Generator (void)
{

}

//
// Visit_Boolean
//
CUTS_INLINE
void Out_Type_Generator::
Visit_Boolean (const PICML::Boolean_in)
{
  this->out_ << "::CORBA::Boolean_out";
}

//
// Visit_Char
//
CUTS_INLINE
void Out_Type_Generator::
Visit_Char (const PICML::Char_in )
{
  this->out_ << "::CORBA::Char_out";
}

//
// Visit_WideChar
//
CUTS_INLINE
void Out_Type_Generator::
Visit_WideChar (const PICML::WideChar_in )
{
  this->out_ << "::CORBA::WChar_out";
}

//
// Visit_Byte
//
CUTS_INLINE
void Out_Type_Generator::
Visit_Byte (const PICML::Byte_in)
{
  this->out_ << "::CORBA::Octet_out";
}

//
// Visit_UnsignedShortInteger
//
CUTS_INLINE
void Out_Type_Generator::
Visit_UnsignedShortInteger (const PICML::UnsignedShortInteger_in)
{
  this->out_ << "::CORBA::UnsignedShort_out";
}

//
// Visit_ShortInteger
//
CUTS_INLINE
void Out_Type_Generator::
Visit_ShortInteger (const PICML::ShortInteger_in)
{
  this->out_ << "::CORBA::Short_out";
}

//
// Visit_LongInteger
//
CUTS_INLINE
void Out_Type_Generator::
Visit_LongInteger (const PICML::LongInteger_in)
{
  this->out_ << "::CORBA::Long_out";
}

//
// Visit_UnsignedLongInteger
//
CUTS_INLINE
void Out_Type_Generator::
Visit_UnsignedLongInteger (const PICML::UnsignedLongInteger_in)
{
  this->out_ << "::CORBA::UnsignedLong_out";
}

//
// Visit_LongLongInteger
//
CUTS_INLINE
void Out_Type_Generator::
Visit_LongLongInteger (const PICML::LongLongInteger_in)
{
  this->out_ << "::CORBA::LongLong_out";
}

//
// Visit_UnsignedLongLongInteger
//
CUTS_INLINE
void Out_Type_Generator::
Visit_UnsignedLongLongInteger (const PICML::UnsignedLongLongInteger_in)
{
  this->out_ << "::CORBA::UnsignedLongLong_out";
}

//
// Visit_String
//
CUTS_INLINE
void Out_Type_Generator::
Visit_String (const PICML::String_in)
{
  this->out_ << "::CORBA::String_out";
}

//
// Visit_WideString
//
CUTS_INLINE
void Out_Type_Generator::
Visit_WideString (const PICML::WideString_in)
{
  this->out_ << "::CORBA::WString_out";
}

//
// Visit_FloatNumber
//
CUTS_INLINE
void Out_Type_Generator::
Visit_FloatNumber (const PICML::FloatNumber_in)
{
  this->out_ << "::CORBA::Float_out";
}

//
// Visit_DoubleNumber
//
CUTS_INLINE
void Out_Type_Generator::
Visit_DoubleNumber (const PICML::DoubleNumber_in)
{
  this->out_ << "::CORBA::Double_out";
}

//
// Visit_LongDoubleNumber
//
CUTS_INLINE
void Out_Type_Generator::
Visit_LongDoubleNumber (const PICML::LongDoubleNumber_in)
{
  this->out_ << "::CORBA::LongDouble_out";
}

//
// Visit_GenericValue
//
CUTS_INLINE
void Out_Type_Generator::
Visit_GenericValue (const PICML::GenericValue_in)
{
  this->out_ << "::CORBA::Any_out";
}

//
// Visit_GenericValueObject
//
CUTS_INLINE
void Out_Type_Generator::
Visit_GenericValueObject (const PICML::GenericValueObject_in)
{

}

//
// Visit_GenericObject
//
CUTS_INLINE
void Out_Type_Generator::
Visit_GenericObject (const PICML::GenericObject_in)
{
  this->out_ << "::CORBA::Object_out";
}

//
// Visit_TypeKind
//
CUTS_INLINE
void Out_Type_Generator::
Visit_TypeKind (const PICML::TypeKind_in)
{
  this->out_ << "::CORBA::TCKind_out";
}

//
// Visit_TypeEncoding
//
CUTS_INLINE
void Out_Type_Generator::
Visit_TypeEncoding (const PICML::TypeEncoding_in)
{
  this->out_ << "::CORBA::TypeCode_out";
}

}
}
