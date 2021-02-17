#include "tiledb_cxx_column.h"

namespace tiledb {
	ColumnData::ColumnData():
		name_(""),
		datatype_(tiledb_datatype_t::TILEDB_ANY),
		offsets_(NULL), ///< offset buffer for variable-sized
		offset_nelements_(0), ///< for variable-sized
		data_(NULL), ///< data buffer 
		data_nelements_(0), ///< number of data elements
		data_element_size_(sizeof(char)), ///< byte size of data element
		is_dim_(false), ///< is dimension or not
		is_var_(false),
		lower_bound_(""),
		upper_bound_("")
	{
	}

	const std::string& ColumnData::name()
	{
		return name_;
	}
	void ColumnData::set_name(const std::string& s)
	{
		name_ = s;
	}

	tiledb_datatype_t ColumnData::datatype()
	{
		return datatype_;
	}
	void ColumnData::set_datatype(tiledb_datatype_t t)
	{
		datatype_ = t;
	}

	uint64_t* ColumnData::offsets()
	{
		return offsets_;
	}

	uint64_t ColumnData::offset_nelements()
	{
		return offset_nelements_;
	}

	uint64_t& ColumnData::offset_bytes_size()
	{
		return offset_bytes_size_;
	}
	//  void set_oofset_nelements(uint64_t sz);

	void* ColumnData::data()
	{
		return data_;
	}

	uint64_t ColumnData::data_nelements()
	{
		return data_nelements_;
	}
	//  void set_data_nelements();

	uint64_t& ColumnData::data_bytes_size()
	{
		return data_bytes_size_;
	}

	size_t& ColumnData::data_element_size()
	{
		return data_element_size_;
	}
	//  void set_data_element_size(size_t sz);

	bool ColumnData::is_dim()
	{
		return is_dim_;
	}
	void ColumnData::set_is_dim(bool b)
	{
		is_dim_ = b;
	}

	bool ColumnData::is_var()
	{
		return is_var_;
	}
	void ColumnData::set_is_var(bool b)
	{
		is_var_ = b;
	}

	const std::string& ColumnData::lower_bound()
	{
 
		return lower_bound_;
	}

 
	void ColumnData::set_lower_bound(const std::string& s)
	{
		lower_bound_ = s;
	}

 
	const std::string& ColumnData::upper_bound()
	{
		return upper_bound_;
	}
 
	void ColumnData::set_upper_bound(const std::string& s)
	{
		upper_bound_ = s;
	}

	bool ColumnData::is_buffer_empty()
	{
		return data_ != NULL;
	}

	

	void ColumnData::reset_buffer()
	{
 
		offsets_ = NULL;  ///< offset buffer for variable-sized
		offset_nelements_ = 0; ///< for variable-sized
		data_ = NULL;  ///< data buffer 
		data_nelements_ = 0; ///< number of data elements
		data_bytes_size_ = 0;
 
	}

	int ColumnData::resize_vector(uint64_t sz)
	{
		//implemented in derived class
		return -1;
	}

 
	int ColumnData::resize_bytes_vector(uint64_t sz)
	{
		//implemented in derived class
		return -1;
	}

	int ColumnData::set_buffer()
	{
		//implemented in derived class
		return -1;
		
	}

	int ColumnData::read_buffer()
	{
		//implemented in derived class
		return -1;

	}

	void ColumnData::clear()
	{
		reset_buffer();
	}
 

/////////
 
	 

//////ColumnDataMap

	std::shared_ptr<tiledb::ColumnData> ColumnDataMap::empty_columndata_ = std::shared_ptr<tiledb::ColumnData>(new tiledb::ColumnData());

