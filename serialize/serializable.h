#pragma once

namespace melon
{
  namespace serialize
  {
    class DataStream;

    class Serializable
    {
      public:
        virtual void serialize(DataStream& stream) const = 0;
        virtual bool unserialize(DataStream& stream) = 0;
    };
  }
}
