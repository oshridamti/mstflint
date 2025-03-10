/*
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.

 *
 */

#include "mlxlink_utils.h"

void termHandler(int sig) {
    printf("Interrupted, Exiting...\n");
    exit(sig);
}

u_int32_t findMaxKey(vector<string> keys)
{
    u_int32_t maxKeySize = 0;
    for (vector<string>::iterator it = keys.begin(); it != keys.end();
         ++it) {
        if ((*it).length() > maxKeySize) {
            maxKeySize = (*it).length();
        }
    }
    return maxKeySize;
}

string convertIntToHexString(int toConvert)
{
    stringstream hexStr;
    hexStr << hex << toConvert;
    return hexStr.str();
}

string deleteLastChar(const string &s, u_int32_t numOfCharsToRemove)
{
    string newStr = s;
    if (newStr.size() && newStr.size() > numOfCharsToRemove) {
        newStr.erase(newStr.size() - numOfCharsToRemove);
    }
    return newStr;
}

string getStringFromVector(vector<string> values)
{
    string s;
    for (vector<string>::const_iterator i = values.begin();
         i != values.end(); ++i) {
        s += *i + ',';
    }
    return deleteLastChar(s);
}

string getStringFromVector(vector<float> values)
{
    string s;
    char strVal[32];
    u_int32_t prec = 0;
    for (vector<float>::const_iterator i = values.begin();
         i != values.end(); ++i) {
        if ((*i - ((int)*i)) > 0) {
            prec = 3;
        } else {
            prec = 0;
        }
        snprintf(strVal, sizeof(strVal), "%.*f", prec, *i);
        s += string(strVal) + ',';
    }
    return deleteLastChar(s);
}

u_int64_t add32BitTo64(u_int32_t value1, u_int32_t value2)
{
    return (((u_int64_t) value1) << 32 | value2);
}

string status2Color(u_int32_t status)
{
    return (status == 0 || status == 1023) ? ANSI_COLOR_GREEN : ANSI_COLOR_RED;
}

string getLoopbackColor(u_int32_t loopbackMode)
{
    switch (loopbackMode) {
    case PHY_NO_LOOPBACK:
        return ANSI_COLOR_GREEN;
        break;

    case PHY_REMOTE_LOOPBACK:
        return ANSI_COLOR_CYAN;
        break;

    case PHY_LOCAL_LOOPBACK:
        return ANSI_COLOR_BLUE;
        break;

    case EXTERNAL_LOCAL_LOOPBACK:
        return ANSI_COLOR_MAGENTA;

    default:
        return ANSI_COLOR_RED;
    }
    return ANSI_COLOR_RED;
}

string getAnDisableColor(u_int32_t anDisable)
{
    switch (anDisable) {
    case AN_DISABLE_NORMAL:
        return ANSI_COLOR_GREEN;

    case AN_DISABLE_FORCE:
        return ANSI_COLOR_BLUE;

    default:
        return ANSI_COLOR_RED;
    }
}

string IBSupportedSpeeds2Str(u_int32_t mask)
{
    string maskStr = "";

    if (mask & IB_LINK_SPEED_NDR) {
        maskStr += "NDR,";
    }
    if (mask & IB_LINK_SPEED_HDR) {
        maskStr += "HDR,";
    }
    if (mask & IB_LINK_SPEED_EDR) {
        maskStr += "EDR,";
    }
    if (mask & IB_LINK_SPEED_FDR) {
        maskStr += "FDR,";
    }
    if (mask & IB_LINK_SPEED_FDR10) {
        maskStr += "FDR10,";
    }
    if (mask & IB_LINK_SPEED_QDR) {
        maskStr += "QDR,";
    }
    if (mask & IB_LINK_SPEED_DDR) {
        maskStr += "DDR,";
    }
    if (mask & IB_LINK_SPEED_SDR) {
        maskStr += "SDR,";
    }

    return deleteLastChar(maskStr);
}

