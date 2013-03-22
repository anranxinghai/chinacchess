// ChessBoard.cpp: implementation of the CChessBoard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChessBoard.h"
#include "cv.h"
#include "highgui.h"
#include <Mmsystem.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Point CChessBoard::qipan[10][9];
CChessPieces CChessBoard::m_ChessPieces;
bool CChessBoard::isRedPieces;
bool CChessBoard::m_IsOver;
CChessOption CChessBoard::m_Option;
char * CChessBoard::m_WindowsName;
//vector<Point[10][9]> CChessBoard::m_Panel;
/*
IplImage **CChessBoard::m_Regret;
IplImage **CChessBoard::m_Reload;
IplImage **CChessBoard::m_RePlay;
IplImage **CChessBoard::m_Sound;*/
CChessBoard::CChessBoard()
{
	
}

CChessBoard::~CChessBoard()
{
	
}

void CChessBoard::OnMouse(int event, int x, int y, int flags, void *param)
{
	
	int i = 0,j = 0;
	if (event == CV_EVENT_LBUTTONDOWN && !m_IsOver &&
		x>20 && x<628 && y>30 && y<659 )
	{		
		//i和j为鼠标点击的地方所在矩阵的坐标值
		printf("%d  %d\n",x,y);
		i = abs(y - 50 + 36)/67;
		j = abs(x - 50 + 33)/66;
		//attention ：这里i，j对于数组来说i是行，j是列，对于棋盘来说，同样i是行，j是列
		printf("%d  %d\n",i,j);
		
		
		int prex ,prey;
		for (prex = 0;prex<10;prex++)
		{
			bool flag = false;
			//获取上次点击选中的棋子坐标
			for (prey = 0;prey<9;prey++)
			{
				if (qipan[prex][prey].isChecked)
				{
					flag = true;
					break;
				}				
			}
			if (flag)
			{
				break;
			}
		}
		//如果当前点击到某个棋子，并且和之前选中的棋子分别于双方
		if (qipan[i][j].point!=0 && 
			(abs(qipan[i][j].point + qipan[prex][prey].point) 
			== abs(qipan[i][j].point) + abs(qipan[prex][prey].point)))
		{
			for (int k =0; k<10;k++)
			{
				for (int l = 0;l < 9;l++)
				{
					//找到当前点击的棋子坐标，
					if (k == i && l == j)
					{
						//点击某个棋子
						sndPlaySound(".\\Sounds\\CLICK.WAV",SND_ASYNC);
						qipan[i][j].isChecked = !qipan[i][j].isChecked;
					}
					//把之前选中的棋子改为为选中状态
					else	qipan[k][l].isChecked = false;
				}
			}
			
		}
		else if (qipan[i][j].point == 0)
		{
			if (isRedPieces)
			{
				if (m_ChessPieces.MoveRedPieces(qipan,i,j,isRedPieces))
				{
					//红移
					sndPlaySound(".\\Sounds\\MOVE.WAV",SND_ASYNC);
					//m_Panel.push_back(qipan);
				}
				
				
			}
			else
			{
				
				if (m_ChessPieces.MoveBlackPieces(qipan,i,j,isRedPieces))
				{
					//黑移
					sndPlaySound(".\\Sounds\\MOVE2.WAV",SND_ASYNC);
				}
				
			}
			qipan[prex][prey].isChecked = false;
		}
		if (qipan[i][j].point!=0 && 
			(abs(qipan[i][j].point + qipan[prex][prey].point) 
			< abs(qipan[i][j].point) + abs(qipan[prex][prey].point)))
		{
			if (isRedPieces)
			{
				if (m_ChessPieces.MoveRedPieces(qipan,i,j,isRedPieces))
				{
					//红吃
					sndPlaySound(".\\Sounds\\CAPTURE.WAV",SND_ASYNC);
				}		
				
			}
			else
			{
				if (m_ChessPieces.MoveBlackPieces(qipan,i,j,isRedPieces))
				{
					//黑吃
					sndPlaySound(".\\Sounds\\CAPTURE2.WAV",SND_ASYNC);
				}
				
			}
			qipan[prex][prey].isChecked = false;
		}
		
		//测试辅助代码，输出象棋矩阵
		for (i =0; i<10;i++)
		{
			for (j= 0;j < 9;j++)
			{
				if (qipan[i][j].isChecked)
				{
					printf("已选\t");
				}
				else 
				{
					printf("%d\t", qipan[i][j].point);
				}
			}
			printf("\n");
		}
	}
	if (x<20 && y<30 && event == CV_EVENT_LBUTTONDOWN || event==CV_EVENT_LBUTTONUP)
	{
		//m_Option.m_IsSelected = true;
		//cvShowImage(m_WindowsName,NULL);
		if (event == CV_EVENT_LBUTTONUP && x<20 && y<30 )
		{
		//	m_Option.m_IsSelected = false;
			if (IDYES == MessageBox(NULL,"是否重新开始！", "中国象棋", MB_YESNO))
			{
				InitQiPan();
				m_IsOver = false;
			}
		}
	}
}

