#pragma once
#ifndef TILEDB_COLUMN_H
#define TILEDB_COLUMN_H

/**
* \file column_data.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide column data buffer classes for tiledb dimensions and attributes.
*
* \description
*	This component provides data buffer classes  for tiledb dimensions and attributes.
*/

#include <iostream>
#include <memory>

#include <limits>
//#include <codecvt>

#include "array.h"
#include "array_schema.h"
#include "attribute.h"
#include "config.h"
#include "context.h"
#include "deleter.h"
#include "dimension.h"
#include "domain.h"
#include "exception.h"
#include "filter.h"
#include "filter_list.h"
#include "group.h"
#include "object.h"
#include "object_iter.h"
#include "query.h"
#include "schema_base.h"
#include "stats.h"
#include "tiledb.h"
#include "utils.h"
#include "version.h"
#include "vfs.h"

//#include "pybind11/pybind11.h"
//#include "pybind11/stl.h"
//#include "pybind11/functional.h"
//#include "pybind11/numpy.h"

//#include <arrow/api.h>
//#include <arrow/python/pyarrow.h>

namespace tiledb {

class ColumnData {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	ColumnData();

	/**
	* @brief copy constructor
	*/
	ColumnData(const tiledb::ColumnData& from) 
	{}

	/**
	* @brief copy assignment
	*/
	ColumnData& operator=(const tiledb::ColumnData& from)
	{
		return *this;
	}

	/**
	* @breif move constructor
	*/
	ColumnData(tiledb::ColumnData&&)
	{}


	/**
	* @brief move assignment
	*/
	tiledb::ColumnData& operator=(tiledb::ColumnData&&)
	{
		return *this;
	}


    /**
	* @brief destructor
	*/
	virtual ~ColumnData() {}
	///@}

protected:
	/**
	* @name Buffer Data 
	* member data for set_buffer for fixed_size or variable-size 
	* please refer to parameters for set_buffer function of Query class
	* @param offsets Offsets array pointer where a new element begins in the data
	*        buffer.
	* @param offsets_nelements Number of elements in offsets buffer.
	* @param data Buffer array pointer with elements of the attribute type.
	*        For variable sized attributes, the buffer should be flattened.
	* @param data_nelements Number of array elements in data buffer.
	* @param element_size Size of data array elements (in bytes).
	*/
	///@{

	std::string name_;///< name of dimension or attribute
	tiledb_datatype_t datatype_;
	uint64_t* offsets_;  ///< offset buffer for variable-sized
	uint64_t offset_nelements_; ///< 
	uint64_t offset_bytes_size_; ///< total bytes of offset buffer
	void* data_; ///< data buffer 
	uint64_t data_nelements_; ///< number of data elements
	uint64_t data_bytes_size_; ///< total bytes of data buffer
	size_t data_element_size_; ///< byte size of data element

	bool is_dim_; ///< is dimension or not
	bool is_var_; ///< is varialbe length or not

	std::string lower_bound_;///< dimension domain lower bound
	std::string upper_bound_; ///< dimension domain upper bound

	///@}

public:
	/**
	* @brief name getter
	*/
	const std::string& name();
	/**
	* @brief name setter
	*/
	void set_name(const std::string& s);

	/**
	* @brief datatype getter
	*/
	tiledb_datatype_t datatype();
	/**
	* @brief datatype setter
	*/
	void set_datatype(tiledb_datatype_t t);

	/**
	* @brief offset buffer
	*/
	uint64_t* offsets();

	/**
	* @brief offset_nelements getter
	*/
	uint64_t offset_nelements();
//  void set_oofset_nelements(uint64_t sz);

	/**
	* @brief offset bytes size
	*/
	uint64_t& offset_bytes_size();

	/**
	* @brief data buffer
	*/
	void* data();

	/**
	* @brief data_nelements getter
	*/
	uint64_t data_nelements();
//  void set_data_nelements();

	/**
	* @brief data bytes size
	*/
	uint64_t& data_bytes_size();

	/**
	* @brief data_element_size getter
	*/
	size_t& data_element_size();
//  void set_data_element_size(size_t sz);

	/**
	* @brief is_dim getter
	*/
	bool is_dim();
	/**
	* @brief is_dim setter
	*/
	void set_is_dim(bool b);

