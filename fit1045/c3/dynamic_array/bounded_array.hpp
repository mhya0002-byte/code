#ifndef _BOUNDED_ARRAY_H
#define _BOUNDED_ARRAY_H 1

class array_full
{
};

class array_invalid_index
{
};

template <typename T, int MAX_CAPACITY>
class bounded_array
{
    int size;
    T data[MAX_CAPACITY];

public:
    bounded_array()
    {
        size = 0;
    }

    int length()
    {
        return size;
    }

    int capacity()
    {
        return MAX_CAPACITY;
    }

    void add(T value)
    {
        if (size >= MAX_CAPACITY)
        {
            throw array_full();
        }

        data[size] = value;

        size++;
    }

    T &get(int index)
    {
        if (index < 0 || index >= size)
        {
            throw array_invalid_index();
        }
        return data[index];
    }

    const T &get(int index) const
    {
        if (index < 0 || index >= size)
        {
            throw array_invalid_index();
        }
        return data[index];
    }
    T &operator[](int index)
    {
        return get(index);
    }
    const T &operator[](int index) const
    {
        return get(index);
    }
    void remove(int index)
    {
        if (index < 0 || index >= size)
        {
            throw array_invalid_index();
        }

        for (int i = index + 1; i < size; i++)
        {
            data[i - 1] = data[i];
        }
        size--;
    }

    void fill(int count, T value)
    {
        if (count + size > MAX_CAPACITY)
        {
            throw array_full();
        }

        if (count >= 0)
        {
            for (int i = 0; i < count; i++)
            {
                add(value);
            }
        }
    }
};
#endif /* _BOUNDED_ARRAY_H */