#pragma once
#include <map>
#include <string>
#include <sstream>

namespace FLYINGCOLLECTION_NAMESPACE
{
    class SanCodedStr
    {
    private:
        std::string _codedstring;

        template <typename T>
        bool extractKV(std::string const &kvpair, SanPair<T> &sanpair);
        // {
        //     std::istringstream ss_kvpair(kvpair);
        //     std::getline(ss_kvpair, sanpair.first, ':') >> sanpair.second;
        //     std::string last;
        //     bool res = !ss_kvpair.fail();
        //     if (std::getline(ss_kvpair, last, ':'))
        //         return false;
        //     return res;
        // }


    public:
        SanCodedStr(const char *codedstring)
        {
            _codedstring = std::string(codedstring);
        }
        ~SanCodedStr(){}

        std::string getCodedString()
        {
            return _codedstring;
        }

        template <typename T>
        SanPair<T> get(const char *key)
        {
            std::istringstream iss(_codedstring);
            std::string coddedkv;
            std::string strkey(key);
            SanPair<T> kv;
            while (std::getline(iss, coddedkv, ';'))
            {
                if (extractKV(coddedkv, kv))
                {
                    if (kv.first == strkey)
                    {
                        return kv;
                    }
                }
            }
            return kv;
        }

        template <typename T>
        bool tryGetValue(const char *key, T &outvalue)
        {
            std::istringstream iss(_codedstring);
            std::string coddedkv;
            std::string strkey(key);
            SanPair<T> kv;
            while (std::getline(iss, coddedkv, ';'))
            {
                if (extractKV(coddedkv, kv))
                {
                    if (kv.first == strkey)
                    {
                        outvalue = kv.second;
                        return true;
                    }
                }
            }
            return false;
        }

        template <typename T>
        bool extractKVmap(std::map<std::string, T> &data)
        {
            std::istringstream iss(_codedstring);
            std::string coddedkv;
            SanPair<T> kv;
            while (std::getline(iss, coddedkv, ';'))
            {
                if (extractKV(coddedkv, kv))
                {
                    data.emplace(kv.first, kv.second);
                }
            }
            return true;
        }
    };

   
    template <typename T>
    bool SanCodedStr::extractKV(std::string const &kvpair, SanPair<T> &sanpair)
    {
        std::istringstream ss_kvpair(kvpair);
        std::getline(ss_kvpair, sanpair.first, ':') >> sanpair.second;
        std::string last;
        bool res = !ss_kvpair.fail();
        if (std::getline(ss_kvpair, last, ':'))
            return false;
        return res;
    }
    template <>
    bool SanCodedStr::extractKV(std::string const &kvpair, SanPair<const char *> &sanpair)
    {
        std::istringstream ss_kvpair(kvpair);
        std::string secondstr;
        std::getline(ss_kvpair, sanpair.first, ':') >> secondstr;
        sanpair.second = secondstr.c_str();
        std::string last;
        bool res = !ss_kvpair.fail();
        if (std::getline(ss_kvpair, last, ':'))
            return false;
        return res;
    }

} // namespace FLYINGCOLLECTION_NAMESPACE