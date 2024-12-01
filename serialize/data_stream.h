#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

namespace melon
{
  namespace serialize
  {
    class DataStream
    {
      public:
        enum DataType
        {
          bool_type = 1,
          char_type,
          int32_type,
          int64_type,
          float_type,
          double_type,
          string_type,
        };
        
        DataStream();
        ~DataStream() = default;

        void write(bool value);
        void write(char value);
        void write(int32_t value);
        void write(int64_t value);
        void write(float value);
        void write(double value);
        void write(const char* value);
        void write(const std::string& value);
        void write(const char* data, int len);

        DataStream& operator<<(bool value);
        DataStream& operator<<(char value);
        DataStream& operator<<(int32_t value);
        DataStream& operator<<(int64_t value);
        DataStream& operator<<(float value);
        DataStream& operator<<(double value);
        DataStream& operator<<(const char* value);
        DataStream& operator<<(const std::string& value);

        void show() const;

      private:
        void reserve(int len);

      private:
        std::vector<char> m_buffer;
        int m_index;
    };
  }
}
