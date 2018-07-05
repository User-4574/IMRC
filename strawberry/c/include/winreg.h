#ifndef _WINREG_H
#define _WINREG_H
#if __GNUC__ >= 3
#pragma GCC system_header
#endif

#ifndef WINADVAPI
#define WINADVAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif
#define HKEY_CLASSES_ROOT	((HKEY)0x80000000)
#define HKEY_CURRENT_USER	((HKEY)0x80000001)
#define HKEY_LOCAL_MACHINE	((HKEY)0x80000002)
#define HKEY_USERS	((HKEY)0x80000003)
#define HKEY_PERFORMANCE_DATA	((HKEY)0x80000004)
#define HKEY_CURRENT_CONFIG	((HKEY)0x80000005)
#define HKEY_DYN_DATA	((HKEY)0x80000006)
#define REG_OPTION_VOLATILE 1
#define REG_OPTION_NON_VOLATILE 0
#define REG_CREATED_NEW_KEY 1
#define REG_OPENED_EXISTING_KEY 2
#define REG_NONE 0
#define REG_SZ 1
#define REG_EXPAND_SZ 2
#define REG_BINARY 3
#define REG_DWORD_LITTLE_ENDIAN 4
#define REG_DWORD 4
#define REG_DWORD_BIG_ENDIAN 5
#define REG_LINK 6
#define REG_MULTI_SZ 7
#define REG_RESOURCE_LIST 8
#define REG_FULL_RESOURCE_DESCRIPTOR 9
#define REG_RESOURCE_REQUIREMENTS_LIST 10
#define REG_QWORD_LITTLE_ENDIAN 11
#define REG_QWORD 11
#define REG_NOTIFY_CHANGE_NAME 1
#define REG_NOTIFY_CHANGE_ATTRIBUTES 2
#define REG_NOTIFY_CHANGE_LAST_SET 4
#define REG_NOTIFY_CHANGE_SECURITY 8

#if (WINVER >= 0x0502)
#define KEY_WOW64_32KEY 0x0200
#define KEY_WOW64_64KEY 0x0100
#endif

