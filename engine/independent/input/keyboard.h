#if !defined(__KEYBOARD_H__)
#define __KEYBOARD_H__

//==============================================================================

namespace engine
{
	//============================================================================
	// CDisplay
	//============================================================================
	class CKeyboard
	{
		public:
			static	void				Initialise(void);
			static	void				Uninitialise(void);

			static	void				Update(int key, int action);
			static	bool				IsKeyPressed(int key);
			static	bool				IsKeyHeld(int key);
			static	bool				IsKeyDown(int key);
			static	void				ClearKey(int key);

		protected:
			static	bool				s_keyState[512];
			static	bool				s_keyPrevState[512];
	}; // End [class CKeyboard]

	//============================================================================
} // End [namespace engine]

//==============================================================================
#endif // !defined(__KEYBOARD_H__)
// [EOF]
