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
/*************************** ExceptionHolder ***************************/

#ifndef ADB_EXCEPTIONHOLDER_H
#define ADB_EXCEPTIONHOLDER_H

#include <string>
#include <map>
#include <vector>
#include <cstdarg>
#include <stdio.h>
#include <stdarg.h>

using namespace std;


typedef vector<string> StringVector;
typedef map<string, StringVector> ExceptionsMap;



class ExceptionHolder {
public:
    // METHODS
    static void insertNewException(const string exceptionType, string exceptionTxt);
    static ExceptionsMap getAdbExceptionsMap();
    static int getNumberOfExceptions();
public:
    // VARIABLES
    static ExceptionsMap adbExceptionMap;
    static const string FATAL_EXCEPTION;
    static const string ERROR_EXCEPTION;
    static const string WARN_EXCEPTION;
    static int exceptionCounter;
};

/*************************** AdbException ***************************/
class AdbException: public std::exception {
public:
    // Methods
    AdbException();
    AdbException(const char *msg, ...) __attribute__((format(__printf__, 2, 3)));
    AdbException(string msg);
    virtual ~AdbException() throw (); 
    virtual const char* what() const throw (); 
    virtual string what_s() const;

private:
    string _msg;
};


/**
 * Function: ExceptionHolder::getNumberOfExceptions
 * This function return the number of exceptions found
 **/

/*int ExceptionHolder::getNumberOfExceptions() {
    return ExceptionHolder::exceptionCounter;
}*/

/**
 * Function: ExceptionHolder::getAdbExceptionsMap
 * This function return the adb exception map
 **/

/*ExceptionsMap ExceptionHolder::getAdbExceptionsMap() {
    return ExceptionHolder::adbExceptionMap;
}*/

/**
 * Function: ExceptionHolder::insertNewException
 * This function take the excpetion type [FATAL:0, ERROR:1, WARNING:2] and the exception string
 * Then it insert it to the adb exception map
 **/
/*void ExceptionHolder::insertNewException(const string exceptionType, string exceptionTxt) {
    ExceptionHolder::adbExceptionMap[exceptionType].push_back(exceptionTxt);
    ExceptionHolder::exceptionCounter += 1;
}*/

#endif
