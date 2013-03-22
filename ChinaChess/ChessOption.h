// ChessOption.h: interface for the CChessOption class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHESSOPTION_H__A0F46C73_41A0_4CB9_B1F6_08E220DF33CD__INCLUDED_)
#define AFX_CHESSOPTION_H__A0F46C73_41A0_4CB9_B1F6_08E220DF33CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "cv.h"
class CChessOption  
{
public:
	bool m_IsSelected;
	CvSize m_Size;
	void InitOption(IplImage *pImage, int x, int y);
	IplImage * m_OptionImage;
	void Draw2Back(IplImage * pBack);
	CvPoint m_Position;
	CChessOption();
	virtual ~CChessOption();

};

#endif // !defined(AFX_CHESSOPTION_H__A0F46C73_41A0_4CB9_B1F6_08E220DF33CD__INCLUDED_)
