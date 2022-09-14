#pragma once

#include "../GameInfo.h"

class CExcel
{
	friend class CExcelManager;

protected:
	CExcel();
	virtual ~CExcel();

private:
	libxl::Book*	m_Book;
	wchar_t			m_Name[32];
	wchar_t			m_FullPath[MAX_PATH];
	bool			m_WriteMode;
	bool			m_xlsx;

protected:
	libxl::Sheet*	m_Sheet;
	libxl::CellType	m_CellType;
	int				m_Row;
	int				m_Col;

public:
	void Init(const char* Name, const wchar_t* Extension = L".xlsx");
	void Init(const wchar_t* Name, const wchar_t* Extension = L".xlsx");
	void SetPath(const char* FileName, const char* MiddlePath, const wchar_t* Extension = L".xlsx");
	bool Save();

private:
	void SetPath(const wchar_t* FileName, const wchar_t* MiddlePath, const wchar_t* Extension = L".xlsx");

public:
	void Reset();

public:
	double ReadNumber();
	float ReadNumberFloat();
	const wchar_t* ReadString();
	bool ReadBool();

public:
	void WriteNumber(double Number);
	void WriteString(const wchar_t String[64]);
	void WriteBool(bool Bool);

public:
	void NewLine();
	void NextLine();

protected:
	void SetFullPathMultibyte(const char* FullPath);

protected:
	void Read();
	void Write();
};