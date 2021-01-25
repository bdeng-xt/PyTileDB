#pragma once
#ifndef PYBIND_COMMON_INCLUDE_H
#define PYBIND_COMMON_INCLUDE_H

#include <memory>
//#include <boost/shared_ptr.hpp>

//#include <google/protobuf/stubs/common.h>
//#include <google/protobuf/arena.h>
//#include <google/protobuf/arenastring.h>
//#include <google/protobuf/generated_message_util.h>
//#include <google/protobuf/metadata.h>
//#include <google/protobuf/message.h>
//#include <google/protobuf/repeated_field.h>
//#include <google/protobuf/extension_set.h>
//#include <google/protobuf/unknown_field_set.h>

//#include "safe_ptr.h"

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "pybind11/stl_bind.h"
#include "pybind11/functional.h"
///////////////////////////////////////////


namespace py = pybind11;

//namespace pb = google::protobuf;

//PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>)
//PYBIND11_DECLARE_HOLDER_TYPE(T, sf::safe_ptr<T>)
//PYBIND11_DECLARE_HOLDER_TYPE(T, sf::contfree_safe_ptr<T>)
//namespace pybind11
//{
//	namespace  detail
//	{
//
//template <typename T>
//class type_caster<boost::shared_ptr<T>> : public copyable_holder_caster<T, boost::shared_ptr>> {};
//
//template <typename T>
//class type_caster<sf::safe_ptr<T>> : public copyable_holder_caster<T, sf::safe_ptr>> {};
//
//template < typename T>
//class type_caster<sf::contfree_safe_ptr<T>> : public copyable_holder_caster<T, sf::contfree_safe_ptr>> {};
//
//	}
//}


//////

//https://github.com/pybind/pybind11/issues/1791
//namespace pybind11 { namespace detail {
//	template <typename Type>
//	class type_caster<pb::RepeatedField<Type>> : public list_caster<pb::RepeatedField<Type>, Type> {};
//
//	template <typename Type>
//	class type_caster<pb::RepeatedPtrField<Type>> : public list_caster<pb::RepeatedPtrField<Type>, Type> {};
//}} // namespace pybind11::detail


#endif
