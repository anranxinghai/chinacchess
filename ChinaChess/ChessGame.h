// ChessGame.h: interface for the CChessGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHESSGAME_H__5A9CB21A_4B6C_4106_943C_026216029CC5__INCLUDED_)
#define AFX_CHESSGAME_H__5A9CB21A_4B6C_4106_943C_026216029CC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "cv.h"
#include "ChessBoard.h"	// Added by ClassView
#include "ChessPieces.h"	// Added by ClassView
#include "VFW.H"

class CChessGame  
{
public:
	void InitBackGroundSound();
	IplImage * m_ChessPiecesChoosedImage[14];
	void WinTheGame();
	char * m_WindowsName;
	CChessBoard m_ChessBoard;

	void InitChessPiecesImg();
	void InitChessBoard();
	IplImage * m_ChessPiecesImage[14];
	void ReleasePiecesImg();	
	void RunGame();
	void ReleaseGame();
	void ReleaseBackGround();
	void Draw();
	void InitBackGround();
	void InitGame();
	IplImage *m_pImgBackCopy;
	IplImage *m_pImgBack;
	CChessGame();
	virtual ~CChessGame();

};

#endif // !defined(AFX_CHESSGAME_H__5A9CB21A_4B6C_4106_943C_026216029CC5__INCLUDED_)
