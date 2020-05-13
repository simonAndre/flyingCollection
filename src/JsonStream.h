#pragma once
#include <vector>

namespace FLYINGCOLLECTION_NAMESPACE
{
    /**
     * @brief build a collection of json string from key-value pairs. Each json string beeing big enough to fit the JsonMaxCapacity template parameter.
     * 
     * @tparam size max of the json string. If needed, several string will be created wrapped in a vactor.  
     */
    template <size_t JsonMaxCapacity = 106>
    class JsonStream
    {
    private:
        std::ostringstream *o_currentjsonstream;
        std::vector<std::string> jsoncollection;

    public:
        JsonStream()
        {
            o_currentjsonstream = new std::ostringstream();
        }
        ~JsonStream()
        {
            delete o_currentjsonstream;
        }

        std::vector<std::string> getJsons();

        /**
     * @brief number of json strings holded by the collection
     * 
     * @return uint16_t 
     */
        uint16_t size();


        /**
 * @brief add the key/value pair to the json stream
 * 
 * @tparam T 
 * @param key 
 * @param value 
 * @return true 
 * @return false : add impossible mainly dur to oversizing.
 */
        template <typename T>
        bool add(std::string key, const T &value)
        {
            auto skv = SanPair<T>(key, value);
            uint16_t currentpos = o_currentjsonstream->tellp();
            uint16_t forcastedjsonsize = skv.forcastedjsonsize();
            if (forcastedjsonsize > JsonMaxCapacity)
                return false; // size of the kv pair oversize the capacity.
            if (currentpos + forcastedjsonsize > JsonMaxCapacity - 1)
                if (!this->flush())
                    return false;
            *o_currentjsonstream << skv;
            return true;
        }

        /**
         * @brief close the current json string and append it to the collection
         * 
         * @return true 
         * @return false 
         */
        bool flush();
    };
} // namespace FLYINGCOLLECTION_NAMESPACE