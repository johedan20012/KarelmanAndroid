#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H
#include <SDL.h>
#include <string.h>
#include "MathHelper.h"
#include "Texture.h"
#include "Button.h"

class InputManager {

public:

	enum BUTTON {fire};

private:

	struct Joystick{
		Vector2 mAsis; //Normalizados 0 ---- 1
		Texture* mText[2];
		int mFingerID;
		float GetRadio(){
			return (mText[0]->ScaledDimensions().x / 2) - (mText[1]->ScaledDimensions().x / 2);
		}

		Vector2 GetLocalPos(){
			return mText[0]->Pos() - mText[1]->Pos();
		}

		Joystick(){
			mAsis = VEC2_ONE * 0.5f;

			mText[0] = new Texture("ScreenGamepad/joystick_1.png",250,250);
			mText[1] = new Texture("ScreenGamepad/joystick_2.png",100,100);
            mFingerID = -1;
		};

		~Joystick(){
			delete mText[0];
			mText[0] = NULL;

			delete mText[1];
			mText[1] = NULL;
		}
	};


private:

	static InputManager *sInstance;

	int mTouchState;  // 0 nada, 1 abajo, 2 presionado , 3 soltado
	Vector2 mTouchPos;

	/*std::vector<Vector2> mTouches;*/
	SDL_TouchID device;

	const static int mNumButtons = 0;

	Button* mGamepadButtons[mNumButtons];

	const static int mNumJoys = 2;

	Joystick* mJoysticks[mNumJoys];

public:

	static InputManager* Instance();
	static void Release();

	int GetGamepadState(BUTTON boton);
	Vector2 GetJoystickState(int index);
	int TouchState();

	void Update();
	void Render();
	void UpdatePrevInput();

private:
	
	InputManager();
	~InputManager();

};

#endif 