void CChessBoard::InitChessBoard(char *pWindowsName,IplImage *pBack,IplImage **pImg,IplImage **pImgChoosed,
		IplImage **pRePlay,IplImage **pRegret,IplImage **pSound,IplImage **pReload)
{	
	int i = 0,j = 0;
	InitQiPan();
	for (i =0; i<10;i++)
	{
		for (j= 0;j < 9;j++)
		{
			qipan[i][j].isChecked = false;
			printf("%d\t", qipan[i][j].point);
		}
		printf("\n");
	}
	isRedPieces = true;
	m_IsOver = false;

	m_WindowsName = pWindowsName;
	m_RePlay = pRePlay;
	m_Regret = pRegret;
	m_Reload = pReload;
	m_Sound = pSound;
	m_ChessPiecesImg = pImg;
	m_ChessPiecesImgChoosed = pImgChoosed;
	m_Back = pBack;

	cvSetMouseCallback(m_WindowsName, OnMouse);
	DrawBorad();
}

void CChessBoard::DrawBorad()
{
	
	int i,j,x = -1,y = -1;
	for (i = 0;i < 10;i++)
	{
		for (j = 0;j < 9;j++)
		{
			if (qipan[i][j].point >= 1 && qipan[i][j].point <= 7)
			{
				if (!qipan[i][j].isChecked)
				{
					m_ChessPieces.InitChessPieces(m_ChessPiecesImg[qipan[i][j].point - 1],i,j);
					m_ChessPieces.Draw2Back(m_Back);
				}
				else
				{
					x = i;
					y = j;
				}
			}
			else if (qipan[i][j].point <= -1 && qipan[i][j].point >= -7)
			{
				if (!qipan[i][j].isChecked)
				{
					m_ChessPieces.InitChessPieces(m_ChessPiecesImg[qipan[i][j].point*(-1) + 6],i,j);
					m_ChessPieces.Draw2Back(m_Back);
				}
				else
				{
					x = i;
					y = j;
				}
			}
		}
	}
	//将选中的棋子最后绘制，实现选中棋子在其他棋子之上的感觉
	if (qipan[x][y].point >= 1 && qipan[x][y].point <= 7)
	{
		if (qipan[x][y].isChecked)
		{
			m_ChessPieces.InitChessChoosedPieces(m_ChessPiecesImgChoosed[qipan[x][y].point - 1],x,y);
			m_ChessPieces.Draw2Back(m_Back);
		}
	}
	else if (qipan[x][y].point <= -1 && qipan[x][y].point >= -7)
	{
		if (qipan[x][y].isChecked)
		{
			m_ChessPieces.InitChessChoosedPieces(m_ChessPiecesImgChoosed[qipan[x][y].point*(-1) + 6],x,y);
			m_ChessPieces.Draw2Back(m_Back);
		}
	}
	if(m_Option.m_IsSelected)
	{
		m_Option.InitOption(m_RePlay[1],0,0);
	}
	else
	{
		m_Option.InitOption(m_RePlay[0],0,0);
	}
	m_Option.Draw2Back(m_Back);

	if(m_Option.m_IsSelected)
	{
		m_Option.InitOption(m_Regret[1],0,608);
	}
	else
	{
		m_Option.InitOption(m_Regret[0],0,608);
	}
	m_Option.Draw2Back(m_Back);

	if(m_Option.m_IsSelected)
	{
		m_Option.InitOption(m_Sound[1],670,0);
	}
	else
	{
		m_Option.InitOption(m_Sound[0],670,0);
	}
	m_Option.Draw2Back(m_Back);

	if (m_Option.m_IsSelected)
	{
		m_Option.InitOption(m_Reload[1],670,608);
	}
	else
	{
		m_Option.InitOption(m_Reload[0],670,608);
	}
	m_Option.Draw2Back(m_Back);
}
void CChessBoard::WinTheGame()
{
	bool isRedWin = false;
	bool isBlackWin = false;
	int i = 0,j = 0;
	for ( i = 0;i<3;i++)
	{
		bool flag = false;
		for (j = 3;j<6;j++)
		{
			if (qipan[i][j].point == REDSHUAI)
			{
				isBlackWin = false;
				flag = true;
				break;
			}
		}
		if (flag)	break;	
	}
	if (i==3&&j==6 && !m_IsOver)
	{
		isBlackWin = true;
		m_IsOver = true;
		MessageBox(NULL,"黑棋获胜！", "中国象棋", MB_OK | MB_ICONSTOP);
	}
	
	for (i = 7;i<10;i++)
	{
		bool flag = false;
		for (j = 3;j<6;j++)
		{
			if (qipan[i][j].point == BLACKJIANG)
			{
				isRedWin = false;
				flag = true;
				break;
			}
		}
		if (flag)	break;	
	}
	if(i==10 && j==6 && !m_IsOver)
	{
		isRedWin = true;
		m_IsOver = true;
		MessageBox(NULL,"红旗获胜！", "中国象棋", MB_OK | MB_ICONSTOP);	
	}
}

