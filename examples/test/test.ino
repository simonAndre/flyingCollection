#include <flyingCollection.h>
#include <Arduino.h>

using namespace flyingCollection;

void setup()
{
    Serial.begin(115200);
    delay(500);
    Serial.println("start");
}

void loop()
{
    JsonStream<30> jss;
    jss.add<uint16_t>("k1", 25);
    jss.add<uint16_t>("k2", 3);
    jss.add<float>("k3", 255.4546);
    jss.add<std::string>("k4", "chaineC++");
    jss.add<const char *>("k5", "chaine static c-like");
    jss.add<int>("k6", -35325);
    auto vecres = jss.getJsons();
    Serial.print("nb jsons strings : ");
    Serial.println(vecres.size());
    int i = 1;
    for (const std::string &json : vecres)
    {
        Serial.print("part : ");
        Serial.print(i++);
        Serial.print("=");
        Serial.println(json.c_str());
    }

    const char *inputstr = "key1:12;key2:2k.22225;key3:FjfB3V;key4:45.67;keybool1:1;keybool2:0;keybool3:y;keybool4:1";
    SanCodedStr sancstr(inputstr);

    printkey<int>(sancstr, "key1");
    printkey<uint16_t>(sancstr, "key1");
    printkey<const char *>(sancstr, "key2");
    printkey<const char *>(sancstr, "key3");
    printkey<const char *>(sancstr, "nokey3");
    printkey<float>(sancstr, "key2");
    printkey<float>(sancstr, "key3");
    printkey<float>(sancstr, "key4");
    printkey<bool>(sancstr, "keybool1");
    printkey<bool>(sancstr, "keybool2");
    printkey<bool>(sancstr, "keybool3");
    printkey<bool>(sancstr, "keybool4");

    delay(1000);
}

template <class T>
void printkey(SanCodedStr sancsr, const char *key)
{
    T myval;
    if (sancsr.tryGetValue(key, myval))
    {
        Serial.print("found ");
        Serial.print(key);
        Serial.print("=");
        Serial.println(myval);
    }
    else
    {
        Serial.print("not found key ");
        Serial.println(key);
    }
}