// ChessBoard.cpp: implementation of the CChessBoard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChessBoard.h"
#include "cv.h"
#include "highgui.h"
#include <vfw.h>
#pragma   comment(lib, "vfw32.lib ")
#pragma comment(lib, "WINMM.LIB")
#include <windows.h>
#include <mmsystem.h>

#include <vector>
using std::vector;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
uchar CChessBoard::bB;
uchar CChessBoard::bS;
uchar CChessBoard::gB;
uchar CChessBoard::gS;
uchar CChessBoard::rS;
uchar CChessBoard::rB;*/
IplImage *CChessBoard::m_Back;
IplImage *CChessBoard::m_StartBack;

bool CChessBoard::m_IsSave;
void CChessBoard::GetQiPan();
void CChessBoard::SaveToFile();
/*float CChessBoard::m_Insist;*/
Point *CChessBoard::qipan;
CChessPieces CChessBoard::m_ChessPieces;
bool CChessBoard::m_IsRedPieces;
bool CChessBoard::m_IsOver;
bool CChessBoard::m_IsPlayMusic;
bool CChessBoard::m_IsStart;
CChessOption CChessBoard::m_Option;
char * CChessBoard::m_WindowsName;
vector<Point> CChessBoard::m_Panel;
int CChessBoard::m_StepNum;
std::vector<Point>::iterator CChessBoard::point;
HWND CChessBoard::m_hMCI;
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
		x>251 && x<386 && y>245 && y<311 && !m_IsStart)
	{
		m_IsStart = true;
		/*while(m_Insist<50)
		{
		
		  ChangeToGame();
	}*/
		//延时1秒
		Sleep(1000);
	}
	else if (event == CV_EVENT_LBUTTONDOWN && !m_IsOver &&
		x>251 && x<386 && y>377 && y<443 && !m_IsStart)
	{
		m_IsStart = false;
		exit(0);
	}
	if (event == CV_EVENT_LBUTTONDOWN && !m_IsOver &&
		x>20 && x<628 && y>30 && y<659 && m_IsStart)
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
				if (qipan->isChecked[prex][prey])
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
		//if (prex == 10 && prey ==9) return;
		//如果当前点击到某个棋子，并且和之前选中的棋子分别于双方,  吃子
		if (qipan->point[i][j]!=0 && 
			(abs(qipan->point[i][j] + qipan->point[prex][prey]) 
			== abs(qipan->point[i][j]) + abs(qipan->point[prex][prey])))
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
						qipan->isChecked[i][j] = !qipan->isChecked[i][j];
					}
					//把之前选中的棋子改为为选中状态
					else	qipan->isChecked[k][l] = false;
				}
			}
			
		}
		else if (qipan->point[i][j] == 0)
		{
			if (m_IsRedPieces)
			{
				if (m_ChessPieces.MoveRedPieces(qipan,i,j,m_IsRedPieces))
				{
					m_IsSave=false;
					m_Panel.push_back(*qipan);
					//红移
					sndPlaySound(".\\Sounds\\MOVE.WAV",SND_ASYNC);
					m_StepNum++;
				}
				
				
			}
			else
			{
				
				if (m_ChessPieces.MoveBlackPieces(qipan,i,j,m_IsRedPieces))
				{
					m_IsSave=false;
					m_Panel.push_back(*qipan);
					//黑移
					sndPlaySound(".\\Sounds\\MOVE2.WAV",SND_ASYNC);
					m_StepNum++;
				}
				
			}
			qipan->isChecked[prex][prey] = false;
		}
		//吃子的情况。
		if (qipan->point[i][j]!=0 && 
			(abs(qipan->point[i][j] + qipan->point[prex][prey])
			< abs(qipan->point[i][j]) + abs(qipan->point[prex][prey])))
		{
			if (m_IsRedPieces)
			{
				if (m_ChessPieces.MoveRedPieces(qipan,i,j,m_IsRedPieces))
				{
					m_IsSave=false;
					m_Panel.push_back(*qipan);
					//红吃
					sndPlaySound(".\\Sounds\\CAPTURE.WAV",SND_ASYNC);
				}
			}
			else
			{
				if (m_ChessPieces.MoveBlackPieces(qipan,i,j,m_IsRedPieces))
				{
					m_IsSave=false;
					m_Panel.push_back(*qipan);
					//黑吃
					sndPlaySound(".\\Sounds\\CAPTURE2.WAV",SND_ASYNC);
					
				}
				
			}
			qipan->isChecked[prex][prey] = false;
		}
		else return;
		
		//测试辅助代码，输出象棋矩阵
		for (i =0; i<10;i++)
		{
			for (j= 0;j < 9;j++)
			{
				if (qipan->isChecked[i][j])
				{
					printf("已选\t");
				}
				else 
				{
					printf("%d\t", qipan->point[i][j]);
				}
			}
			printf("\n");
		}
		printf("%d\t%d\n",x,y);
	}
	else if (x<20 && y<30 && (event == CV_EVENT_LBUTTONDOWN || event==CV_EVENT_LBUTTONUP))
	{
		//m_Option.m_IsSelected = true;
		//cvShowImage(m_WindowsName,NULL);
		if (event == CV_EVENT_LBUTTONUP && x<20 && y<30 )
		{
			//	m_Option.m_IsSelected = false;
			if (IDYES == MessageBox(NULL,"是否重新开始！", "中国象棋", MB_YESNO))
			{
				InitQiPan();
				m_Panel.clear();
				m_IsOver = false;
			}
		}
	}
	
	else if(x>608 && y<30 && event==CV_EVENT_LBUTTONUP)
	{
		if(m_Panel.size()<=0) return;
		for (point = m_Panel.begin();point < m_Panel.end();point++)
		{
			printf("Vector[%d]中的数据：\n\n",m_Panel.size());
			for (int i =0; i<10;i++)
			{
				for (int j= 0;j < 9;j++)
				{
					qipan->isChecked[i][j] = false;
					printf("%d\t", qipan->point[i][j]);
				}
				printf("\n");
			}
		}
		m_IsOver = false;
		m_IsRedPieces = !m_IsRedPieces; 
		m_Panel.pop_back();
		point = m_Panel.end()-1;
		qipan = point;
		
		if (m_Panel.size()<1)
		{
			InitQiPan();
			m_Panel.clear();
			//return;
		}
		//point++;
	}
	else if (x<30 && y>670 && event==CV_EVENT_LBUTTONUP)
	{
		m_IsPlayMusic = !m_IsPlayMusic;
		if (m_IsPlayMusic)
		{
			PlayMusic();
		}
		else StopMusic();
		printf("%d %d\n",x,y);
	}
	else if (x>608,y>670 && event==CV_EVENT_LBUTTONUP)
	{
		if (m_IsSave)
		{
			if (IDYES == MessageBox(NULL,"是否恢复棋局！", "中国象棋", MB_YESNO))
			{
				GetQiPan();
			}
		
		}
		else{
			if (IDYES == MessageBox(NULL,"是否保存棋局！", "中国象棋", MB_YESNO))
			{
				SaveToFile();
			}
			
		}
		
	}
	//测试代码，输出点击坐标
	if (CV_EVENT_LBUTTONUP==event)
	{
		printf("%d %d\n",x,y);
	}
	
}

