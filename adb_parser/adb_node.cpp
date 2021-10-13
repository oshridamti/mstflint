/*
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */
/*************************** AdbNode ***************************/

/**
 *  * Function: AdbNode::AdbNode
 *   **/

#include "adb_node.h"
#include "adb_field.h"
#include <iostream>

#if __cplusplus >= 201402L
#include <regex>
#else
#include <boost/regex.hpp>
using namespace boost;
#endif

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

AdbNode::AdbNode() : size(0), isUnion(false), lineNumber(-1), userData(0)
{
}

/**
 *  * Function: AdbNode::~AdbNode
 *   **/
AdbNode::~AdbNode()
{
    for (size_t i = 0; i < fields.size(); i++)
    {
        delete fields[i];
    }
    fields.clear();
    for (size_t i = 0; i < condFields.size(); i++)
    {
        delete condFields[i];
    }
    condFields.clear();
}

/**
 *  * Function: AdbNode::toXml
 *   **/
string AdbNode::toXml(const string &addPrefix)
{
    string xml = "<node name=\"" + addPrefix + name + "\" descr=\"" + encodeXml(descNativeToXml(desc)) + "\"";
    for (AttrsMap::iterator it = attrs.begin(); it != attrs.end(); it++)
    {
        if (it->first == "name" || it->first == "descr")
        {
            continue;
        }

        xml += " " + it->first + "=\"" + encodeXml(it->second) + "\"";
    }
    xml += " >\n";

    FieldsList allFields = fields;
    allFields.insert(allFields.end(), condFields.begin(), condFields.end());
    stable_sort(allFields.begin(), allFields.end(), compareFieldsPtr<AdbField>);

    for (size_t i = 0; i < allFields.size(); i++)
    {
        if (allFields[i]->isReserved)
        {
            continue;
        }

        xml += "\t" + allFields[i]->toXml(addPrefix) + "\n";
    }

    xml += "</node>";
    return xml;
}

/**
 *  * Function: AdbNode::print
 *   **/
void AdbNode::print(int indent)
{
    cout << indentString(indent);
    cout << "+ Node Name: " << name << " size: 0x" << hex << size / 32 * 4
         << "." << dec << size % 32 << " isUnion: " << isUnion
         << " Description: " << desc << endl;

    cout << indentString(indent) << "Fields:" << endl;
    for (size_t i = 0; i < fields.size(); i++)
        fields[i]->print(indent + 1);
}
