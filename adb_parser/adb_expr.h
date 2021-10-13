
/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */

#ifndef ADB_EXPR_H
#define ADB_EXPR_H

#include <map>
#include <string>
#include "expr.h"
#include "adb_exceptionHolder.h"

using namespace std;

class AdbExpr : public Expr
{
public:
    AdbExpr();
    ~AdbExpr();

    static const char* statusStr(int status);
    int  ResolveName(char *name, u_int64_t *val);
    void Error(const std::string& message);
    void setVars(map<string, string> *varsMap);

private:
    map<string, string> *_varsMap;
};

#endif // ADB_EXPR_H