void CChessBoard::InitChessBoard(char *pWindowsName,IplImage *pBack,IplImage **pImg,IplImage **pImgChoosed,
								 IplImage **pRePlay,IplImage **pRegret,IplImage **pSound,IplImage **pReload,IplImage*pStartBack,
								 IplImage **pStartImage,IplImage **pExitImage)
{
	int i = 0,j = 0;
	qipan = new Point;
	InitQiPan();
	//	m_IsRedPieces = true;
	m_IsSave = false;
	FILE *fp =  fopen("save.txt","rb");
	if (fp!=NULL)
	{
		fread(&m_IsSave,sizeof(bool),1,fp);
	}
	fclose(fp);
	m_IsOver = false;
	
	m_WindowsName = pWindowsName;
	m_RePlay = pRePlay;
	m_Regret = pRegret;
	m_Reload = pReload;
	m_Sound = pSound;
	m_ChessPiecesImg = pImg;
	m_ChessPiecesImgChoosed = pImgChoosed;
	m_Back = pBack;
	m_IsPlayMusic = true;
	m_IsStart = false;
	m_StartBack = pStartBack;
	m_StartImage = pStartImage;
	m_ExitImage = pExitImage;
// 	m_Insist = 0;
	cvSetMouseCallback(m_WindowsName, OnMouse);
	//DrawBorad();
/*
	
	bS = CV_IMAGE_ELEM(m_StartBack,uchar,i,j*3);
	gS = CV_IMAGE_ELEM(m_StartBack,uchar,i,j*3+1);
	rS = CV_IMAGE_ELEM(m_StartBack,uchar,i,j*3+2);
	
	bB = CV_IMAGE_ELEM(m_Back,uchar,i,j*3);
	gB = CV_IMAGE_ELEM(m_Back,uchar,i,j*3+1);
	rB = CV_IMAGE_ELEM(m_Back,uchar,i,j*3+2);
*/
}