string EthSupportedSpeeds2Str(u_int32_t int_mask)
{
    string maskStr = "";

    if ((int_mask & ETH_LINK_SPEED_100G_CR4) || (int_mask & ETH_LINK_SPEED_100G_KR4) || (int_mask & ETH_LINK_SPEED_100G_SR4) || (int_mask & ETH_LINK_SPEED_100G_LR4)) {
        maskStr += "100G,";
    }
    if ((int_mask & ETH_LINK_SPEED_56G_R4) || (int_mask & ETH_LINK_SPEED_56G_CR4) || (int_mask & ETH_LINK_SPEED_56G_KR4)) {
        maskStr += "56G,";
    }
    if ((int_mask & ETH_LINK_SPEED_50G_CR2) || (int_mask & ETH_LINK_SPEED_50G_KR2) || (int_mask & ETH_LINK_SPEED_50G_SR2) || (int_mask & ETH_LINK_SPEED_50G_KR4)) {
        maskStr += "50G,";
    }
    if ((int_mask & ETH_LINK_SPEED_40G_CR4) || (int_mask & ETH_LINK_SPEED_40G_KR4) || (int_mask & ETH_LINK_SPEED_40G_SR4) || (int_mask & ETH_LINK_SPEED_40G_LR4)) {
        maskStr += "40G,";
    }
    if ((int_mask & ETH_LINK_SPEED_25G_CR) || (int_mask & ETH_LINK_SPEED_25G_KR) || (int_mask & ETH_LINK_SPEED_25G_SR)) {
        maskStr += "25G,";
    }
    if (int_mask & ETH_LINK_SPEED_20G_KR2) {
        maskStr += "20G,";
    }
    if ((int_mask & ETH_LINK_SPEED_10G_CR) || (int_mask & ETH_LINK_SPEED_10G_KR) || (int_mask & ETH_LINK_SPEED_10G_SR) || (int_mask & ETH_LINK_SPEED_10G_LR) || (int_mask & ETH_LINK_SPEED_10G_CX4) || (int_mask & ETH_LINK_SPEED_10G_KX4) || (int_mask & ETH_LINK_SPEED_10G_BaseT)) {
        maskStr += "10G,";
    }
    if ((int_mask & ETH_LINK_SPEED_1000_SGMII) || (int_mask & ETH_LINK_SPEED_1000_KX) || (int_mask & ETH_LINK_SPEED_1000_BaseT)) {
        maskStr += "1G,";
    }
    if (int_mask & ETH_LINK_SPEED_100_BaseTx) {
        maskStr += "100M,";
    }

    return deleteLastChar(maskStr);
}

string EthExtSupportedSpeeds2Str(u_int32_t int_mask)
{
    string maskStr = "";

    if (int_mask & ETH_LINK_SPEED_EXT_400GAUI_4) {
        maskStr += "400G_4x,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_400GAUI_8) {
        maskStr += "400G_8X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_200GAUI_2) {
        maskStr += "200G_2X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_200GAUI_4) {
        maskStr += "200G_4X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_100GAUI_1) {
        maskStr += "100G_1X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_100GAUI_2) {
        maskStr += "100G_2X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_CAUI_4) {
        maskStr += "100G_4X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_50GAUI_1) {
        maskStr += "50G_1X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_50GAUI_2) {
        maskStr += "50G_2X,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_XLAUI_4) {
        maskStr += "40G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_25GAUI_1) {
        maskStr += "25G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_XFI) {
        maskStr += "10G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_5GBASE_R) {
        maskStr += "5G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_2_5GBASE_X) {
        maskStr += "2.5G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_1000BASE_X) {
        maskStr += "1G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_SGMII_100M) {
        maskStr += "100M,";
    }

    return deleteLastChar(maskStr);
}

string SupportedSpeeds2Str(u_int32_t proto_active, u_int32_t mask, bool extended)
{
    if(extended && proto_active == ETH ) {
        return EthExtSupportedSpeeds2Str(mask);
    }
    return proto_active == IB ?
               IBSupportedSpeeds2Str(mask) : EthSupportedSpeeds2Str(mask);
}

string getOui(u_int32_t oui)
{
    string ouiStr;
    switch (oui) {
    case OTHER:
        ouiStr = "Other";
        break;

    case MELLANOX:
        ouiStr = "Mellanox";
        break;

    case KNOWN_OUI:
        ouiStr = "Known OUI";
        break;

    default:
        ouiStr = "Other";
    }
    return ouiStr;
}

