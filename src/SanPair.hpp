#pragma once
#include <string>
#include <sstream>


namespace FLYINGCOLLECTION_NAMESPACE
{
    template <typename T>
    class SanPair : public std::pair<std::string, T>
    {
    private:
    public:
        SanPair() : std::pair<std::string, T>(){};
        SanPair(const std::string &key, const T &value) : std::pair<std::string, T>(key, value){};

        template <typename V>
        friend std::ostream &operator<<(std::ostream &os, const SanPair<V> &pkv);

        uint16_t forcastedjsonsize();
    };

    inline void prependStream(std::ostream &os, const std::string &key)
    {
        if (os.tellp() == 0)
            os << '{';
        else if (os.tellp() > 1)
            os << ',';
        os << '\'' << key << "':";
    }

    template <typename V>
    inline std::ostream &operator<<(std::ostream &os, const SanPair<V> &pkv)
    {
        prependStream(os, pkv.first);
        os << pkv.second;
        return os;
    }

    template <>
    inline std::ostream &operator<<(std::ostream &os, const SanPair<std::string> &pkv)
    {
        prependStream(os, pkv.first);
        os << '\'' << pkv.second << '\'';
        return os;
    }
    template <>
    inline std::ostream &operator<<(std::ostream &os, const SanPair<const char *> &pkv)
    {
        prependStream(os, pkv.first);
        os << '\'' << pkv.second << '\'';
        return os;
    }

    template <typename T>
    inline uint16_t baseforcastedjsonsize(SanPair<T> *sp)
    {
        std::ostringstream oss;
        oss << sp->second;
        uint16_t skey = sp->first.size();
        uint16_t svvalue = oss.tellp();
        return skey + svvalue + 5;
    }

    template <typename V>
    inline uint16_t SanPair<V>::forcastedjsonsize()
    {
        return baseforcastedjsonsize(this);
    }

    template <>
    inline uint16_t SanPair<const char *>::forcastedjsonsize()
    {
        return baseforcastedjsonsize(this) + 2;
    }
    template <>
    inline uint16_t SanPair<std::string>::forcastedjsonsize()
    {
        return baseforcastedjsonsize(this) + 2;
    }
} // namespace FLYINGCOLLECTION_NAMESPACE