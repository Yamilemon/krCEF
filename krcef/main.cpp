/*krkr*/
#include "ncbind.hpp"

#include <windows.h>

#include "include/cef_command_line.h"
#include "include/cef_sandbox_win.h"
#include "cef/simple_app.h"

using namespace std;

static string _outter_param;
static bool _isBring2Top;
static string _url;
static int _left;
static int _top;
static int _width;
static int _height;
static HWND khwnd;
static CefRefPtr<SimpleApp> _app;

static char* wchar2char(const wchar_t* wchar)
{	
	char* m_char;
	int len = WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);
	m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}

static wchar_t* trstring2wchar(const  char* str)
{
	int mystringsize = (int)(strlen(str) + 1);
	WCHAR* wchart = new wchar_t[mystringsize];
	MultiByteToWideChar(CP_ACP, 0, str, -1, wchart, mystringsize);
	return wchart;
}

class krCEF {
private:
	
public:
	CefRefPtr<CefBrowser> browser;
	// 初始化
	static tjs_error TJS_INTF_METHOD init(
		tTJSVariant* result,
		tjs_int numparams,
		tTJSVariant** param,
		iTJSDispatch2* objthis)
	{
		// 默认参数
		_outter_param = "";
		_isBring2Top = false;
		_url = "";
		_left = 0;
		_top = 0;
		khwnd = FindWindow(L"TTVPWindowForm", NULL);
		RECT krect;
		GetWindowRect(khwnd, &krect);
		_width = krect.right - krect.left;
		_height = krect.bottom - krect.top;

		// 七个外置参数
		if (param[0]->Type() != tvtVoid) _outter_param = wchar2char(param[0]->GetString());
		if (param[1]->Type() != tvtVoid) _isBring2Top = param[1]->AsInteger();
		if (param[2]->Type() != tvtVoid) _url = wchar2char(param[2]->GetString());
		if (param[3]->Type() != tvtVoid) _left = param[3]->AsInteger();
		if (param[4]->Type() != tvtVoid) _top = param[4]->AsInteger();
		if (param[5]->Type() != tvtVoid) _width = param[5]->AsInteger();
		if (param[6]->Type() != tvtVoid) _height = param[6]->AsInteger();


		//UNREFERENCED_PARAMETER(hPrevInstance);
		//UNREFERENCED_PARAMETER(lpCmdLine);

		// Enable High-DPI support on Windows 7 or newer.
		CefEnableHighDPISupport();

		void* sandbox_info = nullptr;

#if defined(CEF_USE_SANDBOX)
		// Manage the life span of the sandbox information object. This is necessary
		// for sandbox support on Windows. See cef_sandbox_win.h for complete details.
		CefScopedSandboxInfo scoped_sandbox;
		sandbox_info = scoped_sandbox.sandbox_info();
#endif

		// Provide CEF with command-line arguments.
		// CefMainArgs main_args(hInstance);
		CefMainArgs main_args;

		// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
		// that share the same executable. This function checks the command-line and,
		// if this is a sub-process, executes the appropriate logic.
		int exit_code = CefExecuteProcess(main_args, nullptr, sandbox_info);
		if (exit_code >= 0) {
			// The sub-process has completed so return here.
			return exit_code;
		}

		// Parse command-line arguments for use in this method.
		CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
		command_line->InitFromString(::GetCommandLineW());
		// command_line->AppendArgument(outter_param);// 添加外部参数
		
		// Specify CEF global settings here.
		CefSettings settings;

		if (command_line->HasSwitch("enable-chrome-runtime")) {
			// Enable experimental Chrome runtime. See issue #2969 for details.
			settings.chrome_runtime = true;
		}

#if !defined(CEF_USE_SANDBOX)
		settings.no_sandbox = true;
#endif
		settings.command_line_args_disabled = true;
		// SimpleApp implements application-level callbacks for the browser process.
		// It will create the first browser instance in OnContextInitialized() after
		// CEF has initialized.
		CefRefPtr<SimpleApp> app(new SimpleApp(_outter_param, _isBring2Top, _url, _left, _top, _width, _height, khwnd));
		_app = app;
		// 自己处理消息循环，和krkr独立开来
		settings.multi_threaded_message_loop = true;
		// Initialize CEF.
		CefInitialize(main_args, settings, app.get(), sandbox_info);

		// Run the CEF message loop. This will block until CefQuitMessageLoop() is
		// called.
		//CefRunMessageLoop();

		// Shut down CEF.
		//CefShutdown();
		// if (numparams != 1) return TJS_E_BADPARAMCOUNT;
		// bool isOpenWin = param[0]->AsInteger();
		/*DWORD dwThreadID = 0;
		HANDLE cefHandle = CreateThread(NULL, NULL, initCefFunc, NULL, 0, 0);
		CloseHandle(cefHandle);
		Sleep(1);*/
		return TJS_S_OK;
	}

	static tjs_error TJS_INTF_METHOD toTop(
		tTJSVariant* result,
		tjs_int numparams,
		tTJSVariant** param,
		iTJSDispatch2* objthis) {

		HWND cef_hwnd = FindWindowEx(khwnd, NULL, L"CefBrowserWindow", NULL);
		BringWindowToTop(cef_hwnd);
		return TJS_S_OK;
	}

	static tjs_error TJS_INTF_METHOD close(
		tTJSVariant* result,
		tjs_int numparams,
		tTJSVariant** param,
		iTJSDispatch2* objthis) {
		// Shut down CEF.
		CefShutdown();
		return TJS_S_OK;
	}

	static tjs_error TJS_INTF_METHOD loadUrl(
		tTJSVariant* result,
		tjs_int numparams,
		tTJSVariant** param,
		iTJSDispatch2* objthis) {

		if (numparams != 1) return TJS_E_BADPARAMCOUNT;
		char* url = wchar2char(param[0]->GetString());
		_app->browser->GetMainFrame()->LoadURL(url);
		// CefRefPtr<CefBrowser> browser = Cef
		return TJS_S_OK;
		// CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
		// Shut down CEF.
		// CefShutdown();
	}

};

NCB_REGISTER_CLASS(krCEF) {
	RawCallback("init", &Class::init, 0);
	RawCallback("toTop", &Class::toTop, 0);
	RawCallback("close", &Class::close, 0);
	RawCallback("loadUrl", &Class::loadUrl, 0);
}