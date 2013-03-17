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

bool CChessPieces::MoveBlackPieces(Point qipan[10][9],int x,int y,bool &isRedPieces)
{
	int i,j;
	for(i = 0;i < 10;i++)
	{
		bool flag = false;
		for (j = 0;j < 9;j++)
		{
			if (qipan[i][j].isChecked)
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
		switch(qipan[i][j].point)
		{
		case BLACKMA:
			if(MoveMa(qipan,i,j,x,y,BLACKMA))
			{			
			isRedPieces = true;
			return true;
			}
			else 
			{
				isRedPieces = false;			
				return false;
			} 
			break;
		case BLACKXIANG:
			if(MoveXiang(qipan,i,j,x,y,BLACKXIANG))
			{
				isRedPieces = true;
				return true;
			}
			else 
			{
				isRedPieces = false;			
				return false;
			}
			break;
		case BLACKJU:
			if (MoveJu(qipan,i,j,x,y,BLACKJU))
			{
			isRedPieces = true;
			return true;
			}
			else 
			{
				isRedPieces = false;			
				return false;
			}		
			break;
		case BLACKPAO:
			if(MovePao(qipan,i,j,x,y,BLACKPAO))
			{
				isRedPieces = true;
				return true;
			}
			else 
			{
				isRedPieces = false;			
				return false;
			}
			break;
		case BLACKSHI:
			if (MoveShi(qipan,i,j,x,y,BLACKSHI))
			{
				isRedPieces = true;
				return true;
			}
			else 
			break;
		case BLACKZU:
			if (MoveZu(qipan,i,j,x,y,BLACKZU))
			{
				isRedPieces = true;
				return true;
			}
			else 
			{
				isRedPieces = false;
				return false;
			}
			break;
		case BLACKJIANG:
			if (MoveShuai(qipan,i,j,x,y,BLACKJIANG))
			{
				isRedPieces = true;
				return true;
			}
			else 
			{
				isRedPieces = false;			
				return false;
			}
			break;
		default:
			{
				isRedPieces = false;
				return false;
			}
		
		}	
	
}

bool CChessPieces::MoveRedPieces(Point qipan[10][9],int x,int y,bool &isRedPieces)
{
	int i,j;
	//�ҳ���ǰѡ�е������x��y���ꡣ
	for(i = 0;i < 10;i++)
	{
		bool flag = false;
		for (j = 0;j < 9;j++)
		{
			if (qipan[i][j].isChecked)
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
		
		switch(qipan[i][j].point)
		{
		case REDMA:
			if (MoveMa(qipan,i,j,x,y,REDMA))
			{
				isRedPieces = false;
				return true;
			}			
			else 
			{
				isRedPieces = true;
				return false;
			}
			break;
		case REDXIANG:
			if (MoveXiang(qipan,i,j,x,y,REDXIANG))
			{
			isRedPieces = false;
			return true;
			}
			else 
			{
				isRedPieces = true;
				return false;
			}
			break;
		case REDJU:
			if (MoveJu(qipan,i,j,x,y,REDJU))
			{
				isRedPieces = false;
				return true;
			}			
			else 
			{
				isRedPieces = true;
				return false;
			}
			break;
		case REDPAO:
			if (MovePao(qipan,i,j,x,y,REDPAO))
			{
				isRedPieces = false;
			}
			else isRedPieces = true;
			
			break;
		case REDSHI:
			if (MoveShi(qipan,i,j,x,y,REDSHI))
			{
				isRedPieces = false;
				return true;
			}
			else 
			{
				isRedPieces = true;
				return false;
			}
			break;
		case REDBING:
			if (MoveZu(qipan,i,j,x,y,REDBING))
			{
				isRedPieces = false;
				return true;
			}
			else 
			{
				isRedPieces = true;
				return false;
			}
			break;
		case REDSHUAI:
			if (MoveShuai(qipan,i,j,x,y,REDSHUAI))
			{
				isRedPieces = false;
				return true;
			}
			else 
			{
				isRedPieces = true;
				return false;
			}
			break;
		default: isRedPieces = true;
			return false;
		}
	
	
}

bool CChessPieces::MoveMa(Point qipan[10][9],int i, int j,int x,int y,int MA)
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
			if (qipan[i][j-1].point!=0)
			{
				//����ϵͳ��CLICK.WAV�ļ�
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = MA;
				return true;
			}
		}
		else if ((i - x)==2 && (j - y) == 1)
		{
			if (qipan[i-1][j].point!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = MA;
				return true;
			}
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ����·�
	else if (x>i && y>j)
	{
		if ((x - i)==1 && (y - j) == 2)
		{
			if (qipan[i][j+1].point!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = MA;
				return true;
			}
		}
		else if ((x - i)==2 && (y - j) == 1)
		{
			if (qipan[i+1][j].point!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = MA;
				return true;
			}
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ����Ϸ�
	else if (x<i && y>j)
	{
		if ((i - x)==1 && (y - j) == 2)
		{
			if (qipan[i][j+1].point!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = MA;
				return true;
			}
		}
		else if ((i - x)==2 && (y - j) == 1)
		{
			if (qipan[i-1][j].point!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = MA;
				return true;
			}
		}
	}
	//���½�
	else if (x>i && y<j)
	{
		if ((x - i)==1 && (j - y) == 2)
		{
			if (qipan[i][j-1].point!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = MA;
				return true;
			}
		}
		else if ((x - i)==2 && (j - y) == 1)
		{
			if (qipan[i+1][j].point!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ȣ�\n");
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = MA;
				return true;
			}
		}
	}
}


bool CChessPieces::MoveXiang(Point qipan[10][9],int i, int j,int x,int y,int XIANG)
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
	if (qipan[i][j].point == REDXIANG && x>4)
	{
		return false;
	}
	if (qipan[i][j].point == BLACKXIANG && x<5)
	{
		return false;
	}
	//Ŀ��λ���ڵ�ǰλ�õ����Ϸ�
	else if(x<i && y <j)
	{
		if ((i - x)==2 && (j - y) == 2)
		{
			if (qipan[i-1][j-1].point!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ۣ�\n");
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = XIANG;
				return true;
			}
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ����·�
	else if (x>i && y>j)
	{
		if ((x - i)==2 && (y - j) == 2)
		{
			if (qipan[i+1][j+1].point!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ۣ�\n");
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = XIANG;
				return true;
			}
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ����Ϸ�
	else if (x<i && y>j)
	{
		if ((i - x)==2 && (y - j) == 2)
		{
			if (qipan[i-1][j+1].point!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ۣ�\n");
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = XIANG;
				return true;
			}
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ����½�
	else if (x>i && y<j)
	{
		if ((x - i)==2 && (j - y) == 2)
		{
			if (qipan[i+1][j-1].point!=0)
			{
				sndPlaySound(".\\Sounds\\ILLEGAL.WAV",SND_ASYNC);
				printf("�����ۣ�\n");
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = XIANG;
				return true;
			}
		}
	}
}

bool CChessPieces::MoveJu(Point qipan[10][9], int i, int j, int x, int y, int JU)
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
			qipan[i][j].isChecked = false;
			qipan[i][j].point = 0;
			qipan[x][y].point = JU;
			return true;
		}
		for (int step = y+1;step < j;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan[i][step].point!=0)
			{
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = JU;
				return true;
			}
			
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ��ҷ�
	else if (i == x && j < y)
	{
		if (y-j==1)
		{
			qipan[i][j].isChecked = false;
			qipan[i][j].point = 0;
			qipan[x][y].point = JU;
			return true;
			
		}
		for (int step = j+1;step < y;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan[i][step].point!=0)
			{
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = JU;
				return true;
			}
			
		}
	}
	
	//Ŀ��λ���ڵ�ǰλ�õ��·�
	else if (i < x && j == y)
	{
		if (x-i==1)
		{
			qipan[i][j].isChecked = false;
			qipan[i][j].point = 0;
			qipan[x][y].point = JU;
			return true;
		}
		for (int step = i+1;step < x;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan[step][j].point!=0)
			{
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = JU;
				return true;
			}
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ��Ϸ�
	else if (i > x && j == y)
	{
		if (i-x==1)
		{
			qipan[i][j].isChecked = false;
			qipan[i][j].point = 0;
			qipan[x][y].point = JU;
			return true;
		}
		for (int step = x+1;step < i;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan[step][j].point!=0)
			{
				return false;
			}
			else
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = JU;
				return true;
			}
			
		}
	}
	
}

bool CChessPieces::MovePao(Point qipan[][9], int i, int j, int x, int y, int PAO)
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
			if(qipan[x][y].point!=0) return false;
			qipan[i][j].isChecked = false;
			qipan[i][j].point = 0;
			qipan[x][y].point = PAO;
			return true;
		}
		for (int step = y+1;step < j;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan[i][step].point!=0)
			{
				num++;
			}
			
		}
		if (num>1 || num == 0 && qipan[x][y].point != 0)
		{
			return false;
		}
		else
		{
			//�ƶ�һ����Ŀ��λ�������ӡ� 
			if (num == 1 && qipan[x][y].point==0)return false;

			qipan[i][j].isChecked = false;
			qipan[i][j].point = 0;
			qipan[x][y].point = PAO;
			return true;
		}
		
	}
	//Ŀ��λ���ڵ�ǰλ�õ��ҷ�
	else if (i == x && j < y)
	{
		int num = 0;
		if (y-j==1)
		{
			if(qipan[x][y].point!=0) return false;
			qipan[i][j].isChecked = false;
			qipan[i][j].point = 0;
			qipan[x][y].point = PAO;
			return true;
			
		}
		for (int step = j+1;step < y;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan[i][step].point!=0)
			{
				num++;
			}			
		}
		if (num>1 || num == 0 && qipan[x][y].point != 0)
		{
			return false;
		}
		else
		{
			if (num == 1 && qipan[x][y].point==0)return false;
			qipan[i][j].isChecked = false;
			qipan[i][j].point = 0;
			qipan[x][y].point = PAO;
		}
		
	}
	
	//Ŀ��λ���ڵ�ǰλ�õ��·�
	else if (i < x && j == y)
	{
		int num = 0;
		if (x-i==1)
		{
			if(qipan[x][y].point!=0) return false;
			qipan[i][j].isChecked = false;
			qipan[i][j].point = 0;
			qipan[x][y].point = PAO;
			return true;
		}
		for (int step = i+1;step < x;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan[step][j].point!=0)
			{
				num++;
			}
		}
		if (num>1 || num == 0 && qipan[x][y].point != 0)
		{
			return false;
		}
		else
		{
			if (num == 1 && qipan[x][y].point==0)return false;
			qipan[i][j].isChecked = false;
			qipan[i][j].point = 0;
			qipan[x][y].point = PAO;
			return true;
		}
	}
	//Ŀ��λ���ڵ�ǰλ�õ��Ϸ�
	else if (i > x && j == y)
	{
		int num = 0;
		if (i-x==1)
		{
			if(qipan[x][y].point!=0) return false;
			qipan[i][j].isChecked = false;
			qipan[i][j].point = 0;
			qipan[x][y].point = PAO;
			return true;
		}
		for (int step = x+1;step < i;step++)
		{
			//��ǰλ����Ŀ��λ��֮���������
			if (qipan[step][j].point!=0)
			{
				num++;
			}
		}
		if (num>1 || num == 0 && qipan[x][y].point != 0)
		{
			return false;
		}
		else
		{
			if (num == 1 && qipan[x][y].point==0)return false;
			qipan[i][j].isChecked = false;
			qipan[i][j].point = 0;
			qipan[x][y].point = PAO;
			return true;
		}
	}
	
}