	std::vector<int> ColumnDataMap::empty_int32_vector_ = std::vector<int>();
	std::vector<uint32_t> ColumnDataMap::empty_uint32_vector_ = std::vector<uint32_t>();
	std::vector<int64_t> ColumnDataMap::empty_int64_vector_ = std::vector<int64_t>();
	std::vector<uint64_t> ColumnDataMap::empty_uint64_vector_ = std::vector<uint64_t>();
	std::vector<double> ColumnDataMap::empty_double_vector_ = std::vector<double>();
	std::vector<std::string> ColumnDataMap::empty_string_vector_ = std::vector<std::string>();

	std::vector<std::vector<int> > ColumnDataMap::empty_int32_vector_of_vector_ = std::vector<std::vector<int> >();
	std::vector<std::vector<uint32_t> > ColumnDataMap::empty_uint32_vector_of_vector_ = std::vector<std::vector<uint32_t> >();
	std::vector<std::vector<int64_t> > ColumnDataMap::empty_int64_vector_of_vector_ = std::vector<std::vector<int64_t> >();
	std::vector<std::vector<uint64_t> > ColumnDataMap::empty_uint64_vector_of_vector_ = std::vector<std::vector<uint64_t> >();
	std::vector<std::vector<double> > ColumnDataMap::empty_double_vector_of_vector_ = std::vector<std::vector<double> >();
	std::vector<std::vector<std::string> > ColumnDataMap::empty_string_vector_of_vector_ = std::vector<std::vector<std::string> >();

	std::unordered_map<std::string, std::shared_ptr<tiledb::ColumnData> > & ColumnDataMap::columns()
	{
		return columns_;
	}

	bool ColumnDataMap::has_column(const std::string& column_name)
	{
		return columns_.find(column_name) != columns_.end();
	}

 
	uint64_t* ColumnDataMap::offsets(const std::string& column_name)
	{
		return (columns_.find(column_name) == columns_.end()) ? nullptr : columns_[column_name]->offsets();
	}

 
	uint64_t ColumnDataMap::offset_nelements(const std::string& column_name)
	{
		return (columns_.find(column_name) == columns_.end()) ? 0 : columns_[column_name]->offset_nelements();
	}
	 
 
	uint64_t ColumnDataMap::offset_bytes_size(const std::string& column_name)
	{
		return (columns_.find(column_name) == columns_.end()) ? 0 : columns_[column_name]->offset_bytes_size();
	}
 
	void* ColumnDataMap::data(const std::string& column_name)
	{
		return (columns_.find(column_name) == columns_.end()) ? nullptr : columns_[column_name]->data();
	}

 
	uint64_t ColumnDataMap::data_nelements(const std::string& column_name)
	{
		return (columns_.find(column_name) == columns_.end()) ? 0 : columns_[column_name]->data_nelements();
	}
	//  void set_data_nelements();

 
	uint64_t ColumnDataMap::data_bytes_size(const std::string& column_name)
	{
		return (columns_.find(column_name) == columns_.end()) ? 0 : columns_[column_name]->data_bytes_size();
	}

 
	size_t ColumnDataMap::data_element_size(const std::string& column_name)
	{
		return (columns_.find(column_name) == columns_.end()) ? 0 : columns_[column_name]->data_element_size();
	}
	//  void set_data_element_size(size_t sz);

 
	bool ColumnDataMap::is_dim(const std::string& column_name)
	{
		return (columns_.find(column_name) == columns_.end()) ? false : columns_[column_name]->is_dim();
	}
 
	void ColumnDataMap::set_is_dim(const std::string& column_name, bool b)
	{
		if (columns_.find(column_name) != columns_.end())
		{
			columns_[column_name]->set_is_dim(b);
		}
	}

 
	bool ColumnDataMap::is_var(const std::string& column_name)
	{
		return (columns_.find(column_name) == columns_.end()) ? false : columns_[column_name]->is_var();
	}
 
