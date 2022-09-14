
#include "ExcelManager.h"
#include "Excel.h"

DEFINITION_SINGLE(CExcelManager)

CExcelManager::CExcelManager()	:
	m_ExcelData(nullptr)
{
}

CExcelManager::~CExcelManager()
{
	SAFE_DELETE(m_ExcelData);
}

CExcel* CExcelManager::CreateExcel(const char* FileName, const char* MiddlePath, bool IsWriteMode, const wchar_t* Extension)
{
	int Length = (int)strlen(FileName) + 7;

	char* Name = DBG_NEW char[Length];

	strcpy_s(Name, Length, FileName);

	if (IsWriteMode)
		strcat_s(Name, Length, "Write");

	else
		strcat_s(Name, Length, "Read");

	wchar_t* ConFile = DBG_NEW wchar_t[Length];
	//wchar_t ConFile[32] = {};

	int	FileLen = MultiByteToWideChar(CP_ACP, 0, FileName, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, FileName, -1, ConFile, FileLen);

	if (m_ExcelData)
		SAFE_DELETE(m_ExcelData);

	m_ExcelData = new CExcel;

	m_ExcelData->Init(Name, Extension);
	m_ExcelData->SetPath(FileName, MiddlePath, Extension);

	if (IsWriteMode)
		m_ExcelData->Write();

	else
		m_ExcelData->Read();

	SAFE_DELETE_ARRAY(ConFile);
	SAFE_DELETE_ARRAY(Name);

	m_ExcelData->Reset();

	return m_ExcelData;
}

void CExcelManager::SetExcelPath(const wchar_t* Name, const wchar_t* FileName, const wchar_t* MiddlePath, const wchar_t* Extension)
{
	if (!m_ExcelData)
		ASSERT("if (!Excel)");

	m_ExcelData->SetPath(FileName, MiddlePath, Extension);
}

const wchar_t* CExcelManager::GetExcelName() const
{
	if (!m_ExcelData)
		return L"";

	return m_ExcelData->m_Name;
}