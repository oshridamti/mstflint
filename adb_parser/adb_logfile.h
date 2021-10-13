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
/*************************** LogFile ***************************/

#ifndef ADB_LOGFILE_H
#define ADB_LOGFILE_H

#include <string>
#include <stdlib.h>
#include <cstring>
#include <errno.h>
#include "adb_exceptionHolder.h"
#include <stdio.h>

using namespace std;

class LogFile {
public:
    LogFile();
    void init(string logFileName, bool allowMultipleExceptions);
    ~LogFile();
    void appendLogFile(string adbFileName);
private:
    FILE *_logFile;
};

#endif
