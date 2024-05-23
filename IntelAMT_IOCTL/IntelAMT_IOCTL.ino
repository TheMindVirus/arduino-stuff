#include "intel_amt_pthi_ioctl.h"

#define ENTRY_MESSAGE \
    "[BOOT]: Intel AMT PTHI IOCTL Emulator"

#define MAX_LEN        255
#define SERIAL_BAUD    115200

String AMT_CMD[] =
{
    "DACAMT", "EHH", "GRNGS", "GANACLES", "GAMTSAR", "GCHE",
    "GCV", "GCM", "GLSA", "GMESAR", "GALR", "GALS",
    "GPID", "GPKIFQDNS", "GPS", "GPTLSM", "GRNGSS", "GZTCES",
    "SPKIFQDNS", "SPSOTP", "SZTE", "SEHBCS", "GEHBCS", "SC",
    "SCE", "SCHB", "HC", "U", "SAMTOS", "SICTAMT",
    "SIISCTAMTE"
};
size_t AMT_SZCMD = sizeof(AMT_CMD) / sizeof(String);

String AMT_STAT(AMT_STATUS Status)
{
    switch (Status)
    {
        case (AMT_STATUS_SUCCESS): { return F("AMT_STATUS_SUCCESS"); } break;
        case (AMT_STATUS_INTERNAL_ERROR): { return F("AMT_STATUS_INTERNAL_ERROR"); } break;
        case (AMT_STATUS_INVALID_AMT_MODE): { return F("AMT_STATUS_INVALID_AMT_MODE"); } break;
        case (AMT_STATUS_INVALID_MESSAGE_LENGTH): { return F("AMT_STATUS_INVALID_MESSAGE_LENGTH"); } break;
        case (AMT_STATUS_MAX_LIMIT_REACHED): { return F("AMT_STATUS_MAX_LIMIT_REACHED"); } break;
        case (AMT_STATUS_INVALID_PARAMETER): { return F("AMT_STATUS_INVALID_PARAMETER"); } break;
        case (AMT_STATUS_RNG_GENERATION_IN_PROGRESS): { return F("AMT_STATUS_RNG_GENERATION_IN_PROGRESS"); } break;
        case (AMT_STATUS_RNG_NOT_READY): { return F("AMT_STATUS_RNG_NOT_READY"); } break;
        case (AMT_STATUS_CERTIFICATE_NOT_READY): { return F("AMT_STATUS_CERTIFICATE_NOT_READY"); } break;
        case (AMT_STATUS_INVALID_HANDLE): { return F("AMT_STATUS_INVALID_HANDLE"); } break;
        case (AMT_STATUS_NOT_FOUND): { return F("AMT_STATUS_NOT_FOUND"); } break;
        default: { return F("Unknown AMT_STATUS"); } break;
    }
    return F("Unknown AMT_STATUS");
}

typedef AMT_STATUS(*AMT_IVT_T)();
AMT_IVT_T AMT_IVT[] =
{
    CFG_DisableAndClearAMT,
    CFG_EnumerateHashHandles,
    CFG_GenerateRNGSeed,
    CFG_GetAdminNetACLEntryStatus,
    CFG_GetAMTSetupAuditRecord,
    CFG_GetCertificateHashEntry,
    CFG_GetCodeVersions,
    CFG_GetControlMode,
    CFG_GetLocalSystemAccount,
    CFG_GetMESetupAuditRecord,
    CFG_GetAuditLogRecords,
    CFG_GetAuditLogSignature,
    CFG_GetPID,
    CFG_GetPKIFQDNSuffix,
    CFG_GetProvisioningState,
    CFG_GetProvisioningTLSMode,
    CFG_GetRNGSeedStatus,
    CFG_GetZTCEnabledStatus,
    CFG_SetPKIFQDNSuffix,
    CFG_SetProvisioningServerOTP,
    CFG_SetZeroTouchEnabled,
    CFG_SetEHBCState,
    CFG_GetEHBCState,
    CFG_StartConfiguration,
    CFG_StartConfigurationEx,
    CFG_StartConfigurationHBased,
    CFG_HaltConfiguration,
    CFG_Unprovision,
    MHC_SetAMTOperationalState,
    SI_ChangeToAMT,
    SI_IsChangeToAMTEnabled,
};