#ifndef RC_INVOKED
typedef ACCESS_MASK REGSAM;
typedef struct value_entA {
	LPSTR ve_valuename;
	DWORD ve_valuelen;
	DWORD ve_valueptr;
	DWORD ve_type;
} VALENTA,*PVALENTA;
typedef struct value_entW {
	LPWSTR ve_valuename;
	DWORD ve_valuelen;
	DWORD ve_valueptr;
	DWORD ve_type;
} VALENTW,*PVALENTW;
WINADVAPI BOOL WINAPI AbortSystemShutdownA(LPCSTR);
WINADVAPI BOOL WINAPI AbortSystemShutdownW(LPCWSTR);
WINADVAPI BOOL WINAPI InitiateSystemShutdownA(LPSTR,LPSTR,DWORD,BOOL,BOOL);
WINADVAPI BOOL WINAPI InitiateSystemShutdownW(LPWSTR,LPWSTR,DWORD,BOOL,BOOL);
WINADVAPI LONG WINAPI RegCloseKey(HKEY);
WINADVAPI LONG WINAPI RegConnectRegistryA(LPCSTR,HKEY,PHKEY);
WINADVAPI LONG WINAPI RegConnectRegistryW(LPCWSTR,HKEY,PHKEY);
WINADVAPI LONG WINAPI RegCreateKeyA(HKEY,LPCSTR,PHKEY);
WINADVAPI LONG WINAPI RegCreateKeyExA(HKEY,LPCSTR,DWORD,LPSTR,DWORD,REGSAM,LPSECURITY_ATTRIBUTES,PHKEY,PDWORD);
WINADVAPI LONG WINAPI RegCreateKeyExW(HKEY,LPCWSTR,DWORD,LPWSTR,DWORD,REGSAM,LPSECURITY_ATTRIBUTES,PHKEY,PDWORD);
WINADVAPI LONG WINAPI RegCreateKeyW(HKEY,LPCWSTR,PHKEY);
WINADVAPI LONG WINAPI RegDeleteKeyA(HKEY,LPCSTR);
WINADVAPI LONG WINAPI RegDeleteKeyW(HKEY,LPCWSTR);
#if (WINVER >= 0x0502)
WINADVAPI LONG WINAPI RegDeleteKeyExA(HKEY,LPCSTR,REGSAM,DWORD);
WINADVAPI LONG WINAPI RegDeleteKeyExW(HKEY,LPCWSTR,REGSAM,DWORD);
#endif
WINADVAPI LONG WINAPI RegDeleteValueA(HKEY,LPCSTR);
WINADVAPI LONG WINAPI RegDeleteValueW(HKEY,LPCWSTR);
WINADVAPI LONG WINAPI RegEnumKeyA(HKEY,DWORD,LPSTR,DWORD);
WINADVAPI LONG WINAPI RegEnumKeyW(HKEY,DWORD,LPWSTR,DWORD);
WINADVAPI LONG WINAPI RegEnumKeyExA(HKEY,DWORD,LPSTR,PDWORD,PDWORD,LPSTR,PDWORD,PFILETIME);
WINADVAPI LONG WINAPI RegEnumKeyExW(HKEY,DWORD,LPWSTR,PDWORD,PDWORD,LPWSTR,PDWORD,PFILETIME);
WINADVAPI LONG WINAPI RegEnumValueA(HKEY,DWORD,LPSTR,PDWORD,PDWORD,PDWORD,LPBYTE,PDWORD);
WINADVAPI LONG WINAPI RegEnumValueW(HKEY,DWORD,LPWSTR,PDWORD,PDWORD,PDWORD,LPBYTE,PDWORD);
WINADVAPI LONG WINAPI RegFlushKey(HKEY);
WINADVAPI LONG WINAPI RegGetKeySecurity(HKEY,SECURITY_INFORMATION,PSECURITY_DESCRIPTOR,PDWORD);
WINADVAPI LONG WINAPI RegLoadKeyA(HKEY,LPCSTR,LPCSTR);
WINADVAPI LONG WINAPI RegLoadKeyW(HKEY,LPCWSTR,LPCWSTR);
WINADVAPI LONG WINAPI RegNotifyChangeKeyValue(HKEY,BOOL,DWORD,HANDLE,BOOL);
WINADVAPI LONG WINAPI RegOpenKeyA(HKEY,LPCSTR,PHKEY);
WINADVAPI LONG WINAPI RegOpenKeyExA(HKEY,LPCSTR,DWORD,REGSAM,PHKEY);
WINADVAPI LONG WINAPI RegOpenKeyExW(HKEY,LPCWSTR,DWORD,REGSAM,PHKEY);
WINADVAPI LONG WINAPI RegOpenKeyW(HKEY,LPCWSTR,PHKEY);
WINADVAPI LONG WINAPI RegQueryInfoKeyA(HKEY,LPSTR,PDWORD,PDWORD,PDWORD,PDWORD,PDWORD,PDWORD,PDWORD,PDWORD,PDWORD,PFILETIME);
WINADVAPI LONG WINAPI RegQueryInfoKeyW(HKEY,LPWSTR,PDWORD,PDWORD,PDWORD,PDWORD,PDWORD,PDWORD,PDWORD,PDWORD,PDWORD,PFILETIME);
WINADVAPI LONG WINAPI RegQueryMultipleValuesA(HKEY,PVALENTA,DWORD,LPSTR,LPDWORD);
WINADVAPI LONG WINAPI RegQueryMultipleValuesW(HKEY,PVALENTW,DWORD,LPWSTR,LPDWORD);
WINADVAPI LONG WINAPI RegQueryValueA(HKEY,LPCSTR,LPSTR,PLONG);
WINADVAPI LONG WINAPI RegQueryValueExA(HKEY,LPCSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD);
WINADVAPI LONG WINAPI RegQueryValueExW(HKEY,LPCWSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD);
WINADVAPI LONG WINAPI RegQueryValueW(HKEY,LPCWSTR,LPWSTR,PLONG);
WINADVAPI LONG WINAPI RegReplaceKeyA(HKEY,LPCSTR,LPCSTR,LPCSTR);
WINADVAPI LONG WINAPI RegReplaceKeyW(HKEY,LPCWSTR,LPCWSTR,LPCWSTR);
WINADVAPI LONG WINAPI RegRestoreKeyA(HKEY,LPCSTR,DWORD);
WINADVAPI LONG WINAPI RegRestoreKeyW(HKEY,LPCWSTR,DWORD);
WINADVAPI LONG WINAPI RegSaveKeyA(HKEY,LPCSTR,LPSECURITY_ATTRIBUTES);
WINADVAPI LONG WINAPI RegSaveKeyW(HKEY,LPCWSTR,LPSECURITY_ATTRIBUTES);
WINADVAPI LONG WINAPI RegSetKeySecurity(HKEY,SECURITY_INFORMATION,PSECURITY_DESCRIPTOR);
WINADVAPI LONG WINAPI RegSetValueA(HKEY,LPCSTR,DWORD,LPCSTR,DWORD);
WINADVAPI LONG WINAPI RegSetValueExA(HKEY,LPCSTR,DWORD,DWORD,const BYTE*,DWORD);
WINADVAPI LONG WINAPI RegSetValueExW(HKEY,LPCWSTR,DWORD,DWORD,const BYTE*,DWORD);
WINADVAPI LONG WINAPI RegSetValueW(HKEY,LPCWSTR,DWORD,LPCWSTR,DWORD);
WINADVAPI LONG WINAPI RegUnLoadKeyA(HKEY,LPCSTR);
WINADVAPI LONG WINAPI RegUnLoadKeyW(HKEY,LPCWSTR);

