#pragma once
#include "IniReader/IniReader.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

bool ReadIniFloat(CIniReader ini, std::fstream *lg, std::string section, std::string key, float* f) {
	*f = ini.ReadFloat(section, key, -1);
	if (*f != -1) {
		*lg << section << ": " << key << " = " << std::fixed << *f << std::endl;
		return true;
	}
	else return false;
}

bool ReadIniInt(CIniReader ini, std::fstream *lg, std::string section, std::string key, int* i) {
	*i = ini.ReadInteger(section, key, -1);
	if (*i != -1) {
		*lg << section << ": " << key << " = " << *i << std::endl;
		return true;
	}
	else return false;
}

bool ReadIniBool(CIniReader ini, std::fstream *lg, std::string section, std::string key) {
	//bool b = ini.ReadBoolean(section, key, 0);
	bool b = ini.ReadInteger(section, key, 0) == 1;
	if (b == true) {
		*lg << section << ": " << key << " = true" << std::endl;
		return true;
	}
	else return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

