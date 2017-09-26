/*
 * PropertyMap.cpp
 *
 *  Created on: Jul 11, 2011
 *      Author: augcampos
 */

#include "asteriskcpp/structs/PropertyMap.h"
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include "asteriskcpp/utils/LogHandler.h"
#include <typeinfo>
#include <stdio.h>

#define SEP ": "
#define NEWLINE "\r\n"

namespace asteriskcpp {
    const std::string strEmpty("");

    PropertyMap::PropertyMap() {
    }

    PropertyMap::PropertyMap(const std::string & str) {
        convertStr(str);
    }

    PropertyMap::~PropertyMap() {
    }

    const std::string PropertyMap::getClassName() const {
        char str[128];
        int i;
        const char *realname = typeid (*this).name();
        sscanf(realname, "N11asteriskcpp%d%s", &i, str);
        return std::string(str, 0, i);
    }

    const std::string PropertyMap::toString() const {
        std::stringstream stream;
        for (propertyIndex::const_iterator it = index.begin(); it != index.end(); it++) {
            stream << makeStdLine(*it, getProperty(*it));
        }
        stream << NEWLINE;
        return (stream.str());
    }

    std::string PropertyMap::toLog() const {
        return (str2Log(this->toString()));
    }

    void PropertyMap::setProperty(const std::string& key, const std::string& value) {
        propertyMap::const_iterator it = values.find(key);
        if (it != values.end())
            editProperty(key, value);
        else
            addProperty(key, value);
    }

    const std::string& PropertyMap::getGetterValue(const char *functionName) const {
        return (getProperty(func2property(functionName)));
    }

    void PropertyMap::setSetterValue(const char *functionName, const std::string& value) {
        setProperty(func2property(functionName), value);
    }

    const std::string& PropertyMap::getProperty(const std::string& key) const {
        propertyMap::const_iterator it = values.find(key);
        if (it != values.end()) {
            return (it->second);
        }

        return ((strEmpty));
    }

    void PropertyMap::convertStr(const std::string& propertyStr) {
        std::string knull;
        std::string::size_type lastPos = propertyStr.find_first_not_of(NEWLINE, 0);
        std::string::size_type pos = propertyStr.find(NEWLINE);
        while (std::string::npos != pos && std::string::npos != lastPos) {
            std::string line = propertyStr.substr(lastPos, pos - lastPos);

            size_t sep = line.find(SEP);
            if (knull.size() == 0 && sep != line.npos && sep < 35) {
                setProperty(line.substr(0, sep), line.substr(sep + 2));
            } else {
                //std::cout << "knull[" << str2Log(line) << "]" << std::endl;
                knull.append(line);
            }

            std::string::size_type tmpLastPos = lastPos;
            lastPos = propertyStr.find_first_not_of(NEWLINE, pos);
            pos = propertyStr.find(NEWLINE, tmpLastPos);
        }

        if (knull.size())
            setProperty("", knull);
    }

    void PropertyMap::addProperty(const std::string& key, const std::string& value) {
        propertyPair p = std::make_pair(key, value);
        index.push_back(key);
        values.insert(p);
    }

    std::string PropertyMap::makeStdLine(const std::string & key, const std::string & value) {
        if (key.length() < 2) {
            return (std::string(value + NEWLINE));
        }
        return (std::string(key + SEP + value + NEWLINE));
    }

    void PropertyMap::editProperty(const std::string& key, const std::string& value) {
        values[key] = value;
    }

    const std::string PropertyMap::func2property(const char *functionName) {
        std::string fn(functionName);
        if ((fn.at(0) == 'g' || fn.at(0) == 's') && fn.at(1) == 'e' && fn.at(2) == 't') {
            fn.erase(0, 3);
        } else if (fn.at(0) == 'i' && fn.at(1) == 's') {
            fn.erase(0, 2);
        }
        return (fn);
    }

}
