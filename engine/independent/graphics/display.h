#if !defined(__DISPLAY_H__)
#define __DISPLAY_H__

#include "common/types.h"

class CDisplay
{
public:
	CDisplay(uint32 width, uint32 height, const char* title);
	~CDisplay(void);

	bool Update(const void* pData);
	void SetDisplayScale(float scale);
	float GetDisplayScale(void);

protected:

	enum eState
	{
		eS_Uninitialised,
		eS_Initialised,
		eS_Window
	};

	enum eTextureID
	{
		eTID_Main = 1
	};

	eState m_state;
	float m_displayScale;
	uint32 m_width;
	uint32 m_height;
};

#endif // !defined(__DISPLAY_H__)