bool CChessPieces::MoveShi(Point qipan[10][9], int i, int j, int x, int y, int SHI)
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
	switch(qipan[i][j].point)
	{
	case REDSHI:
		{
			if (x<0 || x>2) return false;
			if (abs(i-x)==1 && abs(j-y)==1)
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = SHI;
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
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = SHI;
				return true;
			}
			else return false;
		}	
	}
	
}

bool CChessPieces::MoveZu(Point qipan[10][9], int i, int j, int x, int y, int ZU)
{
	if (x<0||x>9||y<0||y>8) return false;
	switch(qipan[i][j].point)
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
					qipan[i][j].isChecked = false;
					qipan[i][j].point = 0;
					qipan[x][y].point = ZU;
					return true;
				}
				else if (y==j && x - i==1)
				{
					qipan[i][j].isChecked = false;
					qipan[i][j].point = 0;
					qipan[x][y].point = ZU;
					return true;
				}
				else return false;
			}
			else if (y==j && x - i==1)
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = ZU;
				return true;
			}
			else return false;
		}
		break;
	case BLACKZU:
		{
			if (x>i)return false;
			if (i<5)
			{
				if (abs(y-j)==1 && x==i)
				{
					qipan[i][j].isChecked = false;
					qipan[i][j].point = 0;
					qipan[x][y].point = ZU;
					return true;
				}
				else if (y==j && i - x==1)
				{
					qipan[i][j].isChecked = false;
					qipan[i][j].point = 0;
					qipan[x][y].point = ZU;
					return true;
				}
			}
			else if (y==j && i - x==1)
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = ZU;
				return true;
			}
			else return false;
		}
		break;
	}
}

