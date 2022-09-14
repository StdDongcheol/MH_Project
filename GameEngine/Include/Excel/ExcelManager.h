#pragma once

#include "../GameInfo.h"

class CExcelManager
{
private:
	class CExcel* m_ExcelData;

public:
	class CExcel* CreateExcel(const char* FileName, const char* MiddlePath, bool IsWriteMode, const wchar_t* Extension = L".xlsx");
	void SetExcelPath(const wchar_t* Name, const wchar_t* FileName, const wchar_t* MiddlePath, const wchar_t* Extension = L".xlsx");

public:
	const wchar_t* GetExcelName()	const;

	DECLARE_SINGLE(CExcelManager)
};