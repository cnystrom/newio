#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

int get_special_folder(int csidl, TCHAR * sfp)
{
	HRESULT hr;
	LPITEMIDLIST pidl = NULL;
	BOOL b = 0;

	hr = SHGetSpecialFolderLocation(NULL, csidl, &pidl);
	if (hr == S_OK) {
		b = SHGetPathFromIDList(pidl, sfp);
		if (b)
			CoTaskMemFree(pidl);
		else sfp[0] = 0;
	}
	return b;
}

void get_windows_directory_root(TCHAR * windowsdir)
{
	if (GetWindowsDirectory(windowsdir, sizeof(windowsdir))) {
		PathStripToRoot(windowsdir);
		return;
	}
	strcpy(windowsdir, "C:\\");
	return;
}

int get_home_dir(char *s)
{
	int len;

	TCHAR *tmp;
	TCHAR homestr[MAX_PATH+1];

	tmp = getenv("HOME");
	if (tmp && isalpha(tmp[0]) && tmp[1] == ':') {
		strcpy(homestr, tmp);
	}else{
		if ((tmp = getenv("USERPROFILE")) != NULL) {
			strcpy(homestr, tmp);
		}else {
			if (get_special_folder(CSIDL_PROFILE, homestr)==0)
				get_windows_directory_root(homestr);
		}
	}
	tmp = homestr;

	len = strlen(tmp);

	strcpy(s, tmp);

	return (len);
}

extern "C" __declspec(dllexport) void __stdcall PutHomeInEnv(void)
{
  char buf[32768];
  get_home_dir(buf);
  SetEnvironmentVariable("HOME",buf);
  //MessageBox(NULL, buf, "DLL", MB_OK);
}