int ptysSpeedToExtMaskETH(const string & speed)
{
    if (speed == "100M") {
        return (ETH_LINK_SPEED_EXT_SGMII_100M);
    }
    if (speed == "1G") {
        return (ETH_LINK_SPEED_EXT_1000BASE_X);
    }
    if (speed == "2.5G") {
        return (ETH_LINK_SPEED_EXT_2_5GBASE_X);
    }
    if (speed == "5G") {
        return (ETH_LINK_SPEED_EXT_5GBASE_R);
    }
    if (speed == "10G") {
        return (ETH_LINK_SPEED_EXT_XFI);
    }
    if (speed == "25G") {
        return (ETH_LINK_SPEED_EXT_25GAUI_1);
    }
    if (speed == "40G") {
        return (ETH_LINK_SPEED_EXT_XLAUI_4);
    }
    if (speed == "50G_2X") {
        return (ETH_LINK_SPEED_EXT_50GAUI_2);
    }
    if (speed == "50G_1X") {
        return (ETH_LINK_SPEED_EXT_50GAUI_1);
    }
    if (speed =="100G_4X") {
        return (ETH_LINK_SPEED_EXT_CAUI_4);
    }
    if (speed =="100G_1X") {
        return (ETH_LINK_SPEED_EXT_100GAUI_1);
    }
    if (speed =="100G_2X") {
        return (ETH_LINK_SPEED_EXT_100GAUI_2);
    }
    if (speed == "200G_2X") {
        return ETH_LINK_SPEED_EXT_200GAUI_2;
    }
    if (speed == "200G_4X") {
        return ETH_LINK_SPEED_EXT_200GAUI_4;
    }
    if (speed == "400G_4X") {
        return ETH_LINK_SPEED_EXT_400GAUI_4;
    }
    if (speed == "400G_8X") {
        return ETH_LINK_SPEED_EXT_400GAUI_8;
    }
    return 0x0;
}

int ptysSpeedToMaskETH(const string &speed)
{
    if (speed == "1G") {
        return (ETH_LINK_SPEED_1000_SGMII | ETH_LINK_SPEED_1000_KX
                | ETH_LINK_SPEED_1000_BaseT);
    }
    if (speed == "10G") {
        return (ETH_LINK_SPEED_10G_CX4 | ETH_LINK_SPEED_10G_KX4
                | ETH_LINK_SPEED_10G_CR | ETH_LINK_SPEED_10G_KR
                | ETH_LINK_SPEED_10G_LR | ETH_LINK_SPEED_10G_SR
                | ETH_LINK_SPEED_10G_BaseT);
    }
    if (speed == "20G") {
        return ETH_LINK_SPEED_20G_KR2;
    }
    if (speed == "40G") {
        return (ETH_LINK_SPEED_40G_CR4 | ETH_LINK_SPEED_40G_KR4
                | ETH_LINK_SPEED_40G_LR4 | ETH_LINK_SPEED_40G_SR4);
    }
    if (speed == "56G") {
        return (ETH_LINK_SPEED_56G_CR4 | ETH_LINK_SPEED_56G_KR4
                | ETH_LINK_SPEED_56G_R4);
    }
    if (speed == "50G") {
        return (ETH_LINK_SPEED_50G_CR2 | ETH_LINK_SPEED_50G_KR2
                | ETH_LINK_SPEED_50G_SR2 | ETH_LINK_SPEED_50G_KR4);
    }
    if (speed == "100G") {
        return (ETH_LINK_SPEED_100G_CR4 | ETH_LINK_SPEED_100G_KR4
                | ETH_LINK_SPEED_100G_LR4 | ETH_LINK_SPEED_100G_SR4);
    }
    if (speed == "100") {
        return ETH_LINK_SPEED_100_BaseTx;
    }
    if (speed == "25G") {
        return (ETH_LINK_SPEED_25G_CR | ETH_LINK_SPEED_25G_KR
                | ETH_LINK_SPEED_25G_SR);
    }
    return 0x0;
}