#ifdef UNICODE
typedef VALENTW VALENT,*PVALENT;
#define AbortSystemShutdown AbortSystemShutdownW
#define InitiateSystemShutdown InitiateSystemShutdownW
#define RegConnectRegistry RegConnectRegistryW
#define RegCreateKey RegCreateKeyW
#define RegCreateKeyEx RegCreateKeyExW
#define RegDeleteKey RegDeleteKeyW
#if (WINVER >= 0x0502)
#define RegDeleteKeyEx RegDeleteKeyExW
#endif
#define RegDeleteValue RegDeleteValueW
#define RegEnumKey RegEnumKeyW
#define RegEnumKeyEx RegEnumKeyExW
#define RegEnumValue RegEnumValueW
#define RegLoadKey RegLoadKeyW
#define RegOpenKey RegOpenKeyW
#define RegOpenKeyEx RegOpenKeyExW
#define RegQueryInfoKey RegQueryInfoKeyW
#define RegQueryMultipleValues RegQueryMultipleValuesW
#define RegQueryValue RegQueryValueW
#define RegQueryValueEx RegQueryValueExW
#define RegReplaceKey RegReplaceKeyW
#define RegRestoreKey RegRestoreKeyW
#define RegSaveKey RegSaveKeyW
#define RegSetValue RegSetValueW
#define RegSetValueEx RegSetValueExW
#define RegUnLoadKey RegUnLoadKeyW
#else
typedef VALENTA VALENT,*PVALENT;
#define AbortSystemShutdown AbortSystemShutdownA
#define InitiateSystemShutdown InitiateSystemShutdownA
#define RegConnectRegistry RegConnectRegistryA
#define RegCreateKey RegCreateKeyA
#define RegCreateKeyEx RegCreateKeyExA
#define RegDeleteKey RegDeleteKeyA
#if (WINVER >= 0x0502)
#define RegDeleteKeyEx RegDeleteKeyExA
#endif
#define RegDeleteValue RegDeleteValueA
#define RegEnumKey RegEnumKeyA
#define RegEnumKeyEx RegEnumKeyExA
#define RegEnumValue RegEnumValueA
#define RegLoadKey RegLoadKeyA
#define RegOpenKey RegOpenKeyA
#define RegOpenKeyEx RegOpenKeyExA
#define RegQueryInfoKey RegQueryInfoKeyA
#define RegQueryMultipleValues RegQueryMultipleValuesA
#define RegQueryValue RegQueryValueA
#define RegQueryValueEx RegQueryValueExA
#define RegReplaceKey RegReplaceKeyA
#define RegRestoreKey RegRestoreKeyA
#define RegSaveKey RegSaveKeyA
#define RegSetValue RegSetValueA
#define RegSetValueEx RegSetValueExA
#define RegUnLoadKey RegUnLoadKeyA
#endif
#endif
#ifdef __cplusplus
}
#endif
#endif
