#include "StdAfx.h"
#include "YCIni.h"

/// Constructor
YCIni::YCIni(LPCTSTR ini_path)
{
	// Gets the execution path of the file
	std::array<TCHAR, MAX_PATH> exe_folder_path;
	::GetModuleFileName(nullptr, exe_folder_path.data(), static_cast<u32>(exe_folder_path.size()));
	::PathRemoveFileSpec(exe_folder_path.data());

	// Get INI file path
	m_ini_path.Format(_T("%s\\%s"), exe_folder_path.data(), ini_path);
}

YCIni::~YCIni() = default;

/// Set a section name
void YCIni::SetSection(LPCTSTR section)
{
	m_section = section;
}

/// Set a section name
///
/// @param id String ID
///
void YCIni::SetSection(u32 id)
{
	std::array<TCHAR, 256> buffer;

	::LoadString(::GetModuleHandle(nullptr), id, buffer.data(), static_cast<u32>(buffer.size()));

	SetSection(buffer.data());
}

/// Set key name
void YCIni::SetKey(LPCTSTR key)
{
	m_key = key;
}

/// Gets a string
///
/// @param dst            Storage location for the string
/// @param dst_size       Buffer size
/// @param default_string Default value
///
void YCIni::ReadStr(LPTSTR dst, DWORD dst_size, LPCTSTR default_string)
{
	::GetPrivateProfileString(m_section, m_key, default_string, dst, dst_size, m_ini_path);
}

/// Gets a string
///
/// @param dst            Storage location for the string
/// @param default_string Default value
///
void YCIni::ReadStr(YCString& dst, const YCString& default_string)
{
	std::array<TCHAR, 1024> buffer;

	ReadStr(buffer.data(), static_cast<u32>(buffer.size()), default_string);

	dst = buffer.data();
}

/// Sets the string
void YCIni::WriteStr(LPCTSTR str)
{
	::WritePrivateProfileString(m_section, m_key, str, m_ini_path);
}

/// Delete section
bool YCIni::DeleteSection(LPCTSTR section)
{
	if (section == nullptr)
		section = m_section;

	return ::WritePrivateProfileString(section, nullptr, nullptr, m_ini_path) != 0;
}
