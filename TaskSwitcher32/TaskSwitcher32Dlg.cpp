#include "stdafx.h"
#include "TaskSwitcher32.h"
#include "TaskSwitcher32Dlg.h"

#include "WindowItem.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTaskSwitcher32Dlg::CTaskSwitcher32Dlg(std::wstring search, CWnd* pParent /*=NULL*/)
	: CDialog(CTaskSwitcher32Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->search = search;
}

void CTaskSwitcher32Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_filterBox);
	DDX_Control(pDX, IDC_LIST2, m_windowList2);
}

BEGIN_MESSAGE_MAP(CTaskSwitcher32Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT1, &CTaskSwitcher32Dlg::OnEnUpdateEdit1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CTaskSwitcher32Dlg::OnNMDblclkList2)
	ON_NOTIFY(NM_RETURN, IDC_LIST2, &CTaskSwitcher32Dlg::OnNMReturnList2)
END_MESSAGE_MAP()


// CTaskSwitcher32Dlg message handlers

BOOL CTaskSwitcher32Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Setup list view headers
	m_windowList2.SetView( LV_VIEW_DETAILS );
	m_windowList2.InsertColumn( 0, _T("Name"), LVCFMT_LEFT, 200, -1 );
	m_windowList2.InsertColumn( 1, _T("Process" ), LVCFMT_LEFT, 400, -1 );
	
	// Set the search box 
	m_filterBox.SetWindowTextW( this->search.c_str() );

	// Call the filter
	FilterList();

	// Setup filter text box to send special keys to the list box and put focus on text box
	m_filterBox.SetListBox( &m_windowList2 );
	m_filterBox.SetFocus();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTaskSwitcher32Dlg::FilterList()
{
	m_windowList2.DeleteAllItems();

	window_list *list = window_item::get_window_list();
	CImageList *pImageList = new CImageList(); pImageList->Create( 16, 16, ILC_COLOR32 | ILC_MASK | ILC_PERITEMMIRROR, 0, 10);

	m_windowList2.SetImageList( pImageList, LVSIL_SMALL);
	int default_idx = pImageList->Add( m_hIcon );
		
	for ( unsigned int i = 0; i < list->size(); i++ )
	{
		window_item *item = (*list)[i];
		bool ok = true;
		if ( this->search.length() > 0 )
		{
			int pos = item->get_lower_title().find( this->search ) ; 
			int pos2 = item->get_process_name().find( this->search );
			if ( pos == std::string::npos && pos2 == std::string::npos ) 
				ok = false;
		}
		if ( ok )
		{
			HWND hwnd = item->get_handle();
			HICON hIcon = NULL;
 
			SendMessageTimeout(hwnd, WM_GETICON, ICON_BIG, 0, SMTO_ABORTIFHUNG, 1000, (LPDWORD)&hIcon);
			if (!hIcon) SendMessageTimeout(hwnd, WM_GETICON, ICON_SMALL2, 0, SMTO_ABORTIFHUNG, 1000, (LPDWORD)&hIcon);
 			if (!hIcon) SendMessageTimeout(hwnd, WM_GETICON, ICON_SMALL, 0, SMTO_ABORTIFHUNG, 1000, (LPDWORD)&hIcon);
            if (!hIcon) hIcon = (HICON)GetClassLong(hwnd, GCL_HICON);
            if (!hIcon) hIcon = (HICON)GetClassLong(hwnd, GCL_HICONSM);
        
		
			int imageidx = -1;
			if ( hIcon != NULL )
			{
				HICON iconCopy = CopyIcon( hIcon );				
				imageidx = pImageList->Add( iconCopy );
				DestroyIcon( iconCopy );
			}
			else
			{
				imageidx = 1;
			}
			int idx = m_windowList2.InsertItem( 0, item->get_title().c_str(), imageidx );
			m_windowList2.SetItem(  idx, 1, LVIF_TEXT | LVIF_IMAGE, item->get_process_name().c_str(), imageidx, 0, 0, 0 );
			m_windowList2.SetItemData( idx, (DWORD_PTR) item );
			
		}
	}
	m_windowList2.SetItemState( 0, LVIS_SELECTED, LVIS_SELECTED );
	m_windowList2.SetSelectionMark( 0 );

}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTaskSwitcher32Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTaskSwitcher32Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTaskSwitcher32Dlg::OnEnUpdateEdit1()
{
	int length = m_filterBox.GetWindowTextLengthW();
	if ( length > 0 )
	{
		LPTSTR filter = new TCHAR[ length + 1];
		memset( filter, 0, sizeof( TCHAR )*(length+1) );
		m_filterBox.GetWindowTextW( filter, length+1 );
		this->search = std::wstring( filter );	
		delete [] filter;
	}
	else	
	{	
		this->search = _T("");
	}

	FilterList();
}

/// Make controls follow window size
void CTaskSwitcher32Dlg::OnSize( UINT nType, int cx, int cy )
{
	if ( m_windowList2.m_hWnd != 0 )
		m_windowList2.MoveWindow( 10,10, cx - 20, cy - 50 );
	if ( m_filterBox.m_hWnd != 0)
		m_filterBox.MoveWindow( 10, cy - 35, cx - 20, 20 );
	CDialog::OnSize( nType, cx, cy );
}

// Dbl click is select
void CTaskSwitcher32Dlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{	
	OnOK();
	*pResult = 0;
}

// Return is select
void CTaskSwitcher32Dlg::OnNMReturnList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnOK();
	*pResult = 0;
}

// Go to selected window
void CTaskSwitcher32Dlg::OnOK()
{
	int idx = m_windowList2.GetSelectionMark();
	window_item * item = (window_item*)m_windowList2.GetItemData( idx );
	if ( ::IsIconic( item->get_handle() ) )
		::OpenIcon( item->get_handle() );
	::SetForegroundWindow( item->get_handle() );	
	CDialog::OnOK(); // End window
}