	void ColumnDataMap::set_is_var(const std::string& column_name, bool b)
	{
		if (columns_.find(column_name) != columns_.end())
		{
			columns_[column_name]->set_is_var(b);
		}
	}

 
	const std::string ColumnDataMap::lower_bound(const std::string& column_name)
	{
		return (columns_.find(column_name) == columns_.end()) ? "" : columns_[column_name]->lower_bound();
	}

 
	void ColumnDataMap::set_lower_bound(const std::string& column_name, const std::string& s)
	{
		if (columns_.find(column_name) != columns_.end())
		{
			columns_[column_name]->set_lower_bound(s);
		}
	}

 
	const std::string ColumnDataMap::upper_bound(const std::string& column_name)
	{
		return (columns_.find(column_name) == columns_.end()) ? "" : columns_[column_name]->upper_bound();
	}

 
	void ColumnDataMap::set_upper_bound(const std::string& column_name, const std::string& s)
	{
		if (columns_.find(column_name) != columns_.end())
		{
			columns_[column_name]->set_upper_bound(s);
		}
	}

 
	bool ColumnDataMap::is_buffer_empty(const std::string& column_name)
	{
		return (columns_.find(column_name) == columns_.end()) ? false : columns_[column_name]->is_buffer_empty();
	}

	bool ColumnDataMap::is_empty()
	{
		return columns_.size() == 0;
	}

	std::shared_ptr<tiledb::ColumnData>& ColumnDataMap::column_by_name(const std::string& column_name)
	{
		return (columns_.find(column_name) == columns_.end()) ? empty_columndata_ : columns_[column_name];
	}

	uint32_t ColumnDataMap::ncol()
	{
		return (uint32_t)columns_.size();
	}

	uint64_t ColumnDataMap::nrows(const std::string& column_name)
	{
		if (columns_.size() == 0) { return 0; }
		if (columns_.find(column_name) != columns_.end())
		{
			return columns_[column_name]->data_nelements();
		}
		else
		{
			return columns_.begin()->second->data_nelements();
		}
	}

	std::vector<std::string> ColumnDataMap::dimension_names()
	{
		std::vector<std::string> result;
		for (auto& column : columns_)
		{
			if (column.second->is_dim())
			{
				result.push_back(column.first);
			}
		}
		return result;
	}
 
	std::vector<tiledb_datatype_t> ColumnDataMap::dimension_datatypes()
	{
		std::vector<tiledb_datatype_t> result;
		for (auto& column : columns_)
		{
			if (column.second->is_dim())
			{
				result.push_back(column.second->datatype());
			}
		}
		return result;
	}

	std::vector<std::string> ColumnDataMap::attribute_names()
	{
		std::vector<std::string> result;
		for (auto& column : columns_)
		{
			if (!column.second->is_dim())
			{
				result.push_back(column.first);
			}
		}
		return result;
	}

	std::vector<tiledb_datatype_t> ColumnDataMap::attribute_datatypes()
	{
		std::vector<tiledb_datatype_t> result;
		for (auto& column : columns_)
		{
			if (!column.second->is_dim())
			{
				result.push_back(column.second->datatype());
			}
		}
		return result;
	}

	void ColumnDataMap::add_column(const std::shared_ptr<tiledb::ColumnData>& column)
	{
		if (!column)
		{
			return;
		}
		columns_[column->name()] = column;
	}
 
