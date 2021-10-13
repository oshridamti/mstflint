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


#ifndef xmlCreator_H
#define xmlCreator_H

#include <string>
#include <common/compatibility.h>

using namespace std;

namespace xmlCreator
{

  template <class T>
  bool compareFieldsPtr(T *f1, T *f2);
  string indentString(int i);
  int dword(int bits);
  int startBit(int bits);
  string formatAddr(u_int32_t offs, u_int32_t size);
  string encodeXml(const string &data);
  string descNativeToXml(const string &desc);

}

template <class T>
bool xmlCreator::compareFieldsPtr(T *f1, T *f2)
{
    return (*f1) < (*f2);
}

#endif
