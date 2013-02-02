#ifndef SEARCH_EDIT_H
#define SEARCH_EDIT_H

#include "stdafx.h"

#define IDD_SEARCH_BOX 1000

class CSearchEdit : public CEdit
{
public:
	CSearchEdit();

	enum { IDD = IDD_SEARCH_BOX };

	void SetListBox( CListCtrl * list );
protected:
	afx_msg void OnChar( UINT nChar, UINT nRepCount, UINT nFlags );
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCount, UINT nFlags );
	DECLARE_MESSAGE_MAP();

private:

	CListCtrl *list;
};

#endif