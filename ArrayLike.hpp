#include <cstddef>

template <typename t>
class ArrayLike
{
    struct Accessor
    {
        Accessor(ArrayLike& parent, size_t index):
            parent(parent),
            index(index)
        {}

        size_t index;
        ArrayLike& parent;

        // Assignment to Accessor is a call to write
        int operator=(const int value)
        {
            parent.write(index, value);
        }

        // Referencing an Accessor is a call to read
        operator t() const
        {
            return parent.read(index);
        }
    };

    typedef t (*read_function)(size_t);
    typedef void (*write_function)(size_t, t);

    size_t index;
    read_function read;
    write_function write;

public:
    ArrayLike(read_function read, write_function write, size_t index=0):
        index(index),
        read(read),
        write(write)
    {}

    Accessor operator[](size_t idx)
    {
        return Accessor(*this, index + idx);
    };

    Accessor operator*()
    {
        return Accessor(*this, index);
    }

    ArrayLike operator+(size_t offset)
    {
        return ArrayLike(read, write, index+offset);
    }
};