String AMT_STRCMD(String Command)
{
    if (Command == "DACAMT") { return F("CFG_DisableAndClearAMT"); }
    if (Command == "EHH") { return F("CFG_EnumerateHashHandles"); }
    if (Command == "GRNGS") { return F("CFG_GenerateRNGSeed"); }
    if (Command == "GANACLES") { return F("CFG_GetAdminNetACLEntryStatus"); }
    if (Command == "GAMTSAR") { return F("CFG_GetAMTSetupAuditRecord"); }
    if (Command == "GCHE") { return F("CFG_GetCertificateHashEntry"); }
    if (Command == "GCV") { return F("CFG_GetCodeVersions"); }
    if (Command == "GCM") { return F("CFG_GetControlMode"); }
    if (Command == "GLSA") { return F("CFG_GetLocalSystemAccount"); }
    if (Command == "GMESAR") { return F("CFG_GetMESetupAuditRecord"); }
    if (Command == "GALR") { return F("CFG_GetAuditLogRecords"); }
    if (Command == "GALS") { return F("CFG_GetAuditLogSignature"); }
    if (Command == "GPID") { return F("CFG_GetPID"); }
    if (Command == "GPKIFQDNS") { return F("CFG_GetPKIFQDNSuffix"); }
    if (Command == "GPS") { return F("CFG_GetProvisioningState"); }
    if (Command == "GPTLSM") { return F("CFG_GetProvisioningTLSMode"); }
    if (Command == "GRNGSS") { return F("CFG_GetRNGSeedStatus"); }
    if (Command == "GZTCES") { return F("CFG_GetZTCEnabledStatus"); }
    if (Command == "SPKIFQDNS") { return F("CFG_SetPKIFQDNSuffix"); }
    if (Command == "SPSOTP") { return F("CFG_SetProvisioningServerOTP"); }
    if (Command == "SZTE") { return F("CFG_SetZeroTouchEnabled"); }
    if (Command == "SEHBCS") { return F("CFG_SetEHBCState"); }
    if (Command == "GEHBCS") { return F("CFG_GetEHBCState"); }
    if (Command == "SC") { return F("CFG_StartConfiguration"); }
    if (Command == "SCE") { return F("CFG_StartConfigurationEx"); }
    if (Command == "SCHB") { return F("CFG_StartConfigurationHBased"); }
    if (Command == "HC") { return F("CFG_HaltConfiguration"); }
    if (Command == "U") { return F("CFG_Unprovision"); }
    if (Command == "SAMTOS") { return F("MHC_SetAMTOperationalState"); }
    if (Command == "SICTAMT") { return F("SI_ChangeToAMT"); }
    if (Command == "SIISCTAMTE") { return F("SI_IsChangeToAMTEnabled"); }
    return F("Unknown AMT_CMD");
}

void AMT_COMMANDS()
{
    String text = "\t";
    for (size_t i = 0; i < AMT_SZCMD; ++i)
    {
        text += AMT_CMD[i];
        if (i != AMT_SZCMD - 1) { text += ", "; }
        if ((i % 6) == (6 - 1)) { text += "\n\t"; }
    }
    Serial.println(text.c_str());
}

void AMT_METHODS()
{
    for (size_t i = 0; i < AMT_SZCMD; ++i)
    {
        Serial.print("\t");
        Serial.print(AMT_CMD[i]);
        Serial.print(" - ");
        Serial.println(AMT_STRCMD(AMT_CMD[i]));
    }
}

void HELPTEXT()
{
    Serial.println("[INFO]: Engines: AMT MEBX ASMB3 HECI SOL");
    Serial.println("[INFO]: Interfaces: BIOS DMI COM SSH IOCTL PCIE");
    Serial.println("[INFO]: Commands: ");
    //AMT_COMMANDS();
    AMT_METHODS();
}

char buffer[MAX_LEN] = {0};
size_t pos = 0;

void clear_buffer()
{
    for (size_t i = 0; i < MAX_LEN; ++i)
    {
        buffer[i] = '\0';
    }
    pos = 0;
}

void process_command()
{
    bool found = false;
    AMT_STATUS status = AMT_STATUS_NOT_FOUND;
    Serial.print(buffer);
    Serial.print(": ");
    for (size_t i = 0; i < AMT_SZCMD; ++i)
    {
        if ((0 == strncmp(buffer, AMT_CMD[i].c_str(), strlen(buffer)))
        && (AMT_IVT[i]))
        {
            AMT_STATUS status = AMT_IVT[i]();
            Serial.println(AMT_STAT(status));
            found = true;
            break;
        }
    }
    if (found == false)
    {
        Serial.println(AMT_STAT(status));
        HELPTEXT();
    }
    clear_buffer();
}

void setup()
{
    Serial.begin(SERIAL_BAUD);
    Serial.println(ENTRY_MESSAGE);
    HELPTEXT();
}

void loop()
{
    size_t n = Serial.available();
    for (size_t i = 0; i < n; ++i)
    {
        char c = Serial.read();
        if ((c >= 32) && (c <= 128))
        {
            buffer[pos] = c;
            if (pos < MAX_LEN) { ++pos; };
        }
        if (c == '\n') { process_command(); }
    }
}
