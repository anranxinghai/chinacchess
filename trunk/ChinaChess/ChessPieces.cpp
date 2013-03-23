// ChessPieces.cpp: implementation of the CChessPieces class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChessPieces.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "math.h"
#include <Mmsystem.h>
CChessPieces::CChessPieces()
{
	
}

CChessPieces::~CChessPieces()
{
	
}

void CChessPieces::Draw2Back(IplImage *pImage)
{
	if (m_PiecesImage == NULL)
	{
		printf("this pointer is null");
		return;
	}
	for (int i = 0; i<m_PiecesImage->height;i++)
	{
		for (int j = 0;j<m_PiecesImage->width;j++)
		{
			uchar b = CV_IMAGE_ELEM(m_PiecesImage,uchar,i,j*3);
			uchar g = CV_IMAGE_ELEM(m_PiecesImage,uchar,i,j*3+1);
			uchar r = CV_IMAGE_ELEM(m_PiecesImage,uchar,i,j*3+2);
			if (b==255 && g==255 && r==255)continue;
			CV_IMAGE_ELEM(pImage,uchar,
				m_Position.x + i,(m_Position.y + j)*3) = b;
			CV_IMAGE_ELEM(pImage,uchar,
				m_Position.x + i,(m_Position.y + j)*3 + 1) = g;
			CV_IMAGE_ELEM(pImage,uchar,
				m_Position.x + i,(m_Position.y + j)*3 + 2) = r;
		}
	}
}

void CChessPieces::InitChessPieces(IplImage *pImage, int x, int y)
{
	m_PiecesImage = pImage;
	m_Size.height = m_PiecesImage->height;
	m_Size.width = m_PiecesImage->width;
	m_Position.x = 51 + x*m_PiecesImage->width-1.01*m_PiecesImage->width/2;
	m_Position.y = 52 + 1.02*y*m_PiecesImage->height-m_PiecesImage->height/2;
}
void CChessPieces::InitChessChoosedPieces(IplImage *pImage, int x, int y)
{
	m_PiecesImage = pImage;
	m_Size.height = m_PiecesImage->height;
	m_Size.width = m_PiecesImage->width;
	m_Position.x = 46 + 0.868*x*m_PiecesImage->width-0.868*1.01*m_PiecesImage->width/2;
	m_Position.y = 47 + 0.868*1.02*y*m_PiecesImage->height-0.868*m_PiecesImage->height/2;
}

