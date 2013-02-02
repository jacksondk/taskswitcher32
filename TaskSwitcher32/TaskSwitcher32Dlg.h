// TaskSwitcher32Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "SearchEdit.h"
#include <string>

// CTaskSwitcher32Dlg dialog
class CTaskSwitcher32Dlg : public CDialog
{
// Construction
public:
	CTaskSwitcher32Dlg(std::wstring search, CWnd *pParent = NULL);

// Dialog Data
	enum { IDD = IDD_TASKSWITCHER32_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	
// Implementation
protected:

	virtual void OnOK();
	afx_msg void OnSize(UINT nType, int cx, int cy );
	HICON m_hIcon;

	std::wstring search;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnUpdateEdit1();
	CSearchEdit m_filterBox;
	CListCtrl m_windowList2;
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);

private:
	void FilterList();
	void GotoWindow();
public:
	afx_msg void OnNMReturnList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
