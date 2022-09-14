
#include "Excel.h"
#include "../PathManager.h"

CExcel::CExcel()	:
	m_Book(nullptr),
	m_Sheet(nullptr),
	m_FullPath{},
	m_Name{},
	m_CellType(libxl::CELLTYPE_EMPTY),
	m_WriteMode(false),
	m_xlsx(false),
	m_Row(1), // 무료 버전은 맨 처음을 띄워준다.
	m_Col(0)
{
}

CExcel::~CExcel()
{
	if (m_Book)
		m_Book->release();
}

double CExcel::ReadNumber()
{
	if (m_Sheet->isFormula(m_Row, m_Col))
		ASSERT("수식이 존재합니다");

	double result = m_Sheet->readNum(m_Row, m_Col);

	++m_Col;

	return result;
}

float CExcel::ReadNumberFloat()
{
	return (float)ReadNumber();
}

const wchar_t* CExcel::ReadString()
{
	if (m_Sheet->isFormula(m_Row, m_Col))
		ASSERT("수식이 존재합니다");

	const wchar_t* result = m_Sheet->readStr(m_Row, m_Col);

	++m_Col;

	return result;
}

bool CExcel::ReadBool()
{
	if (m_Sheet->isFormula(m_Row, m_Col))
		ASSERT("수식이 존재합니다");

	bool result = m_Sheet->readBool(m_Row, m_Col);

	++m_Col;

	return result;
}

void CExcel::WriteNumber(double Number)
{
	m_Sheet->writeNum(m_Row, m_Col, Number);

	++m_Col;
}

void CExcel::WriteString(const wchar_t String[64])
{
	m_Sheet->writeStr(m_Row, m_Col, String);

	++m_Col;
}

void CExcel::WriteBool(bool Bool)
{
	m_Sheet->writeBool(m_Row, m_Col, Bool);

	++m_Col;
}

void CExcel::NewLine()
{
	++m_Row;
	m_Col = 0;
}

void CExcel::NextLine()
{
	++m_Col;
}

void CExcel::Init(const char* Name, const wchar_t* Extension)
{
	int	Length = MultiByteToWideChar(CP_ACP, 0, Name, -1, 0, 0);
	wchar_t* Convert = DBG_NEW wchar_t[Length + 1];
	memset(Convert, 0, sizeof(Convert));
	MultiByteToWideChar(CP_ACP, 0, Name, -1, Convert, Length);

	Init(Convert, Extension);

	SAFE_DELETE_ARRAY(Convert);
}

void CExcel::Init(const wchar_t* Name, const wchar_t* Extension)
{
	if (Name == L"")
		ASSERT("if (Name == L"")");

	if (!lstrcmp(Extension, L".xlsx"))
	{
		m_xlsx = true;
		m_Book = xlCreateXMLBook();
	}

	else if (!lstrcmp(Extension, L".xls"))
		m_Book = xlCreateBook();

	else
		ASSERT("확장자를 잘못 입력하셨습니다");

	lstrcpy(m_Name, Name);
}

void CExcel::SetPath(const char* FileName, const char* MiddlePath, const wchar_t* Extension)
{
	int	Filelen = MultiByteToWideChar(CP_ACP, 0, FileName, -1, 0, 0);
	wchar_t* ConFile = DBG_NEW wchar_t[Filelen + 5 + 1]; // 확장자 포함
	memset(ConFile, 0, sizeof(ConFile));
	MultiByteToWideChar(CP_ACP, 0, FileName, -1, ConFile, Filelen);

	lstrcat(ConFile, Extension);

	int	Midlen = MultiByteToWideChar(CP_ACP, 0, MiddlePath, -1, 0, 0);
	wchar_t* ConMid = DBG_NEW wchar_t[Midlen + 1];
	memset(ConMid, 0, sizeof(ConMid));
	MultiByteToWideChar(CP_ACP, 0, MiddlePath, -1, ConMid, Midlen);

	SetPath(ConFile, ConMid, Extension);

	SAFE_DELETE_ARRAY(ConFile);
	SAFE_DELETE_ARRAY(ConMid);
}

void CExcel::Read()
{
	if (!m_Book->load(m_FullPath))
		ASSERT("if (!m_Book->load(m_FullPath))");

	m_Sheet = m_Book->getSheet(0);

	if (!m_Sheet)
		ASSERT("if (!m_Sheet)");

	m_CellType = m_Sheet->cellType(m_Row, m_Col);
}

void CExcel::Write()
{
	m_Sheet = m_Book->addSheet(m_Name);

	if (!m_Sheet)
		ASSERT("if (!m_Sheet)");

	m_WriteMode = true;
}

void CExcel::SetPath(const wchar_t* FileName, const wchar_t* MiddlePath, const wchar_t* Extension)
{
	memset(m_FullPath, 0, sizeof(wchar_t) * MAX_PATH);

	wchar_t Middle[MAX_PATH] = {};

	lstrcpy(Middle, MiddlePath);
	lstrcat(Middle, L"\\");

	lstrcat(m_FullPath, Middle);
	lstrcat(m_FullPath, FileName);
}

void CExcel::SetFullPathMultibyte(const char* FullPath)
{
	int	PathLength = static_cast<int>(strlen(FullPath));

	memset(m_FullPath, 0, sizeof(wchar_t) * MAX_PATH);

	int length = MultiByteToWideChar(CP_ACP, 0, FullPath, -1, NULL, NULL);

	MultiByteToWideChar(CP_ACP, 0, FullPath, PathLength + 1, m_FullPath, length);

	// xlsx 혹은 xls이 붙었는지 확인

	char Ext[6] = {};
	wchar_t wExt[6] = {};
	int ExtLength = -1;

	if (m_xlsx)
	{
		strcpy_s(Ext, "xslx.");
		lstrcpy(wExt, L".xlsx");

		ExtLength = 5;
	}

	else
	{
		strcpy_s(Ext, "slx.");
		lstrcpy(wExt, L".xls");

		ExtLength = 4;
	}

	bool Find = true;

	for (int i = 1; i < ExtLength; ++i)
	{
		if (m_FullPath[PathLength - i] != Ext[i - 1])
		{
			Find = false;
			break;
		}
	}

	if (!Find) // 확장자가 붙지 않았을 경우 붙여준다.
	{
		length = lstrlen(m_FullPath);

		for (int i = 1; i < 5; ++i)
		{
			m_FullPath[length - i] = 0;
		}

		lstrcat(m_FullPath, wExt);
	}
}

bool CExcel::Save()
{
	if (!m_Book->save(m_FullPath))
		return false;

	return true;
}

void CExcel::Reset()
{
	m_Row = 1;
	m_Col = 0;
}
