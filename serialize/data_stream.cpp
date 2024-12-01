#include "serialize/data_stream.h"

using namespace melon::serialize;

DataStream::DataStream()
  : m_index(0)
{}

void DataStream::write(const char* data, int len)
{
  reserve(len);
  int size = m_buffer.size();
  m_buffer.resize(size + len);
  std::memcpy(&m_buffer[size], data, len);
}

void DataStream::write(bool value)
{
  char type = DataType::bool_type;
  write((char*)(&type), sizeof(char));
  write((char*)(&value), sizeof(char));
}

void DataStream::write(char value)
{
  char type = DataType::char_type;
  write((char*)(&type), sizeof(char));
  write((char*)(&value), sizeof(char));
}

void DataStream::write(int32_t value)
{
  char type = DataType::int32_type;
  write((char*)(&type), sizeof(char));
  write((char*)(&value), sizeof(int32_t));
}

void DataStream::write(int64_t value)
{
  char type = DataType::int64_type;
  write((char*)(&type), sizeof(char));
  write((char*)(&value), sizeof(int64_t));
}

void DataStream::write(float value)
{
  char type = DataType::float_type;
  write((char*)(&type), sizeof(char));
  write((char*)(&value), sizeof(float));
}

void DataStream::write(double value)
{
  char type = DataType::double_type;
  write((char*)(&type), sizeof(char));
  write((char*)(&value), sizeof(double));
}

void DataStream::write(const char* value)
{
  char type = DataType::string_type;
  write((char*)(&type), sizeof(char));

  int32_t len = strlen(value);
  write(len);

  write(value, len);
}

void DataStream::write(const std::string& value)
{
  write(value.c_str());
}

void DataStream::write(const Serializable& value)
{
  value.serialize(*this);
}

DataStream& DataStream::operator<<(bool value)
{
  write(value);
  return *this;
}

DataStream& DataStream::operator<<(char value)
{
  write(value);
  return *this;
}

DataStream& DataStream::operator<<(int32_t value)
{
  write(value);
  return *this;
}

DataStream& DataStream::operator<<(int64_t value)
{
  write(value);
  return *this;
}

DataStream& DataStream::operator<<(float value)
{
  write(value);
  return *this;
}

DataStream& DataStream::operator<<(double value)
{
  write(value);
  return *this;
}

DataStream& DataStream::operator<<(const char* value)
{
  write(value);
  return *this;
}

DataStream& DataStream::operator<<(const std::string& value)
{
  write(value);
  return *this;
}

DataStream& DataStream::operator<<(const Serializable& value)
{
  write(value);
  return *this;
}


void DataStream::show() const
{
  int size = m_buffer.size();
  std::cout << "Data size = " << size << '\n';
    
  int i = 0;
  while (i < size)
  {
    switch ((DataType)(m_buffer[i]))
    {
      case DataType::bool_type:
        if ((int)(m_buffer[ ++ i]) == 0)
          std::cout << "false";
        else 
          std::cout << "true";
        ++ i;
        break;
      case DataType::char_type:
        std::cout << m_buffer[ ++ i];
        ++ i;
        break;
      case DataType::int32_type:
        std::cout << *((int32_t*)(&m_buffer[ ++ i]));
        i += 4;
        break;
      case DataType::int64_type:
        std::cout << *((int64_t*)(&m_buffer[ ++ i]));
        i += 8;
        break;
      case DataType::float_type:
        std::cout << *((float*)(&m_buffer[ ++ i]));
        i += 4;
        break;
      case DataType::double_type:
        std::cout << *((double*)(&m_buffer[ ++ i]));
        i += 8;
        break;
      case DataType::string_type:
        if ((DataType)(m_buffer[ ++ i]) == DataType::int32_type)
        {
          int32_t len = *((int32_t*)(&m_buffer[ ++ i]));
          i += 4;
          std::cout << std::string(&m_buffer[i], len);
          i += len;
        }
        else
        {
          throw std::logic_error("Invalid string length.\n");
        }
        break;
      default:
        std::cout << "Invalid data type." << '\n';
        break;
    }
  }
}

bool DataStream::read(char* data, int len)
{
  std::memcpy(data, (char*)(&m_buffer[m_index]), len);
  m_index += len;
  return true;
}

bool DataStream::read(bool& value)
{
  if (m_buffer[m_index] != DataType::bool_type)
    return false;
  ++ m_index;
  value = m_buffer[m_index];
  ++ m_index;
  return true;
}

bool DataStream::read(char& value)
{
  if (m_buffer[m_index] != DataType::char_type)
    return false;
  ++ m_index;
  value = m_buffer[m_index];
  ++ m_index;
  return true;
}

bool DataStream::read(int32_t& value)
{
  if (m_buffer[m_index] != DataType::int32_type)
    return false;
  ++ m_index;
  value = *((int32_t*)(&m_buffer[m_index]));
  m_index += 4;
  return true;
}

bool DataStream::read(int64_t& value)
{
  if (m_buffer[m_index] != DataType::int64_type)
    return false;
  ++ m_index;
  value = *((int64_t*)(&m_buffer[m_index]));
  m_index += 8;
  return true;
}

bool DataStream::read(float& value)
{
  if (m_buffer[m_index] != DataType::float_type)
    return false;
  ++ m_index;
  value = *((float*)(&m_buffer[m_index]));
  m_index += 4;
  return true;
}

bool DataStream::read(double& value)
{
  if (m_buffer[m_index] != DataType::double_type)
    return false;
  ++ m_index;
  value = *((double*)(&m_buffer[m_index]));
  m_index += 8;
  return true;
}

bool DataStream::read(std::string& value)
{
  if (m_buffer[m_index] != DataType::string_type)
    return false;
  ++ m_index;

  int32_t len = 0;
  read(len);
  if (len < 0)
    return false;

  value.assign((char*)(&m_buffer[m_index]), len);
  m_index += len;
  return true;
}

bool DataStream::read(Serializable& value)
{
  return value.unserialize(*this);
}

DataStream& DataStream::operator>>(bool& value)
{
  read(value);
  return *this;
}

DataStream& DataStream::operator>>(char& value)
{
  read(value);
  return *this;
}

DataStream& DataStream::operator>>(int32_t& value)
{
  read(value);
  return *this;
}

DataStream& DataStream::operator>>(int64_t& value)
{
  read(value);
  return *this;
}

DataStream& DataStream::operator>>(float& value)
{
  read(value);
  return *this;
}

DataStream& DataStream::operator>>(double& value)
{
  read(value);
  return *this;
}

DataStream& DataStream::operator>>(std::string& value)
{
  read(value);
  return *this;
}

DataStream& DataStream::operator>>(Serializable& value)
{
  read(value);
  return *this;
}

void DataStream::reserve(int len)
{
  int size = m_buffer.size();
  int capacity = m_buffer.capacity();
  if (capacity < size + len)
  {
    while (capacity < size + len)
    {
      if (capacity == 0)
        capacity = 1;
      else
        capacity *= 2;
    }
    m_buffer.reserve(capacity);
  }
}

