/*
The base of this code is from InjectorTemplate by Junior_Djjr - MixMods.com.br
*/
#include "stdafx.h"
#include "IniReader/IniReader.h"
#include "ReadIniCustom.h"
#include "injector/injector.hpp"
#include "injector/assembly.hpp"
#include "GameStuff.h"
#include "PatchStuff.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace injector;
using namespace std;

string const projectName = TARGET_NAME;
int const BUILD_NUMBER = 1;

gameVersion version;

gameVersion GetGameVersion()
{
	return VERSION_PLATINUM;

	/*switch (injector::ReadMemory<uint32_t>(0xF3F37C, true))
	{
	case 0x005C3C10:
		//MessageBoxA(0, "VERSION_PLATINUM", "Game version", 0);
		return VERSION_PLATINUM;
	case 0x458BFF4C: // 4C FF 8B 45
		//MessageBoxA(0, "VERSION_COMPLETE", "Game version", 0);
		return VERSION_COMPLETE;
	default:
		//MessageBoxA(0, "VERSION_UNKNOWN", "Game version", 0);
		return VERSION_UNKNOWN;
	}*/
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		version = GetGameVersion();
		if (version != VERSION_UNKNOWN) Init();
		else MessageBoxA(0, "Incompatible game version. Contact me if you think this is wrong.", "Error", 0);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

fstream lg;

///////////////////////////////////////////////////////////////////////////////////////////////////

void ReadIni()
{
	int i;
	float f;

	CIniReader ini(projectName + ".ini");
	if (ini.data.size() <= 0) { lg << projectName << ".ini NOT FOUND\n"; lg.flush(); return; }


	if (ReadIniInt(ini, &lg, "Graphics", "ShadowResolution1", &i)) {
		WriteMemory<uint32_t>(0x1DD0278 + 0x400000, i, true);
	}

	if (ReadIniInt(ini, &lg, "Graphics", "ShadowResolution2", &i)) {
		WriteMemory<uint32_t>(0x1E43CF0 + 0x400000, i, true);
	}

	if (ReadIniInt(ini, &lg, "Graphics", "ShadowResolution3", &i)) {
		WriteMemory<uint32_t>(0x1E441D0 + 0x400000, i, true);
	}

	if (ReadIniBool(ini, &lg, "Graphics", "ForceLOD0")) {
		WriteMemory<uint8_t>(0x11BFE8C + 0x400000, 0x31, true);
		WriteMemory<uint8_t>(0x11BFE8C + 0x400000 + 1, 0xC0, true);
		WriteMemory<uint8_t>(0x11BFE8C + 0x400000 + 2, 0x90, true);

		//B8 00 00 00 FF
		WriteMemory<uint8_t>(0x11BFD89 + 0x400000, 0xB8, true);
		WriteMemory<uint8_t>(0x11BFD89 + 0x400000 + 1, 0xFF, true);
		WriteMemory<uint8_t>(0x11BFD89 + 0x400000 + 2, 0x00, true);
		WriteMemory<uint8_t>(0x11BFD89 + 0x400000 + 3, 0x00, true);
		WriteMemory<uint8_t>(0x11BFD89 + 0x400000 + 4, 0x00, true);
		WriteMemory<uint8_t>(0x11BFD89 + 0x400000 + 5, 0x90, true);
		WriteMemory<uint8_t>(0x11BFD89 + 0x400000 + 6, 0x90, true);
		WriteMemory<uint8_t>(0x11BFD89 + 0x400000 + 7, 0x90, true);
		WriteMemory<uint8_t>(0x11BFD89 + 0x400000 + 8, 0x90, true);
	}

	lg.flush();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

uintptr_t gameInitOriginalCall;

void GameIni()
{
	lg << "Game processing" << "\n";
	lg.flush();

	ReadIni();

	SimpleCall(gameInitOriginalCall);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Init()
{
	lg.open(projectName + ".log", std::fstream::out | std::fstream::trunc);
	lg << "Build " << BUILD_NUMBER << "\n";
	lg.flush();

	//uintptr_t address = (version == gameVersion::VERSION_PLATINUM) ? 0x43D861 : 0x5432EC;
	uintptr_t address = 0x4145B7;
	SimpleHookCallStoreOriginal(address, GameIni, &gameInitOriginalCall);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
