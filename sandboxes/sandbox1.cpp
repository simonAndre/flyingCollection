#include <flyingCollection.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <map>

using namespace flyingCollection;

template <class T>
void printkey(SanCodedStr sancsr, const char *key)
{
    T myval;
    if (sancsr.tryGetValue(key, myval))
        std::cout << "found " << key << "=" << myval << '\n';
    else
        std::cout << "not found key " << key << '\n';
}
bool vb1 = 1;

int main()
{

    std::cout << "json serialization by value, sizelimit=50" << std::endl;
    JsonStream<30> jss;
    jss.add<uint16_t>("k1", 25);
    jss.add<uint16_t>("k2", 3);
    jss.add<float>("k3", 255.4546);
    jss.add<std::string>("k4", "chaineC++");
    jss.add<const char *>("k5", "chaine static c-like");
    jss.add<int>("k6", -35325);
    auto vecres = jss.getJsons();
    std::cout << "nb jsons strings : " << vecres.size() << std::endl;
    int i = 1;
    for (const std::string &json : vecres)
        std::cout<<"part "<<i++<<" = " << json << std::endl;

    std::unique_ptr<JsonStream<80>> jsref = std::make_unique<JsonStream<80>>();
    std::cout << "json serialization byref, sizelimit=80, use of partial flushs" << std::endl;
    jsref->add("k1", 25);
    jsref->add<std::string>("k2", "36");
    jsref->flush();
    const char *cs = "365";
    jsref->add("k5", cs);
    bool b = true;
    jsref->add("kbool", b);
    jsref->add("k3",-253.65);
    std::cout << "nb jsref strings : " << jsref->getJsons().size() << std::endl;
    i = 1;
    for (const std::string &json : jsref->getJsons())
        std::cout << "part " << i++ << " = " << json << std::endl;

    const char *inputstr = "key1:12;key2:2k.22225;key3:FjfB3V;key4:45.67;keybool1:1;keybool2:0;keybool3:y;keybool4:1";
    std::cout << "\n\njson parsing, in string : " << inputstr << std::endl;
    SanCodedStr sancstr(inputstr);

    //streaming
    std::ostringstream oss;
    oss << sancstr.get<std::string>("key2");
    oss << sancstr.get<int>("key1");
    oss << '}';
    std::cout << "\njson streaming output: " << oss.str() << std::endl;

    //extraction to map
    std::map<std::string, double> mapfloat;
    std::cout << "\nextraction to map:\n";
    if (sancstr.extractKVmap(mapfloat))
    {
        std::cout << "codded string:"
                  << sancstr.getCodedString()
                  << "  -- extraction map OK, it contains:"
                  << std::endl;

        for (auto &x : mapfloat)
            std::cout << " [" << x.first << ':' << x.second << ']';
        std::cout << '\n';
    }

    // direct extraction
    std::cout << "\ndirect extraction:\n";
    printkey<int>(sancstr, "key1");
    printkey<uint16_t>(sancstr, "key1");
    printkey<const char *>(sancstr, "key2");
    printkey<const char *>(sancstr, "key3");
    printkey<float>(sancstr, "key2");
    printkey<float>(sancstr, "key3");
    printkey<float>(sancstr, "key4");
    printkey<bool>(sancstr, "keybool1");
    printkey<bool>(sancstr, "keybool2");
    printkey<bool>(sancstr, "keybool3");
    printkey<bool>(sancstr, "keybool4");
}