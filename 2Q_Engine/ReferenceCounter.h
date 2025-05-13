#pragma once
class ReferenceCounter // Animation Asset에도 비트맵과 같이 참조 카운트 확인을 위해 만든 클래스
{
private:
	unsigned int m_refCount;
public:
	ReferenceCounter():m_refCount(0) {}
	virtual ~ReferenceCounter() {}

	unsigned int AddRef()
	{
		m_refCount++;
		return m_refCount;
	}

	unsigned int Release()
	{
		assert(m_refCount != 0, "Release Error");
		m_refCount--;
		if (m_refCount == 0)
		{
			delete this;
			return 0;
		}
		return m_refCount;
	}

	unsigned int GetRefCount()
	{
		return m_refCount;
	}
};

