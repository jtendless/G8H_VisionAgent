#pragma once
class Miscellaneous
{
public:
	Miscellaneous();
	~Miscellaneous();

public:
	static BOOL IsSameDirectory(CString StrLocation);
	static void GetExePath(CString& rStr);
};