	/**
	* @brief is_var getter
	*/
	bool is_var();
	/**
	* @brief is_var setter
	*/
	void set_is_var(bool b);

	/**
	* @brief lower bound
	*/
	const std::string& lower_bound();

	/**
	* @brief set lower bound
	*/
	void set_lower_bound(const std::string& s);

	/**
	* @brief upper bound
	*/
	const std::string& upper_bound();

	/**
	* @brief set upper bound
	*/
	void set_upper_bound(const std::string& s);

	/**
	* @brief is buffer empty or not
	*/
	bool is_buffer_empty();

 

	/**
	* @brief reset buffer to null
	*/
	void reset_buffer();

	/**
	* @brief resize vector 
	*/
	virtual int resize_vector(uint64_t sz);

	/**
	* @brief resize bytes vector
	*/
	virtual int resize_bytes_vector(uint64_t sz);

	/**
	* @brief set buffer from vector data
	*
	* @return status, -1 if failed
	*/
	virtual int set_buffer();

	/**
	* @brief read buffer to vector data
	*
	* @return status, -1 if failed
	*/
	virtual int read_buffer();

	/**
	* @brief clear all data
	*/
	virtual void clear();


};//class Column

template<typename T>
class PrimitiveColumnData : public ColumnData{
public:
 

protected:
	std::vector<T > data_vector_; ///< vector data
public:
 
	std::vector<T>& data_vector()
	{
		return data_vector_;
	}

	/**
	* @brief resize vector
	*/
	virtual int resize_vector(uint64_t sz)
	{
		data_vector_.resize(sz);
		return 0;
	}

	/**
	* @brief resize bytes vector
	*/
	virtual int resize_bytes_vector(uint64_t sz)
	{
		return 0;
	}

	/**
	* @brief set buffer from vector data
	*
	* @return status, -1 if failed
	*/
	virtual int set_buffer()
	{
 
		reset_buffer();
		if (data_vector_.size() == 0)
		{
			return -1;
		}
		is_var_ = false;

		data_ = data_vector_.data();
		data_nelements_ = (uint64_t)(data_vector_.size());
		data_element_size_ = sizeof(T);
		data_bytes_size_ = data_nelements_ * data_element_size_;
		return 0;
	}//virtual int set_buffer()

	 /**
	 * @brief read buffer to vector data
	 *
	 * @return status, -1 if failed
	 */
	virtual int read_buffer()
	{
		//no need to do anything for primitive data
		return 0;
	}
 

};//class PrimitiveDataColumn

using Int32ColumnData = PrimitiveColumnData<int>;
using UInt32ColumnData = PrimitiveColumnData<uint32_t>;
using Int64ColumnData = PrimitiveColumnData<int64_t>;
using UInt64ColumnData = PrimitiveColumnData<uint64_t>;
using DoubleColumnData = PrimitiveColumnData<double>;

//using BoolColumnData = PrimitiveColumnData<bool>;


class StringColumnData : public ColumnData {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	StringColumnData() :
		ColumnData()
	{
		is_var_ = true;
		data_element_size_ = sizeof(char);
	}

	/**
	* @brief copy constructor
	*/
	StringColumnData(const tiledb::StringColumnData& from)
	{}

	/**
	* @brief copy assignment
	*/
	StringColumnData& operator=(const tiledb::StringColumnData& from)
	{
		return *this;
	}

	/**
	* @breif move constructor
	*/
	StringColumnData(tiledb::StringColumnData&&) 
	{}


	/**
	* @brief move assignment
	*/
	tiledb::StringColumnData& operator=(tiledb::StringColumnData&&)
	{
		return *this;
	}


	/**
	* @brief destructor
	*/
	virtual ~StringColumnData() {}
	///@}
protected:
	std::vector<std::string> data_vector_;///< data vector
	std::vector<char> bytes_vector_; ///< byte data buffer, should we use unsigned char(uint8_t)?
	std::vector<uint64_t> offsets_vector_; ///<variable data offset
public:
	std::vector<std::string>& data_vector()
	{
		return data_vector_;
	}
	std::vector<char>& bytes_vector()
	{
		return bytes_vector_;
	}
	std::vector<uint64_t>& offsets_vector()
	{
		return offsets_vector_;
	}

