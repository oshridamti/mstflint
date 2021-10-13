/*
 * Copyright (c) 2012-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*************************** Adb ***************************/
#ifndef ADB_ADB_H
#define ADB_ADB_H



class LogFile;

#include <map>
#include <string>
#include <vector>
#include <list>
#include "adb_expr.h"
#include "adb_xmlCreator.h"

#include <string>
#include <map>
#include <vector>
#include <exception>
#include <list>
#include <common/compatibility.h>
#include "adb_expr.h"
#include "adb_node.h"
#include "adb_field.h"
#include "adb_exceptionHolder.h"
#include "adb_logfile.h"
#include "adb_config.h"
#include "adb_progress.h"
#include "adb_instance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <list>
#include <stdexcept>
#include "adb_xmlCreator.h"

#ifdef __WIN__
#include <process.h>
#define OS_PATH_SEP "\\"
#else
#define OS_PATH_SEP "/"
#endif

#ifdef __linux__
#define LC_ALL_HINT " using `export LC_ALL=C`"
#else
#define LC_ALL_HINT ""
#endif

#define PROGRESS_NODE_CNT   100 // each 100 parsed node call progress callback

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#define CHECK_RUNTIME_ERROR(e) ((strstr(e.what(), "locale::facet::_S_create_c_locale") != NULL) ? \
                                string("Encoding error, please set locale encoding to C") + LC_ALL_HINT + "." : \
                                string("runtime_error: ") + e.what())

using namespace std;

//#define printf win32_printf
#if defined(__MINGW32__) || defined(__MINGW64__)
#define PRINTF_FORMAT __MINGW_PRINTF_FORMAT
#else
#define PRINTF_FORMAT printf
#endif

class AdbInstance;
class AdbField;

using namespace xmlCreator;
using namespace std;

typedef map<string, string> AttrsMap;
typedef vector<string> StringVector;
typedef struct {
    string fullPath;
    string includedFromFile;
    int includedFromLine;
} IncludeFileInfo;
typedef map<string, IncludeFileInfo> IncludeFileMap;
typedef map<string, AdbNode*> NodesMap;
typedef vector<AdbConfig*> ConfigList;
typedef map<string, AttrsMap> InstanceAttrs;
typedef map<string, StringVector> ExceptionsMap;
class Adb {
public:
    // Methods
    Adb();
    ~Adb();
    void raiseException(bool allowMultipleExceptions, string exceptionTxt, const string expType);
    // strict union means:
    //   1- dwrod aligned unions
    //   2- contains nodes only
    //   3- check node size vs instance size
    bool loadFromString(const char *adbContents, bool addReserved = false,
            AdbProgress *progressObj = NULL, bool strict = true,
            bool enforceExtraChecks = false);
    bool load(string fname, bool addReserved = false,
            AdbProgress *progressObj = NULL, bool strict = true,
            string includePath = "", string includeDir = "",
            bool enforceExtraChecks = false, bool getAllExceptions = false,
            string logFile = "");
    string toXml(vector<string> nodeNames = vector<string> (),
            bool addRootNode = false, string rootName = "MainNode",
            string addPrefix = "");

    AdbInstance* addMissingNodes(int depth, bool allowMultipleExceptions);
    AdbInstance* createLayout(string rootNodeName, bool isExprEval = false,
            AdbProgress *progressObj = NULL, int depth = -1, /* -1 means instantiate full tree */
            bool ignoreMissingNodes = false, bool getAllExceptions = false);
    vector<string> getNodeDeps(string nodeName);
    string getLastError();

    void fetchAdbExceptionsMap(ExceptionsMap otherMap);
    // excpetionType [FATAL:0, ERROR:1, WARNING:2]
    void insertNewException(const string exceptionType, string exceptionTxt);
    string printAdbExceptionMap();

    // FOR DEBUG
    void print(int indent = 0);

public:
    // Members
    string version;
    NodesMap nodesMap;
    ConfigList configs;
    string rootNode;
    bool bigEndianArr;
    bool singleEntryArrSupp;
    InstanceAttrs instAttrs; // Key is instance's Adabe full path, value is attribute map
    string srcDocName;
    string srcDocVer;
    LogFile* _logFile;

    /* For internal use */
public:
    StringVector includePaths;
    string mainFileName;
    IncludeFileMap includedFiles;
    StringVector warnings;
    ExceptionsMap adbExceptionMap;
private:
    vector<AdbInstance*> createInstance(AdbField *fieldDesc,
            AdbInstance *parent, map<string, string> vars, bool isExprEval,
            AdbProgress *progressObj, int depth,
            bool ignoreMissingNodes = false, bool getAllExceptions = false);
    u_int32_t calcArrOffset(AdbField *fieldDesc, AdbInstance *parent,
            u_int32_t arrIdx);
    string evalExpr(string expr, AttrsMap *vars);
    bool checkInstSizeConsistency(bool getAllExceptions = false);
    void cleanInstAttrs();

private:
    string _lastError;
    AdbExpr _adbExpr;
    list<AdbInstance*> _unionSelectorEvalDeffered;
    void checkInstanceOffsetValidity(AdbInstance *inst, AdbInstance *parent, bool allowMultipleExceptions);
    void throwExeption(bool allowMultipleExceptions, string exceptionTxt, string addedMsgMultiExp);
};

#endif
