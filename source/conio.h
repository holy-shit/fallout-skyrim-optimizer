/*
Fallout New Vegas/Skyrim 4GB Console IO
Copyright (C) 2010,2011,2012  Alexis Ryan (the.wench@wenchy.net)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

struct ConIO {
	HANDLE h;
	ConIO* Error;

	ConIO* WriteLine();

	ConIO* Write(const char *str);
	ConIO* WriteLine(const char *str);

	ConIO* Write(const wchar_t *str);
	ConIO* WriteLine(const wchar_t *str);

	ConIO* Write(DWORD_PTR val);
	ConIO* WriteLine(DWORD_PTR val);

	ConIO* Write(DWORDLONG val);
	ConIO* WriteLine(DWORDLONG val);

	inline ConIO* Write(LPVOID val) { Write((DWORD_PTR)val); return this; }
	inline ConIO* WriteLine(LPVOID  val) { WriteLine((DWORD_PTR)val); return this; }

	ConIO* Write(int val);
	ConIO* WriteLine(int val);

	ConIO* WriteError(DWORD error=GetLastError());
	ConIO* WriteError(const char *str, DWORD error=GetLastError());
	ConIO* WriteError(const wchar_t *str, DWORD error=GetLastError());

};

extern ConIO *Console;

