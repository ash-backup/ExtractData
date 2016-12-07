#include "StdAfx.h"
#include "UI/Dialog/ExistsDialog.h"

#include "res/ResExtractData.h"

DWORD CExistsDialog::m_overwrite;

void CExistsDialog::DoModal(HWND hWnd, LPCTSTR file_path)
{
	if (m_overwrite == 0x01)
	{
		m_file_path = file_path;
		HINSTANCE hInst = reinterpret_cast<HINSTANCE>(GetWindowLongPtr(hWnd, GWLP_HINSTANCE));
		INT_PTR ret = DialogBoxParam(hInst, _T("EXISTSDLG"), hWnd, reinterpret_cast<DLGPROC>(WndStaticProc), reinterpret_cast<LPARAM>(this));
		if (ret == IDCANCEL)
			throw CExistsDialog();
	}
	else if (m_overwrite == 0x10)
	{
		throw CExistsDialog();
	}
}

LRESULT CExistsDialog::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			Init();
			SetWindowText(GetDlgItem(hWnd, IDC_EXISTS_PATH), m_file_path);
			SetFocus(GetDlgItem(hWnd, IDC_EXISTS_YES));

			return FALSE;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wp))
			{
				case IDC_EXISTS_YES:
					EndDialog(hWnd, IDOK);
					return TRUE;

				case IDC_EXISTS_NO:
				case IDCANCEL:
					EndDialog(hWnd, IDCANCEL);
					return TRUE;

				case IDC_EXISTS_ALLYES:
					m_overwrite = 0x00;
					EndDialog(hWnd, IDOK);
					return TRUE;

				case IDC_EXISTS_ALLNO:
					m_overwrite = 0x10;
					EndDialog(hWnd, IDCANCEL);
					return TRUE;
			}
			return FALSE;
		}
	}

	return FALSE;
}