	/**
	* @brief resize vector
	*/
	virtual int resize_vector(uint64_t sz)
	{
		data_vector_.resize(sz);
		offsets_vector_.resize(sz);
		return 0;
	}

	/**
	* @brief resize bytes vector
	*/
	virtual int resize_bytes_vector(uint64_t sz)
	{
		bytes_vector_.resize(sz);
		return 0;
	}

	/**
	* @brief set buffer from vector data
	*
	* @return status, -1 if failed
	*/
	virtual int set_buffer() 
	{
		reset_buffer();
		if (bytes_vector_.size() == 0)
		{
			return -1;
		}
		is_var_ = true;

		data_ = &bytes_vector_.data()[0];
		data_bytes_size_ = (uint64_t)bytes_vector_.size();
		data_element_size_ = sizeof(char);

		offsets_ = &offsets_vector_.data()[0];
		offset_nelements_ = (uint64_t)(offsets_vector_.size());
		offset_bytes_size_ = offset_nelements_ * sizeof(uint64_t);
		return 0;
	}//virtual int set_buffer() 

	 /**
	 * @brief read buffer to vector data
	 *
	 * @return status, -1 if failed
	 */
	virtual int read_buffer()
	{
		if (data_ == nullptr || offsets_ == nullptr)
		{
			std::cout << "StringColumn::read_buffer, null data_ or offsets_" << std::endl;
			return -1;
		}
		 
		offset_nelements_ = offset_bytes_size_ / sizeof(uint64_t);
		data_nelements_ = offset_nelements_;
		if ( data_element_size_ != sizeof(char))
		{
			//wrong size information
			std::cout << "StringColumn::read_buffer, wrong size information!"
				<< ",data_nelements_:" << data_nelements_
				<< ",offset_nelements_:" << offset_nelements_
				<< ",data_element_size_:" << data_element_size_
				<< std::endl;
		}
		data_vector_.clear();
		data_vector_.reserve(data_nelements_);
		for (uint64_t i = 0; i < data_nelements_; ++i)
		{
			uint64_t str_sz = 0;
			if (i < (data_nelements_ - 1))
			{
				str_sz = offsets_[i + 1] - offsets_[i];
			}
			else
			{
				str_sz = data_bytes_size_ - offsets_[i];
			}
			std::string s = "";
			if (str_sz > 0)
			{
				s = std::string(&(static_cast<char*>(data_))[offsets_[i]], str_sz);
			}
			data_vector_.emplace_back(s);

		}
		return 0;
	}//virtual int read_buffer()

};//class StringColumn

template<typename T>
class VectorColumnData : public ColumnData {
 
protected:
	std::vector<std::vector<T> > data_vector_; ///< data vector of vector

	std::vector<uint64_t> offsets_vector_; ///<variable data offset
public:
	/**
	* @brief data_vector accessor
	*/
	std::vector<std::vector<T> >& data_vector()
	{
		return data_vector_;
	}

	/**
	* @brief data_vector accessor
	*/
	std::vector<uint64_t>& offsets_vector()
	{
		return offsets_vector_;
	}

	/**
	* @brief resize vector
	*/
	virtual int resize_vector(uint64_t sz)
	{
		data_vector_.resize(sz);
		offsets_vector_.resize(sz);

		return 0;
	}

	/**
	* @brief resize bytes vector
	*/
	virtual int resize_bytes_vector(uint64_t sz)
	{
		return 0;
	}

	/**
	* @brief set buffer from vector data
	*
	* @return status, -1 if failed
	*/
	virtual int set_buffer()
	{
		reset_buffer();
		if (data_vector_.size() == 0)
		{
			return -1;
		}
		is_var_ = false;

		data_ = data_vector_.data();
		data_nelements_ = (uint64_t)(data_vector_.size());
		data_element_size_ = sizeof(T);

		int64_t bytes_size = 0;
		int64_t offset = 0;
		for (auto it = data_vector_.begin(); it != data_vector_.end(); ++it)
		{
			int64_t sz = (*it).size() * sizeof(T);

			offsets_vector_.push_back(offset);

			bytes_size += sz;
			offset += sz;
		}

		data_bytes_size_ = bytes_size;

		return 0;
	}

