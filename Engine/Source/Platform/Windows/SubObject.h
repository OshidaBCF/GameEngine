#pragma once

namespace Win32
{
	class ENGINE_API SubObject
	{
	public:
		SubObject(WSTRING className, WSTRING classTitle, HICON icon);
		~SubObject();

		virtual void RegisterNewClass();
		virtual void Initialize() = 0;

	protected:
		static LRESULT CALLBACK	SetupMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT AssignMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		virtual LRESULT MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	protected:
		WSTRING m_Class;
		WSTRING m_Title;

		HICON m_hIcon;

		HWND m_Handle;

	public:
		HWND Handle() { return m_Handle; }
		void Handle(HWND hwnd) { m_Handle = hwnd; }
	};
}