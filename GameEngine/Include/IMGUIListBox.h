#pragma once

#include "IMGUIWidget.h"

class CIMGUIListBox :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUIListBox();
	virtual ~CIMGUIListBox();

protected:
	std::vector<std::string>	m_vecItem;
	std::vector<std::string>	m_vecItemUTF8;
	bool		m_Select;
	bool		m_SelectCancel;
	int			m_SelectIndex;
	int			m_PageItemCount;
	bool		m_Sort;
	std::function<void(int, const char*)>	m_SelectCallback;
	std::function<void()>	m_CancelFunc;

public:
	int GetItemIndex(const std::string& Name)
	{
		int Size = (int)m_vecItem.size();

		if (Size != 0)
		{
			for (int i = 0; i < Size; ++i)
			{
				if (m_vecItem[i] == Name)
					return i;
			}
		}

		return -1;
	}

	int GetItemIndex(const char* Name)
	{
		int Size = (int)m_vecItem.size();

		if (Size != 0)
		{
			for (int i = 0; i < Size; ++i)
			{
				if (!m_vecItem[i].compare(Name))
					return i;
			}
		}

		return -1;
	}

	const std::string& GetItem(int Index)
	{
		return m_vecItem[Index];
	}

	const std::string& GetSelectItem()	const
	{
		return m_vecItem[m_SelectIndex];
	}

	int GetSelectIndex()	const
	{
		return m_SelectIndex;
	}

	int GetItemCount()	const
	{
		return (int)m_vecItem.size();
	}

	bool CheckItem(const std::string& Item)
	{
		size_t	Size = m_vecItem.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_vecItem[i] == Item)
				return true;
		}

		return false;
	}

	bool CheckItem(const char* Item)
	{
		size_t	Size = m_vecItem.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_vecItem[i] == Item)
				return true;
		}

		return false;
	}

public:
	void SetSelectCancel(bool Cancel)
	{
		m_SelectCancel = Cancel;
	}

	void SetSelectIndex(int Index)
	{
		m_SelectIndex = Index;
	}

	void SetSelectItem(const char* Item)
	{
		SetSelectIndex(GetItemIndex(Item));
	}

	void SetSelectItem(const std::string& Item)
	{
		SetSelectIndex(GetItemIndex(Item.c_str()));
	}

	void AddItem(const std::string& Item, bool IsOverlap = false)
	{
		if (!IsOverlap)
		{
			size_t Size = m_vecItem.size();

			for (size_t i = 0; i < Size; ++i)
			{
				if (!m_vecItem[i].compare(Item))
					return;
			}
		}

		m_vecItem.push_back(Item);

		wchar_t	wItem[1024] = {};
		char	ItemUTF8[1024] = {};

		int	Length = MultiByteToWideChar(CP_ACP, 0, Item.c_str(), -1, 0, 0);
		MultiByteToWideChar(CP_ACP, 0, Item.c_str(), -1, wItem, Length);

		// UTF8?? ????????.
		Length = WideCharToMultiByte(CP_UTF8, 0, wItem, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_UTF8, 0, wItem, -1, ItemUTF8, Length, 0, 0);

		m_vecItemUTF8.push_back(ItemUTF8);

		if (m_Sort)
		{
			std::sort(m_vecItem.begin(), m_vecItem.end());
			std::sort(m_vecItemUTF8.begin(), m_vecItemUTF8.end());
		}
	}

	void SetPageItemCount(int Count)
	{
		m_PageItemCount = Count;
	}

	void DeleteItem(int Index)
	{
		auto	iter = m_vecItem.begin() + Index;

		m_vecItem.erase(iter);

		auto	iter1 = m_vecItemUTF8.begin() + Index;

		m_vecItemUTF8.erase(iter1);
	}

	void DeleteItem(const std::string& Item)
	{
		auto	iter = m_vecItem.begin();
		auto	iterEnd = m_vecItem.end();

		for (; iter != iterEnd; ++iter)
		{
			if (!strcmp((*iter).c_str(), Item.c_str()))
			{
				m_vecItem.erase(iter);
				break;
			}
		}

		iter = m_vecItemUTF8.begin();
		iterEnd = m_vecItemUTF8.end();

		for (; iter != iterEnd; ++iter)
		{
			if (!(*iter).compare(Item))
			{
				m_vecItemUTF8.erase(iter);
				break;
			}
		}
	}

	void DeleteLastItem()
	{
		auto	iter = m_vecItem.end() - 1;

		m_vecItem.erase(iter);

		auto	iter1 = m_vecItemUTF8.end() - 1;

		m_vecItemUTF8.erase(iter1);
	}

	void Clear()
	{
		m_vecItem.clear();
		m_vecItemUTF8.clear();

		m_SelectIndex = -1;
		m_Select = false;
	}

	void Sort(bool bSort)
	{
		m_Sort = bSort;

		if (m_Sort)
		{
			std::sort(m_vecItem.begin(), m_vecItem.end());
			std::sort(m_vecItemUTF8.begin(), m_vecItemUTF8.end());
		}
	}

public:
	virtual bool Init();
	virtual bool Render();

public:
	template <typename T>
	void SetSelectCallback(T* Obj, void(T::* Func)(int, const char*))
	{
		m_SelectCallback = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}

	template <typename T>
	void SetCancelFunction(T* Obj, void(T::* Func)())
	{
		m_CancelFunc = std::bind(Func, Obj);
	}
};