void CChessBoard::DrawBorad()
{
	if (m_IsStart)
	{
		
		int i,j,x = -1,y = -1;
		for (i = 0;i < 10;i++)
		{
			for (j = 0;j < 9;j++)
			{
				if (qipan->point[i][j] >= 1 && qipan->point[i][j] <= 7)
				{
					if (!qipan->isChecked[i][j])
					{
						m_ChessPieces.InitChessPieces(m_ChessPiecesImg[qipan->point[i][j] - 1],i,j);
						m_ChessPieces.Draw2Back(m_Back);
					}
					else
					{
						x = i;
						y = j;
					}
				}
				else if (qipan->point[i][j] <= -1 && qipan->point[i][j] >= -7)
				{
					if (!qipan->isChecked[i][j])
					{
						m_ChessPieces.InitChessPieces(m_ChessPiecesImg[qipan->point[i][j]*(-1) + 6],i,j);
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
		if (qipan->point[x][y] >= 1 && qipan->point[x][y] <= 7)
		{
			if (qipan->isChecked[x][y])
			{
				m_ChessPieces.InitChessChoosedPieces(m_ChessPiecesImgChoosed[qipan->point[x][y] - 1],x,y);
				m_ChessPieces.Draw2Back(m_Back);
			}
		}
		else if (qipan->point[x][y] <= -1 && qipan->point[x][y] >= -7)
		{
			if (qipan->isChecked[x][y])
			{
				m_ChessPieces.InitChessChoosedPieces(m_ChessPiecesImgChoosed[qipan->point[x][y]*(-1) + 6],x,y);
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

		/*if (m_Option.m_IsSelected)
		{
			m_Option.InitOption(m_Reload[1],670,500);
		}
		else
		{
			m_Option.InitOption(m_Reload[0],670,500);
		}
		m_Option.Draw2Back(m_Back);*/
		
	}
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
			if (qipan->point[i][j] == REDSHUAI)
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
		sndPlaySound(".\\Sounds\\WIN.WAV",SND_ASYNC);
		MessageBox(NULL,"黑棋获胜！", "中国象棋", MB_OK | MB_ICONSTOP);
	}
	
	for (i = 7;i<10;i++)
	{
		bool flag = false;
		for (j = 3;j<6;j++)
		{
			if (qipan->point[i][j] == BLACKJIANG)
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
		sndPlaySound(".\\Sounds\\WIN.WAV",SND_ASYNC);
		MessageBox(NULL,"红旗获胜！", "中国象棋", MB_OK | MB_ICONSTOP);	
	}
}

void CChessBoard::InitQiPan()
{
	qipan->point[0][0] = REDJU;   
	qipan->point[0][1] =   REDMA;
	qipan->point[0][2] =  REDXIANG;  qipan->point[0][3] =  REDSHI;  qipan->point[0][4] =  REDSHUAI;  
	qipan->point[0][5] = REDSHI;  qipan->point[0][6] = REDXIANG;  qipan->point[0][7] =  REDMA;  qipan->point[0][8] =  REDJU;
	
	qipan->point[1][0] = EMPTY; qipan->point[1][1] = EMPTY;qipan->point[1][2] = EMPTY; qipan->point[1][3] = EMPTY; qipan->point[1][4] = EMPTY; 
	qipan->point[1][5] = EMPTY; qipan->point[1][6] = EMPTY;qipan->point[1][7] = EMPTY; qipan->point[1][8] = EMPTY; 
	
	qipan->point[2][0] = EMPTY;qipan->point[2][1] = REDPAO;qipan->point[2][2] = EMPTY;qipan->point[2][3] = EMPTY;
	qipan->point[2][4] = EMPTY;qipan->point[2][5] = EMPTY;qipan->point[2][6] = EMPTY;qipan->point[2][7] = REDPAO;qipan->point[2][8] = EMPTY; 
	
	qipan->point[3][0] = REDBING;qipan->point[3][1] = EMPTY;qipan->point[3][2] = REDBING;qipan->point[3][3] = EMPTY;
	qipan->point[3][4] = REDBING;qipan->point[3][5] = EMPTY;qipan->point[3][6] = REDBING;qipan->point[3][7] = EMPTY;qipan->point[3][8] = REDBING; 
	
	qipan->point[4][0] = EMPTY;qipan->point[4][1] = EMPTY;qipan->point[4][2] = EMPTY;qipan->point[4][3] = EMPTY;
	qipan->point[4][4] = EMPTY;qipan->point[4][5] = EMPTY;qipan->point[4][6] = EMPTY;qipan->point[4][7] = EMPTY; qipan->point[4][8] = EMPTY;
	
	qipan->point[5][0] = EMPTY;qipan->point[5][1] = EMPTY;qipan->point[5][2] = EMPTY;qipan->point[5][3] = EMPTY;qipan->point[5][4] = EMPTY;
	qipan->point[5][5] = EMPTY;qipan->point[5][6] = EMPTY;qipan->point[5][7] = EMPTY;qipan->point[5][8] = EMPTY; 
	
	qipan->point[6][0] = BLACKZU;  qipan->point[6][1] = EMPTY;  qipan->point[6][2] = BLACKZU;qipan->point[6][3] = EMPTY;  qipan->point[6][4] = BLACKZU; 
	qipan->point[6][5] = EMPTY; qipan->point[6][6] = BLACKZU;  qipan->point[6][7] = EMPTY;qipan->point[6][8] = BLACKZU; 
	
	qipan->point[7][0] = EMPTY; qipan->point[7][1] =  BLACKPAO; qipan->point[7][2] =  EMPTY;qipan->point[7][3] = EMPTY;qipan->point[7][4] = EMPTY;
	qipan->point[7][5] = EMPTY;qipan->point[7][6] = EMPTY;qipan->point[7][7] = BLACKPAO;qipan->point[7][8] = EMPTY; 
	
	qipan->point[8][0]	= EMPTY;qipan->point[8][1]	= EMPTY;qipan->point[8][2]	= EMPTY;qipan->point[8][3]	= EMPTY;qipan->point[8][4]	= EMPTY;
	qipan->point[8][5]	=  EMPTY;qipan->point[8][6]= EMPTY;qipan->point[8][7]	= EMPTY;qipan->point[8][8]	= EMPTY; 
	
	qipan->point[9][0] = BLACKJU; qipan->point[9][1] = BLACKMA; qipan->point[9][2] = BLACKXIANG;qipan->point[9][3] = BLACKSHI;qipan->point[9][4] =  BLACKJIANG;
	qipan->point[9][5] = BLACKSHI;qipan->point[9][6] = BLACKXIANG;qipan->point[9][7] = BLACKMA;qipan->point[9][8] = BLACKJU;
	
	for (int i =0; i<10;i++)
	{
		for (int j= 0;j < 9;j++)
		{
			qipan->isChecked[i][j] = false;
			printf("%d\t", qipan->point[i][j]);
		}
		printf("\n");
	}
	m_IsRedPieces = true;
	m_Panel.push_back(*qipan);	
	m_StepNum = 0;
}

void CChessBoard::InitBackGroundSound()
{	
	m_hMCI = MCIWndCreate(NULL, NULL, WS_POPUP | WS_VISIBLE | MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU, ".//sounds//PINGSHANLUOYAN.WAV");
	MCIWndPlay(m_hMCI);
}



void CChessBoard::PlayMusic()
{
	MCIWndPlay(m_hMCI);
}

void CChessBoard::StopMusic()
{
	MCIWndStop(m_hMCI);
}

void CChessBoard::DrawStart()
{
	if (!m_IsStart)
	{
		m_Option.InitOption(m_StartImage[0],251,245);
		m_Option.Draw2Back(m_StartBack);
		
		m_Option.InitOption(m_ExitImage[0],386,245);
		m_Option.Draw2Back(m_StartBack);
	}
}

//此函数值起到了延时的功能,但是被取消。
//DEL void CChessBoard::ChangeToGame()
//DEL {
//DEL 	for (int i = 0; i<m_StartBack->height;i++)
//DEL 	{
//DEL 		for (int j = 0;j<m_StartBack->width;j++)
//DEL 		{
//DEL 			
//DEL 			
//DEL 			CV_IMAGE_ELEM( m_Back, uchar, j, i*3 + 0 ) = CV_IMAGE_ELEM( m_Back, uchar, j, i*3 + 0 )*(m_Insist)/100;// + rB*(100-m_Insist)/100;
//DEL 			CV_IMAGE_ELEM( m_Back, uchar, j, i*3 + 1 ) = CV_IMAGE_ELEM( m_Back, uchar, j, i*3 + 1 )*(m_Insist)/100 ;//+ gB*(100-m_Insist)/100;
//DEL 			CV_IMAGE_ELEM( m_Back, uchar, j, i*3 + 2 ) = CV_IMAGE_ELEM( m_Back, uchar, j, i*3 + 2 )*(m_Insist)/100 ;//+ rB*(100-m_Insist)/100;
//DEL 		}
//DEL 	}
//DEL 	cvNamedWindow("Chess",1);
//DEL 	cvShowImage("Chess",m_Back);
//DEL 	if (m_Insist<50)
//DEL 	{
//DEL 		Sleep(10);
//DEL 		m_Insist= m_Insist +1;
//DEL 	}
//DEL 	
//DEL }

void CChessBoard::SaveToFile()
{
	FILE *fp;
	if ((fp=fopen("save.txt", "wb")) ==NULL )
	{
		printf("cannot open this file\n");
		exit(0);
	}
	m_IsSave = !m_IsSave;
	fwrite(&m_IsSave,sizeof(bool),1,fp);
	for (int i = 0;i<10;i++)
	{
		fwrite(qipan->point[i],9*sizeof(int),1,fp);
	}
	
	
	printf("save success\n");

	fclose(fp);

}

void CChessBoard::GetQiPan()
{
	FILE *fp;
	if ((fp=fopen("save.txt", "rb")) ==NULL )
	{
		printf("cannot open this file\n");
		exit(0);
	}
	m_IsSave = !m_IsSave;
	fread(&m_IsSave,sizeof(bool),1,fp);
	for (int i = 0;i<10;i++)
	{
		fread(qipan->point[i],9*sizeof(int),1,fp);	
	}
	
	printf("get success\n");
	fclose(fp);

}
