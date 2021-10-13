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
/*************************** AdbException Implementation ***************************/

#include "adb_exceptionHolder.h"

ExceptionsMap ExceptionHolder::adbExceptionMap;
const string ExceptionHolder::FATAL_EXCEPTION = "FATAL";
const string ExceptionHolder::ERROR_EXCEPTION = "ERROR"; 
const string ExceptionHolder::WARN_EXCEPTION = "WARNING"; 
int ExceptionHolder::exceptionCounter = 0;

AdbException::AdbException() {
}

/**
 * Function: AdbException::AdbException
 **/
AdbException::AdbException(const char *fmt, ...) {
    char tmp[1024];
    va_list args;
    va_start(args, fmt);
    vsprintf(tmp, fmt, args);
    va_end(args);
    _msg = tmp;
}

/**
 * Function: AdbException::AdbException
 **/
AdbException::AdbException(string msg) :
    _msg(msg) {
}

/**
 * Function: AdbException::~AdbException
 **/
AdbException::~AdbException() throw () {
}

/**
 * Function: AdbException::what
 **/
const char* AdbException::what() const throw () {
    return _msg.c_str();
}

/**
 * Function: AdbException::what_s
 **/
string AdbException::what_s() const {
    return _msg;
}

int ExceptionHolder::getNumberOfExceptions() {
    return ExceptionHolder::exceptionCounter;
}

/**
 *  * Function: ExceptionHolder::getAdbExceptionsMap
 *   * This function return the adb exception map
 *    **/

ExceptionsMap ExceptionHolder::getAdbExceptionsMap() {
    return ExceptionHolder::adbExceptionMap;
}

/**
 *  * Function: ExceptionHolder::insertNewException
 *   * This function take the excpetion type [FATAL:0, ERROR:1, WARNING:2] and the exception string
 *    * Then it insert it to the adb exception map
 *     **/
void ExceptionHolder::insertNewException(const string exceptionType, string exceptionTxt) {
    ExceptionHolder::adbExceptionMap[exceptionType].push_back(exceptionTxt);
    ExceptionHolder::exceptionCounter += 1;
}
