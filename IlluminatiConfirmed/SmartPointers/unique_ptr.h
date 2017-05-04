#pragma once

namespace IlluminatiConfirmed
{
    template<class Tp>
    class unique_ptr
    {
    public:
        /*!
         * \brief unique_ptr
         * \param ptr
         */
        explicit unique_ptr(Tp *ptr = nullptr) : m_ptr(ptr) { }

        /*!
         * \brief unique_ptr
         * \param obj
         */
        unique_ptr(Tp &obj) : m_ptr(&obj) { }

        /*!
         * \brief unique_ptr
         * \param other
         */
        unique_ptr(unique_ptr &&other) { std::swap(m_ptr, other.m_ptr); }

        ~unique_ptr() { if (m_ptr != nullptr) delete m_ptr; m_ptr = nullptr; }

        /*!
         * \brief operator =
         * \param rhs
         * \return
         */
        Tp* operator=(Tp *rhs) = delete;

        /*!
         * \brief operator =
         * \param rhs
         * \return
         */
        unique_ptr& operator=(unique_ptr && rhs) { std::swap(m_ptr, rhs.m_ptr); return *this; }

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
        void reset(Tp * ptr) { if (m_ptr != nullptr) delete m_ptr; m_ptr = ptr; }

        /*!
         * \brief release
         * \return
         */
        Tp* release() { Tp *temp = m_ptr; m_ptr = nullptr; return temp; }
    private:
        Tp *m_ptr;
    };
}
