#pragma once
#include "injector/injector.hpp"

void SimpleHookCallStoreOriginal(uintptr_t hookAddress, injector::memory_pointer_raw functionToCall, uintptr_t *pointerToOriginalPointer)
{
	*pointerToOriginalPointer = injector::ReadMemory<uintptr_t>(hookAddress + 1, true) + hookAddress + 5;
	MakeCALL(hookAddress, functionToCall, true);
}

void SimpleCall(uintptr_t cdeclCallAddress)
{
	((void(__cdecl *)())cdeclCallAddress)();
}
