// ChessPieces.h: interface for the CChessPieces class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHESSPIECES_H__2536E265_0419_42AC_9AA7_E0D901FB9134__INCLUDED_)
#define AFX_CHESSPIECES_H__2536E265_0419_42AC_9AA7_E0D901FB9134__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "cv.h"
#include "highgui.h"
#include "point.h"
class CChessPieces
{
public:
/*
	int m_Step;
	int m_StepY;
	int m_StepX;
	CvPoint m_DPosition;*/
	void InitChessChoosedPieces(IplImage *pImage, int x, int y);
	bool MoveShuai	(Point qipan[10][9], int i, int j, int x, int y, int SHUAI);
	bool MoveZu		(Point qipan[10][9], int i, int j, int x, int y, int ZU);
	bool MoveShi	(Point qipan[10][9], int i, int j, int x, int y, int SHI);
	bool MovePao	(Point qipan[10][9], int i, int j, int x, int y, int PAO);
	bool MoveJu		(Point qipan[10][9], int i, int j, int x, int y, int JU);
	bool MoveXiang	(Point qipan[10][9], int i, int j, int x, int y, int XIANG);
	bool MoveMa		(Point qipan[10][9], int i, int j, int x, int y, int MA);
	bool MoveRedPieces(Point qipan[10][9],int x,int y,bool & isRedPieces);
	bool MoveBlackPieces(Point qipan[10][9],int x,int y,bool & isRedPieces);
	void InitChessPieces(IplImage *pImage, int x, int y);
	CvSize m_Size;
	CvPoint m_Position;
	void Draw2Back(IplImage *pImage);
	IplImage * m_PiecesImage;
	CChessPieces();
	virtual ~CChessPieces();

};

#endif // !defined(AFX_CHESSPIECES_H__2536E265_0419_42AC_9AA7_E0D901FB9134__INCLUDED_)
