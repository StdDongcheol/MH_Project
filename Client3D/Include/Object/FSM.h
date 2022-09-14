#pragma once
#pragma once
#include "GameInfo.h"

// �÷��̾� ����� ��Ŭ������ �� ����� �ִ�.
// �ٸ� Ŭ������ ���ʿ䰡 ����.

template<typename EventTarget>
class FSM
{
public:
	class State
	{
	public:

		EventTarget* mObj;
		void(EventTarget::* mStartFunc)(); // �� �̺�Ʈ�� �����Ҷ� �Լ�
		void(EventTarget::* mEndFunc)();  // �ð��� ��� ����Ǹ� ����Ǵ� �Լ�
		void(EventTarget::* mStayFunc)(); // �ð��� ���µ��� ��� ����Ǵ� �Լ�

	public:

		void Start()
		{
			if (nullptr == mStartFunc)
			{
				return;
			}

			(mObj->*mStartFunc)();
		}

		void End()
		{
			if (nullptr == mEndFunc)
			{
				return;
			}

			(mObj->*mEndFunc)();
		}


		void Update()
		{
			if (nullptr == mStayFunc)
			{
#ifdef _DEBUG

				assert("if (nullptr == mStayFunc)");
#endif
			
			}

			(mObj->*mStayFunc)();
		}

	public:
		State() : mObj(nullptr), mStartFunc(nullptr), mEndFunc(nullptr), mStayFunc(nullptr)
		{

		}
		~State()
		{

		}
	};

private:
	std::unordered_map<std::string, State> mState;
	State* mCurState;

public:
	void CreateState(std::string _StateName, EventTarget* _Obj,
		void(EventTarget::* _StayFunc)(),
		void(EventTarget::* _StartFunc)() = nullptr,// 0.0�ʿ� ����Ǵ� �Լ��Դϴ�.
		void(EventTarget::* _EndFunc)() = nullptr  // 0 ~ 1�� ���̿� �����Ӹ��� ����Ǵ� �Լ�
	)
	{
		if (mState.end() != mState.find(_StateName))
		{
#ifdef _DEBUG

			assert("if (mState.end() != mState.find(_StateName))");
#endif

		}

		mState[_StateName].mObj = _Obj;
		mState[_StateName].mStartFunc = _StartFunc;
		mState[_StateName].mStayFunc = _StayFunc;
		mState[_StateName].mEndFunc = _EndFunc;
	}

	void ChangeState(std::string _StateName)
	{
		if (mState.end() == mState.find(_StateName))
		{
#ifdef _DEBUG

			assert("if (mState.end() == mState.find(_StateName))");
#endif

		}


		if (nullptr != mCurState)
		{
			if (nullptr != mCurState->mEndFunc)
				mCurState->End();
		}
		mCurState = &mState[_StateName];

		if (nullptr != mCurState->mStartFunc)
			mCurState->Start();
	}

	bool CheckCurrentState(std::string _StateName)
	{
		if (mCurState == &mState[_StateName])
		{
			return true;
		}

		return false;
	}

	void Update()
	{
		if (nullptr == mCurState)
		{
#ifdef _DEBUG

			assert("if (0 == mEvents.size())");
#endif

		}
		mCurState->Update();
	}

public:
	FSM() : mCurState(nullptr)
	{

	}
	~FSM()
	{
		mState.clear();
	}
};

