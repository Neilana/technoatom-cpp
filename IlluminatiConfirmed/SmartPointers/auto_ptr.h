#pragma once

namespace IlluminatiConfirmed
{
    template<class Tp>
    class auto_ptr
    {
    public:
        explicit auto_ptr(Tp *ptr = nullptr) : m_ptr(ptr) { }
        explicit auto_ptr(Tp &obj) : m_ptr(&obj) { }
        auto_ptr(auto_ptr &other) : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
        ~auto_ptr() { delete m_ptr; }
        Tp* operator=(Tp *rhs) = delete;
        Tp operator*() { return *m_ptr; }
        Tp* operator->() { return m_ptr; }
        void reset( Tp * ptr) { delete m_ptr; m_ptr = ptr; }
        Tp* release() { Tp *temp = m_ptr; m_ptr = nullptr; return temp; }
        auto_ptr& operator=(auto_ptr &rhs) { m_ptr = rhs.m_ptr; rhs.m_ptr = nullptr; return *this; }
    private:
        Tp *m_ptr;
    };
}
