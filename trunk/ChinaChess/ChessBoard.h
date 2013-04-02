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
#include <vector>

using std::vector;
class CChessBoard  
{
public:
	static uchar rB;
	static uchar gB;
	static uchar bB;
	static uchar rS;
	static uchar gS;
	static uchar bS;
	static float m_Insist;
	CvPoint m_Position;
	static void ChangeToGame();
	void DrawStart();
	IplImage ** m_ExitImage;
	IplImage ** m_StartImage;
	static IplImage * m_StartBack;
	static bool m_IsStart;
	static HWND m_hMCI;
	static void StopMusic();
	static void PlayMusic();
	static bool m_IsPlayMusic;
	void InitBackGroundSound();
	static int m_StepNum;
	static CChessOption m_Option;
	static char * m_WindowsName;
	static void InitQiPan();
	static bool m_IsOver;
	static bool m_IsRedPieces;
	static  vector<Point> m_Panel;
	static std::vector<Point>::iterator point;
	void WinTheGame();
	void DrawBorad();
	IplImage ** m_ChessPiecesImg;
	IplImage ** m_ChessPiecesImgChoosed;
 	static IplImage * m_Back;
	IplImage ** m_RePlay;
	IplImage ** m_Regret;
	IplImage ** m_Sound;
	IplImage ** m_Reload;
	static CChessPieces m_ChessPieces;
	void InitChessBoard(char *pWindowsName,IplImage *pBack,IplImage **pImg,IplImage **pImgChoosed,
		IplImage **pRePlay,IplImage **pRegret,IplImage **pSound,IplImage **pReload,
		IplImage *pStartBack,IplImage **m_StartImage,IplImage **pExitImage);
	CChessBoard();
	virtual ~CChessBoard();
	static Point*qipan;
	static void OnMouse(int event, int x, int y, int flags, void* param);

};

#endif // !defined(AFX_CHESSBOARD_H__8E4A732A_5A9D_45DB_A563_5A95BAB41690__INCLUDED_)
