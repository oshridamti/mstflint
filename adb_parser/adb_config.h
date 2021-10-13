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
/*************************** AdbConfig ***************************/

#ifndef ADB_CONFIG_H
#define ADB_CONFIG_H

#include "adb_xmlCreator.h"
#include <map>
#include <string>

using namespace xmlCreator;

using namespace std;

typedef map<string, string> AttrsMap;

class AdbConfig {
public:
    // FOR DEBUG
    void print(int indent = 0);

    string toXml();

public:
    // Members
    AttrsMap attrs;
    AttrsMap enums;
};

#endif
