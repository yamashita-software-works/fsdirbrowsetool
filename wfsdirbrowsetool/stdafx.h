#pragma once

#include "targetver.h"

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#undef WIN32_NO_STATUS        // defines STATUS_XXX in ntddk, now using includes DDK.
#include <ntstatus.h>

#define WIN32_LEAN_AND_MEAN
#define WIN32_NO_STATUS       // no include STATUS_XXX in winnt.h
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <strsafe.h>
#include <winternl.h> // WinSDK 7.1
#include <winioctl.h>
#include <commoncontrols.h>
#include <uxtheme.h>

#include "builddefs.h"

#include "common_control_helper.h"

#if _MSC_VER <= 1500
#define nullptr NULL
#endif

#pragma warning(disable : 4995)

#include "debug.h"
#include "mem.h"
#include "libmisc.h"

#define SetRedraw(h,f)	SendMessage(h,WM_SETREDRAW,(WPARAM)f,0)
#define GETINSTANCE(hWnd)   (HINSTANCE)GetWindowLongPtr(hWnd,GWLP_HINSTANCE)
#define GETCLASSBRUSH(hWnd) (HBRUSH)GetClassLongPtr(hWnd,GCLP_HBRBACKGROUND)
HINSTANCE _GetResourceInstance();

#include "dparray.h"
#include "..\wfslib\wfslib.h"
#include "..\libntwdk\libntwdk.h"
#include "..\inc\common.h"

#define  _ASSERT ASSERT

//
// Data definitions
//
#include "fileinfo.h"

class CFileItem : public FILEITEM
{
public:
	CFileItem()
	{
		memset(this,0,sizeof(FILEITEM));
	}

	CFileItem(PCWSTR pszDirPath,PCWSTR pszFile)
	{
		memset(this,0,sizeof(FILEITEM));
		if( pszDirPath )
			hdr.Path = _MemAllocString(pszDirPath);
		if( pszFile )
			hdr.FileName = _MemAllocString(pszFile);
	}

	~CFileItem()
	{
		_SafeMemFree(hdr.Path);
		_SafeMemFree(hdr.FileName);
	}
};

typedef struct _FILELIST
{
	PWSTR RootPath;
	ULONG cItemCount;
	CFileItem **pFI;
} FILELIST,*PFILELIST;

enum {
	TitleNone = 0,                // 0
	TitleName,                    // 1
	TitleAttributes,              // 2
	TitleLastWriteTime,           // 3
	TitleCreationTime,            // 4
	TitleLastAccessTime,          // 5
	TitleChangeTime,              // 6
	TitleLastWriteTimeDirEntry,   // 7
	TitleCreationTimeDirEntry,    // 8
	TitleLastAccessTimeDirEntry,  // 9
	TitleChangeTimeDirEntry,      // 10
	TitleEndOfFile,               // 11
	TitleAllocationSize,          // 12
	TitleEndOfFileDirEntry,       // 13
	TitleAllocationSizeDirEntry,  // 14
	TitleNumberOfHardLink,        // 15
	TitleDirectory,               // 16
	TitleDeletePending,           // 17
	TitleShortName,               // 18
	TitleExtension,               // 19
	TitleEAData,                  // 20
	TitleObjectId,                // 21
	TitleBirthVolumeId,           // 22
	TitleBirthObjectId,           // 23
	TitleDomainId,                // 24
	TitleFileId,                  // 25
	TitleLocation,                // 26
	TitleWofItem,                 // 27
	TitleCount,
	TitleTableSize = TitleCount,
};

//
// Folder tree item ident
//
typedef enum {
	ITEM_FOLDER_NAME,
	ITEM_FOLDER_PATH, /* reserved */
	ITEM_FOLDER_ROOT,
	ITEM_BLANK,
	ITEM_GROUP,
} TREEITEMTYPE;

//
// WM_CONTROL_MESSAGE
//
#define WM_CONTROL_MESSAGE  (WM_APP+1000)

// WPARAM LOWORD(f)
#define CODE_SELECT_PATH        (0x0001)
#define CODE_CHANGE_DIRECTORY   (0x0002)
#define CODE_ASYNC_UPDATE_PATH  (0x0003)
#define CODE_SELECT_ITEM        (0x0004)

typedef struct _SELECT_FILE
{
	UINT mask;
	PWSTR pszPath;
	PWSTR pszName;
	PWSTR pszLocation;
	UINT Type;
} SELECT_FILE;

typedef struct _SELECT_TITLE
{
	UINT TitleId;
	FILE_INFORMATION_STRUCT *pFileInfo;
} SELECT_TITLE;

HIMAGELIST DIRBGetShareImageList();
INT DIRBGetUpDirImageIndex();
