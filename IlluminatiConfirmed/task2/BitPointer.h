#pragma once

namespace IlluminatiConfirmed
{
    template <class Tp>
    class Iterator;     // forward declaration (for "friend" word)

    class BitPointer
    {
    public:
        BitPointer(unsigned char * newData, size_t newIndex) : m_dataPtr(newData), m_index(newIndex) { }

        bool getValue() { int bit = m_dataPtr[m_index/8] & 1 << (m_index % 8); return !!bit; }

        void setValue(bool newValue)
        {
            if (newValue)   // newValue = true
                m_dataPtr[m_index/8] |= 1 << (m_index % 8);
            else           // newValue = false
                m_dataPtr[m_index/8] &= ~(1 << (m_index % 8));
        }

        //  a[2] = 0
        bool operator=(bool newValue) { setValue(newValue); return newValue; }

        // a[2] = a[1]
        bool operator=(BitPointer &rhs) { setValue(rhs.getValue()); return getValue(); }

        // bool x = a[2]
        operator bool() { return getValue(); }

        // bool x = a[2]
        operator bool() const { int bit = m_dataPtr[m_index/8] & 1 << (m_index % 8); return !!bit; }    // !!!

        friend class IlluminatiConfirmed::Iterator<bool>;
    private:
        unsigned char *m_dataPtr;
        size_t m_index;
    };
}
