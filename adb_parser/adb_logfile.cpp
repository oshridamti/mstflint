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

#include "adb_logfile.h"

#define WRITE   "w"

LogFile::LogFile() : _logFile(NULL) {
}

void LogFile::init(string logFileName, bool allowMultipleExceptions) {
    if (logFileName.compare("") != 0) {
        _logFile = fopen(logFileName.c_str(), WRITE);
        if (!_logFile) {
            string  _lastError = "Can't open file (" + logFileName + ") for writing: "
                    + strerror(errno);
            if (allowMultipleExceptions) {
                ExceptionHolder::insertNewException(ExceptionHolder::FATAL_EXCEPTION, _lastError);
            } else {
                throw AdbException(_lastError);
            }
        }
    } else {
        _logFile = NULL;
    }
}

LogFile::~LogFile() {
    if (_logFile) {
        fclose (_logFile);
    }
}

void LogFile::appendLogFile(string str) {
    if (_logFile) {
        fprintf(_logFile, "%s", str.c_str());
    }
}
