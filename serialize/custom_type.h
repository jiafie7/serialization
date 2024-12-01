#pragma once

#include "serialize/data_stream.h"
#include "serialize/serializable.h"

using namespace melon::serialize;

namespace melon
{
  namespace serialize
  {
    class Student : public Serializable
    {
      public:
        Student() = default;
        Student(const std::string& name, int age)
          : m_name(name), m_age(age)
        {}
        ~Student() = default;

        virtual void serialize(DataStream& stream) const
        {
          char type = DataStream::custom_type;
          stream.write((char*)(&type), sizeof(char));
          stream.write(m_name);
          stream.write(m_age);
        }

        virtual bool unserialize(DataStream& stream)
        {
          char type;
          stream.read((char*)(&type), sizeof(char));
          if (type != DataStream::custom_type)
            return false;
          stream.read(m_name);
          stream.read(m_age);
          return true;
        }

        void show() const
        {
          std::cout << "name = " << m_name << ", age = " << m_age << '\n';
        }

      private:
        std::string m_name;
        int m_age;
    };

    class Fruit : public Serializable
    {
      public:
        Fruit() = default;
        Fruit(const std::string& name, const std::string& color)
          : m_name(name), m_color(color)
        {}
        ~Fruit() = default;

        void show() const
        {
          std::cout << "name = " << m_name << ", color = " << m_color << '\n';
        }

        SERIALIZE(m_name, m_color);

      private:
        std::string m_name;
        std::string m_color;
    };  
  }
}
