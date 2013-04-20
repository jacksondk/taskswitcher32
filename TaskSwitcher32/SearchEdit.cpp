#include "stdafx.h"

#include "SearchEdit.h"

BEGIN_MESSAGE_MAP(CSearchEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CSearchEdit::CSearchEdit()
{
	list = NULL;
}

void CSearchEdit::OnChar( UINT nChar, UINT nRep, UINT nFlags )
{
	CEdit::OnChar( nChar, nRep, nFlags );
}

void CSearchEdit::OnKeyDown(UINT nChar, UINT nRep, UINT nFlags )
{
	int count, idx; 
	switch ( nChar )
	{
	case VK_UP:
		if ( list != NULL )
		{
				idx = list->GetSelectionMark();
				if ( idx > 0 )
				{
					list->SetItemState( idx, 0 ,0 );
					list->SetItemState( --idx, LVIS_SELECTED, LVIS_SELECTED );
					list->SetSelectionMark( idx );
				}
		}
		break;

	case VK_DOWN:
		if ( list != NULL )
		{
			idx = list->GetSelectionMark();
			count = list->GetItemCount();
			if ( idx < count - 1 )
			{
					list->SetItemState( idx, 0 ,0 );
					list->SetItemState( ++idx, LVIS_SELECTED, LVIS_SELECTED );
					list->SetSelectionMark( idx );				
			}
			
		}
		break;

	case VK_RETURN:
		if ( list != NULL )
		{
			::SendMessage( list->m_hWnd, NM_DBLCLK, 0, 0 );
		}
	}
	CEdit::OnKeyDown(nChar, nRep, nFlags);
}

void CSearchEdit::SetListBox( CListCtrl * list )
{
	this->list = list;
}