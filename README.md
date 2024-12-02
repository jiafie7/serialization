# Serialization

The DataStream library is a comprehensive C++ serialization solution designed to handle a wide range of data types. It supports serialization and unserialization of basic types, complex types, and custom types, making it ideal for saving and transmitting structured data.

## Features

1. **Supported Multiple Data Types**

   - **Primitive Types**: bool, char, int32_t, int64_t, float, double, and string.
   - **Container Types**: vector, list, map, set.
   - **Custom Types**: Extendable for user-defined classes using the Serializable interface.

2. **Serialization and Unserialization**

   - Serialize and unserialize data with intuitive APIs.
     - Overloaded write() and read() methods for various types.
     - Operator overloads (<< and >>) for concise syntax.
   - Support for multiple arguments serialization/deserialization using write_args() and read_args().

3. **Cross-Platform Compatibility**

   - Handles both **Big-Endian** and **Little-Endian** byte orders automatically.

4. **File I/O**
   - Save serialized data to a file with save().
   - Load serialized data from a file using load().

## Getting Started

1. Prerequisites

   - C++ 11 or later

2. Clone the Repository

```bash
git clone https://github.com/jiafie7/serialization.git
cd serialization
```

3. Build the Project

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

1. Example code

```c
#include "serialize/data_stream.h"
#include "serialize/custom_type.h"

using namespace melon::serialize;

int main()
{
  // basic type
  DataStream ds1;
  ds1 << false << 123 << "hello world";
  bool b;
  int i;
  std::string s;
  ds1 >> b >> i >> s;
  std::cout << "b = " << b << ", i = " << i << ", s = " << s << '\n';

  // composite type
  DataStream ds2;
  std::map<char, int> v1 = {{'a', 7}, {'b', 77}, {'c', 777}};
  ds2 << v1;

  std::map<char, int> v2;
  ds2 >> v2;
  for (auto it = v2.begin(); it != v2.end(); ++ it)
    std::cout << it->first << ' ' << it->second << '\n';

  // custom type
  Fruit f1("Banana", "yellow");
  DataStream ds4;
  ds4 << f1;
  ds4.save("./../fruit.out");

  Fruit f2;
  DataStream ds5;
  ds5.load("./../fruit.out");
  ds5 >> f2;
  f2.show();

  return 0;
}
```

2. Run the Example

```bash
./main
```

3. Output

```bash
b = 0, i = 123, s = hello world
a 7
b 77
c 777
name = Banana, color = yellow
```

## API Reference

### Serialization Methods

- void write(...): Serialize data into the buffer. Supported overloads for:
- Primitive types (`bool`, `char`, `int32_t`, `double`, etc.).
- Containers (`vector`, `map`, etc.).
- Custom types implementing the Serializable interface.
- DataStream& operator<<(...): Overloaded insertion operator for concise serialization syntax.

### Unserialization Methods

- bool read(...): Deserialize data from the buffer. Supported overloads for:
- Primitive types (bool, char, int32_t, etc.).
- Containers (std::vector, std::map, etc.).
- Custom types implementing the Serializable interface.
- DataStream& operator>>(...): Overloaded extraction operator for concise deserialization syntax.

### Multi-Argument Support

- void write_args(...): Serialize multiple arguments at once.
- bool read_args(...): Deserialize multiple arguments at once.

### Buffer Operations

- int size(): Get the size of the serialized data.
- void clear(): Clear the buffer.
- void reset(): Reset the read position.

### File Operations

- void save(const std::string& filename): Save the buffer to a file.
- void load(const std::string& filename): Load data into the buffer from a file.

### Byte Order Handling

- Automatic detection and handling of endianness using set_byte_order().

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature-name`.
3. Commit your changes: `git commit -m "Add feature-name"`.
4. Push to your branch: `git push origin feature-name`.
5. Open a pull request.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.