void CChessBoard::InitQiPan()
{
	qipan[0][0].point = REDJU;   qipan[0][1].point =   REDMA;  qipan[0][2].point =  REDXIANG;  qipan[0][3].point =  REDSHI;  qipan[0][4].point =  REDSHUAI;  
	qipan[0][5].point = REDSHI;  qipan[0][6].point = REDXIANG;  qipan[0][7].point =  REDMA;  qipan[0][8].point =  REDJU;
	
	qipan[1][0].point = EMPTY; qipan[1][1].point = EMPTY;qipan[1][2].point = EMPTY; qipan[1][3].point = EMPTY; qipan[1][4].point = EMPTY; 
	qipan[1][5].point = EMPTY; qipan[1][6].point = EMPTY;qipan[1][7].point = EMPTY; qipan[1][8].point = EMPTY; 
	
	qipan[2][0].point = EMPTY;qipan[2][1].point = REDPAO;qipan[2][2].point = EMPTY;qipan[2][3].point = EMPTY;
	qipan[2][4].point = EMPTY;qipan[2][5].point = EMPTY;qipan[2][6].point = EMPTY;qipan[2][7].point = REDPAO;qipan[2][8].point = EMPTY; 
	
	qipan[3][0].point = REDBING;qipan[3][1].point = EMPTY;qipan[3][2].point = REDBING;qipan[3][3].point = EMPTY;
	qipan[3][4].point = REDBING;qipan[3][5].point = EMPTY;qipan[3][6].point = REDBING;qipan[3][7].point = EMPTY;qipan[3][8].point = REDBING; 
	
	qipan[4][0].point = EMPTY;qipan[4][1].point = EMPTY;qipan[4][2].point = EMPTY;qipan[4][3].point = EMPTY;
	qipan[4][4].point = EMPTY;qipan[4][5].point = EMPTY;qipan[4][6].point = EMPTY;qipan[4][7].point = EMPTY; qipan[4][8].point = EMPTY;
	
	qipan[5][0].point = EMPTY;qipan[5][1].point = EMPTY;qipan[5][2].point = EMPTY;qipan[5][3].point = EMPTY;qipan[5][4].point = EMPTY;
	qipan[5][5].point = EMPTY;qipan[5][6].point = EMPTY;qipan[5][7].point = EMPTY;qipan[5][8].point = EMPTY; 
	
	qipan[6][0].point = BLACKZU;  qipan[6][1].point = EMPTY;  qipan[6][2].point = BLACKZU;qipan[6][3].point = EMPTY;  qipan[6][4].point = BLACKZU; 
	qipan[6][5].point = EMPTY; qipan[6][6].point = BLACKZU;  qipan[6][7].point = EMPTY;qipan[6][8].point = BLACKZU; 
	
	qipan[7][0].point = EMPTY; qipan[7][1].point =  BLACKPAO; qipan[7][2].point =  EMPTY;qipan[7][3].point = EMPTY;qipan[7][4].point = EMPTY;
	qipan[7][5].point = EMPTY;qipan[7][6].point = EMPTY;qipan[7][7].point = BLACKPAO;qipan[7][8].point = EMPTY; 
	
	qipan[8][0].point	= EMPTY;qipan[8][1].point	= EMPTY;qipan[8][2].point	= EMPTY;qipan[8][3].point	= EMPTY;qipan[8][4].point	= EMPTY;
	qipan[8][5].point	=  EMPTY;qipan[8][6].point= EMPTY;qipan[8][7].point	= EMPTY;qipan[8][8].point	= EMPTY; 
	
	qipan[9][0].point = BLACKJU; qipan[9][1].point = BLACKMA; qipan[9][2].point = BLACKXIANG;qipan[9][3].point = BLACKSHI;qipan[9][4].point =  BLACKJIANG;
	qipan[9][5].point = BLACKSHI;qipan[9][6].point = BLACKXIANG;qipan[9][7].point = BLACKMA;qipan[9][8].point = BLACKJU;
}