bool CChessPieces::MoveShuai(Point qipan[10][9], int i, int j, int x, int y, int SHUAI)
{
	//����ͬһ��ֱ����
	if (i!=x && j!=y) return false;
	//������֮��û������
	else if (qipan[i][j].point + qipan[x][y].point == 0)
	{
		bool isHasNOPieces = true;
		if (i>x && j==y)
		{
			
			for (int k = 1+x;k<i;k++)
			{
				if (qipan[k][j].point != 0) isHasNOPieces = false;
			}
			if (isHasNOPieces)
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = SHUAI;
				return true;
			}
		}
		else if (i<x && j==y)
		{
			
			for (int k = i+1;k<x;k++)
			{
				if (qipan[k][j].point != 0) isHasNOPieces = false;
			}
			if (isHasNOPieces)
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = SHUAI;
				return true;
			}
		}	
		
	}
	switch(qipan[i][j].point)
	{
	case REDSHUAI:
		{
			//�����Ź���
			if (x<0||x>2||y<3||y>5) return false;
			else if(abs(x-i)+abs(y-j) == 1)
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = SHUAI;				
				return true;
			}
		}break;
	case BLACKJIANG:
		{
			if (x<7||x>9||y<3||y>5) return false;
			else if(abs(x-i)+abs(y-j) == 1)
			{
				qipan[i][j].isChecked = false;
				qipan[i][j].point = 0;
				qipan[x][y].point = SHUAI;				
				return true;
			}
			
		}
		break;
	default:return false;
	}
}


