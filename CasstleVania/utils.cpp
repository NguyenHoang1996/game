#include "utils.h"

#include <signal.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

// Cắt chuỗi.
// inout: chuỗi cần cắt.
// seperate: kí tự dùng để cắt chuỗi
// return: mãng các chuỗi đã được cắt.
std::vector<std::string> splitString(const std::string & input, char seperate)
{
	std::vector<std::string> output;
	std::stringstream ss(input);

	std::string item;

	while (std::getline(ss, item, seperate))
	{
		output.push_back(item);
	}

	return output;
}

char *__trace_file = "D:\\trace.log";
int __trace = 1;

//void trace(const LPCSTR format, ...)
//{
//	if (!__trace) return;
//
//	FILE *f = stderr;
//
//	if (__trace_file != NULL)
//	{
//		if (fopen_s(&f, __trace_file, "a") != 0)
//		{
//			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", __trace_file);
//			return;
//		}
//	}
//
//	va_list ap;
//	va_start(ap, format);
//	vfwprintf(f, (wchar_t*)format, ap);
//	va_end(ap);
//
//	fprintf(f, "\n");
//
//	if (__trace_file != NULL) fclose(f);
//}

void trace(const LPCSTR str, float x)
{
	if (!__trace) return;

	FILE *f = stderr;

	if (__trace_file != NULL)
	{
		if (fopen_s(&f, __trace_file, "a") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", __trace_file);
			return;
		}
	}

	
	fprintf(f, str);
	fprintf(f, "   %f", x);
	fprintf(f, "\n");

	if (__trace_file != NULL) fclose(f);
}