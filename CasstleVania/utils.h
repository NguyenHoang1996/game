#pragma once
#ifndef __UTILS_H__
#define __UTILS_H__
#include "Global.h"
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> splitString(const std::string & input, char seperate);

/**
	debug
*/
//void trace(const LPCSTR format, ...);
void trace(const LPCSTR str, float x);
#endif // !__UTILS_H__

