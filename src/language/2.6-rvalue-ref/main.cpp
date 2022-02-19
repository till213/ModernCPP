#include <algorithm>
#include <iostream>

class DataObject
{
public:
    DataObject()
        : m_data(nullptr),
          m_size(0)
    {}

    DataObject(int n, int v)
        : m_data(new int[n]),
          m_size(n)
    {
        std::fill(m_data, m_data + m_size, v);
    }

    DataObject(const DataObject &src)
    {
        std::cout << "Lvalue ctor called." << std::endl;
        m_data = new int[src.m_size];
        // Expensive copy operation
        std::copy(src.m_data, src.m_data + src.m_size, m_data);
        m_size = src.m_size;
    }

    DataObject(DataObject &&src)
        : // Data (ownership) is moved
          m_data(src.m_data),
          m_size(src.m_size)
    {
        std::cout << "Rvalue ctor called." << std::endl;
        // This operation destroys the source, but this is okay, as src
        // is an rvalue
        src.m_data = nullptr;
        src.m_size = 0;
    }

    virtual ~DataObject()
    {
        delete[] m_data;
    }

    int getSize() const
    {
        return m_size;
    }

    /*!
     * We instance of this class can also either be an lvalue or rvalue,
     * so we can decorate its members accordingly: this method is
     * invoked for lvalue instances.
     */
    int *getData() const&
    {
        std::cout << "Lvalue getData method called." << std::endl;
        int *result(new int[m_size]);
        std::copy(m_data, m_data + m_size, result);
        return result;
    }

    /*!
     * This method is invoked for rvalue class instances, as specified with
     * the && decorator.
     */
    int *getData() &&
    {
        std::cout << "Rvalue getData method called." << std::endl;
        int *result = m_data;
        m_data = nullptr;
        m_size = 0;
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

        m_size = 0;
        delete[] m_data;
        m_data = new int[src.m_size];
        // Expensive copy operation
        std::copy(src.m_data, src.m_data + src.m_size, m_data);
        m_size = src.m_size;
    }

    /*!
     * This assignment operator is used when assigning rvalues:
     * the data (ownership) is simply moved from the \c src (which
     * must not be used thereafter, as its internal state is destroyed).
     */
    void operator=(DataObject &&src)
    {
        std::cout << "Rvalue assignment operator called." << std::endl;

        delete[] m_data;
        // Data (ownership) is moved
        m_data = src.m_data;
        m_size = src.m_size;
        // This operation destroys the source, but this is okay, as src
        // is an rvalue
        src.m_size = 0;
        src.m_data = nullptr;
    }

private:
    int *m_data;
    int m_size;
};

int main(int, char *[])
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