int ptysSpeedToMaskIB(const string &speed)
{
    if (speed == "SDR") {
        return IB_LINK_SPEED_SDR;
    }
    if (speed == "DDR") {
        return IB_LINK_SPEED_DDR;
    }
    if (speed == "QDR") {
        return IB_LINK_SPEED_QDR;
    }
    if (speed == "FDR10") {
        return IB_LINK_SPEED_FDR10;
    }
    if (speed == "FDR") {
        return IB_LINK_SPEED_FDR;
    }
    if (speed == "EDR") {
        return IB_LINK_SPEED_EDR;
    }
    if (speed == "HDR") {
        return IB_LINK_SPEED_HDR;
    }
    if (speed == "NDR") {
        return IB_LINK_SPEED_NDR;
    }
    return 0x0;
}

bool isPAM4Speed(u_int32_t activeSpeed, u_int32_t protoActive, bool extended)
{
    bool pam4Signal = false;
    if (protoActive == ETH && extended) {
        if (activeSpeed == ETH_LINK_SPEED_EXT_50GAUI_1 ||
            activeSpeed == ETH_LINK_SPEED_EXT_100GAUI_2 ||
            activeSpeed == ETH_LINK_SPEED_EXT_200GAUI_4 ||
            activeSpeed == ETH_LINK_SPEED_EXT_400GAUI_8) {
            pam4Signal = true;
        }
    } else if (protoActive == IB) {
        if (activeSpeed == IB_LINK_SPEED_HDR ||
            activeSpeed == IB_LINK_SPEED_NDR) {
            pam4Signal = true;
        }
    }
    return pam4Signal;
}

bool checkPaosCmd(const string &paosCmd)
{
    if (paosCmd != "UP" && paosCmd != "DN" && paosCmd != "TG") {
        return false;
    }
    return true;
}

bool checkPepcForceMode(const string &forceMode)
{
    if (forceMode != "MA" && forceMode != "SL") {
        return false;
    }
    return true;
}

bool checkPepcANMode(const string &anMode)
{
    if (anMode != "AU" && anMode != "MA" && anMode != "SL") {
        return false;
    }
    return true;
}

bool checkPplmCmd(const string &pplmCmd)
{
    if (pplmCmd != "AU" && pplmCmd != "NF" && pplmCmd != "FC"
        && pplmCmd != "RS") {
        return false;
    }
    return true;
}

bool checkPplrCmd(const string &pplrCmd)
{
    if (pplrCmd != "NO" && pplrCmd != "PH" && pplrCmd != "EX") {
        return false;
    }
    return true;
}

string prbsMaskToLaneRate(u_int32_t mask)
{
    if (mask == PRBS_SDR) {
        return "2.5G";
    }
    if (mask == PRBS_DDR) {
        return "5G";
    }
    if (mask == PRBS_QDR) {
        return "10G";
    }
    if (mask == PRBS_FDR10) {
        return "10.3125G";
    }
    if (mask == PRBS_FDR) {
        return "14.0625G";
    }
    if (mask == PRBS_EDR) {
        return "25.78125G";
    }
    if (mask == PRBS_HDR) {
        return "53.125G";
    }
    if (mask == PRBS_NDR) {
        return "106.25G";
    }
    if (mask == PRBS_1G) {
        return "1.25G";
    }
    if (mask == PRBS_XAUI) {
        return "3.125G";
    }
    if (mask == PRBS_50G) {
        return "12.89G";
    }
    return "N/A";
}

u_int32_t prbsMaskToRateNum(u_int32_t mask)
{
    if (mask == PRBS_SDR) {
        return 1;
    }
    if (mask == PRBS_DDR) {
        return 5;
    }
    if (mask == PRBS_QDR) {
        return 10;
    }
    if (mask == PRBS_FDR10) {
        return 40;
    }
    if (mask == PRBS_FDR) {
        return 56;
    }
    if (mask == PRBS_EDR) {
        return 100;
    }
    if (mask == PRBS_HDR) {
        return 200;
    }
    if (mask == PRBS_NDR) {
        return 400;
    }
    if (mask == PRBS_1G) {
        return 1;
    }
    if (mask == PRBS_XAUI) {
        return 2;
    }
    if (mask == PRBS_50G) {
        return 12;
    }
    return 0;
}

