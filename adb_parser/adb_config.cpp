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
/**
 * Function: AdbField::print
 **/

#include "adb_config.h"
#include <iostream>

void AdbConfig::print(int indent) {
    cout << indentString(indent) << "Attributes:" << endl;
    AttrsMap::iterator iter;
    for (iter = attrs.begin(); iter != attrs.end(); iter++)
        cout << indentString(indent + 1) << iter->first << " - "
                << iter->second << endl;

    cout << indentString(indent) << "Enums:" << endl;
    for (iter = enums.begin(); iter != enums.end(); iter++)
        cout << indentString(indent + 1) << iter->first << " - "
                << iter->second << endl;
}

/**
 * Function: AdbConfig::toXml
 **/
string AdbConfig::toXml() {
    string xml = "<config ";

    for (AttrsMap::iterator it = attrs.begin(); it != attrs.end(); it++) {
        xml += " " + it->first + "=\"" + encodeXml(it->second) + "\"";
    }

    if (!enums.empty()) {
        xml += " >\n";

        for (AttrsMap::iterator it = enums.begin(); it != enums.end(); it++) {
            xml += "\t<enum  name=\"" + encodeXml(it->first) + "\" value=\""
                    + encodeXml(it->second) + "\" />\n";
        }
        xml += "</config>";
    } else {
        xml += " />";
    }

    return xml;
}
