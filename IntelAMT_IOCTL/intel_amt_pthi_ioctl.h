#ifndef _INTEL_AMT_PTHI_IOCTL_H_
#define _INTEL_AMT_PTHI_IOCTL_H_

//https://software.intel.com/sites/manageability/AMT_Implementation_and_Reference_Guide/default.htm?turl=WordDocuments%2Fconnectingwiththeintelmeidriver.htm

#define GUID_DEVINTERFACE_HECI    "E2D1FF34-3458-49A9-88DA-8E6915CE9BE5"
#define HECI_WATCHDOG_GUID        "05B79A6F-4628-4D7F-899D-A91514CB32AB"

#define AMT_MAJOR_VERSION    15
#define AMT_MINOR_VERSION    0

typedef struct _PTHI_VERSION
{
    uint8_t    MajorNumber;
    uint8_t    MinorNumber;
}   PTHI_VERSION;

typedef struct _COMMAND_FMT
{
    unsigned    Operation : 23;
    unsigned    IsResponse : 1;
    unsigned    Class : 8;
}   COMMAND_FMT;

typedef struct _PTHI_MESSAGE_HEADER
{
    PTHI_VERSION    Version;
    uint16_t        Reserved;
    union
    {
        COMMAND_FMT    CommandFmt;
        uint32_t       Command;
    };
    uint32_t        Length;
}   PTHI_MESSAGE_HEADER;

typedef enum _AMT_STATUS
{
    AMT_STATUS_SUCCESS = 0,
    AMT_STATUS_INTERNAL_ERROR = 1,
    AMT_STATUS_INVALID_AMT_MODE = 3,
    AMT_STATUS_INVALID_MESSAGE_LENGTH = 4,
    AMT_STATUS_MAX_LIMIT_REACHED = 23,
    AMT_STATUS_INVALID_PARAMETER = 36,
    AMT_STATUS_RNG_GENERATION_IN_PROGRESS = 47,
    AMT_STATUS_RNG_NOT_READY = 48,
    AMT_STATUS_CERTIFICATE_NOT_READY = 49,
    AMT_STATUS_INVALID_HANDLE = 2053,
    AMT_STATUS_NOT_FOUND = 2068,
}   AMT_STATUS;

typedef struct _CFG_DISABLE_AND_CLEAR_AMT_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_DISABLE_AND_CLEAR_AMT_REQUEST;

CFG_DISABLE_AND_CLEAR_AMT_REQUEST CFG_DisableAndClearAMT_Request(uint32_t Length = 0)
{
    CFG_DISABLE_AND_CLEAR_AMT_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000088;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_DISABLE_AND_CLEAR_AMT_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
}   CFG_DISABLE_AND_CLEAR_AMT_RESPONSE;

CFG_DISABLE_AND_CLEAR_AMT_RESPONSE CFG_DisableAndClearAMT_Response(uint32_t Length = 0)
{
    CFG_DISABLE_AND_CLEAR_AMT_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000088; //0x04000088;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    //Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    return Data; //AMT_STATUS_UNCHANGED; //!!!
}

typedef struct _CFG_DISABLE_AND_CLEAR_AMT
{
    CFG_DISABLE_AND_CLEAR_AMT_REQUEST Request;
    CFG_DISABLE_AND_CLEAR_AMT_RESPONSE Response;
}   CFG_DISABLE_AND_CLEAR_AMT;

AMT_STATUS CFG_DisableAndClearAMT()
{
    CFG_DISABLE_AND_CLEAR_AMT Data = {0};
    Data.Request = CFG_DisableAndClearAMT_Request();
    Data.Response = CFG_DisableAndClearAMT_Response();
    return Data.Response.Status;
}

typedef struct _CFG_ENUMERATE_HASH_HANDLES_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_ENUMERATE_HASH_HANDLES_REQUEST;

CFG_ENUMERATE_HASH_HANDLES_REQUEST CFG_EnumerateHashHandles_Request(uint32_t Length = 0)
{
    CFG_ENUMERATE_HASH_HANDLES_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x0400002C;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_ENUMERATE_HASH_HANDLES_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    uint32_t               EntriesCount;
    uint32_t               Handles[];
}   CFG_ENUMERATE_HASH_HANDLES_RESPONSE;

CFG_ENUMERATE_HASH_HANDLES_RESPONSE CFG_EnumerateHashHandles_Response(uint32_t Length = 0)
{
    CFG_ENUMERATE_HASH_HANDLES_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400002C; //0x0480002C;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    Data.EntriesCount = 0;
    for (size_t i = 0; i < Data.EntriesCount; ++i) { Data.Handles[i] = 0; }
    return Data;
}

typedef struct _CFG_ENUMERATE_HASH_HANDLES
{
    CFG_ENUMERATE_HASH_HANDLES_REQUEST Request;
    CFG_ENUMERATE_HASH_HANDLES_RESPONSE Response;
}   CFG_ENUMERATE_HASH_HANDLES;