bool prbsLaneRateCheck(const string &rate)
{
    if (rate == "SDR" || rate == "IB-SDR") {
        return true;
    }
    if (rate == "DDR" || rate == "IB-DDR" || rate == "5G") {
        return true;
    }
    if (rate == "QDR" || rate == "IB-QDR") {
        return true;
    }
    if (rate == "FDR10" || rate == "IB-FDR10" || rate == "10G" || rate == "40G") {
        return true;
    }
    if (rate == "FDR" || rate == "IB-FDR" || rate == "14G") {
        return true;
    }
    if (rate == "EDR" || rate == "IB-EDR" || rate == "25G" || rate == "50G"
            || rate == "100G"|| rate == "50G_2X" || rate == "100G_4X") {
        return true;
    }
    if (rate == "HDR" || rate == "IB-HDR" || rate == "200G_4X"
            || rate == "50G_1X" || rate == "100G_2X" || rate == "400G_8X") {
        return true;
    }
    if (rate == "NDR" || rate == "IB-NDR" || rate == "100G_1X"
            || rate == "200G_2X" || rate == "400G_4X" || rate == "800G_8X") {
        return true;
    }
    if (rate == "1G") {
        return true;
    }
    if (rate == "XAUI" || rate == "2.5G") {
        return true;
    }
    if (rate == "50GE-KR4" || rate == "12.89G") {
        return true;
    }
    if (rate == "") {
        return true;
    }
    return false;
}

string prbsMaskToTuningStatus(u_int32_t mask)
{
    if (mask == PRBS_TUNING_NOT_PERFORMED) {
        return "PRBS mode tuning was not performed.";
    }
    if (mask == PRBS_TUNING_PERFORMING) {
        return "Performing PRBS mode tuning.";
    }
    if (mask == PRBS_TUNING_COMPLETE) {
        return "PRBS mode tuning completed.";
    }
    return "N/A";
}

string prbsMaskToLockStatus(u_int32_t mask, u_int32_t numOfLanesToUse, bool &allLocked)
{
    string res = "";
    allLocked = true;
    for (u_int32_t i = 0; i < numOfLanesToUse; i++) {
        if (mask & 1 << i) {
            res += "Locked";
        } else {
            res += "Not Locked";
            allLocked = false;
        }
        if (i < numOfLanesToUse - 1) {
            res += MlxlinkRecord::jsonFormat? "," : ",    ";
        }
    }
    return res;
}

bool checkPrbsCmd(const string &prbsCmd)
{
    if (prbsCmd != "DS" && prbsCmd != "EN" && prbsCmd != "TU") {
        return false;
    }
    return true;
}

bool checkTestMode(const string &testMode)
{
    if (testMode != "Nominal" && testMode != "NOMINAL" && testMode != "CORNER"
        && testMode != "DRIFT" && testMode != "") {
        return false;
    }
    return true;
}

string FEC2Str(const string &fecShort, const string &speedStrG)
{
    string fec = "";
    if (fecShort == "NF") {
        fec = "No FEC";
    } else if (fecShort == "FC") {
        fec = "Firecode FEC";
    } else if (fecShort == "RS") {
        fec = "RS FEC";
    }
    if (speedStrG == "400g_8x" || speedStrG == "200g_4x" ||
            speedStrG == "100g_2x" || speedStrG == "50g_1x") {
        if (fec == "RS544") {
            fec = "Standard_RS-FEC - (544,514)";
        }
        if (fec == "RS272") {
            fec = "Ethernet_Consortium_LL_50G_RS-FEC - (272,257+1)";
        }
    }
    return fec;
}

int fecToBit(const string &fec, const string &speedStrG)
{
    if (fec == "AU") {
        return 0;
    }
    if (fec == "NF") {
        return 1;
    }
    if (fec == "FC") {
        return 2;
    }
    if (fec == "RS") {
        return 4;
    }
    if (speedStrG == "400g_8x" || speedStrG == "200g_4x" ||
            speedStrG == "100g_2x" || speedStrG == "50g_1x") {
        if (fec == "RS544") {
            return 0x80;
        }
        if (fec == "RS272") {
            return 0x200;
        }
    }
    return 0;
}