bool CChessPieces::MoveBlackPieces(Point *qipan,int x,int y,bool &m_IsRedPieces)
{
	int i,j;
	for(i = 0;i < 10;i++)
	{
		bool flag = false;
		for (j = 0;j < 9;j++)
		{
			if (qipan->isChecked[i][j])
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
		switch(qipan->point[i][j])
		{
		case BLACKMA:
			if(MoveMa(qipan,i,j,x,y,BLACKMA))
			{			
			m_IsRedPieces = true;
			return true;
			}
			else 
			{
				m_IsRedPieces = false;			
				return false;
			} 
			break;
		case BLACKXIANG:
			if(MoveXiang(qipan,i,j,x,y,BLACKXIANG))
			{
				m_IsRedPieces = true;
				return true;
			}
			else 
			{
				m_IsRedPieces = false;			
				return false;
			}
			break;
		case BLACKJU:
			if (MoveJu(qipan,i,j,x,y,BLACKJU))
			{
			m_IsRedPieces = true;
			return true;
			}
			else 
			{
				m_IsRedPieces = false;			
				return false;
			}		
			break;
		case BLACKPAO:
			if(MovePao(qipan,i,j,x,y,BLACKPAO))
			{
				m_IsRedPieces = true;
				return true;
			}
			else 
			{
				m_IsRedPieces = false;			
				return false;
			}
			break;
		case BLACKSHI:
			if (MoveShi(qipan,i,j,x,y,BLACKSHI))
			{
				m_IsRedPieces = true;
				return true;
			}
			else 
			break;
		case BLACKZU:
			if (MoveZu(qipan,i,j,x,y,BLACKZU))
			{
				m_IsRedPieces = true;
				return true;
			}
			else 
			{
				m_IsRedPieces = false;
				return false;
			}
			break;
		case BLACKJIANG:
			if (MoveShuai(qipan,i,j,x,y,BLACKJIANG))
			{
				m_IsRedPieces = true;
				return true;
			}
			else 
			{
				m_IsRedPieces = false;			
				return false;
			}
			break;
		default:
			{
				m_IsRedPieces = false;
				return false;
			}
		
		}	
	
}

bool CChessPieces::MoveRedPieces(Point *qipan,int x,int y,bool &m_IsRedPieces)
{
	int i,j;
	//�ҳ���ǰѡ�е������x��y���ꡣ
	for(i = 0;i < 10;i++)
	{
		bool flag = false;
		for (j = 0;j < 9;j++)
		{
			if (qipan->isChecked[i][j])
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
		
		switch(qipan->point[i][j])
		{
		case REDMA:
			if (MoveMa(qipan,i,j,x,y,REDMA))
			{
				m_IsRedPieces = false;
				return true;
			}			
			else 
			{
				m_IsRedPieces = true;
				return false;
			}
			break;
		case REDXIANG:
			if (MoveXiang(qipan,i,j,x,y,REDXIANG))
			{
			m_IsRedPieces = false;
			return true;
			}
			else 
			{
				m_IsRedPieces = true;
				return false;
			}
			break;
		case REDJU:
			if (MoveJu(qipan,i,j,x,y,REDJU))
			{
				m_IsRedPieces = false;
				return true;
			}			
			else 
			{
				m_IsRedPieces = true;
				return false;
			}
			break;
		case REDPAO:
			if (MovePao(qipan,i,j,x,y,REDPAO))
			{
				m_IsRedPieces = false;
			}
			else 
			{
				m_IsRedPieces = true;
				return false;
			}
			
			break;
		case REDSHI:
			if (MoveShi(qipan,i,j,x,y,REDSHI))
			{
				m_IsRedPieces = false;
				return true;
			}
			else 
			{
				m_IsRedPieces = true;
				return false;
			}
			break;
		case REDBING:
			if (MoveZu(qipan,i,j,x,y,REDBING))
			{
				m_IsRedPieces = false;
				return true;
			}
			else 
			{
				m_IsRedPieces = true;
				return false;
			}
			break;
		case REDSHUAI:
			if (MoveShuai(qipan,i,j,x,y,REDSHUAI))
			{
				m_IsRedPieces = false;
				return true;
			}
			else 
			{
				m_IsRedPieces = true;
				return false;
			}
			break;
		default: m_IsRedPieces = true;
			return false;
		}
	
	
}

bool CChessPieces::MoveMa(Point *qipan,int i, int j,int x,int y,int MA)
{
	//����
	if (x<0 || y<0 || x>9 || y>8 )
	{
		return false;
	}
	//�����㲻���ɡ��ա��֣��Ƿ��Ĳ���
	else if ( (abs(x - i) !=1 || abs(y - j) != 2) && ( abs(x - i) != 2 || abs(y - j) != 1))
	{
		return false;
	}
	//Ŀ��λ���ڵ�ǰλ�õ����Ϸ�
	else if(x<i && y <j)
	{
		if ((i - x)==1 && (j - y) == 2)
		{
			if (qipan->point[i][j-1]!=0)
			{
				//����ϵͳ��CLICK.WAV�ļ�
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = MA;
				return true;
			}
		}
		else if ((i - x)==2 && (j - y) == 1)
		{
			if (qipan->point[i-1][j]!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = MA;
				return true;
			}
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ����·�
	else if (x>i && y>j)
	{
		if ((x - i)==1 && (y - j) == 2)
		{
			if (qipan->point[i][j+1]!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = MA;
				return true;
			}
		}
		else if ((x - i)==2 && (y - j) == 1)
		{
			if (qipan->point[i+1][j]!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = MA;
				return true;
			}
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ����Ϸ�
	else if (x<i && y>j)
	{
		if ((i - x)==1 && (y - j) == 2)
		{
			if (qipan->point[i][j+1]!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = MA;
				return true;
			}
		}
		else if ((i - x)==2 && (y - j) == 1)
		{
			if (qipan->point[i-1][j]!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = MA;
				return true;
			}
		}
	}
	//���½�
	else if (x>i && y<j)
	{
		if ((x - i)==1 && (j - y) == 2)
		{
			if (qipan->point[i][j-1]!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = MA;
				return true;
			}
		}
		else if ((x - i)==2 && (j - y) == 1)
		{
			if (qipan->point[i+1][j]!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = MA;
				return true;
			}
		}
	}
}


bool CChessPieces::MoveXiang(Point *qipan,int i, int j,int x,int y,int XIANG)
{
	//����
	if (x<0 || y<0 || x>9 || y>8 )
	{ 
		return false;
	}
	//�����㲻���ɡ���֣��Ƿ��Ĳ���
	else if ( abs(x - i) !=2 || abs(y - j) != 2)
	{
		return false;
	}
	if (qipan->point[i][j] == REDXIANG && x>4)
	{
		return false;
	}
	if (qipan->point[i][j] == BLACKXIANG && x<5)
	{
		return false;
	}
	//Ŀ��λ���ڵ�ǰλ�õ����Ϸ�
	else if(x<i && y <j)
	{
		if ((i - x)==2 && (j - y) == 2)
		{
			if (qipan->point[i-1][j-1]!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ۣ�\n");
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = XIANG;
				return true;
			}
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ����·�
	else if (x>i && y>j)
	{
		if ((x - i)==2 && (y - j) == 2)
		{
			if (qipan->point[i+1][j+1]!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ۣ�\n");
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = XIANG;
				return true;
			}
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ����Ϸ�
	else if (x<i && y>j)
	{
		if ((i - x)==2 && (y - j) == 2)
		{
			if (qipan->point[i-1][j+1]!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ۣ�\n");
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = XIANG;
				return true;
			}
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ����½�
	else if (x>i && y<j)
	{
		if ((x - i)==2 && (j - y) == 2)
		{
			if (qipan->point[i+1][j-1]!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ۣ�\n");
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = XIANG;
				return true;
			}
		}
	}
}

bool CChessPieces::MoveJu(Point *qipan, int i, int j, int x, int y, int JU)
{
	//����
	if (x<0 || y<0 || x>9 || y>8 )
	{
		return false;
	}
	//����ͬһ��ֱ����
	if (i!=x && j!=y)
	{
		return false;
	}
	//Ŀ��λ���ڵ�ǰλ�õ���
	else if (i == x && j > y)
	{
		if (j-y==1)
		{
			qipan->isChecked[i][j] = false;
			qipan->point[i][j] = 0;
			qipan->point[x][y] = JU;
			return true;
		}
		for (int step = y+1;step < j;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan->point[i][step]!=0)
			{
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = JU;
				return true;
			}
			
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ��ҷ�
	else if (i == x && j < y)
	{
		if (y-j==1)
		{
			qipan->isChecked[i][j] = false;
			qipan->point[i][j] = 0;
			qipan->point[x][y] = JU;
			return true;
			
		}
		for (int step = j+1;step < y;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan->point[i][step]!=0)
			{
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = JU;
				return true;
			}
			
		}
	}
	
	//Ŀ��λ���ڵ�ǰλ�õ��·�
	else if (i < x && j == y)
	{
		if (x-i==1)
		{
			qipan->isChecked[i][j] = false;
			qipan->point[i][j] = 0;
			qipan->point[x][y] = JU;
			return true;
		}
		for (int step = i+1;step < x;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan->point[step][j]!=0)
			{
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = JU;
				return true;
			}
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ��Ϸ�
	else if (i > x && j == y)
	{
		if (i-x==1)
		{
			qipan->isChecked[i][j] = false;
			qipan->point[i][j] = 0;
			qipan->point[x][y] = JU;
			return true;
		}
		for (int step = x+1;step < i;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan->point[step][j]!=0)
			{
				return false;
			}
			else
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = JU;
				return true;
			}
			
		}
	}
	
}

bool CChessPieces::MovePao(Point *qipan, int i, int j, int x, int y, int PAO)
{
	if (x<0 || y<0 || x>9 || y>8 )
	{
		return false;
	}
	//����ͬһ��ֱ����
	if (i!=x && j!=y)
	{
		return false;
	}
	//Ŀ��λ���ڵ�ǰλ�õ���
	else if (i == x && j > y)
	{
		int num = 0;
		if (j-y==1)
		{
			if(qipan->point[x][y]!=0) return false;
			qipan->isChecked[i][j] = false;
			qipan->point[i][j] = 0;
			qipan->point[x][y] = PAO;
			return true;
		}
		for (int step = y+1;step < j;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan->point[i][step]!=0)
			{
				num++;
			}
			
		}
		if (num>1 || num == 0 && qipan->point[x][y] != 0)
		{
			return false;
		}
		else
		{
			//�ƶ�һ����Ŀ��λ�������ӡ� 
			if (num == 1 && qipan->point[x][y]==0)return false;

			qipan->isChecked[i][j] = false;
			qipan->point[i][j] = 0;
			qipan->point[x][y] = PAO;
			return true;
		}
		
	}
	//Ŀ��λ���ڵ�ǰλ�õ��ҷ�
	else if (i == x && j < y)
	{
		int num = 0;
		if (y-j==1)
		{
			if(qipan->point[x][y]!=0) return false;
			qipan->isChecked[i][j] = false;
			qipan->point[i][j] = 0;
			qipan->point[x][y] = PAO;
			return true;
			
		}
		for (int step = j+1;step < y;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan->point[i][step]!=0)
			{
				num++;
			}			
		}
		if (num>1 || num == 0 && qipan->point[x][y] != 0)
		{
			return false;
		}
		else
		{
			if (num == 1 && qipan->point[x][y]==0)return false;
			qipan->isChecked[i][j] = false;
			qipan->point[i][j] = 0;
			qipan->point[x][y] = PAO;
		}
		
	}
	
	//Ŀ��λ���ڵ�ǰλ�õ��·�
	else if (i < x && j == y)
	{
		int num = 0;
		if (x-i==1)
		{
			if(qipan->point[x][y]!=0) return false;
			qipan->isChecked[i][j] = false;
			qipan->point[i][j] = 0;
			qipan->point[x][y] = PAO;
			return true;
		}
		for (int step = i+1;step < x;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan->point[step][j]!=0)
			{
				num++;
			}
		}
		if (num>1 || num == 0 && qipan->point[x][y] != 0)
		{
			return false;
		}
		else
		{
			if (num == 1 && qipan->point[x][y]==0)return false;
			qipan->isChecked[i][j] = false;
			qipan->point[i][j] = 0;
			qipan->point[x][y] = PAO;
			return true;
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ��Ϸ�
	else if (i > x && j == y)
	{
		int num = 0;
		if (i-x==1)
		{
			if(qipan->point[x][y]!=0) return false;
			qipan->isChecked[i][j] = false;
			qipan->point[i][j] = 0;
			qipan->point[x][y] = PAO;
			return true;
		}
		for (int step = x+1;step < i;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan->point[step][j]!=0)
			{
				num++;
			}
		}
		if (num>1 || num == 0 && qipan->point[x][y] != 0)
		{
			return false;
		}
		else
		{
			if (num == 1 && qipan->point[x][y]==0)return false;
			qipan->isChecked[i][j] = false;
			qipan->point[i][j] = 0;
			qipan->point[x][y] = PAO;
			return true;
		}
	}
	
}

bool CChessPieces::MoveShi(Point *qipan, int i, int j, int x, int y, int SHI)
{
	//�����Ź���
	if (y<3||y>5)
	{
		return false;
	}
	//��ͬһ��ֱ����
	if (i==x || j==y)
	{
		return false;
	}
	switch(qipan->point[i][j])
	{
	case REDSHI:
		{
			if (x<0 || x>2) return false;
			if (abs(i-x)==1 && abs(j-y)==1)
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = SHI;
				return true;
			}
			else return false;
		}
		break;
	case BLACKSHI:
		{
			if (x>9||x<7) return false;
			if (abs(i-x)==1 && abs(j-y)==1)
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = SHI;
				return true;
			}
			else return false;
		}	
	}
	
}

bool CChessPieces::MoveZu(Point *qipan, int i, int j, int x, int y, int ZU)
{
	if (x<0||x>9||y<0||y>8) return false;
	switch(qipan->point[i][j])
	{
	case REDBING:
		{
			//���ܻ�ͷ��
			if (x<i)return false;
			if (i>4)
			{
				//
				if (abs(y-j)==1 && x==i)
				{
					qipan->isChecked[i][j] = false;
					qipan->point[i][j] = 0;
					qipan->point[x][y] = ZU;
					return true;
				}
				else if (y==j && x - i==1)
				{
					qipan->isChecked[i][j] = false;
					qipan->point[i][j] = 0;
					qipan->point[x][y] = ZU;
					return true;
				}
				else return false;
			}
			else if (y==j && x - i==1)
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = ZU;
				return true;
			}
			else return false;
		}
		break;
	case BLACKZU:
		{
			//���ܻ�ͷ��
			if (x>i)return false;
			//���˺ӽ�
			if (i<5)
			{
				if (abs(y-j)==1 && x==i)
				{
					qipan->isChecked[i][j] = false;
					qipan->point[i][j] = 0;
					qipan->point[x][y] = ZU;
					return true;
				}
				else if (y==j && i - x==1)
				{
					qipan->isChecked[i][j] = false;
					qipan->point[i][j] = 0;
					qipan->point[x][y] = ZU;
					return true;
				}
				else return false;
			}
			else if (y==j && i - x==1)
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = ZU;
				return true;
			}
			else return false;
		}
		break;
	}
}

bool CChessPieces::MoveShuai(Point *qipan, int i, int j, int x, int y, int SHUAI)
{
	//����ͬһ��ֱ����
	if (i!=x && j!=y) return false;
	//������֮��û������
	else if (qipan->point[i][j] + qipan->point[x][y] == 0)
	{
		bool isHasNOPieces = true;
		if (i>x && j==y)
		{
			
			for (int k = 1+x;k<i;k++)
			{
				if (qipan->point[k][j] != 0) isHasNOPieces = false;
			}
			if (isHasNOPieces)
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = SHUAI;
				return true;
			}
		}
		else if (i<x && j==y)
		{
			
			for (int k = i+1;k<x;k++)
			{
				if (qipan->point[k][j] != 0) isHasNOPieces = false;
			}
			if (isHasNOPieces)
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = SHUAI;
				return true;
			}
		}	
		
	}
	switch(qipan->point[i][j])
	{
	case REDSHUAI:
		{
			//�����Ź���
			if (x<0||x>2||y<3||y>5) return false;
			else if(abs(x-i)+abs(y-j) == 1)
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = SHUAI;				
				return true;
			}
		}break;
	case BLACKJIANG:
		{
			if (x<7||x>9||y<3||y>5) return false;
			else if(abs(x-i)+abs(y-j) == 1)
			{
				qipan->isChecked[i][j] = false;
				qipan->point[i][j] = 0;
				qipan->point[x][y] = SHUAI;				
				return true;
			}
			
		}
		break;
	default:return false;
	}
}


//DEL void CChessPieces::SetPostionStep(int x, int y, int stepX, int stepY)
//DEL {
//DEL 	
//DEL 	m_Position.x = 51 + x*m_PiecesImage->width-1.01*m_PiecesImage->width/2;
//DEL 	m_Position.y = 52 + 1.02*y*m_PiecesImage->height-m_PiecesImage->height/2;
//DEL 	m_StepY = stepY;//y���򲽳�
//DEL 	m_StepX = stepX;//x���򲽳�
//DEL }

//DEL void CChessPieces::CalcOriStep()
//DEL {
//DEL 	double dx = m_DPosition.x - m_Position.x;
//DEL 	double dy = m_DPosition.y - m_Position.y;
//DEL 	double angle;
//DEL 	if (dx!=0)
//DEL 	{
//DEL 		angle = atan(abs(dy/dx));		
//DEL 	}
//DEL 	else angle = 0;
//DEL 	// (angle*180/3.14);û�����Ż���ֲ���ͷ�ߵ�����
//DEL 	int tem =(int) (angle*180/3.14);
//DEL 	
//DEL 	if (dx<=0 && dy<=0)
//DEL 	{
//DEL 		//��һ����
//DEL 		m_StepX = (-1) * m_Step*cos(angle);
//DEL 		m_StepY = (-1) * m_Step*sin(angle);
//DEL 	}
//DEL 	else if (dx>0 && dy<0)
//DEL 	{
//DEL 		//�ڶ�����
//DEL 		tem = 180 - tem;
//DEL 		m_StepX = m_Step*cos(angle);
//DEL 		m_StepY = (-1) * m_Step*sin(angle);
//DEL 	}
//DEL 	else if (dx> 0 && dy>0)
//DEL 	{
//DEL 		//��������
//DEL 		tem = 180 + tem;
//DEL 		m_StepX = m_Step*cos(angle);
//DEL 		m_StepY = m_Step*sin(angle);
//DEL 	}
//DEL 	else if (dx<0 && dy>0)
//DEL 	{
//DEL 		//��������
//DEL 		tem = 360 - tem;
//DEL 		m_StepX = (-1) * m_Step*cos(angle);
//DEL 		m_StepY = m_Step*sin(angle);
//DEL 	}
//DEL }

//DEL void CChessPieces::Move()
//DEL {
//DEL 	int dx = m_DPosition.x - m_Position.x;
//DEL 	int dy = m_DPosition.y - m_Position.y;
//DEL 
//DEL 		CalcOriStep();
//DEL 		m_Position.x+= m_StepX;
//DEL 		m_Position.y+= m_StepY;
//DEL }

//DEL void CChessPieces::ChangePosition()
//DEL {
//DEL 		m_Position.x += m_StepX;
//DEL 		m_Position.y += m_StepY;
//DEL }
