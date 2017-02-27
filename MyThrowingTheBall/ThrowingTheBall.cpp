// ThrowingTheBall.cpp : Defines the entry point for the console application.
//
// also here:
//
//  create the thead for UI
// define log filename
// load motion engine

#include "stdafx.h"

#include "thread_with_winfow.h"
#include "all_messages.h"
#include "constants.h"
#include "Parameter_Parser.h"

#undef max
#undef min
using namespace ttb_thread;

namespace
{
	// just for dynamic use dll

	RequestBallMotionF RequestBallMotion = nullptr;
	FinalizeMotionForBallF FinalizeMotionForBall = nullptr;

	// return true in case if success
	//
	// dynamically loads our motion engine
	//
	//
	bool InitializeMotionEngine()
	{
		char t_buf[MAX_PATH] = { 0 };
		::GetModuleFileNameA(::GetModuleHandle(NULL), t_buf, sizeof(t_buf));//получаем полное им€ файла; т.к. NULL беретс€ текущий путь


		std::vector<char> drive(_MAX_DRIVE + 1);
		std::vector<char> dir(_MAX_DIR + 1);

		_splitpath_s(t_buf, drive.data(), _MAX_DRIVE, dir.data(), _MAX_DIR, nullptr, 0, nullptr, 0);//разбивает буфер (полное им€ файла) на компоненты(диск, путь, им€, расширение)

		_makepath_s(t_buf, MAX_PATH, drive.data(), dir.data(), "MotionLogicLib", "dll");//копирует в буфер компоненты

		auto hModule = ::LoadLibraryA(t_buf);//€вный вызов функции dll; она поищет DLL, еcли найдет, то загрузит ее в пам€ть и вернет ¬ам указатель
		if (NULL == hModule)
			return false;

		// request functions adresses
		FinalizeMotionForBall = (FinalizeMotionForBallF)::GetProcAddress(hModule, FinalizeMotionForBallFUNCTION_NAME);//получает адрес экспортированной функции в DLL
		RequestBallMotion = (RequestBallMotionF)::GetProcAddress(hModule, RequestBallMotionFUNCTION_NAME);

		if (nullptr == RequestBallMotion || nullptr == FinalizeMotionForBall)
		{
			::FreeLibrary(hModule);//сообщ€ет Windows, что данна€ программа DLL больше не использует
			return false;
		}
		return true;
	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	if (!InitializeMotionEngine())
	{
		std::cout << "failed to load motion engine" << std::endl;
		return 2;
	}

	WLOGFILE("we are started|%s %d", "parameters count", argc);

	// next parameters can be specified
	//
	//
	// g:-2.5 h:2.3 sx:8 sy:3 sz:2 wx:0 wy:-7.1 wz:0
	//
	// gravity  (meters/(second*second))
	//        height (will be conbvert into positive value in any case)  (meters)
	//             speed in x Axis  (meters/second)
	//                  speed in y Axis   (meters/second)
	//                       speed in z Axis  (meters/second)
	//                            wind speed in x Axis  (meters/(second*second))   // it's like the wind doing acceleration
	//                                 wind speed in y Axis   (meters/(second*second))  // it's like the wind doing acceleration
	//                                      wind speed in z Axis  (meters/(second*second))  // it's like the wind doing acceleration


	if (argc == 1)
	{
		// provide help
		// and execute then with default parameters
		WLOGFILE("next parameters can be specified:");
		WLOGFILE("g:-2.5 h:2.3 sx:8 sy:3 sz:2 wx:0 wy:-7.1 wz:0  (default values)");
		WLOGFILE(" g: gravity  (meters / (second*second)) = default acceleration for Z");
		WLOGFILE(" h: height (will be converted into positive value in any case)  (meters)");
		WLOGFILE(" height treated as initial Z coordinate, initial x and y are 0 both");
		WLOGFILE(" sx: speed in x Axis  (meters / second)");
		WLOGFILE(" sy: speed in y Axis  (meters / second)");
		WLOGFILE(" sz: speed in z Axis  (meters / second)");
		WLOGFILE(" wx: wind speed in x Axis  (meters /(second*second))   it's like we are doing acceleration");
		WLOGFILE(" wy: wind speed in y Axis   (meters / (second*second))  it's like we are doing acceleration");
		WLOGFILE(" wz: wind speed in z Axis  (meters / (second*second))  it's like we are doing acceleration");
		WLOGFILE(" NOTE: overwrite every parameter to change default values");
	}

	Parameter_Parser t_parser; //класс с параметром map


	// step here:
	//  Parse parameters

	SD_VECTOR t_position = { 0., 0., 2.3 }; // 2.3 meters above the ground
	SD_VECTOR t_speed = { 8., 3., 2. }; // up and forward by default
	SD_VECTOR t_acceleration = { 0., -7.1, 0. };
	double t_gravity = -2.5; // gravity to bottom should be negative
	t_parser.AddParameterNamePointer(TEXT("g"), &t_gravity); //добавл€ютс€ значени€ "текст-значение" в карту
	t_parser.AddParameterNamePointer(TEXT("h"), &t_position.z_axis);
	t_parser.AddParameterNamePointer(TEXT("sx"), &t_speed.x_axis);
	t_parser.AddParameterNamePointer(TEXT("sy"), &t_speed.y_axis);
	t_parser.AddParameterNamePointer(TEXT("sz"), &t_speed.z_axis);
	t_parser.AddParameterNamePointer(TEXT("wx"), &t_acceleration.x_axis);
	t_parser.AddParameterNamePointer(TEXT("wy"), &t_acceleration.y_axis);
	t_parser.AddParameterNamePointer(TEXT("wz"), &t_acceleration.z_axis);
	{
		for (int i = 1; i < argc; ++i)
		{
			if (!t_parser.Parse(argv[i]))
			{
				std::wstring w_str(argv[i]); //convert to wstring
				std::string s_str(w_str.begin(), w_str.end()); //and convert to string.

				WLOGFILE("failed to parse parameter number %d '%s'", i, s_str.c_str());
			}
		}
	}
	if (t_position.z_axis < 0)
		t_position.z_axis *= -1.;
	// setup acceleration
	t_acceleration.z_axis += t_gravity;

	SD_VECTOR t_lowLimit = { std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), 0. }; //максимальное значение double с минусом
	SD_VECTOR t_highLimit = { std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), 8000. }; //максимальное значение double

	// step here:
	// create a ball motion exemplar
	std::shared_ptr<IBallMotion> m_ball(RequestBallMotion(&t_position, &t_speed), [](IBallMotion const * p){FinalizeMotionForBall(p); });
	if (m_ball == nullptr)
	{
		WLOGFILE("failed to create a ball motion object");
		return 3;
	}
	m_ball->AddForse(&t_acceleration); // setup forces
	m_ball->BallMotionEdges(&t_lowLimit, &t_highLimit); // setup limits to where we move

	if (m_ball == nullptr)
	{
		WLOGFILE("failed to create a ball motion object");
		return 1;
	}

	::SetThreadPriority(::GetCurrentThread(), BELOW_NORMAL_PRIORITY_CLASS); // calculation with delta time - no need to rush //  устанавливает значение приоритета дл€ заданного потока (ниже стандартного)







	// step here:
	// setup UI thread
	// 
	SThreadInitialData t_threadsLink; // structure to send messages from/to thread
	std::thread t_uiThread(UIThreadFunction, &t_threadsLink); // execute the thread //t_uiThread - это объект, представл€ющий поток выполнени€, в котором будет выполн€тьс€ функци€ UIThreadFunction; 
	//t_threadsLink - аргумент функции UIThreadFunction. ѕотоки позвол€ют нескольким фрагментам кода работать асинхронно и одновременно.







	// step here:
	// move the ball with time
	// time step 0.01 sec
	double t_flyTime = 0.0; // full fly time

	FILETIME t_now; // calculating time for event into motion engine
	::GetSystemTimeAsFileTime(&t_now);
	auto t_before = t_now; // time at previous iteration

	const decltype(t_flyTime) dt = 0.01; // time step

	auto t_nowPos = t_position;
	auto t_nowSpeed = t_speed;
	WLOGFILE("ball start fly time %0.02f|\t now at [x,y,z]:[%.02f, %.02f, %.02f]meters|\t with speed [%.02f, %.02f, %.02f] meters/second|\t under forses [%.02f, %.02f, %.02f] meters /square second",
		t_flyTime, t_nowPos.x_axis, t_nowPos.y_axis, t_nowPos.z_axis, t_nowSpeed.x_axis, t_nowSpeed.y_axis, t_nowSpeed.z_axis,
		t_acceleration.x_axis, t_acceleration.y_axis, t_acceleration.z_axis
		);

	auto t_flyTimeResult = t_flyTime; // will acquire accurate data about time
	t_threadsLink.m_toUIThread.AddMessage(CMessageQueue::T_Message(new CMessageTimeEvent(t_nowPos, t_flyTime)));

	while (t_flyTime < 1000.) // we fly up to 1000. sec
	{
		::Sleep(0); // not overheat

		// calculate dt
		::GetSystemTimeAsFileTime(&t_now);
		double dt = (double)(*((int64_t*)(&t_now)) - *((int64_t*)(&t_before))) / (double)1.e7;// in seconds
		if (dt <= 0.)
			continue;
		t_before = t_now;


		t_flyTime += dt;
		if (m_ball->BallMotion(dt, &t_nowPos, &t_nowSpeed, &t_flyTimeResult)) // simulate - time pass
		{
			t_threadsLink.m_toUIThread.AddMessage(CMessageQueue::T_Message(new CMessageTimeEvent(t_nowPos, t_flyTime)));
			WLOGFILE("ball fly time %0.02f|\t now at [x,y,z]:[%.02f, %.02f, %.02f](m)|\t with speed [%.02f, %.02f, %.02f](m/s)",
				t_flyTime, t_nowPos.x_axis, t_nowPos.y_axis, t_nowPos.z_axis, t_nowSpeed.x_axis, t_nowSpeed.y_axis, t_nowSpeed.z_axis
				);

		}
		else
		{
			t_threadsLink.m_toUIThread.AddMessage(CMessageQueue::T_Message(new CMessageTimeEvent(t_nowPos, t_flyTime)));
			// we are reach the limit
			break;
		}

		auto t_messageFromUIThread = t_threadsLink.m_fromUIThread.NextMessage();
		if (t_messageFromUIThread != nullptr)
		{
			if (t_messageFromUIThread->Type() == EMESSAGE_TYPE::message_no_more_data)
			{
				WLOGFILE("simulation terminated - any further position message are fake");
				break;
			}
		}
	};


	t_threadsLink.m_toUIThread.AddMessage(CMessageQueue::T_Message(new CMessage(EMESSAGE_TYPE::message_no_more_data))); // we allow to quit in UI thread

	if (t_nowPos.z_axis < (t_lowLimit.z_axis + t_highLimit.z_axis) / 2.)
	{
		WLOGFILE("ball full fly time %0.05f|\t landed at [x,y]:[%.02f, %.02f](m)",
			t_flyTimeResult, t_nowPos.x_axis, t_nowPos.y_axis
			);
	}
	else
	{
		WLOGFILE("The new artificial satellite of the earth is successfully put to planet orbit in %.05f seconds after start.", t_flyTimeResult);
	}

	t_uiThread.join();//¬ызов join блокирует вызывающий поток (в нашем случае Ч поток main) до тех пор, пока t_uiThread (а точнее UIThreadFunction()) не выполнит свою работу

	::Sleep(0);

	WLOGFILE("Simulation done");
	return 0;
};