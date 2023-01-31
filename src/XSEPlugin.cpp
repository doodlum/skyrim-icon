#include <SimpleINI.h>

struct Unk_SetForegroundWindow
{
	static BOOL __stdcall thunk(HWND hWnd)
	{
		auto hIcon = LoadImage(NULL, L"Data\\SKSE\\Plugins\\CustomWindow.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
		if (hIcon) {
			logger::info("Replacing window icon");
			SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
			SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		} else {
			logger::warn("Could not load icon");
		}

		CSimpleIniA ini;
		ini.SetUnicode();
		ini.LoadFile(L"Data\\SKSE\\Plugins\\CustomWindow.ini");
	
		if (auto title = ini.GetValue("Settings", "Title")) {
			logger::info("Replacing window title");
			SetWindowTextA(hWnd, title);
		} else {
			logger::warn("Could not find INI string for window title");
		}
		return func(hWnd);
	}
	static inline REL::Relocation<decltype(thunk)> func;
};

void Load()
{
	stl::write_thunk_call6F15<Unk_SetForegroundWindow>(REL::VariantID(75591, 77226, 0xDC4B90).address() + REL::Relocate(0x195, 0x25E, 0x225));
}