	void ColumnDataMap::add_data_column(const std::string& column_name, tiledb_datatype_t datatype)
	{
		if (columns_.find(column_name) != columns_.end())
		{
			std::cout << "Columns::add_data_column, already has column:" << column_name << std::endl;
			return;
		}
		if (column_name.empty())
		{
			return;
		}
		if (datatype == tiledb_datatype_t::TILEDB_INT32)
		{
			columns_[column_name] = std::shared_ptr<tiledb::Int32ColumnData>(new tiledb::Int32ColumnData());
			columns_[column_name]->set_name(column_name);
			columns_[column_name]->set_datatype(datatype);
			columns_[column_name]->data_element_size() = sizeof(int32_t);
			columns_[column_name]->set_is_var(false);
		}
		else if (datatype == tiledb_datatype_t::TILEDB_UINT32)
		{
			columns_[column_name] = std::shared_ptr<tiledb::UInt32ColumnData>(new tiledb::UInt32ColumnData());
			columns_[column_name]->set_name(column_name);
			columns_[column_name]->set_datatype(datatype);
			columns_[column_name]->data_element_size() = sizeof(uint32_t);
			columns_[column_name]->set_is_var(false);
		}
		else if (datatype == tiledb_datatype_t::TILEDB_INT64)
		{
			columns_[column_name] = std::shared_ptr<tiledb::Int64ColumnData>(new tiledb::Int64ColumnData());
			columns_[column_name]->set_name(column_name);
			columns_[column_name]->set_datatype(datatype);
			columns_[column_name]->data_element_size() = sizeof(int64_t);
			columns_[column_name]->set_is_var(false);
		}
		else if (datatype == tiledb_datatype_t::TILEDB_UINT64)
		{
			columns_[column_name] = std::shared_ptr<tiledb::UInt64ColumnData>(new tiledb::UInt64ColumnData());
			columns_[column_name]->set_name(column_name);
			columns_[column_name]->set_datatype(datatype);
			columns_[column_name]->data_element_size() = sizeof(uint64_t);
			columns_[column_name]->set_is_var(false);
		}
		else if (datatype == tiledb_datatype_t::TILEDB_FLOAT64)
		{
			columns_[column_name] = std::shared_ptr<tiledb::DoubleColumnData>(new tiledb::DoubleColumnData());
			columns_[column_name]->set_name(column_name);
			columns_[column_name]->set_datatype(datatype);
			columns_[column_name]->data_element_size() = sizeof(double);
			columns_[column_name]->set_is_var(false);
		}
		else if (datatype == tiledb_datatype_t::TILEDB_CHAR
			|| datatype == tiledb_datatype_t::TILEDB_STRING_ASCII
			|| datatype == tiledb_datatype_t::TILEDB_STRING_UTF8
			)
		{
			columns_[column_name] = std::shared_ptr<tiledb::StringColumnData>(new tiledb::StringColumnData());
			columns_[column_name]->set_name(column_name);
			columns_[column_name]->set_datatype(datatype);
			columns_[column_name]->data_element_size() = sizeof(char);
			columns_[column_name]->set_is_var(true);
		}
		else
		{
			std::cout << "Columns::add_data_column, column:" << column_name << ",type not implemented:" << datatype << std::endl;
		}
	}//void Columns::add_data_column(const std::string& column_name, tiledb_datatype_t datatype)