	/**
	* @brief read buffer to vector data
	*
	* @return status, -1 if failed
	*/
	virtual int read_buffer()
	{
		return 0;
	}



};//class VectorColumnData

template<typename T>
class GenericColumnData : public ColumnData {

protected:
	std::vector<T > data_vector_; ///< vector data

	std::vector<char> bytes_vector_; ///< byte data buffer
	std::vector<uint64_t> offsets_vector_; ///<variable data offset

public:
	/**
	* @brief data_vector accessor
	*/
	std::vector<T >& data_vector()
	{
		return data_vector_;
	}

	/**
	* @brief bytes_vector accessor
	*/
	std::vector<char>& bytes_vector()
	{
		return bytes_vector_;
	} 

	/**
	* @brief offsets_vector accessor
	*/
	std::vector<uint64_t>& offsets_vector()
	{
		return offsets_vector_;
	}

	/**
	* @brief resize vector
	*/
	virtual int resize_vector(uint64_t sz)
	{
		data_vector_.resize(sz);
		return 0;
	}

	/**
	* @brief resize bytes vector
	*/
	virtual int resize_bytes_vector(uint64_t sz)
	{
		bytes_vector_.resize(sz);
		return 0;
	}

	/**
	* @brief set buffer from vector data
	*
	* @return status, -1 if failed
	*/
	virtual int set_buffer()
	{
		reset_buffer();
		if (data_vector.size() == 0)
		{
			return -1;
		}
		bytes_vector.clear();
		offsets_vector.clear();


		return 0;
	}

	/**
	* @brief serialize data to bytes, mostly we use protobuf2
	*/
	virtual std::vector<char> serialize()
	{
		//should be implemented in derived class
		return std::vector<char>();
	}

	/**
	* @brief deserialize bytes to data, mostly we use protobuf2
	*/
	virtual T deserialize(std::vector<char> & bytes)
	{
		//should be implemented in derived class
		return T();
	}

};//class GenericDataColumn


//////

/**
* a collection of columns
*/
class ColumnDataMap {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	ColumnDataMap(){}

	/**
	* @brief copy constructor
	*/
	ColumnDataMap(const tiledb::ColumnDataMap& from) = default;//

	/**
	* @brief copy assignment
	*/
	ColumnDataMap& operator=(const tiledb::ColumnDataMap& from) = default;

	/**
	* @breif move constructor
	*/
	ColumnDataMap(tiledb::ColumnDataMap&&) = default;


	/**
	* @brief move assignment
	*/
	tiledb::ColumnDataMap& operator=(tiledb::ColumnDataMap&&) = default;


	/**
	* @brief destructor
	*/
	virtual ~ColumnDataMap() {}
	///@}

	/**
	* @name column accessors
	*/
	///@{


	/**
	* @brief columns accessor
	*/
	std::unordered_map<std::string, std::shared_ptr<tiledb::ColumnData> > & columns();

	/**
	* @brief check if has column or not
	*
	* @param column_name
	*
	* @return true if column exists
	*/
	bool has_column(const std::string& column_name);

	/**
	* @brief offset buffer
	*/
	uint64_t* offsets(const std::string& column_name);

	/**
	* @brief offset_nelements getter
	*/
	uint64_t offset_nelements(const std::string& column_name);
	//  void set_oofset_nelements(uint64_t sz);

	/**
	* @brief offset bytes size
	*/
	uint64_t offset_bytes_size(const std::string& column_name);

	/**
	* @brief data buffer
	*/
	void* data(const std::string& column_name);

	/**
	* @brief data_nelements getter
	*/
	uint64_t data_nelements(const std::string& column_name);
	//  void set_data_nelements();

	/**
	* @brief data bytes size
	*/
	uint64_t data_bytes_size(const std::string& column_name);

	/**
	* @brief data_element_size getter
	*/
	size_t data_element_size(const std::string& column_name);
	//  void set_data_element_size(size_t sz);

	/**
	* @brief is_dim getter
	*/
	bool is_dim(const std::string& column_name);
	/**
	* @brief is_dim setter
	*/
	void set_is_dim(const std::string& column_name,bool b);

