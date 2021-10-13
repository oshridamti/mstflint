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
/*************************** AdbInstance ***************************/

#ifndef ADB_INSTANCE_H
#define ADB_INSTANCE_H
\
#include"adb_xmlCreator.h"
#include <map>
#include <string>
#include <vector>

using namespace std;
using namespace xmlCreator;


typedef map<string, string> AttrsMap;
class AdbField;
class AdbNode;

class AdbInstance {
public:
    // Methods
    AdbInstance();
    ~AdbInstance();
    bool isLeaf();
    bool isUnion();
    bool isStruct();
    bool isNode();
    bool isPartOfArray();
    string fullName(int skipLevel = 0);
    bool isReserved();
    u_int32_t dwordAddr();
    u_int32_t startBit();
    bool isEnumExists();
    bool enumToInt(const string &name, u_int64_t &val); // false means no enum value found
    bool intToEnum(u_int64_t val, string &valName); // false means no enum name found
    map<string, u_int64_t> getEnumMap();
    vector<u_int64_t> getEnumValues();
    AdbInstance* getUnionSelectedNodeName(const u_int64_t& selectorVal);
    AdbInstance* getUnionSelectedNodeName(const string& selectorEnum);
    bool operator<(const AdbInstance& other);
    bool isConditionalNode();
    bool isConditionValid(map<string, string> *valuesMap);
    // DB like access methods
    AdbInstance
    * getChildByPath(const string& path, bool isCaseSensitive = true);
    vector<AdbInstance*> findChild(const string& name,
            bool isCaseSensitive = true, bool by_inst_name = false);
    string getInstanceAttr(const string &attrName) const;
    AttrsMap::iterator getInstanceAttrIterator(const string &attrName, bool &isEnd);
    void setInstanceAttr(const string &attrName, const string &attrValue);
    void copyAllInstanceAttr(AttrsMap &attsToCopy); 
    AttrsMap getFullInstanceAttrsMapCopy();
    void setVarsMap(const string &attrName, const string &attrValue);
    void setVarsMap(const AttrsMap &AttrsMap);
    AttrsMap getVarsMap();
    vector<AdbInstance*> getLeafFields(bool extendedName); // Get all leaf fields
    void pushBuf(u_int8_t *buf, u_int64_t value);
    u_int64_t popBuf(u_int8_t *buf);
    int instAttrsMapLen() {return instAttrsMap.size();}
    // FOR DEBUG
    void print(int indent = 0);

public:
    // Members
    AdbField *fieldDesc;
    AdbNode *nodeDesc;
    AdbInstance *parent;
    string name; // instance name
    vector<AdbInstance*> subItems;
    u_int32_t offset; // Global offset in bits (Relative to 0)
    u_int32_t size; // in bits
    u_int32_t arrIdx;
    bool      isNameBeenExtended;
    AdbInstance *unionSelector; // For union instances only
    bool isDiff;
    // FOR USER USAGE
    void *userData;
private:
    AttrsMap instAttrsMap; // Attributes after evaluations and array expanding
    AttrsMap varsMap; // all variables relevant to this item after evaluation
};

#endif
