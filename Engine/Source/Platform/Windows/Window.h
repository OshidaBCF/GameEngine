#pragma once

#include "SubObject.h"

namespace Win32
{
	class ENGINE_API Window : public Win32::SubObject
	{
	public:
		Window(std::wstring className, std::wstring classTitle, HICON icon, int width, int height);
		~Window();

		virtual void Initialize() override;

	protected:
		int m_Width;
		int m_Height;
	};
}