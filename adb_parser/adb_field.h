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

#ifndef ADB_FIELD_H
#define ADB_FIELD_H

#include "adb_xmlCreator.h"
#include <map>
#include <string>

using namespace xmlCreator;
using namespace std;

typedef map<string, string> AttrsMap;

class AdbField
{
public:
    // Methods
    AdbField();
    ~AdbField();
    bool isLeaf();
    bool isStruct();
    bool isArray();
    u_int32_t arrayLen();
    bool isUnlimitedArr();
    u_int32_t eSize();
    string toXml(const string &addPrefix);

    // Operator overloading - useful for sorting
    bool operator<(AdbField &other);

    // FOR DEBUG
    void print(int indent = 0);

public:
    // Members
    string name;
    u_int32_t size;   // in bits
    u_int32_t offset; // in bits (relative to the node start addr)
    string desc;
    bool definedAsArr;
    u_int32_t lowBound;
    u_int32_t highBound;
    bool unlimitedArr;
    string subNode;
    AttrsMap attrs;
    bool isReserved;
    string condition; // field's visibility dynamic condition

    // FOR USER USAGE
    void *userData;
};

#endif
