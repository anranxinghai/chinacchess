// ChessGame.cpp: implementation of the CChessGame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChessGame.h"
#include "cv.h"
#include "highgui.h"

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
	m_IsStart = false;
	m_WindowsName = "ChessGame";
	InitStartGame();
	InitBackGround();
	InitImage();
	cvNamedWindow(m_WindowsName);
	InitChessBoard();
	InitBackGroundSound();	
}

void CChessGame::InitBackGround()
{
	m_StartBack = cvLoadImage(".//image//start.jpg",1);
	m_StartBackCopy = cvCloneImage(m_StartBack);

	m_pImgBack = cvLoadImage(".//image//qipan.jpg",1);
	m_pImgBackCopy = cvCloneImage(m_pImgBack);
}

void CChessGame::Draw()
{
	if (m_ChessBoard.m_IsStart)
	{
		cvCopy( m_pImgBack, m_pImgBackCopy,NULL);
		m_ChessBoard.DrawBorad();
		cvShowImage("ChessGame", m_pImgBackCopy);//ÏÔÊ¾Í¼Ïñ
	}
	else
	{
		cvCopy(m_StartBack,m_StartBackCopy,NULL);
		m_ChessBoard.DrawStart();
		cvShowImage("ChessGame", m_StartBackCopy);//ÏÔÊ¾Í¼Ïñ
	}

	
}

void CChessGame::ReleaseBackGround()
{	
	cvReleaseImage(&m_pImgBack);
	cvReleaseImage(&m_pImgBackCopy);
	cvReleaseImage(&m_StartBackCopy);
}


void CChessGame::ReleaseGame()
{
	ReleaseImage();
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






void CChessGame::ReleaseImage()
{
	for (int i = 0;i<24;i++)
	{
		cvReleaseImage(&m_ChessPiecesImage[i]);
	}

	for (i = 0;i<2;i++)
	{
		cvReleaseImage(&m_Reload[i]);
		cvReleaseImage(&m_RePlay[i]);
		cvReleaseImage(&m_Regret[i]);
		cvReleaseImage(&m_Sound[i]);
		cvReleaseImage(&m_StartImg[i]);
		cvReleaseImage(&m_ExitImg[i]);

	}
}



void CChessGame::InitChessBoard()
{
	m_ChessBoard.InitChessBoard(m_WindowsName,m_pImgBackCopy,m_ChessPiecesImage,m_ChessPiecesChoosedImage,
	m_RePlay,m_Regret,m_Sound,m_Reload,m_StartBackCopy,m_StartImg,m_ExitImg);
}

void CChessGame::InitImage()
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

	m_RePlay[0] = cvLoadImage(".//image//replay.png");
	m_RePlay[1] = cvLoadImage(".//imagechoosed//replay.png");
	
	m_Regret[0] = cvLoadImage(".//image//regret.png");
	m_Regret[1] = cvLoadImage(".//imagechoosed//regret.png");
	
	m_Reload[0] = cvLoadImage(".//image//reload.png");
	m_Reload[1] = cvLoadImage(".//imagechoosed//reload.png");
	
	m_Sound[0] = cvLoadImage(".//image//sound.png");
	m_Sound[1] = cvLoadImage(".//imagechoosed//sound.png");
	m_StartImg[0] = cvLoadImage(".//image//start.png");	
	m_StartImg[1] = cvLoadImage(".//imagechoosed//start.png");

	m_ExitImg[0] = cvLoadImage(".//image//exit.png");
	m_ExitImg[1] = cvLoadImage(".//imagechoosed//exit.png");
}



void CChessGame::WinTheGame()
{
	m_ChessBoard.WinTheGame();
}

void CChessGame::InitBackGroundSound()
{
	m_ChessBoard.InitBackGroundSound();
}



void CChessGame::InitStartGame()
{
	
}