string speedToStr(const string &speed, u_int32_t numOfLanes)
{
    string fecSpeedStrFormat = "100g";
    string numberOfLanesStr = to_string(numOfLanes) + "x";
    if (speed == "800G") {
        fecSpeedStrFormat = "800g_" + numberOfLanesStr;
    }
    if (speed == "400G") {
        fecSpeedStrFormat = "400g_" + numberOfLanesStr;
    }
    if (speed == "200G") {
        fecSpeedStrFormat = "200g_" + numberOfLanesStr;
    }
    if (speed == "100G") {
        if (numOfLanes == 4) {
            fecSpeedStrFormat = "100g";
        } else {
            fecSpeedStrFormat = "100g_" + numberOfLanesStr;
        }
    }
    if (speed == "50G") {
        if (numOfLanes == 1) {
            fecSpeedStrFormat = "50g_" + numberOfLanesStr;
        } else {
            fecSpeedStrFormat = "50g";
        }
    }
    if (speed == "100GbE") {
        fecSpeedStrFormat = "100g";
    }
    if (speed == "50GbE") {
        fecSpeedStrFormat = "50g";
    }
    if (speed == "25GbE" || speed == "25G") {
        fecSpeedStrFormat = "25g";
    }
    if (speed == "40GbE" || speed == "40G" || speed == "10GbE" || speed == "10G") {
        fecSpeedStrFormat = "10g_40g";
    }
    if (speed == "56GbE") {
        fecSpeedStrFormat = "56g";
    }
    return fecSpeedStrFormat;
}

PAOS_CMD paos_to_int(const string &cmd)
{
    if (cmd == "UP") {
        return UP;
    }
    if (cmd == "DN") {
        return DN;
    }
    if (cmd == "TG") {
        return TG;
    }
    return NO;
}

int pepc_force_mode_to_int(const string &forceMode)
{
    if (forceMode == "MA") {
        return 0;
    }
    if (forceMode == "SL") {
        return 1;
    }
    return 0;
}

int pepc_an_mode_to_int(const string &anMode)
{
    if (anMode == "AU") {
        return 0;
    }
    if (anMode == "MA") {
        return 1;
    }
    if (anMode == "SL") {
        return 2;
    }
    return 0;
}

