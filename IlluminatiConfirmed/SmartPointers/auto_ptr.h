#pragma once

namespace IlluminatiConfirmed
{
    template<class Tp>
    class auto_ptr
    {
    public:
        /*!
         * \brief auto_ptr Pointer to an object of type Tp, which is the auto_ptr's template parameter.
         *        If this parameter is 0 the auto_ptr is a null pointer (points to nowhere).
         * \param ptr
         */
        explicit auto_ptr(Tp *ptr = nullptr) : m_ptr(ptr) { }

        /*!
         * \brief auto_ptr An auto_ptr object. Ownership is taken from it, therefore, a releases it.
         *  When the types held by the origin and destination auto_ptrs are different, an implicit conversion must be available between their pointers.
         * \param obj
         */
        auto_ptr(Tp &obj) : m_ptr(&obj) { }

        /*!
         * \brief auto_ptr
         * \param other
         */
        auto_ptr(auto_ptr &other) : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }

        /*!
         * \brief auto_ptr Overload
         * \param other
         */
        auto_ptr(auto_ptr &&other) { std::swap(m_ptr, other.m_ptr); }

        ~auto_ptr() { if (m_ptr != nullptr) delete m_ptr; m_ptr = nullptr; }

        Tp* operator=(Tp *rhs) = delete;

        /*!
         * \brief operator = When the types held by the origin and destination auto_ptrs are different (second constructor version), an implicit conversion must exist between their pointer types.
         * \param other
         */
        auto_ptr& operator=(auto_ptr &rhs)
        {
            if (this != &rhs)
            {
                this->~auto_ptr();
                m_ptr = rhs.m_ptr;
                rhs.m_ptr = nullptr;
            }
            return *this;
        }
        /*!
         * \brief operator = Overload
         * \param rhs
         * \return
         */
        auto_ptr& operator=(auto_ptr && rhs){ std::swap(m_ptr, rhs.m_ptr); return *this; }

        /*!
         * \brief operator *
         * \return
         */
        Tp operator*()
        {
            if (m_ptr != nullptr)
                return *m_ptr;
            else throw;
        }

        /*!
         * \brief operator ->
         * \return
         */
        Tp* operator->()
        {
            if (m_ptr != nullptr)
                return m_ptr;
            else throw;
        }

        /*!
         * \brief reset
         * \param ptr
         */
        void reset( Tp * ptr) { if (m_ptr != nullptr) delete m_ptr; m_ptr = ptr; }

        /*!
         * \brief release
         * \return
         */
        Tp* release() { Tp *temp = m_ptr; m_ptr = nullptr; return temp; }

    private:
        Tp *m_ptr;
    };
}
