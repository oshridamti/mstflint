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
/*************************** AdbField ***************************/
/**
 * Function: AdbField::AdbField
 **/

#include "adb_field.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>

AdbField::AdbField() : size(0), offset(0xffffffff), definedAsArr(false), lowBound(0),
                       highBound(0), unlimitedArr(false), isReserved(false), userData(0)
{
}

/**
 * Function: AdbField::~AdbField
 **/
AdbField::~AdbField()
{
}

/**
 * Function: AdbField::isLeaf
 **/
bool AdbField::isLeaf()
{
    return subNode.empty();
}

/**
 * Function: AdbField::isStruct
 **/
bool AdbField::isStruct()
{
    return !isLeaf();
}

/**
 * Function: AdbField::operator<
 **/
bool AdbField::operator<(AdbField &other)
{
    return offset < other.offset;
}

/**
 * Function: AdbField::isArray
 **/
bool AdbField::isArray()
{
    if (unlimitedArr)
    {
        return true;
    }
    else
    {
        return definedAsArr ? true : lowBound != highBound;
    }
}

/**
 * Function: AdbField::arrayLen
 **/
u_int32_t AdbField::arrayLen()
{
    if (unlimitedArr)
    {
        return 1;
    }
    else
    {
        return (highBound - lowBound + 1);
    }
}

/**
 * Function: AdbField::isUnlimitedArr
 **/
bool AdbField::isUnlimitedArr()
{
    return unlimitedArr;
}

/**
 * Function: AdbField::isArray
 **/
u_int32_t AdbField::eSize()
{
    if (unlimitedArr)
    {
        return size;
    }
    else
    {
        return size / arrayLen();
    }
}

/**
 * Function: AdbField::print
 **/
void AdbField::print(int indent)
{
    cout << indentString(indent);
    cout << "- FIELD - Name: " << name << " offset: 0x" << hex << offset / 32 * 4 << "." << dec << offset % 32 << " size: 0x" << hex << size / 32 * 4 << "." << dec << size % 32 << " low_bound: " << lowBound
         << " high_bound: " << highBound << " sub_node: " << subNode
         << " isReserved: " << isReserved << endl;
}

/**
 * Function: AdbField::toXml
 **/
string AdbField::toXml(const string &addPrefix)
{
    string xml = "<field name=\"" + name + "\" descr=\"" + encodeXml(descNativeToXml(desc)) + "\"";
    if (isStruct())
    {
        xml += " subnode=\"" + addPrefix + subNode + "\"";
    }

    for (AttrsMap::iterator it = attrs.begin(); it != attrs.end(); it++)
    {
        if (it->first == "name" || it->first == "subnode" || it->first == "descr")
        {
            continue;
        }

        xml += " " + it->first + "=\"" + encodeXml(it->second) + "\"";
    }

    xml += " />";
    return xml;
}