	void ColumnDataMap::add_vector_column(const std::string& column_name, tiledb_datatype_t datatype)
	{
		if (columns_.find(column_name) != columns_.end())
		{
			std::cout << "Columns::add_vector_column, already has column:" << column_name << std::endl;
			return;
		}
		if (column_name.empty())
		{
			return;
		}
		if (datatype == tiledb_datatype_t::TILEDB_INT32)
		{
			columns_[column_name] = std::shared_ptr<tiledb::VectorColumnData<int> >(new tiledb::VectorColumnData<int>());
			columns_[column_name]->set_name(column_name);
		}
		else if (datatype == tiledb_datatype_t::TILEDB_UINT32)
		{
			columns_[column_name] = std::shared_ptr<tiledb::VectorColumnData<uint32_t> >(new tiledb::VectorColumnData<uint32_t>());
			columns_[column_name]->set_name(column_name);
		}
		else if (datatype == tiledb_datatype_t::TILEDB_INT64)
		{
			columns_[column_name] = std::shared_ptr<tiledb::VectorColumnData<int64_t> >(new tiledb::VectorColumnData<int64_t>());
			columns_[column_name]->set_name(column_name);
		}
		else if (datatype == tiledb_datatype_t::TILEDB_UINT64)
		{
			columns_[column_name] = std::shared_ptr<tiledb::VectorColumnData<uint64_t> >(new tiledb::VectorColumnData<uint64_t>());
			columns_[column_name]->set_name(column_name);
		}
		else if (datatype == tiledb_datatype_t::TILEDB_FLOAT64)
		{
			columns_[column_name] = std::shared_ptr<tiledb::VectorColumnData<double> >(new tiledb::VectorColumnData<double>());
			columns_[column_name]->set_name(column_name);
		}
		else if ( datatype == tiledb_datatype_t::TILEDB_CHAR
			|| datatype == tiledb_datatype_t::TILEDB_STRING_ASCII
			|| datatype == tiledb_datatype_t::TILEDB_STRING_UTF8
			)
		{
			//TODO
			std::cout << "Columns::add_data_column, column:" << column_name << ",type not implemented:" << datatype << std::endl;
		}
		else
		{
			std::cout << "Columns::add_data_column, column:" << column_name << ",type not implemented:" << datatype << std::endl;
		}

	}//void Columns::add_vector_column(const std::string& column_name, tiledb_datatype_t datatype)


 
	const std::vector<int>& ColumnDataMap::get_int32_vector(const std::string& column_name)
	{
		if (columns_.find(column_name) == columns_.end())
		{
			return empty_int32_vector_;
		}
		std::shared_ptr<Int32ColumnData> column = std::dynamic_pointer_cast<Int32ColumnData>(columns_[column_name]);
		if (column)
		{
			return column->data_vector();
		}
		else
		{
			return empty_int32_vector_;
		}
	}

 
	const std::vector<uint32_t>& ColumnDataMap::get_uint32_vector(const std::string& column_name)
	{
		if (columns_.find(column_name) == columns_.end())
		{
			return empty_uint32_vector_;
		}
		std::shared_ptr<UInt32ColumnData> column = std::dynamic_pointer_cast<UInt32ColumnData>(columns_[column_name]);
		if (column)
		{
			return column->data_vector();
		}
		else
		{
			return empty_uint32_vector_;
		}
	}

 
	const std::vector<int64_t>& ColumnDataMap::get_int64_vector(const std::string& column_name)
	{
		if (columns_.find(column_name) == columns_.end())
		{
			return empty_int64_vector_;
		}
		std::shared_ptr<Int64ColumnData> column = std::dynamic_pointer_cast<Int64ColumnData>(columns_[column_name]);
		if (column)
		{
			return column->data_vector();
		}
		else
		{
			return empty_int64_vector_;
		}
	}

 
	const std::vector<uint64_t>& ColumnDataMap::get_uint64_vector(const std::string& column_name)
	{
		if (columns_.find(column_name) == columns_.end())
		{
			return empty_uint64_vector_;
		}
		std::shared_ptr<UInt64ColumnData> column = std::dynamic_pointer_cast<UInt64ColumnData>(columns_[column_name]);
		if (column)
		{
			return column->data_vector();
		}
		else
		{
			return empty_uint64_vector_;
		}
	}

 
	const std::vector<double>& ColumnDataMap::get_double_vector(const std::string& column_name)
	{
		if (columns_.find(column_name) == columns_.end())
		{
			return empty_double_vector_;
		}
		std::shared_ptr<DoubleColumnData> column = std::dynamic_pointer_cast<DoubleColumnData>(columns_[column_name]);
		if (column)
		{
			return column->data_vector();
		}
		else
		{
			return empty_double_vector_;
		}
	}

 
	const std::vector<std::string>& ColumnDataMap::get_string_vector(const std::string& column_name)
	{
		if (columns_.find(column_name) == columns_.end())
		{
			return empty_string_vector_;
		}
		std::shared_ptr<StringColumnData> column = std::dynamic_pointer_cast<StringColumnData>(columns_[column_name]);
		if (column)
		{
			return column->data_vector();
		}
		else
		{
			return empty_string_vector_;
		}
	}
	 

}//namespace