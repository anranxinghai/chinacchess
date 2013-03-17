// ChessGame.cpp: implementation of the CChessGame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChessGame.h"
#include "cv.h"
#include "highgui.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChessGame::CChessGame()
{

}

CChessGame::~CChessGame()
{

}

void CChessGame::InitGame()
{
	m_WindowsName = "ChessGame";
	InitBackGround();
	InitChessPiecesImg();
	InitBackGroundSound();
	cvNamedWindow(m_WindowsName);
	InitChessBoard();
	
	
}

void CChessGame::InitBackGround()
{
	m_pImgBack = cvLoadImage(".//image//qipan.jpg",1);
	m_pImgBackCopy = cvCloneImage(m_pImgBack);
}

void CChessGame::Draw()
{

	cvCopy( m_pImgBack, m_pImgBackCopy,NULL);
	m_ChessBoard.DrawBorad(m_pImgBackCopy,m_ChessPiecesImage,m_ChessPiecesChoosedImage);
	cvShowImage("ChessGame", m_pImgBackCopy);//ÏÔÊ¾Í¼Ïñ

}

void CChessGame::ReleaseBackGround()
{
	cvReleaseImage(&m_pImgBack);
	cvReleaseImage(&m_pImgBackCopy);
}

void CChessGame::ReleaseGame()
{
	ReleasePiecesImg();
	ReleaseBackGround();
	cvDestroyWindow("ChessGame");
}

void CChessGame::RunGame()
{
		while (true)
		{
			
			Draw();
			WinTheGame();
			char key = cvWaitKey(10); //µÈ´ý°´¼ü
			if (key == 27)break;
		}
}






void CChessGame::ReleasePiecesImg()
{
	for (int i = 0;i<24;i++)
	{
		cvReleaseImage(&m_ChessPiecesImage[i]);
	}
}



void CChessGame::InitChessBoard()
{
	m_ChessBoard.InitChessBoard(m_WindowsName,m_pImgBackCopy,m_ChessPiecesImage,m_ChessPiecesChoosedImage);
}

void CChessGame::InitChessPiecesImg()
{
	char filename[] = ".//image//00.png";
	for (int i = 0;i<14;i++)
	{
		sprintf(filename,".//image//%02d.png",i);
		m_ChessPiecesImage[i] = cvLoadImage(filename);
	}
	char filenamechoosed[] = ".//imagechoosed//00.png";
	for (i = 0;i<14;i++)
	{
		sprintf(filenamechoosed,".//imagechoosed//%02d.png",i);
		m_ChessPiecesChoosedImage[i] = cvLoadImage(filenamechoosed);
	}

}



void CChessGame::WinTheGame()
{
	m_ChessBoard.WinTheGame();
}

void CChessGame::InitBackGroundSound()
{
	HWND m_hMCI;
	m_hMCI = MCIWndCreate(NULL, NULL, WS_POPUP | WS_VISIBLE | MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU, ".//sounds//PINGSHANLUOYAN.WAV");
	MCIWndPlay(m_hMCI);
}

//DEL void CChessGame::InitBackGroundSound()
//DEL {
//DEL 	mciSendString(TEXT("open PINGSHANLUOYAN.WAV alias mysong"), NULL, 0, NULL);
//DEL 	mciSendString(TEXT("play MySong"), NULL, 0, NULL);
//DEL }