void CChessPieces::SetPostionStep(int x, int y, int stepX, int stepY)
{
	
	m_Position.x = 51 + x*m_PiecesImage->width-1.01*m_PiecesImage->width/2;
	m_Position.y = 52 + 1.02*y*m_PiecesImage->height-m_PiecesImage->height/2;
	m_StepY = stepY;//y���򲽳�
	m_StepX = stepX;//x���򲽳�
}

void CChessPieces::CalcOriStep()
{
	double dx = m_DPosition.x - m_Position.x;
	double dy = m_DPosition.y - m_Position.y;
	double angle;
	if (dx!=0)
	{
		angle = atan(abs(dy/dx));		
	}
	else angle = 0;
	// (angle*180/3.14);û�����Ż���ֲ���ͷ�ߵ�����
	int tem =(int) (angle*180/3.14);
	
	if (dx<=0 && dy<=0)
	{
		//��һ����
		m_StepX = (-1) * m_Step*cos(angle);
		m_StepY = (-1) * m_Step*sin(angle);
	}
	else if (dx>0 && dy<0)
	{
		//�ڶ�����
		tem = 180 - tem;
		m_StepX = m_Step*cos(angle);
		m_StepY = (-1) * m_Step*sin(angle);
	}
	else if (dx> 0 && dy>0)
	{
		//��������
		tem = 180 + tem;
		m_StepX = m_Step*cos(angle);
		m_StepY = m_Step*sin(angle);
	}
	else if (dx<0 && dy>0)
	{
		//��������
		tem = 360 - tem;
		m_StepX = (-1) * m_Step*cos(angle);
		m_StepY = m_Step*sin(angle);
	}
}

void CChessPieces::Move()
{
	int dx = m_DPosition.x - m_Position.x;
	int dy = m_DPosition.y - m_Position.y;

		CalcOriStep();
		m_Position.x+= m_StepX;
		m_Position.y+= m_StepY;
}

void CChessPieces::ChangePosition()
{
		m_Position.x += m_StepX;
		m_Position.y += m_StepY;
}