AMT_STATUS CFG_EnumerateHashHandles()
{
    CFG_ENUMERATE_HASH_HANDLES Data = {0};
    Data.Request = CFG_EnumerateHashHandles_Request();
    Data.Response = CFG_EnumerateHashHandles_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GENERATE_RNG_SEED_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_GENERATE_RNG_SEED_REQUEST;

CFG_GENERATE_RNG_SEED_REQUEST CFG_GenerateRNGSeed_Request(uint32_t Length = 0)
{
    CFG_GENERATE_RNG_SEED_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000028;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_GENERATE_RNG_SEED_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
}   CFG_GENERATE_RNG_SEED_RESPONSE;

CFG_GENERATE_RNG_SEED_RESPONSE CFG_GenerateRNGSeed_Response(uint32_t Length = 0)
{
    CFG_GENERATE_RNG_SEED_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000028; //0x04800028;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_RNG_GENERATION_IN_PROGRESS;
    //Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    return Data;
}

typedef struct _CFG_GENERATE_RNG_SEED
{
    CFG_GENERATE_RNG_SEED_REQUEST Request;
    CFG_GENERATE_RNG_SEED_RESPONSE Response;
}   CFG_GENERATE_RNG_SEED;

AMT_STATUS CFG_GenerateRNGSeed()
{
    CFG_GENERATE_RNG_SEED Data = {0};
    Data.Request = CFG_GenerateRNGSeed_Request();
    Data.Response = CFG_GenerateRNGSeed_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_ADMIN_NET_ACL_ENTRY_STATUS_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_GET_ADMIN_NET_ACL_ENTRY_STATUS_REQUEST;

CFG_GET_ADMIN_NET_ACL_ENTRY_STATUS_REQUEST CFG_GetAdminNetACLEntryStatus_Request(uint32_t Length = 0)
{
    CFG_GET_ADMIN_NET_ACL_ENTRY_STATUS_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x0400001E;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_GET_ADMIN_NET_ACL_ENTRY_STATUS_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    bool                   IsDefault;
}   CFG_GET_ADMIN_NET_ACL_ENTRY_STATUS_RESPONSE;

CFG_GET_ADMIN_NET_ACL_ENTRY_STATUS_RESPONSE CFG_GetAdminNetACLEntryStatus_Response(uint32_t Length = 0)
{
    CFG_GET_ADMIN_NET_ACL_ENTRY_STATUS_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400001E; //0x0480001E;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.IsDefault = false; //true;
    return Data;
}

typedef struct _CFG_GET_ADMIN_NET_ACL_ENTRY_STATUS
{
    CFG_GET_ADMIN_NET_ACL_ENTRY_STATUS_REQUEST Request;
    CFG_GET_ADMIN_NET_ACL_ENTRY_STATUS_RESPONSE Response;
}   CFG_GET_ADMIN_NET_ACL_ENTRY_STATUS;

AMT_STATUS CFG_GetAdminNetACLEntryStatus()
{
    CFG_GET_ADMIN_NET_ACL_ENTRY_STATUS Data = {0};
    Data.Request = CFG_GetAdminNetACLEntryStatus_Request();
    Data.Response = CFG_GetAdminNetACLEntryStatus_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_AMT_SETUP_AUDIT_RECORD_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_GET_AMT_SETUP_AUDIT_RECORD_REQUEST;

CFG_GET_AMT_SETUP_AUDIT_RECORD_REQUEST CFG_GetAMTSetupAuditRecord_Request(uint32_t Length = 0)
{
    CFG_GET_AMT_SETUP_AUDIT_RECORD_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000027;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _AMT_ADMIN_AUDIT_RECORD
{
    String ProvisioningMethod;
    String HashValue;
    String CA;
    String HashAlgo;
    bool IsDefault;
    String IntermediateCA;
    String TimeAndDate;
    String IPAddress;
    bool TimeValidityPass;
    String FQDN;
}   AMT_ADMIN_AUDIT_RECORD;

AMT_ADMIN_AUDIT_RECORD CFG_GetAMTSetupAuditRecord_Default()
{
    AMT_ADMIN_AUDIT_RECORD Data = {}; //{0};
    Data.ProvisioningMethod = "PSK"; //"PKI-CH";
    Data.HashValue = "8WEKYB3D";
    Data.CA = "California";
    Data.HashAlgo = "SHA1"; //"SHA256";
    Data.IsDefault = false; //true;
    Data.IntermediateCA = "Battersea";
    Data.TimeAndDate = "01/01/1997";
    Data.IPAddress = "127.0.0.1";
    Data.TimeValidityPass = true; //false;
    Data.FQDN = "localhost";
    return Data;
}

typedef struct _CFG_GET_AMT_SETUP_AUDIT_RECORD_RESPONSE
{
    PTHI_MESSAGE_HEADER       Header;
    AMT_STATUS                Status;
    AMT_ADMIN_AUDIT_RECORD    AuditRecord;
}   CFG_GET_AMT_SETUP_AUDIT_RECORD_RESPONSE;

CFG_GET_AMT_SETUP_AUDIT_RECORD_RESPONSE CFG_GetAMTSetupAuditRecord_Response(uint32_t Length = 0)
{
    CFG_GET_AMT_SETUP_AUDIT_RECORD_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000027; //0x04800027;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    //Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    Data.AuditRecord = CFG_GetAMTSetupAuditRecord_Default();
    return Data;
}

typedef struct _CFG_GET_AMT_SETUP_AUDIT_RECORD
{
    CFG_GET_AMT_SETUP_AUDIT_RECORD_REQUEST Request;
    CFG_GET_AMT_SETUP_AUDIT_RECORD_RESPONSE Response;
}   CFG_GET_AMT_SETUP_AUDIT_RECORD;

AMT_STATUS CFG_GetAMTSetupAuditRecord()
{
    CFG_GET_AMT_SETUP_AUDIT_RECORD Data = {0};
    Data.Request = CFG_GetAMTSetupAuditRecord_Request();
    Data.Response = CFG_GetAMTSetupAuditRecord_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_CERTIFICATE_HASH_ENTRY_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
    uint32_t               Handle;
}   CFG_GET_CERTIFICATE_HASH_ENTRY_REQUEST;

CFG_GET_CERTIFICATE_HASH_ENTRY_REQUEST CFG_GetCertificateHashEntry_Request(uint32_t Length = 0, uint32_t Handle = 0)
{
    CFG_GET_CERTIFICATE_HASH_ENTRY_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x0400002D;
    Data.Header.Length = Length;
    Data.Handle = Handle;
    return Data;
}

typedef struct _CFG_GET_CERTIFICATE_HASH_ENTRY_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    bool                   IsDefault;
    bool                   IsActive;
    String                 CertificateHash;
    uint8_t                HashAlgorithm;
    String                 Name;
}   CFG_GET_CERTIFICATE_HASH_ENTRY_RESPONSE;

CFG_GET_CERTIFICATE_HASH_ENTRY_RESPONSE CFG_GetCertificateHashEntry_Response(uint32_t Length = 0)
{
    CFG_GET_CERTIFICATE_HASH_ENTRY_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400002D; //0x0480002D;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    //Data.Status = AMT_STATUS_NOT_FOUND;
    Data.IsDefault = false; //true;
    Data.IsActive = true; //false;
    Data.CertificateHash = "XABCDEFX";
    Data.HashAlgorithm = "CERT_HASH_ALGORITHM_SHA1"; //"CERT_HASH_ALGORITHM_CUSTOM";
    Data.Name = "Arduino";
    return Data;
}

typedef struct _CFG_GET_CERTIFICATE_HASH_ENTRY
{
    CFG_GET_CERTIFICATE_HASH_ENTRY_REQUEST Request;
    CFG_GET_CERTIFICATE_HASH_ENTRY_RESPONSE Response;
}   CFG_GET_CERTIFICATE_HASH_ENTRY;

AMT_STATUS CFG_GetCertificateHashEntry()
{
    CFG_GET_CERTIFICATE_HASH_ENTRY Data = {0};
    Data.Request = CFG_GetCertificateHashEntry_Request();
    Data.Response = CFG_GetCertificateHashEntry_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_CODE_VERSIONS_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_GET_CODE_VERSIONS_REQUEST;

CFG_GET_CODE_VERSIONS_REQUEST CFG_GetCodeVersions_Request(uint32_t Length = 0)
{
    CFG_GET_CODE_VERSIONS_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x0400001A;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_GET_CODE_VERSIONS_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    String                 BIOSVersion;
    uint32_t               VersionsCount;
    String                 Versions;
}   CFG_GET_CODE_VERSIONS_RESPONSE;

CFG_GET_CODE_VERSIONS_RESPONSE CFG_GetCodeVersions_Response(uint32_t Length = 0)
{
    CFG_GET_CODE_VERSIONS_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400001A; //0x0480001A;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    Data.BIOSVersion = "";
    Data.VersionsCount = 6;
    Data.Versions = "UEFI EDKII";
    return Data;
}

typedef struct _CFG_GET_CODE_VERSIONS
{
    CFG_GET_CODE_VERSIONS_REQUEST Request;
    CFG_GET_CODE_VERSIONS_RESPONSE Response;
}   CFG_GET_CODE_VERSIONS;

AMT_STATUS CFG_GetCodeVersions()
{
    CFG_GET_CODE_VERSIONS Data = {0};
    Data.Request = CFG_GetCodeVersions_Request();
    Data.Response = CFG_GetCodeVersions_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_CONTROL_MODE_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_GET_CONTROL_MODE_REQUEST;

CFG_GET_CONTROL_MODE_REQUEST CFG_GetControlMode_Request(uint32_t Length = 0)
{
    CFG_GET_CONTROL_MODE_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x0400006B;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_GET_CONTROL_MODE_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    uint32_t               ControlMode;
}   CFG_GET_CONTROL_MODE_RESPONSE;

CFG_GET_CONTROL_MODE_RESPONSE CFG_GetControlMode_Response(uint32_t Length = 0)
{
    CFG_GET_CONTROL_MODE_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400006B; //0x0480006B;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    Data.ControlMode = 0; //(1 - Client, 2 - Admin)
    return Data;
}

typedef struct _CFG_GET_CONTROL_MODE
{
    CFG_GET_CONTROL_MODE_REQUEST Request;
    CFG_GET_CONTROL_MODE_RESPONSE Response;
}   CFG_GET_CONTROL_MODE;

AMT_STATUS CFG_GetControlMode()
{
    CFG_GET_CONTROL_MODE Data = {0};
    Data.Request = CFG_GetControlMode_Request();
    Data.Response = CFG_GetControlMode_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_LOCAL_SYSTEM_ACCOUNT_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
    uint8_t                Reserved[40];
}   CFG_GET_LOCAL_SYSTEM_ACCOUNT_REQUEST;

CFG_GET_LOCAL_SYSTEM_ACCOUNT_REQUEST CFG_GetLocalSystemAccount_Request(uint32_t Length = 0)
{
    CFG_GET_LOCAL_SYSTEM_ACCOUNT_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000067;
    Data.Header.Length = Length;
    for (size_t i = 0; i < 40; ++i) { Data.Reserved[i] = 0; }
    return Data;
}

typedef struct _CFG_GET_LOCAL_SYSTEM_ACCOUNT_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    String                 Username;
    String                 Passphrase;
}   CFG_GET_LOCAL_SYSTEM_ACCOUNT_RESPONSE;

CFG_GET_LOCAL_SYSTEM_ACCOUNT_RESPONSE CFG_GetLocalSystemAccount_Response(uint32_t Length = 0)
{
    CFG_GET_LOCAL_SYSTEM_ACCOUNT_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000067; //0x04800067;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    Data.Username = "Username";
    Data.Passphrase = "Passphrase";
    return Data;
}

typedef struct _CFG_GET_LOCAL_SYSTEM_ACCOUNT
{
    CFG_GET_LOCAL_SYSTEM_ACCOUNT_REQUEST Request;
    CFG_GET_LOCAL_SYSTEM_ACCOUNT_RESPONSE Response;
}   CFG_GET_LOCAL_SYSTEM_ACCOUNT;

AMT_STATUS CFG_GetLocalSystemAccount()
{
    CFG_GET_LOCAL_SYSTEM_ACCOUNT Data = {0};
    Data.Request = CFG_GetLocalSystemAccount_Request();
    Data.Response = CFG_GetLocalSystemAccount_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_ME_SETUP_AUDIT_RECORD_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_GET_ME_SETUP_AUDIT_RECORD_REQUEST;

CFG_GET_ME_SETUP_AUDIT_RECORD_REQUEST CFG_GetMESetupAuditRecord(uint32_t Length = 0)
{
    CFG_GET_ME_SETUP_AUDIT_RECORD_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000050;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _ME_ADMIN_AUDIT_RECORD
{
    String ProvisioningTLSMode;
    bool SecureDNS;
    bool HostInitiated;
    String SelectedHashData;
    String HashAlgo;
    String CACertificateSerials;
    String AdditionalCASerials;
    bool IsOemDefault;
    bool IsTimeValid;
    String ProvisioningServerIP;
    bool TLSStartTime;
    String ProvisioningServerFQDN;
}   ME_ADMIN_AUDIT_RECORD;

ME_ADMIN_AUDIT_RECORD CFG_GetMESetupAuditRecord_Default()
{
    ME_ADMIN_AUDIT_RECORD Data = {}; //{0};
    Data.ProvisioningTLSMode = "PSK"; //"PKI-CH";
    Data.SecureDNS = true; //false;
    Data.HostInitiated = false; //true;
    Data.SelectedHashData = "XABC123X";
    Data.HashAlgo = "SHA1"; //"MD5";
    Data.CACertificateSerials = "A B C D E F";
    Data.AdditionalCASerials = "G H I";
    Data.IsOemDefault = false; //true;
    Data.IsTimeValid = true; //false;
    Data.ProvisioningServerIP = "127.0.0.1";
    Data.TLSStartTime = false; //true;
    Data.ProvisioningServerFQDN = "localhost";
    return Data;
}

CFG_GET_ME_SETUP_AUDIT_RECORD_REQUEST CFG_GetMESetupAuditRecord_Request(uint32_t Length = 0)
{
    CFG_GET_ME_SETUP_AUDIT_RECORD_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000050;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_GET_ME_SETUP_AUDIT_RECORD_RESPONSE
{
    PTHI_MESSAGE_HEADER      Header;
    AMT_STATUS               Status;
    ME_ADMIN_AUDIT_RECORD    AuditRecord;
}   CFG_GET_ME_SETUP_AUDIT_RECORD_RESPONSE;

CFG_GET_ME_SETUP_AUDIT_RECORD_RESPONSE CFG_GetMESetupAuditRecord_Response(uint32_t Length = 0)
{
    CFG_GET_ME_SETUP_AUDIT_RECORD_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000050; //0x04800050;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    //Data.Status = AMT_STATUS_AUDIT_RECORD_NOT_PRESENT; //!!!
    //Data.Status = AMT_STATUS_NOT_FOUND;
    Data.AuditRecord = CFG_GetMESetupAuditRecord_Default();
    return Data;
}

typedef struct _CFG_GET_ME_SETUP_AUDIT_RECORD
{
    CFG_GET_ME_SETUP_AUDIT_RECORD_REQUEST Request;
    CFG_GET_ME_SETUP_AUDIT_RECORD_RESPONSE Response;
}   CFG_GET_ME_SETUP_AUDIT_RECORD;

AMT_STATUS CFG_GetMESetupAuditRecord()
{
    CFG_GET_ME_SETUP_AUDIT_RECORD Data = {0};
    Data.Request = CFG_GetMESetupAuditRecord_Request();
    Data.Response = CFG_GetMESetupAuditRecord_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_AUDIT_LOG_RECORDS_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
    uint32_t               StartIndex;
}   CFG_GET_AUDIT_LOG_RECORDS_REQUEST;

CFG_GET_AUDIT_LOG_RECORDS_REQUEST CFG_GetAuditLogRecords_Request(uint32_t Length = 0, uint32_t StartIndex = 0)
{
    CFG_GET_AUDIT_LOG_RECORDS_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000087;
    Data.Header.Length = Length;
    Data.StartIndex = StartIndex;
    return Data;
}

typedef struct _CFG_GET_AUDIT_LOG_RECORDS_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    uint32_t               TotalRecordsCount;
    uint32_t               ReturnedRecordsCount;
    uint8_t                RecordsBuffer[0];
}   CFG_GET_AUDIT_LOG_RECORDS_RESPONSE;

CFG_GET_AUDIT_LOG_RECORDS_RESPONSE CFG_GetAuditLogRecords_Response(uint32_t Length = 0)
{
    CFG_GET_AUDIT_LOG_RECORDS_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000087; //0x04800087;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_INVALID_INDEX; //!!!
    Data.Status = AMT_STATUS_INVALID_HANDLE;
    Data.TotalRecordsCount = 0;
    Data.ReturnedRecordsCount = 0;
    for (size_t i = 0; i < 0; ++i) { Data.RecordsBuffer[i] = 0; }
    return Data;
}

typedef struct _CFG_GET_AUDIT_LOG_RECORDS
{
    CFG_GET_AUDIT_LOG_RECORDS_REQUEST Request;
    CFG_GET_AUDIT_LOG_RECORDS_RESPONSE Response;
}   CFG_GET_AUDIT_LOG_RECORDS;

AMT_STATUS CFG_GetAuditLogRecords()
{
    CFG_GET_AUDIT_LOG_RECORDS Data = {0};
    Data.Request = CFG_GetAuditLogRecords_Request();
    Data.Response = CFG_GetAuditLogRecords_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_AUDIT_LOG_SIGNATURE_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
    uint8_t                MCNuance[20];
}   CFG_GET_AUDIT_LOG_SIGNATURE_REQUEST;

CFG_GET_AUDIT_LOG_SIGNATURE_REQUEST CFG_GetAuditLogSignature_Request(uint32_t Length = 0)
{
    CFG_GET_AUDIT_LOG_SIGNATURE_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x0400008C; //0x08C;
    Data.Header.Length = Length;
    for (size_t i = 0; i < 20; ++i) { Data.MCNuance[i] = 0; }
    return Data;
}

typedef struct _AMT_DATETIME
{
    uint16_t    Year;
    uint16_t    Month;
    uint16_t    DayOfWeek;
    uint16_t    Day;
    uint16_t    Hour;
    uint16_t    Minute;
    uint16_t    Second;
}   AMT_DATETIME;

AMT_DATETIME CFG_GetAuditLogSignatureDateTime_Default()
{
    AMT_DATETIME Data = {0};
    Data.Year = 0;
    Data.Month = 0;
    Data.DayOfWeek = 0;
    Data.Day = 0;
    Data.Hour = 0;
    Data.Minute = 0;
    Data.Second = 0;
    return Data;
}

typedef struct _CFG_GET_AUDIT_LOG_SIGNATURE_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    uint32_t               TotalRecordCount;
    AMT_DATETIME           StartLogTime;
    AMT_DATETIME           EndLogTime;
    AMT_DATETIME           SignatureGenerationTime;
    String                 AuditLogHash; //!!! This being a String of unknown length conflicts with [] initialisation
    uint8_t                AMTNuance[20];
    String                 UUID;
    String                 FQDN;
    String                 FWVersion;
    uint32_t               AMTSVN;
    uint32_t               SignatureMechanism;
    //uint8_t                Signature[]; //[512];
    //uint16_t               LengthsOfCertificates[]; //[4];
    //uint8_t                Certificates[]; //[3000];
    String                 Signature;
    String                 LengthsOfCertificates;
    String                 Certificates;
}   CFG_GET_AUDIT_LOG_SIGNATURE_RESPONSE;

CFG_GET_AUDIT_LOG_SIGNATURE_RESPONSE CFG_GetAuditLogSignature_Response(uint32_t Length = 0)
{
    CFG_GET_AUDIT_LOG_SIGNATURE_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400008C; //0x0480008C; //0x008C;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    Data.Status = AMT_STATUS_INVALID_PARAMETER;
    //Data.Status = AMT_STATUS_UNSUPPORTED; //!!!
    //Data.Status = AMT_STATUS_DATA_MISSING; //!!!
    //Data.Status = AMT_STATUS_NOT_FOUND;
    Data.TotalRecordCount = 390;
    Data.StartLogTime = CFG_GetAuditLogSignatureDateTime_Default();
    Data.EndLogTime = CFG_GetAuditLogSignatureDateTime_Default();
    Data.SignatureGenerationTime = CFG_GetAuditLogSignatureDateTime_Default();
    Data.AuditLogHash = "";
    for (size_t i = 0; i < 20; ++i) { Data.AMTNuance[i] = 0; }
    Data.UUID = GUID_DEVINTERFACE_HECI;
    Data.FQDN = "localhost";
    Data.FWVersion = "0";
    Data.AMTSVN = 0;
    Data.SignatureMechanism = 0; //ECDSA-P384 w/ SHA384
    //for (size_t i = 0; i < 512; ++i) { Data.Signature[i] = 0; }
    //for (size_t i = 0; i < 4; ++i) { Data.LengthsOfCertificates[i] = 0; }
    //for (size_t i = 0; i < 3000; ++i) { Data.Certificates[i] = 0; }
    Data.Signature = "";
    Data.LengthsOfCertificates = "";
    Data.Certificates = "";
    return Data;
}

typedef struct _CFG_GET_AUDIT_LOG_SIGNATURE
{
    CFG_GET_AUDIT_LOG_SIGNATURE_REQUEST Request;
    CFG_GET_AUDIT_LOG_SIGNATURE_RESPONSE Response;
}   CFG_GET_AUDIT_LOG_SIGNATURE;

AMT_STATUS CFG_GetAuditLogSignature()
{
    CFG_GET_AUDIT_LOG_SIGNATURE Data = {0};
    Data.Request = CFG_GetAuditLogSignature_Request();
    Data.Response = CFG_GetAuditLogSignature_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_PID_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_GET_PID_REQUEST;

CFG_GET_PID_REQUEST CFG_GetPID_Request(uint32_t Length = 0)
{
    CFG_GET_PID_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x0400003B;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_GET_PID_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    uint8_t                PID[8];
}   CFG_GET_PID_RESPONSE;

CFG_GET_PID_RESPONSE CFG_GetPID_Response(uint32_t Length = 0)
{
    CFG_GET_PID_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400003B; //0x0480003B;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    for (size_t i = 0; i < 8; ++i) { Data.PID[i] = 0; }
    return Data;
}

typedef struct _CFG_GET_PID
{
    CFG_GET_PID_REQUEST Request;
    CFG_GET_PID_RESPONSE Response;
}   CFG_GET_PID;

AMT_STATUS CFG_GetPID()
{
    CFG_GET_PID Data = {0};
    Data.Request = CFG_GetPID_Request();
    Data.Response = CFG_GetPID_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_PKI_FQDN_SUFFIX_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_GET_PKI_FQDN_SUFFIX_REQUEST;

CFG_GET_PKI_FQDN_SUFFIX_REQUEST CFG_GetPKIFQDNSuffix_Request(uint32_t Length = 0)
{
    CFG_GET_PKI_FQDN_SUFFIX_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000036;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_GET_PKI_FQDN_SUFFIX_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    String                 Suffix;
}   CFG_GET_PKI_FQDN_SUFFIX_RESPONSE;

CFG_GET_PKI_FQDN_SUFFIX_RESPONSE CFG_GetPKIFQDNSuffix_Response(uint32_t Length = 0)
{
    CFG_GET_PKI_FQDN_SUFFIX_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000036; //0x04800036;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    Data.Suffix = ".local";
    return Data;
}

typedef struct _CFG_GET_PKI_FQDN_SUFFIX
{
    CFG_GET_PKI_FQDN_SUFFIX_REQUEST Request;
    CFG_GET_PKI_FQDN_SUFFIX_RESPONSE Response;
}   CFG_GET_PKI_FQDN_SUFFIX;

AMT_STATUS CFG_GetPKIFQDNSuffix()
{
    CFG_GET_PKI_FQDN_SUFFIX Data = {0};
    Data.Request = CFG_GetPKIFQDNSuffix_Request();
    Data.Response = CFG_GetPKIFQDNSuffix_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_PROVISIONING_STATE_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_GET_PROVISIONING_STATE_REQUEST;

CFG_GET_PROVISIONING_STATE_REQUEST CFG_GetProvisioningState_Request(uint32_t Length = 0)
{
    CFG_GET_PROVISIONING_STATE_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000011;
    Data.Header.Length = Length;
    return Data;
}

enum AMT_PROVISIONING_STATE
{
    AMT_PRE_PROVISIONED = 0,
    AMT_IN_PROVISIONING = 1,
    AMT_POST_PROVISIONED = 2,
};

typedef struct _CFG_GET_PROVISIONING_STATE_RESPONSE
{
    PTHI_MESSAGE_HEADER       Header;
    AMT_STATUS                Status;
    AMT_PROVISIONING_STATE    ProvisioningState;
}   CFG_GET_PROVISIONING_STATE_RESPONSE;

CFG_GET_PROVISIONING_STATE_RESPONSE CFG_GetProvisioningState_Response(uint32_t Length = 0)
{
    CFG_GET_PROVISIONING_STATE_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000011; //0x04800011;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    Data.ProvisioningState = AMT_PRE_PROVISIONED;
    return Data;
}

typedef struct _CFG_GET_PROVISIONING_STATE
{
    CFG_GET_PROVISIONING_STATE_REQUEST Request;
    CFG_GET_PROVISIONING_STATE_RESPONSE Response;
}   CFG_GET_PROVISIONING_STATE;

AMT_STATUS CFG_GetProvisioningState()
{
    CFG_GET_PROVISIONING_STATE Data = {0};
    Data.Request = CFG_GetProvisioningState_Request();
    Data.Response = CFG_GetProvisioningState_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_PROVISIONING_TLS_MODE_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_GET_PROVISIONING_TLS_MODE_REQUEST;

CFG_GET_PROVISIONING_TLS_MODE_REQUEST CFG_GetProvisioningTLSMode_Request(uint32_t Length = 0)
{
    CFG_GET_PROVISIONING_TLS_MODE_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x0400002B;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_GET_PROVISIONING_TLS_MODE_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    uint32_t               ProvisioningTLSMode;
}   CFG_GET_PROVISIONING_TLS_MODE_RESPONSE;

CFG_GET_PROVISIONING_TLS_MODE_RESPONSE CFG_GetProvisioningTLSMode_Response(uint32_t Length = 0)
{
    CFG_GET_PROVISIONING_TLS_MODE_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400002B; //0x0480002B;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    Data.ProvisioningTLSMode = 1; //0 - Unknown, 1 - PSK, 2 - PKI
    return Data;
}

typedef struct _CFG_GET_PROVISIONING_TLS_MODE
{
    CFG_GET_PROVISIONING_TLS_MODE_REQUEST Request;
    CFG_GET_PROVISIONING_TLS_MODE_RESPONSE Response;
}   CFG_GET_PROVISIONING_TLS_MODE;

AMT_STATUS CFG_GetProvisioningTLSMode()
{
    CFG_GET_PROVISIONING_TLS_MODE Data = {0};
    Data.Request = CFG_GetProvisioningTLSMode_Request();
    Data.Response = CFG_GetProvisioningTLSMode_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_RNG_SEED_STATUS_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_GET_RNG_SEED_STATUS_REQUEST;

CFG_GET_RNG_SEED_STATUS_REQUEST CFG_GetRNGSeedStatus_Request(uint32_t Length = 0)
{
    CFG_GET_RNG_SEED_STATUS_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x0400002E;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_GET_RNG_SEED_STATUS_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    uint32_t               RNGStatus;
}   CFG_GET_RNG_SEED_STATUS_RESPONSE;

CFG_GET_RNG_SEED_STATUS_RESPONSE CFG_GetRNGSeedStatus_Response(uint32_t Length = 0)
{
    CFG_GET_RNG_SEED_STATUS_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400002E; //0x0480002E;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    Data.RNGStatus = 0; //0 - exists, 1 - in progress, 2 - does not exist
    return Data;
}

typedef struct _CFG_GET_RNG_SEED_STATUS
{
    CFG_GET_RNG_SEED_STATUS_REQUEST Request;
    CFG_GET_RNG_SEED_STATUS_RESPONSE Response;
}   CFG_GET_RNG_SEED_STATUS;

AMT_STATUS CFG_GetRNGSeedStatus()
{
    CFG_GET_RNG_SEED_STATUS Data = {0};
    Data.Request = CFG_GetRNGSeedStatus_Request();
    Data.Response = CFG_GetRNGSeedStatus_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_ZTC_ENABLED_STATUS_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_GET_ZTC_ENABLED_STATUS_REQUEST;

CFG_GET_ZTC_ENABLED_STATUS_REQUEST CFG_GetZTCEnabledStatus_Request(uint32_t Length = 0)
{
    CFG_GET_ZTC_ENABLED_STATUS_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000030;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_GET_ZTC_ENABLED_STATUS_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    bool                   Enabled;
}   CFG_GET_ZTC_ENABLED_STATUS_RESPONSE;

CFG_GET_ZTC_ENABLED_STATUS_RESPONSE CFG_GetZTCEnabledStatus_Response(uint32_t Length = 0)
{
    CFG_GET_ZTC_ENABLED_STATUS_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000030; //0x04800030;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    Data.Enabled = true; //false;
    return Data;
}

typedef struct _CFG_GET_ZTC_ENABLED_STATUS
{
    CFG_GET_ZTC_ENABLED_STATUS_REQUEST Request;
    CFG_GET_ZTC_ENABLED_STATUS_RESPONSE Response;
}   CFG_GET_ZTC_ENABLED_STATUS;

AMT_STATUS CFG_GetZTCEnabledStatus()
{
    CFG_GET_ZTC_ENABLED_STATUS Data = {0};
    Data.Request = CFG_GetZTCEnabledStatus_Request();
    Data.Response = CFG_GetZTCEnabledStatus_Response();
    return Data.Response.Status;
}

typedef struct _CFG_SET_PKI_FQDN_SUFFIX_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
    String                 Suffix;
}   CFG_SET_PKI_FQDN_SUFFIX_REQUEST;

CFG_SET_PKI_FQDN_SUFFIX_REQUEST CFG_SetPKIFQDNSuffix_Request(uint32_t Length = 0)
{
    CFG_SET_PKI_FQDN_SUFFIX_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x0400002F;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_SET_PKI_FQDN_SUFFIX_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
}   CFG_SET_PKI_FQDN_SUFFIX_RESPONSE;

CFG_SET_PKI_FQDN_SUFFIX_RESPONSE CFG_SetPKIFQDNSuffix_Response(uint32_t Length = 0)
{
    CFG_SET_PKI_FQDN_SUFFIX_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400002F; //0x0480003F;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    //Data.Status = AMT_STATUS_INVALID_PARAMETER;
    //Data.Status = AMT_STATUS_INVALID_AMT_STATE; //!!!
    Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    return Data;
}

typedef struct _CFG_SET_PKI_FQDN_SUFFIX
{
    CFG_SET_PKI_FQDN_SUFFIX_REQUEST Request;
    CFG_SET_PKI_FQDN_SUFFIX_RESPONSE Response;
}   CFG_SET_PKI_FQDN_SUFFIX;

AMT_STATUS CFG_SetPKIFQDNSuffix()
{
    CFG_SET_PKI_FQDN_SUFFIX Data = {0};
    Data.Request = CFG_SetPKIFQDNSuffix_Request();
    Data.Response = CFG_SetPKIFQDNSuffix_Response();
    return Data.Response.Status;
}

typedef struct _CFG_SET_PROVISIONING_SERVER_OTP_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
    String                 OTP;
}   CFG_SET_PROVISIONING_SERVER_OTP_REQUEST;

CFG_SET_PROVISIONING_SERVER_OTP_REQUEST CFG_SetProvisioningServerOTP_Request(uint32_t Length = 0, String OTP = "OTP")
{
    CFG_SET_PROVISIONING_SERVER_OTP_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x0400002A;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_SET_PROVISIONING_SERVER_OTP_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
}   CFG_SET_PROVISIONING_SERVER_OTP_RESPONSE;

CFG_SET_PROVISIONING_SERVER_OTP_RESPONSE CFG_SetProvisioningServerOTP_Response(uint32_t Length = 0)
{
    CFG_SET_PROVISIONING_SERVER_OTP_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400002A; //0x0480002A;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    //Data.Status = AMT_STATUS_INVALID_PARAMETER;
    return Data;
}

typedef struct _CFG_SET_PROVISIONING_SERVER_OTP
{
    CFG_SET_PROVISIONING_SERVER_OTP_REQUEST Request;
    CFG_SET_PROVISIONING_SERVER_OTP_RESPONSE Response;
}   CFG_SET_PROVISIONING_SERVER_OTP;

AMT_STATUS CFG_SetProvisioningServerOTP()
{
    CFG_SET_PROVISIONING_SERVER_OTP Data = {0};
    Data.Request = CFG_SetProvisioningServerOTP_Request();
    Data.Response = CFG_SetProvisioningServerOTP_Response();
    return Data.Response.Status;
}

typedef struct _CFG_SET_ZERO_TOUCH_ENABLED_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
    bool                   Mode;
}   CFG_SET_ZERO_TOUCH_ENABLED_REQUEST;

CFG_SET_ZERO_TOUCH_ENABLED_REQUEST CFG_SetZeroTouchEnabled_Request(uint32_t Length = 0, bool Mode = true)
{
    CFG_SET_ZERO_TOUCH_ENABLED_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x0400003A;
    Data.Header.Length = Length;
    Data.Mode = Mode;
    return Data;
}

typedef struct _CFG_SET_ZERO_TOUCH_ENABLED_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
}   CFG_SET_ZERO_TOUCH_ENABLED_RESPONSE;

CFG_SET_ZERO_TOUCH_ENABLED_RESPONSE CFG_SetZeroTouchEnabled_Response(uint32_t Length = 0)
{
    CFG_SET_ZERO_TOUCH_ENABLED_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400003A; //0x0480003A;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    //Data.Status = AMT_STATUS_NOT_PERMITTED; //!!!
    return Data;
}

typedef struct _CFG_SET_ZERO_TOUCH_ENABLED
{
    CFG_SET_ZERO_TOUCH_ENABLED_REQUEST Request;
    CFG_SET_ZERO_TOUCH_ENABLED_RESPONSE Response;
}   CFG_SET_ZERO_TOUCH_ENABLED;

AMT_STATUS CFG_SetZeroTouchEnabled()
{
    CFG_SET_ZERO_TOUCH_ENABLED Data = {0};
    Data.Request = CFG_SetZeroTouchEnabled_Request();
    Data.Response = CFG_SetZeroTouchEnabled_Response();
    return Data.Response.Status;
}

typedef struct _CFG_SET_EHBC_STATE_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
    uint32_t               State;
}   CFG_SET_EHBC_STATE_REQUEST;

CFG_SET_EHBC_STATE_REQUEST CFG_SetEHBCState_Request(uint32_t Length = 0, uint32_t State = 0)
{
    CFG_SET_EHBC_STATE_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000085;
    Data.Header.Length = Length;
    Data.State = State;
    return Data;
}

typedef struct _CFG_SET_EHBC_STATE_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
}   CFG_SET_EHBC_STATE_RESPONSE;

CFG_SET_EHBC_STATE_RESPONSE CFG_SetEHBCState_Response(uint32_t Length = 0)
{
    CFG_SET_EHBC_STATE_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000085; //0x04800085;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    //Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    Data.Status = AMT_STATUS_INVALID_PARAMETER;
    return Data;
}

typedef struct _CFG_SET_EHBC_STATE
{
    CFG_SET_EHBC_STATE_REQUEST Request;
    CFG_SET_EHBC_STATE_RESPONSE Response;
}   CFG_SET_EHBC_STATE;

AMT_STATUS CFG_SetEHBCState()
{
    CFG_SET_EHBC_STATE Data = {0};
    Data.Request = CFG_SetEHBCState_Request();
    Data.Response = CFG_SetEHBCState_Response();
    return Data.Response.Status;
}

typedef struct _CFG_GET_EHBC_STATE_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
    uint32_t               State;
}   CFG_GET_EHBC_STATE_REQUEST;

CFG_GET_EHBC_STATE_REQUEST CFG_GetEHBCState_Request(uint32_t Length = 0)
{
    CFG_GET_EHBC_STATE_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000084;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_GET_EHBC_STATE_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
    uint32_t               State;
}   CFG_GET_EHBC_STATE_RESPONSE;

CFG_GET_EHBC_STATE_RESPONSE CFG_GetEHBCState_Response(uint32_t Length = 0)
{
    CFG_GET_EHBC_STATE_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000084; //0x04800084;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    Data.State = 1; //0 - disabled, 1 - enabled
    return Data;
}

typedef struct _CFG_GET_EHBC_STATE
{
    CFG_GET_EHBC_STATE_REQUEST Request;
    CFG_GET_EHBC_STATE_RESPONSE Response;
}   CFG_GET_EHBC_STATE;

AMT_STATUS CFG_GetEHBCState()
{
    CFG_GET_EHBC_STATE Data = {0};
    Data.Request = CFG_GetEHBCState_Request();
    Data.Response = CFG_GetEHBCState_Response();
    return Data.Response.Status;
}

typedef struct _CFG_START_CONFIGURATION_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_START_CONFIGURATION_REQUEST;

CFG_START_CONFIGURATION_REQUEST CFG_StartConfiguration_Request(uint32_t Length = 0)
{
    CFG_START_CONFIGURATION_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000029;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_START_CONFIGURATION_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
}   CFG_START_CONFIGURATION_RESPONSE;

CFG_START_CONFIGURATION_RESPONSE CFG_StartConfiguration_Response(uint32_t Length = 0)
{
    CFG_START_CONFIGURATION_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000029; //0x04800029;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_RNG_NOT_READY;
    //Data.Status = AMT_STATUS_CERTIFICATE_NOT_READY;
    //Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    return Data;
}

typedef struct _CFG_START_CONFIGURATION
{
    CFG_START_CONFIGURATION_REQUEST Request;
    CFG_START_CONFIGURATION_RESPONSE Response;
}   CFG_START_CONFIGURATION;

AMT_STATUS CFG_StartConfiguration()
{
    CFG_START_CONFIGURATION Data = {0};
    Data.Request = CFG_StartConfiguration_Request();
    Data.Response = CFG_StartConfiguration_Response();
    return Data.Response.Status;
}

typedef struct _CFG_START_CONFIGURATION_EX_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
    bool                   IPv6Enable;
}   CFG_START_CONFIGURATION_EX_REQUEST;

CFG_START_CONFIGURATION_EX_REQUEST CFG_StartConfigurationEx_Request(uint32_t Length = 0, bool IPv6Enable = false)
{
    CFG_START_CONFIGURATION_EX_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000062;
    Data.Header.Length = Length;
    Data.IPv6Enable = IPv6Enable;
    return Data;
}

typedef struct _CFG_START_CONFIGURATION_EX_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
}   CFG_START_CONFIGURATION_EX_RESPONSE;

CFG_START_CONFIGURATION_EX_RESPONSE CFG_StartConfigurationEx_Response(uint32_t Length = 0)
{
    CFG_START_CONFIGURATION_EX_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000062; //0x04800062;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_RNG_NOT_READY;
    //Data.Status = AMT_STATUS_CERTIFICATE_NOT_READY;
    //Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    return Data;
}

typedef struct _CFG_START_CONFIGURATION_EX
{
    CFG_START_CONFIGURATION_EX_REQUEST Request;
    CFG_START_CONFIGURATION_EX_RESPONSE Response;
}   CFG_START_CONFIGURATION_EX;

AMT_STATUS CFG_StartConfigurationEx()
{
    CFG_START_CONFIGURATION_EX Data = {0};
    Data.Request = CFG_StartConfigurationEx_Request();
    Data.Response = CFG_StartConfigurationEx_Response();
    return Data.Response.Status;
}

enum CERTIFICATE_HASH_ALGORITHM
{
    CERTIFICATE_HASH_ALGORITHM_SHA256 = 0,
    CERTIFICATE_HASH_ALGORITHM_SHA384 = 1,
    CERTIFICATE_HASH_ALGORITHM_SHA224 = 2,
    CERTIFICATE_HASH_ALGORITHM_SHA512 = 3,
};

typedef struct _CFG_START_CONFIGURATION_H_BASED_REQUEST
{
    PTHI_MESSAGE_HEADER           Header;
    CERTIFICATE_HASH_ALGORITHM    ServerHashAlgorithm;
    String                        ServerCertificateHash;
    bool                          HostVPNEnable;
    uint32_t                      SuffixListLength;
    String                        NetworkDNSSuffixList;
}   CFG_START_CONFIGURATION_H_BASED_REQUEST;

CFG_START_CONFIGURATION_H_BASED_REQUEST CFG_StartConfigurationHBased_Request(uint32_t Length = 0,
    CERTIFICATE_HASH_ALGORITHM ServerHashAlgorithm = CERTIFICATE_HASH_ALGORITHM_SHA256,
    String ServerCertificateHash = "X123ABCX",
    bool HostVPNEnable = true,
    uint32_t SuffixListLength = 0,
    String NetworkDNSSuffixList = "")
{
    CFG_START_CONFIGURATION_H_BASED_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000029;
    Data.Header.Length = Length;
    Data.ServerHashAlgorithm = ServerHashAlgorithm;
    Data.ServerCertificateHash = ServerCertificateHash;
    Data.HostVPNEnable = HostVPNEnable;
    Data.SuffixListLength = SuffixListLength;
    Data.NetworkDNSSuffixList = NetworkDNSSuffixList;
    return Data;
}

typedef struct _CFG_START_CONFIGURATION_H_BASED_RESPONSE
{
    PTHI_MESSAGE_HEADER           Header;
    AMT_STATUS                    Status;
    CERTIFICATE_HASH_ALGORITHM    HashAlgorithm;
    String                        AMTCertificateHash;
}   CFG_START_CONFIGURATION_H_BASED_RESPONSE;

CFG_START_CONFIGURATION_H_BASED_RESPONSE CFG_StartConfigurationHBased_Response(uint32_t Length = 0)
{
    CFG_START_CONFIGURATION_H_BASED_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400008B; //0x0480008B;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_RNG_NOT_READY;
    //Data.Status = AMT_STATUS_CERTIFICATE_NOT_READY;
    //Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    Data.HashAlgorithm = CERTIFICATE_HASH_ALGORITHM_SHA256;
    Data.AMTCertificateHash = "X123ABCX";
    return Data;
}

typedef struct _CFG_START_CONFIGURATION_H_BASED
{
    CFG_START_CONFIGURATION_H_BASED_REQUEST Request;
    CFG_START_CONFIGURATION_H_BASED_RESPONSE Response;
}   CFG_START_CONFIGURATION_H_BASED;

AMT_STATUS CFG_StartConfigurationHBased()
{
    CFG_START_CONFIGURATION_H_BASED Data = {0};
    Data.Request = CFG_StartConfigurationHBased_Request();
    Data.Response = CFG_StartConfigurationHBased_Response();
    return Data.Response.Status;
}

typedef struct _CFG_HALT_CONFIGURATION_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_HALT_CONFIGURATION_REQUEST;

CFG_HALT_CONFIGURATION_REQUEST CFG_HaltConfiguration_Request(uint32_t Length = 0)
{
    CFG_HALT_CONFIGURATION_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x0400005E;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_HALT_CONFIGURATION_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
}   CFG_HALT_CONFIGURATION_RESPONSE;

CFG_HALT_CONFIGURATION_RESPONSE CFG_HaltConfiguration_Response(uint32_t Length = 0)
{
    CFG_HALT_CONFIGURATION_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x8400005E; //0x0480005E;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    return Data;
}

typedef struct _CFG_HALT_CONFIGURATION
{
    CFG_HALT_CONFIGURATION_REQUEST Request;
    CFG_HALT_CONFIGURATION_RESPONSE Response;
}   CFG_HALT_CONFIGURATION;

AMT_STATUS CFG_HaltConfiguration()
{
    CFG_HALT_CONFIGURATION Data = {0};
    Data.Request = CFG_HaltConfiguration_Request();
    Data.Response = CFG_HaltConfiguration_Response();
    return Data.Response.Status;
}

typedef struct _CFG_UNPROVISION_REQUEST
{
    PTHI_MESSAGE_HEADER    Header;
}   CFG_UNPROVISION_REQUEST;

CFG_UNPROVISION_REQUEST CFG_Unprovision_Request(uint32_t Length = 0)
{
    CFG_UNPROVISION_REQUEST Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x04000010;
    Data.Header.Length = Length;
    return Data;
}

typedef struct _CFG_UNPROVISION_RESPONSE
{
    PTHI_MESSAGE_HEADER    Header;
    AMT_STATUS             Status;
}   CFG_UNPROVISION_RESPONSE;

CFG_UNPROVISION_RESPONSE CFG_Unprovision_Response(uint32_t Length = 0)
{
    CFG_UNPROVISION_RESPONSE Data = {0};
    Data.Header.Version.MajorNumber = AMT_MAJOR_VERSION;
    Data.Header.Version.MinorNumber = AMT_MINOR_VERSION;
    Data.Header.Reserved = 0x0000;
    Data.Header.Command = 0x84000010; //0x04800010;
    Data.Header.Length = Length;
    //Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY; //!!!
    Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    //Data.Status = AMT_STATUS_INVALID_MESSAGE_LENGTH;
    return Data;
}

typedef struct _CFG_UNPROVISION
{
    CFG_UNPROVISION_REQUEST Request;
    CFG_UNPROVISION_RESPONSE Response;
}   CFG_UNPROVISION;

AMT_STATUS CFG_Unprovision()
{
    CFG_UNPROVISION Data = {0};
    Data.Request = CFG_Unprovision_Request();
    Data.Response = CFG_Unprovision_Response();
    return Data.Response.Status;
}

typedef struct _MHC_SET_AMT_OPERATIONAL_STATE_REQUEST
{
    uint8_t Command;
    uint8_t ByteCount;
    uint8_t SubCommand;
    uint8_t VersionNumber;
    uint8_t Enabled;
}   MHC_SET_AMT_OPERATIONAL_STATE_REQUEST;

MHC_SET_AMT_OPERATIONAL_STATE_REQUEST MHC_SetAMTOperationalState_Request
(
    uint8_t Command = 0x05,
    uint8_t ByteCount = 0x03,
    uint8_t SubCommand = 0x53,
    uint8_t VersionNumber = 0x10,
    uint8_t Enabled = 1
)
{
    MHC_SET_AMT_OPERATIONAL_STATE_REQUEST Data = {0};
    Data.Command = Command;
    Data.ByteCount = ByteCount;
    Data.SubCommand = SubCommand;
    Data.VersionNumber = VersionNumber;
    Data.Enabled = Enabled;
    return Data;
}

typedef struct _MHC_SET_AMT_OPERATIONAL_STATE_RESPONSE
{
    AMT_STATUS    Status;
}   MHC_SET_AMT_OPERATIONAL_STATE_RESPONSE;

MHC_SET_AMT_OPERATIONAL_STATE_RESPONSE MHC_SetAMTOperationalState_Response()
{
    MHC_SET_AMT_OPERATIONAL_STATE_RESPONSE Data = {0};
    Data.Status = AMT_STATUS_SUCCESS;
    //Data.Status = AMT_STATUS_INTERNAL_ERROR;
    //Data.Status = AMT_STATUS_NOT_READY;
    //Data.Status = AMT_STATUS_INVALID_AMT_MODE;
    //Data.Status = AMT_NOT_PERMITTED; //!!!
    return Data;
}

typedef struct _MHC_SET_AMT_OPERATIONAL_STATE
{
    MHC_SET_AMT_OPERATIONAL_STATE_REQUEST Request;
    MHC_SET_AMT_OPERATIONAL_STATE_RESPONSE Response;
}   MHC_SET_AMT_OPERATIONAL_STATE;

AMT_STATUS MHC_SetAMTOperationalState()
{
    MHC_SET_AMT_OPERATIONAL_STATE Data = {0};
    Data.Request = MHC_SetAMTOperationalState_Request();
    Data.Response = MHC_SetAMTOperationalState_Response();
    return Data.Response.Status;
}

typedef struct _SI_CHANGE_TO_AMT_REQUEST
{
    uint8_t    Cmd;
    uint8_t    ByteCount;
    uint8_t    SubCmd;
    uint8_t    Version;
}   SI_CHANGE_TO_AMT_REQUEST;

SI_CHANGE_TO_AMT_REQUEST SI_ChangeToAMT_Request
(
    uint8_t Cmd = 0x05,
    uint8_t ByteCount = 0x02,
    uint8_t SubCmd = 0x52,
    uint8_t Version = 0x10  
)
{
    SI_CHANGE_TO_AMT_REQUEST Data = {0};
    Data.Cmd = Cmd;
    Data.ByteCount = ByteCount;
    Data.SubCmd = SubCmd;
    Data.Version = Version;
    return Data;
}

typedef struct _SI_CHANGE_TO_AMT_RESPONSE
{
    AMT_STATUS    Status;
}   SI_CHANGE_TO_AMT_RESPONSE;

SI_CHANGE_TO_AMT_RESPONSE SI_ChangeToAMT_Response()
{
    SI_CHANGE_TO_AMT_RESPONSE Data = {0};
    Data.Status = 0; //0 - STATUS_SUCCESS, 0x9E - STATUS_FAILURE
    return Data;
}

typedef struct _SI_CHANGE_TO_AMT
{
    SI_CHANGE_TO_AMT_REQUEST Request;
    SI_CHANGE_TO_AMT_RESPONSE Response;
}   SI_CHANGE_TO_AMT;

AMT_STATUS SI_ChangeToAMT()
{
    SI_CHANGE_TO_AMT Data = {0};
    Data.Request = SI_ChangeToAMT_Request();
    Data.Response = SI_ChangeToAMT_Response();
    return Data.Response.Status;
}

typedef struct _SI_IS_CHANGE_TO_AMT_ENABLED_REQUEST
{
    uint8_t    Cmd;
    uint8_t    ByteCount;
    uint8_t    SubCmd;
    uint8_t    Version;
}   SI_IS_CHANGE_TO_AMT_ENABLED_REQUEST;

SI_IS_CHANGE_TO_AMT_ENABLED_REQUEST SI_IsChangeToAMTEnabled_Request
(
    uint8_t Cmd = 0x05,
    uint8_t ByteCount = 0x02,
    uint8_t SubCmd = 0x51,
    uint8_t Version = 0x10
)
{
    SI_IS_CHANGE_TO_AMT_ENABLED_REQUEST Data = {0};
    Data.Cmd = Cmd;
    Data.ByteCount = ByteCount;
    Data.SubCmd = SubCmd;
    Data.Version = Version;
    return Data;
}

#define SI_AMT_TRANSITION_ALLOWED                    (1 << 0)
#define SI_AMT_TRANSITION_IS_ALLOWED(ENABLED)        (ENABLED & SI_AMT_TRANSITION_ALLOWED == 1)
#define SI_AMT_TRANSITION_IS_NOT_ALLOWED(ENABLED)    (ENABLED & SI_AMT_TRANSITION_ALLOWED == 0)

#define SI_AMT_OPERATION_ENABLED                     (1 << 1)
#define SI_AMT_OPERATION_IS_ENABLED(ENABLED)         (ENABLED & SI_AMT_OPERATION_ENABLED == 1)
#define SI_AMT_OPERATION_IS_DISABLED(ENABLED)        (ENABLED & SI_AMT_OPERATION_ENABLED == 0)

#define SI_AMT_TLS_ENFORCED                          (1 << 6)
#define SI_AMT_TLS_IS_ENFORCED(ENABLED)              (ENABLED & SI_AMT_TLS_ENFORCED == 1)
#define SI_AMT_TLS_IS_OPTIONAL(ENABLED)              (ENABLED & SI_AMT_TLS_ENFORCED == 0)

#define SI_AMT_ENABLEMENT_NEW                        (1 << 7)
#define SI_AMT_ENABLEMENT_IS_NEW(ENABLED)            (ENABLED & SI_AMT_ENABLEMENT_NEW == 1)
#define SI_AMT_ENABLEMENT_IS_OLD(ENABLED)            (ENABLED & SI_AMT_ENABLEMENT_NEW == 0)

typedef struct _SI_IS_CHANGE_TO_AMT_ENABLED_RESPONSE
{
    uint8_t    Enabled;
}   SI_IS_CHANGE_TO_AMT_ENABLED_RESPONSE;

SI_IS_CHANGE_TO_AMT_ENABLED_RESPONSE SI_IsChangeToAMTEnabled_Response()
{
    SI_IS_CHANGE_TO_AMT_ENABLED_RESPONSE Data = {0};
    Data.Enabled = SI_AMT_TRANSITION_ALLOWED
                 | SI_AMT_OPERATION_ENABLED
              // | SI_TLS_ENFORCED
                 | SI_AMT_ENABLEMENT_NEW;
    return Data;
}

typedef struct _SI_IS_CHANGE_TO_AMT_ENABLED
{
    SI_IS_CHANGE_TO_AMT_ENABLED_REQUEST Request;
    SI_IS_CHANGE_TO_AMT_ENABLED_RESPONSE Response;
}   SI_IS_CHANGE_TO_AMT_ENABLED;

AMT_STATUS SI_IsChangeToAMTEnabled()
{
    SI_IS_CHANGE_TO_AMT_ENABLED Data = {0};
    Data.Request = SI_IsChangeToAMTEnabled_Request();
    Data.Response = SI_IsChangeToAMTEnabled_Response();
    return (SI_AMT_TRANSITION_IS_ALLOWED(Data.Response.Enabled))
        ? AMT_STATUS_SUCCESS : AMT_STATUS_CERTIFICATE_NOT_READY;
}

#endif//_INTEL_AMT_PTHI_IOCTL_H_