	/**
	* @brief is_var getter
	*/
	bool is_var(const std::string& column_name);
	/**
	* @brief is_var setter
	*/
	void set_is_var(const std::string& column_name, bool b);

	/**
	* @brief lower bound
	*/
	const std::string lower_bound(const std::string& column_name);

	/**
	* @brief set lower bound
	*/
	void set_lower_bound(const std::string& column_name, const std::string& s);

	/**
	* @brief upper bound
	*/
	const std::string upper_bound(const std::string& column_name);

	/**
	* @brief set upper bound
	*/
	void set_upper_bound(const std::string& column_name, const std::string& s);

	/**
	* @brief is buffer empty or not
	*/
	bool is_buffer_empty(const std::string& column_name);

	///@}

	/**
	* @brief test if it is empty or not
	*
	* @return true if there are columns in map
	*/
	bool is_empty();

	/**
	* @brief get column pointer by name
	*
	* @param column_name
	*
	* @return column
	*/
	std::shared_ptr<tiledb::ColumnData>& column_by_name(const std::string& column_name);

	/**
	* @brief number of columns
	*
	* @ return number of columns
	*/
	uint32_t ncol();

	/**
	* @brief number of rows
	*
	* @return number of rows
	*/
	uint64_t nrows(const std::string& column_name);

	/**
	* @brief get vector of dimension column names
	*
	* @return dimension names
	*/
	std::vector<std::string> dimension_names();

	/**
	* @brief get vector of dimension datatypes
	*
	* @return dimension datatypes
	*/
	std::vector<tiledb_datatype_t> dimension_datatypes();



	/**
	* @brief get 
	*/

	/**
	* @brief get vector of attribute column names
	*
	* @return attribute names
	*/
	std::vector<std::string> attribute_names();

	/**
	* @brief get vector of attribute column datatypes
	*
	* @return attribute datatypes
	*/
	std::vector<tiledb_datatype_t> attribute_datatypes();

	/**
	* @brief add column
	*
	* @param column
	*/
	void add_column(const std::shared_ptr<tiledb::ColumnData>& column);

	/**
	* @brief add data column
	*
	* @param column_name
	* @param datatype
	*/
	void add_data_column(const std::string& column_name, tiledb_datatype_t datatype);

	/**
	* @brief add vector<tiledb_datatype_t> data column
	* @param column_name
	* @param datatype
	*/
	void add_vector_column(const std::string& column_name, tiledb_datatype_t datatype);

	/**
	* @brief get int32 vector data
	*/
	const std::vector<int>& get_int32_vector(const std::string& column_name);

	/**
	* @brief get uint32 vector data
	*/
	const std::vector<uint32_t>& get_uint32_vector(const std::string& column_name);

	/**
	* @brief get int64 vector data
	*/
	const std::vector<int64_t>& get_int64_vector(const std::string& column_name);

	/**
	* @brief get uint64 vector data
	*/
	const std::vector<uint64_t>& get_uint64_vector(const std::string& column_name);

	/**
	* @brief get double vector data
	*/
	const std::vector<double>& get_double_vector(const std::string& column_name);

	/**
	* @brief get string vector data
	*/
	const std::vector<std::string>& get_string_vector(const std::string& column_name);

protected:
	std::unordered_map<std::string, std::shared_ptr<tiledb::ColumnData> > columns_; ///< column data map

	static std::shared_ptr<tiledb::ColumnData> empty_columndata_;

	static std::vector<int> empty_int32_vector_;
	static std::vector<uint32_t> empty_uint32_vector_;
	static std::vector<int64_t> empty_int64_vector_;
	static std::vector<uint64_t> empty_uint64_vector_;
	static std::vector<double> empty_double_vector_;
	static std::vector<std::string> empty_string_vector_;

	static std::vector<std::vector<int> > empty_int32_vector_of_vector_;
	static std::vector<std::vector<uint32_t> > empty_uint32_vector_of_vector_;
	static std::vector<std::vector<int64_t> > empty_int64_vector_of_vector_;
	static std::vector<std::vector<uint64_t> > empty_uint64_vector_of_vector_;
	static std::vector<std::vector<double> > empty_double_vector_of_vector_;
	static std::vector<std::vector<std::string> > empty_string_vector_of_vector_;


};



}//namespace

#endif
