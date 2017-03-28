#pragma once

namespace IlluminatiConfirmed
{
    template<class Tp>
    class unique_ptr
    {
    public:
        explicit unique_ptr(Tp *ptr = nullptr) : m_ptr(ptr) { }
        explicit unique_ptr(Tp &obj) : m_ptr(&obj) { }
        unique_ptr(unique_ptr &other) = delete;
        ~unique_ptr() { delete m_ptr; }
        unique_ptr& operator=(unique_ptr &) = delete;
        Tp* operator=(Tp *rhs) = delete;
        Tp operator*() { return *m_ptr; }
        Tp* operator->() { return m_ptr; }
        void reset( Tp * ptr) { if (m_ptr != nullptr) delete m_ptr; m_ptr = ptr; }
        Tp* release() { Tp *temp = m_ptr; m_ptr = nullptr; return temp; }
    private:
        Tp *m_ptr;
    };
}
