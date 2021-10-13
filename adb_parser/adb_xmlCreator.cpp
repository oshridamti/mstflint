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

#include "adb_xmlCreator.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

string xmlCreator::indentString(int i)
{
  string s;
  while (i--)
  {
    s += "\t";
  }
  return s;
}

int xmlCreator::dword(int bits)
{
  if (bits < 0)
  {
    bits -= 31;
  }

  return (bits / 32) * 4;
}

int xmlCreator::startBit(int bits)
{
  return bits % 32;
}

string xmlCreator::formatAddr(u_int32_t offs, u_int32_t size)
{
  char str[64];
  sprintf(str, "0x%x.%u:%u", dword(offs), startBit(offs), size);
  return str;
}

/*template <class AdbInstance>
bool xmlCreator::compareFieldsPtr(AdbInstance *f1, AdbInstance *f2)
{
  return (*f1) < (*f2);
}*/

string xmlCreator::encodeXml(const string &data)
{
  std::string buffer;
  buffer.reserve(data.size());
  for (size_t pos = 0; pos != data.size(); ++pos)
  {
    switch (data[pos])
    {
    case '&':
      buffer.append("&amp;");
      break;

    case '\"':
      buffer.append("&quot;");
      break;

    case '\'':
      buffer.append("&apos;");
      break;

    case '<':
      buffer.append("&lt;");
      break;

    case '>':
      buffer.append("&gt;");
      break;

    default:
      buffer.append(1, data.at(pos));
      break;
    }
  }

  return buffer;
}

string xmlCreator::descNativeToXml(const string &desc)
{
  return boost::replace_all_copy(desc, "\n", "\\;");
}
