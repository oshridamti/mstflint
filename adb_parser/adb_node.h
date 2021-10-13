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

#ifndef ADB_NODE_H
#define ADB_NODE_H

#include "adb_xmlCreator.h"
#include <string>
#include <map>
#include <vector>

using namespace std;
using namespace xmlCreator;

class AdbField;

typedef map<string, string> AttrsMap;
typedef vector<AdbField *> FieldsList;
class AdbNode
{
public:
    // Methods
    AdbNode();
    ~AdbNode();
    string toXml(const string &addPrefix);

    // FOR DEBUG
    void print(int indent = 0);

public:
    // Members
    string name;
    u_int32_t size; // in bits
    bool isUnion;
    string desc;
    FieldsList fields;
    FieldsList condFields; // Field that weren't instantiated due to not satisfied condition
    AttrsMap attrs;

    // defined in
    string fileName;
    int lineNumber;

    // FOR USER USAGE
    void *userData;
};

#endif
