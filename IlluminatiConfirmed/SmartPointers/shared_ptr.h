#pragma once

#include <iostream>

using std::size_t;

namespace IlluminatiConfirmed
{
    template<class Tp>
    class shared_ptr
    {
    private:
        class shared_ptr_counter
        {
        public:
            shared_ptr_counter(Tp *data) : m_data(data), m_count(0)
            {
                if (m_data != nullptr) m_count = 1;
            }
            ~shared_ptr_counter() { delete m_data; }
            size_t count() { return m_count; }
            void inc()  { ++m_count; }
            void dec() { --m_count; if (m_count == 0) delete m_data;  }

        private:
            Tp *m_data;
            size_t m_count;
        };

    public:
        // constructors and destructor
        explicit shared_ptr(Tp *ptr = nullptr) : m_ptr(ptr), m_counter(new shared_ptr_counter(ptr)) { }

        // ... (const shared_ptr<Tp>& other) ... ?
        shared_ptr(const shared_ptr &other) : m_ptr(other.m_ptr), m_counter(other.m_counter)
        {
            m_counter->inc();
        }

        ~shared_ptr() { m_counter->dec(); }

        // operators overload
        shared_ptr& operator=(shared_ptr& rhs)
        {
            if (this != &rhs)
            {
                shared_ptr<Tp> buf (rhs);
                std::swap(m_ptr, buf.m_ptr);
                std::swap(m_counter, buf.m_counter);
            }
        }
        Tp& operator*() { return *m_ptr; }
        Tp* operator->() { return m_ptr; }

        // other functions
        void reset(Tp *ptr = nullptr) { m_counter->dec(); m_ptr = ptr; m_counter = new shared_ptr_counter(ptr); }
        size_t use_count() { return m_counter->count(); }

    private:
        Tp *m_ptr;
        shared_ptr_counter *m_counter;
    };
}
