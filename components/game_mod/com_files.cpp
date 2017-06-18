#include "stdafx.h"
#include <iostream>

char dirList[DIRLIST_LEN];

unsigned int __cdecl FS_ReadModDescription(void *ptr, unsigned int len, _iobuf *stream)
{
	return FS_FileRead(ptr, MODDESC_LEN, stream);
}

void __declspec(naked) mfh_FS_GetModList(void)
{
	static void* dwRetn = (void*)0x00455A34;

	_asm
	{
		push esi
		lea edx, [esp + 0x44]
		push MODDESC_LEN
		push edx
		jmp dwRetn;
	}
}

unsigned int __cdecl Sys_CountFileList(char **list)
{
	int i = 0;
	if (list)
	{
		while (*list)
		{
			++list;
			++i;
		}
	}
	return i;
}

int __cdecl FS_GetModList(char *listbuf, int bufsize)
{
	*listbuf = 0;

	int nTotal = 0;
	int nPotential = 0;
	int nMods = 0;

	const char* basepath = fs_homepath->current.string;

	const int bufLen = max(MODDESC_LEN, 256);
	char descPath[max(bufLen, 256)];
	sprintf_s(descPath, bufLen, "%s/%s", basepath, "mods");

	int dummy = 0;
	char** pFiles = Sys_ListFiles(descPath, 0, 0, &dummy, 1);
	nPotential = Sys_CountFileList(pFiles);
	for (int i = 0; i < nPotential; ++i)
	{
		char* name = pFiles[i];
		int nLen = strlen(name) + 1;

		//
		// Try to load mod.json first
		//
		strcpy_s(descPath, name);
		strncat_s(descPath, "/mod.json", bufLen);

		char* descData = descPath + 1;

		int descHandle = 0;
		if (FS_SV_FOpenFileRead(descPath, "mods", &descHandle) > 0 && descHandle)
		{
			_iobuf* file = FS_FileForHandle(descHandle);
			memset(descData, 0, bufLen - 1);
			int nDescLen = FS_ReadModDescription(descData, MODDESC_LEN - 1, file);
			if (nDescLen >= 0)
				descData[nDescLen] = 0;
			descPath[0] = DESC_JSON;
			FS_FCloseFile(descHandle);
		}
		else
		{
			//
			// Otherwise fallback to legacy description.txt
			//
			strcpy_s(descPath, name);
			strncat_s(descPath, "/description.txt", bufLen);

			int descHandle = 0;
			if (FS_SV_FOpenFileRead(descPath, "mods", &descHandle) > 0 && descHandle)
			{
				_iobuf* file = FS_FileForHandle(descHandle);
				memset(descData, 0, bufLen - 1);
				int nDescLen = FS_ReadModDescription(descData, MODDESC_LEN - 1, file);
				if (nDescLen >= 0)
					descData[nDescLen] = 0;
				descPath[0] = DESC_DESC;
				FS_FCloseFile(descHandle);
			}
			else
			{
				Com_Printf(10, "FS_GetModList: failed to open %s\n", descPath);
				descPath[0] = DESC_ERROR;
				descData[0] = '\0';
			}
		}

		int nDescLen = strlen(descPath) + 1;
		if (nLen + nTotal + nDescLen + 2 >= bufsize)
			break;

#pragma warning( push )
#pragma warning( disable : 4996 )
		strcpy(listbuf, name);
		strcpy(&listbuf[nLen], descPath);
#pragma warning( pop )  

		listbuf = &listbuf[nLen + nDescLen];
		nTotal += nDescLen + nLen;
		++nMods;
	}

	FS_FreeFileList((const char**)pFiles, 0);
	return nMods;
}

typedef int(__cdecl* FS_FOpenFileWriteToDir_t)(const char *filename, const char *dir, const char *osbasepath);
FS_FOpenFileWriteToDir_t FS_FOpenFileWriteToDir_o = (FS_FOpenFileWriteToDir_t)0x00625D90;

int __cdecl FS_FOpenFileWriteToDir(const char *filename, const char *dir, const char *osbasepath)
{
	if (com_cfg_readOnly && com_cfg_readOnly->current.enabled)
		return 0;

	return FS_FOpenFileWriteToDir_o(filename, dir, osbasepath);
}
