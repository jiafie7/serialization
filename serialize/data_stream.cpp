#include "serialize/data_stream.h"

using namespace melon::serialize;

DataStream::DataStream()
  : m_index(0)
{}

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

void DataStream::write(const char* data, int len)
{
  reserve(len);
  int size = m_buffer.size();
  m_buffer.resize(size + len);
  std::memcpy(&m_buffer[size], data, len);
}

void DataStream::reserve(int len)
{

}

