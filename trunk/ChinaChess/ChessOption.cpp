// ChessOption.cpp: implementation of the CChessOption class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChessOption.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChessOption::CChessOption()
{

}

CChessOption::~CChessOption()
{

}

//DEL void CChessOption::SetPosition()
//DEL {
//DEL 
//DEL }

//将菜单图片绘制到背景上
void CChessOption::Draw2Back(IplImage *pBack)
{
	if (m_OptionImage == NULL)
	{
		printf("this pointer is null");
		return;
	}
	for (int i = 0; i<m_OptionImage->height;i++)
	{
		for (int j = 0;j<m_OptionImage->width;j++)
		{
			uchar b = CV_IMAGE_ELEM(m_OptionImage,uchar,i,j*3);
			uchar g = CV_IMAGE_ELEM(m_OptionImage,uchar,i,j*3+1);
			uchar r = CV_IMAGE_ELEM(m_OptionImage,uchar,i,j*3+2);
			if (b==190 && g==251 && r==255 || b==255 && g==255 && r==255)continue;
			CV_IMAGE_ELEM(pBack,uchar,
				m_Position.x + i,(m_Position.y + j)*3) = b;
			CV_IMAGE_ELEM(pBack,uchar,
				m_Position.x + i,(m_Position.y + j)*3 + 1) = g;
			CV_IMAGE_ELEM(pBack,uchar,
				m_Position.x + i,(m_Position.y + j)*3 + 2) = r;
		}
	}
}

//初始化菜单按钮
void CChessOption::InitOption(IplImage *pImage, int x, int y)
{
	m_OptionImage = pImage;
	m_Position.x = x;
	m_Position.y = y;

	m_Size.height = m_OptionImage->height;
	m_Size.width = m_OptionImage->width;
	m_IsSelected = false;
}