bool endsWith(string const & value, string const & ending)
{
    if (ending.size() >= value.size()) {
        return false;
    }
    return equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void findAndReplace(string& source, string const& find, string const& replace)
{
    for (string::size_type i = 0; (i = source.find(find, i)) != string::npos;) {
        source.replace(i, find.length(), replace);
        i += replace.length();
    }
}

string getCableIdentifier(u_int32_t identifier)
{
    string identifierStr;
    switch (identifier) {
    case IDENTIFIER_QSFP28:
        identifierStr = "QSFP28";
        break;

    case IDENTIFIER_QSFP_PLUS:
        identifierStr = "QSFP+";
        break;

    case IDENTIFIER_SFP:
        identifierStr = "SFP28/SFP+";
        break;

    case IDENTIFIER_QSA:
        identifierStr = "QSA (QSFP->SFP)";
        break;

    case IDENTIFIER_BACKPLANE:
        identifierStr = "Backplane";
        break;

    case IDENTIFIER_SFP_DD:
        identifierStr = "SFP-DD";
        break;

    case IDENTIFIER_QSFP_DD:
        identifierStr = "QSFP-DD";
        break;

    case IDENTIFIER_QSFP_CMIS:
        identifierStr = "QSFP_CMIS";
        break;
    case IDENTIFIER_OSFP:
        identifierStr = "OSFP";
        break;
    case IDENTIFIER_DSFP:
        identifierStr = "DSFP";
        break;
    default:
        identifierStr = "N/A";
    }
    return identifierStr;
}

bool isCMISCable(u_int32_t identifier)
{
    bool cmisCable = (identifier == IDENTIFIER_SFP_DD) ||
                    (identifier == IDENTIFIER_QSFP_DD) ||
                    (identifier == IDENTIFIER_QSFP_CMIS) ||
                    (identifier == IDENTIFIER_OSFP) ||
                    (identifier == IDENTIFIER_DSFP);
    return cmisCable;
}

bool isQsfpCable(u_int32_t identifier)
{
    bool qsfpCable = (identifier == IDENTIFIER_QSFP28) ||
                    (identifier == IDENTIFIER_QSFP_PLUS) ||
                    (identifier == IDENTIFIER_QSFP_DD) ||
                    (identifier == IDENTIFIER_DSFP);
    return qsfpCable;
}

string getCableType(u_int32_t cableType)
{
    string cableTypeStr;
    switch (cableType) {
    case UNIDENTIFIED:
        cableTypeStr = "Unidentified";
        break;

    case ACTIVE:
        cableTypeStr = "Active cable (active copper / optics)";
        break;

    case OPTICAL_MODULE:
        cableTypeStr = "Optical Module (separated)";
        break;

    case PASSIVE:
        cableTypeStr = "Passive copper cable";
        break;

    case UNPLUGGED:
        cableTypeStr = "Cable unplugged";
        break;

    default:
        cableTypeStr = "Unidentified";
        break;
    }
    return cableTypeStr;
}

string getTemp(u_int32_t temp)
{
    if (temp & 0x8000) {
        return "-" + to_string(((~temp & 0xFFFF) + 1) / 256);
    }
    return to_string(temp / 256);
}

float getPower(u_int16_t power)
{
    if (power & 0x8000) {
        return -((~power & 0xFFFF) + 1);
    }
    return power;
}

int getHeight(u_int16_t height)
{
    if (height & 0x8000) {
        return -((~height & 0xFFFF) + 1);
    }
    return height;
}

int getPhase(u_int8_t phase)
{
    if (phase & 0x80) {
        return -((~phase & 0xFF) + 1);
    }
    return phase;
}

int getVersion(u_int8_t version)
{
    if (version & 0x8) {
        return -((~version & 0xF) + 1);
    }
    return version;
}

string getGroupStr(u_int32_t advancedOpcode)
{
    if (advancedOpcode == 0 || advancedOpcode == 1023) {
        return "N/A";
    } else if (advancedOpcode < 1023) {
        return "PHY FW";
    } else if (advancedOpcode < 2048) {
        return "MNG FW";
    }
    return "CORE/DRIVER";
}

string toUpperCase(string &str)
{
    for (u_int32_t i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

string toLowerCase(string &str)
{
    for (u_int32_t i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

string getCableMedia(u_int32_t cableType)
{
    string cableTypeStr;
    switch (cableType) {
    case UNIDENTIFIED:
        cableTypeStr = "Unidentified";
        break;

    case ACTIVE:
        cableTypeStr = "Active";
        break;

    case OPTICAL_MODULE:
        cableTypeStr = "Optical Module";
        break;

    case PASSIVE:
        cableTypeStr = "Passive";
        break;

    case UNPLUGGED:
        cableTypeStr = "Unplugged";
        break;

    default:
        cableTypeStr = "Unidentified";
    }
    return cableTypeStr;
}

string pcieSpeedStr(u_int32_t linkSpeedActive)
{
    string linkSpeedActiveStr;
    if (linkSpeedActive & GEN5) {
        linkSpeedActiveStr = "32G-Gen 5";
    } else if (linkSpeedActive & GEN4) {
        linkSpeedActiveStr = "16G-Gen 4";
    } else if (linkSpeedActive & GEN3) {
        linkSpeedActiveStr = "8G-Gen 3";
    } else if (linkSpeedActive & GEN2) {
        linkSpeedActiveStr = "5G-Gen 2";
    } else if (linkSpeedActive & GEN1) {
        linkSpeedActiveStr = "2.5G-Gen 1";
    } else {
        linkSpeedActiveStr = "N/A";
    }
    return linkSpeedActiveStr;
}

string pcieDeviceStatusStr(u_int32_t deviceStatus)
{
    string deviceStatusStr, comma;
    if (!deviceStatus) {
        return "N/A";
    }
    if ((deviceStatus >> 0) & 0x1) {
        deviceStatusStr += "Correctable Error detected";
        comma=", ";
    }
    if ((deviceStatus >> 1) & 0x1) {
        deviceStatusStr += comma + "Non-Fatal Error detected";
        comma=", ";
    }
    if ((deviceStatus >> 2) & 0x1) {
        deviceStatusStr  += comma + "Fatal Error detected" + comma;
        comma=", ";
    }
    if ((deviceStatus >> 3) & 0x1) {
        deviceStatusStr += comma + "Unsupported Request detected";
        comma=", ";
    }
    if ((deviceStatus >> 4) & 0x1) {
        deviceStatusStr += comma + "AUX power";
        comma=", ";
    }
    if ((deviceStatus >> 5) & 0x1) {
        deviceStatusStr += comma + "Transaction Pending";
    }
    if ("" != deviceStatusStr) {
        deviceStatusStr += ".";
    }
    return deviceStatusStr;
}

double mw_to_dbm(double x)
{
    return 10 * log10(x);
}

int readSignedByte(u_int32_t value)
{
    if (value & 0x80) {
        return -((~value & 0xFF) + 1);
    }
    return value;
}

void setPrintVal(MlxlinkCmdPrint &mlxlinkCmdPrint, string key,
        string value, string color, bool print, bool valid, bool arrayValue,
        bool colorKey)
{
    mlxlinkCmdPrint.mlxlinkRecords[mlxlinkCmdPrint.lastInsertedRow].key = key;
    mlxlinkCmdPrint.mlxlinkRecords[mlxlinkCmdPrint.lastInsertedRow].val = valid? value: "N/A";
    mlxlinkCmdPrint.mlxlinkRecords[mlxlinkCmdPrint.lastInsertedRow].color = color;
    mlxlinkCmdPrint.mlxlinkRecords[mlxlinkCmdPrint.lastInsertedRow].visible = print;
    mlxlinkCmdPrint.mlxlinkRecords[mlxlinkCmdPrint.lastInsertedRow].arrayValue = arrayValue;
    mlxlinkCmdPrint.mlxlinkRecords[mlxlinkCmdPrint.lastInsertedRow].colorKey = colorKey;
    mlxlinkCmdPrint.lastInsertedRow++;
}

void setPrintTitle(MlxlinkCmdPrint &mlxlinkCmdPrint, string title,
        u_int32_t size, bool print)
{
    if (!MlxlinkRecord::gboxTitle.empty()) {
        title = MlxlinkRecord::gboxTitle + " - " + title;
    }

    mlxlinkCmdPrint.title = title;
    mlxlinkCmdPrint.visible = print;
    mlxlinkCmdPrint.initRecords(size);
}

int eyeTypeStrToInt(const string &str)
{
    int code = -1;
    if (str == "CMP") {
        code = SLRG_COMPOSITE_EYE;
    } else if (str == "ALL") {
        code = SLRG_COMPOSITE_WITH_ALL_EYES;
    } else if (str == "UP") {
        code = SLRG_UPPER_EYE;
    } else if (str == "MID") {
        code = SLRG_MIDDLE_EYE;
    } else if (str == "LOW") {
        code = SLRG_LOWER_EYE;
    }
    return code;
}

bool isSpeed25GPerLane(u_int32_t speed, u_int32_t protocol)
{
    bool valid = true;
    if ((protocol == IB && speed != IB_LINK_SPEED_EDR) ||
        (protocol == ETH && (speed != ETH_LINK_SPEED_100G_CR4 &&
        speed != ETH_LINK_SPEED_100G_KR4 && speed != ETH_LINK_SPEED_100G_LR4 &&
        speed != ETH_LINK_SPEED_100G_SR4 && speed != ETH_LINK_SPEED_50G_KR2 &&
        speed != ETH_LINK_SPEED_50G_SR2 && speed != ETH_LINK_SPEED_50G_CR2 &&
        speed != ETH_LINK_SPEED_25G_CR && speed != ETH_LINK_SPEED_25G_KR &&
        speed != ETH_LINK_SPEED_25G_SR && speed != ETH_LINK_SPEED_50G_KR4))) {
        valid = false;
    }
    return valid;
}

bool askUser(const char *question, bool force)
{
    if (MlxlinkRecord::jsonFormat && force) {
        return true;
    }

    bool ret = true;
    void (*old)(int);
    old = signal(SIGINT, termHandler);

    printf("\n %s ? (y/n) [n] : ", question);
    if (force) {
        printf("y\n");
    } else {
        fflush(stdout);
        string answer;
        getline(cin, answer);
        if (strcasecmp(answer.c_str(), "y") &&
            strcasecmp(answer.c_str(), "yes")) {
            return false;
        }
    }

    signal(SIGINT, old);

    return ret;
}

