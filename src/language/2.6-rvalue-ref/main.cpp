#include <algorithm>
#include <iostream>

class DataObject
{
public:
    DataObject()
        : data_(nullptr),
          size_(0)
    {}

    DataObject(int n, int v)
        : data_(new int[n]),
          size_(n)
    {
        std::fill(data_, data_ + size_, v);
    }

    DataObject(const DataObject &src)
    {
        std::cout << "Lvalue ctor called." << std::endl;
        data_ = new int[src.size_];
        // Expensive copy operation
        std::copy(src.data_, src.data_ + src.size_, data_);
        size_ = src.size_;
    }

    DataObject(DataObject &&src)
        : // Data (ownership) is moved
          data_(src.data_),
          size_(src.size_)
    {
        std::cout << "Rvalue ctor called." << std::endl;
        // This operation destroys the source, but this is okay, as src
        // is an rvalue
        src.data_ = nullptr;
        src.size_ = 0;
    }

    virtual ~DataObject()
    {
        delete[] data_;
    }

    int getSize() const
    {
        return size_;
    }

    /*!
     * We instance of this class can also either be an lvalue or rvalue,
     * so we can decorate its members accordingly: this method is
     * invoked for lvalue instances.
     */
    int *getData() const&
    {
        std::cout << "Lvalue getData method called." << std::endl;
        int *result(new int[size_]);
        std::copy(data_, data_ + size_, result);
        return result;
    }

    /*!
     * This method is invoked for rvalue class instances, as specified with
     * the && decorator.
     */
    int *getData() &&
    {
        std::cout << "Rvalue getData method called." << std::endl;
        int *result = data_;
        data_ = nullptr;
        size_ = 0;
        return result;
    }

    /*!
     * This assignment operator is used when assigning lvalues: the
     * data is copied (which may be an expensive operation, especially
     * for larger data payloads).
     */
    void operator=(const DataObject &src)
    {
        std::cout << "Lvalue assignment operator called." << std::endl;

        size_ = 0;
        delete[] data_;
        data_ = new int[src.size_];
        // Expensive copy operation
        std::copy(src.data_, src.data_ + src.size_, data_);
        size_ = src.size_;
    }

    /*!
     * This assignment operator is used when assigning rvalues:
     * the data (ownership) is simply moved from the \c src (which
     * must not be used thereafter, as its internal state is destroyed).
     */
    void operator=(DataObject &&src)
    {
        std::cout << "Rvalue assignment operator called." << std::endl;

        delete[] data_;
        // Data (ownership) is moved
        data_ = src.data_;
        size_ = src.size_;
        // This operation destroys the source, but this is okay, as src
        // is an rvalue
        src.size_ = 0;
        src.data_ = nullptr;
    }

private:
    int *data_;
    int size_;
};

int main(int argc, char *argv[])
{
    DataObject dataObject1(100, 10);
    // dataObject1 is a named instance (lvalue), so the lvalue ctor is called here
    DataObject dataObject2(dataObject1);
    // Here the rvalue ctor is called;
    DataObject dataObject3(DataObject(200, 20));

    // dataObject3 is a named instance (lvalue), so the assignment operator is called
    dataObject1 = dataObject3;
    // Here the rvalue assignment operator is called
    dataObject2 = DataObject(300, 30);

    // dataObject1 is a named instance (lvalue), so the lvalue getData() method is called
    int *data1 = dataObject1.getData();
    delete[] data1;

    // Here the rvalue getData() method is called
    int *data2 = DataObject(400, 40).getData();
    delete[] data2;

    return 0;
}
