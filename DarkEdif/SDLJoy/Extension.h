#include <DarkEdif.h>

#define SDL_MAIN_HANDLED
#include "sdl/SDL_config.h"
#include "sdl/SDL.h"
#include "sdl/SDL_main.h"
#include "sdl/SDL_joystick.h"
#include "sdl/SDL_haptic.h"

#pragma comment (lib, "Setupapi.lib")
#pragma comment (lib, "Version.lib")
#pragma comment (lib, "Imm32.lib")

#ifdef _DEBUG
#pragma comment (lib, "../Lib/Windows/sdl2d.lib")
#pragma comment (lib, "../Lib/Windows/sdl2maind.lib")
#else
#pragma comment (lib, "../Lib/Windows/sdl2.lib")
#pragma comment (lib, "../Lib/Windows/sdl2main.lib")
#endif

struct SDL_JoystickData
{
	SDL_Joystick * joystick;
	SDL_Haptic * haptic;
	bool connected;
	int joy_id;
	Sint16 axis[8];
	Uint8 held_buttons[32];
	Uint8 held_buttons_last[32];
	Uint8 hat[4];
	int ball_x[4];
	int ball_y[4];
	Sint8 currentheld[32];
	Sint8 lastpressed;
	Sint8 lastreleased;
	char num_buttons;
	char num_axes;
	char num_hats;
	char num_balls;
};


class Extension
{
public:

	RUNDATA * rdPtr;
	RunHeader *	rhPtr;

	Edif::Runtime Runtime;

	static const int MinimumBuild = 254;
	static const int Version = 2;

	static const OEFLAGS OEFLAGS = OEFLAGS::NEVER_SLEEP;
	static const OEPREFS OEPREFS = OEPREFS::NONE;
	
	static const int WindowProcPriority = 100;

	Extension(RUNDATA * rdPtr, EDITDATA * edPtr, CreateObjectInfo * cobPtr);
	~Extension();

	// To add items to the Fusion Debugger, just uncomment this line.
	DarkEdif::FusionDebugger FusionDebugger;
	// After enabling it, you run FusionDebugger.AddItemToDebugger() inside Extension's constructor
	// As an example:
	std::tstring exampleDebuggerTextItem;

	/*  Add any data you want to store in your extension to this class
		(eg. what you'd normally store in rdPtr in old SDKs).

		Unlike rdPtr, you can store real C++ objects with constructors
		and destructors, without having to call them manually or store
		a pointer.
	*/


	constexpr static int NUM_HATS = 4;
	constexpr static int NUM_AXES = 8;
	constexpr static int NUM_BALLS = 8;
	constexpr static int NUM_DEVICES = 16;
	constexpr static int NUM_BUTTONS = 32;

	SDL_JoystickData SDL_Data[NUM_DEVICES];
	bool DeviceIDOK(int devID);
	bool ButtonIDOK(int buttonID);
	bool HatIDOK(int devID);
	bool AxisIDOK(int axisID);
	bool BallIDOK(int ballID);

	// int MyVariable;




	/*  Add your actions, conditions and expressions as real class member
		functions here. The arguments (and return type for expressions) must
		match EXACTLY what you defined in the JSON.

		Remember to link the actions, conditions and expressions to their
		numeric IDs in the class constructor (Extension.cpp)
	*/

	/// Actions

	/// Conditions

		bool IsConnected(int devID);
		bool ButtonPressed(int devID, int buttonID);
		bool ButtonHeldDown(int devID, int buttonID);
		bool ButtonReleased(int devID, int buttonID);
		bool AnyButtonPressed(int devID);
		bool AnyButtonHeldDown(int devID);
		bool AnyButtonReleased(int devID);

	/// Expressions
		
		int GetAxis(int joy, int axis);
		int GetButtonPressedState(int joy, int button);
		int GetHat(int joy, int hat);
		int GetBallXDelta(int joy, int ball);
		int GetBallYDelta(int joy, int ball);
		int NumAxes(int joy);
		int NumButtons(int joy);
		int NumHats(int joy);
		int NumBalls(int joy);
		int NumJoysticks();
		const TCHAR * GetDeviceGUID(int joy);
		const TCHAR * GetDeviceName(int joy);
		const TCHAR * GetButtonsHeldHex(int joy);
		int HeldButtonIndex(int joy, int index);
		int LastButtonPressedIndex(int joy);
		int LastButtonReleasedIndex(int joy);



	/* These are called if there's no function linked to an ID */

	void Action(int ID, RUNDATA * rdPtr, long param1, long param2);
	long Condition(int ID, RUNDATA * rdPtr, long param1, long param2);
	long Expression(int ID, RUNDATA * rdPtr, long param);




	/*  These replace the functions like HandleRunObject that used to be
		implemented in Runtime.cpp. They work exactly the same, but they're
		inside the extension class.
	*/

	REFLAG Handle();
	REFLAG Display();

	short Pause();
	short Continue();
};
