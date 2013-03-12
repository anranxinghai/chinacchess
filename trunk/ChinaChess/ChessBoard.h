// ChessBoard.h: interface for the CChessBoard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHESSBOARD_H__8E4A732A_5A9D_45DB_A563_5A95BAB41690__INCLUDED_)
#define AFX_CHESSBOARD_H__8E4A732A_5A9D_45DB_A563_5A95BAB41690__INCLUDED_

#include "ChessPieces.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChessBoard  
{
public:
	void WinTheGame();
	void DrawBorad(IplImage *pBack,IplImage **pImg,IplImage **pImgChoosed);
	IplImage ** m_ChessPiecesImg;
	static CChessPieces m_ChessPieces;
	void InitChessBoard(char *m_WindowsName,IplImage *pBack,IplImage **pImg,IplImage **pImgChoosed);
	CChessBoard();
	virtual ~CChessBoard();
	static Point qipan[10][9];
	static void OnMouse(int event, int x, int y, int flags, void* param);

};

#endif // !defined(AFX_CHESSBOARD_H__8E4A732A_5A9D_45DB_A563_5A95BAB41690__INCLUDED_)
