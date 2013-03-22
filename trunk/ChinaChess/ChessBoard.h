// ChessBoard.h: interface for the CChessBoard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHESSBOARD_H__8E4A732A_5A9D_45DB_A563_5A95BAB41690__INCLUDED_)
#define AFX_CHESSBOARD_H__8E4A732A_5A9D_45DB_A563_5A95BAB41690__INCLUDED_

#include "ChessOption.h"	// Added by ClassView
#include "ChessPieces.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include <vector>

//using std::vector;
class CChessBoard  
{
public:
	static CChessOption m_Option;
	static char * m_WindowsName;
	static void InitQiPan();
	static bool m_IsOver;
	static bool isRedPieces;
	//static vector<Point[10][9]> m_Panel;
	void WinTheGame();
	void DrawBorad();
	IplImage ** m_ChessPiecesImg;
	IplImage ** m_ChessPiecesImgChoosed;
 	IplImage * m_Back;
	IplImage ** m_RePlay;
	IplImage ** m_Regret;
	IplImage ** m_Sound;
	IplImage ** m_Reload;
	static CChessPieces m_ChessPieces;
	void InitChessBoard(char *pWindowsName,IplImage *pBack,IplImage **pImg,IplImage **pImgChoosed,
		IplImage **pRePlay,IplImage **pRegret,IplImage **pSound,IplImage **pReload);
	CChessBoard();
	virtual ~CChessBoard();
	static Point qipan[10][9];
	static void OnMouse(int event, int x, int y, int flags, void* param);

};

#endif // !defined(AFX_CHESSBOARD_H__8E4A732A_5A9D_45DB_A563_5A95BAB41690__INCLUDED_)
