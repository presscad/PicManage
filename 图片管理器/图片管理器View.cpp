
// 图片管理器View.cpp : C图片管理器View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "图片管理器.h"
#endif

#include "图片管理器Doc.h"
#include "图片管理器View.h"
#include "MainFrm.h"
#include "MyLine.h"
#include "MyRectangle.h"
#include "MyEllipse.h"
#include "MyCircle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C图片管理器View

IMPLEMENT_DYNCREATE(C图片管理器View, CView)

BEGIN_MESSAGE_MAP(C图片管理器View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	
END_MESSAGE_MAP()

// C图片管理器View 构造/析构

C图片管理器View::C图片管理器View()
	: m_pre_point(CPoint(0,0))
{
	// TODO: 在此处添加构造代码

}

C图片管理器View::~C图片管理器View()
{
}

BOOL C图片管理器View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//m_mousestatus = false;
	return CView::PreCreateWindow(cs);
}

// C图片管理器View 绘制

void C图片管理器View::OnDraw(CDC* pDC)
{
	C图片管理器Doc* pDoc = GetDocument();
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//CClientDC dc(this);
	//pDC->MoveTo(100,100);
	//pDC->LineTo(200,200);
	RECT rect;
	GetClientRect(&rect);
	CDC MemDC;
	//MemDC.SetBkColor(cm->m_bkgclr);
	MemDC.CreateCompatibleDC(NULL);
	CBitmap MemBitmap;
	MemBitmap.CreateCompatibleBitmap(pDC,rect.right-rect.left,rect.bottom-rect.top);
	//MemBitmap.LoadBitmap(IDR_IDB_BITMAP11); 
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0,0,rect.right-rect.left,rect.bottom-rect.top,pDoc->m_bkgclr);
	//给MeMDC绘图
	
	
	for(int i=0;i<pDoc->data.size();i++)
	{
		//CBrush brush(RGB(rand()%255,rand()%255,rand()%255)); 
		//CBrush *pOld = MemDC.SelectObject( &brush ); 
		//CPen pen(pDoc->data[i]->m_linestyle,pDoc->data[i]->m_linewidth,pDoc->data[i]->m_lineclr); 
		//CPen *penOld = MemDC.SelectObject( &pen ); 

		pDoc->data[i]->draw(MemDC);
		//MemDC.SelectObject(pOld);
		//MemDC.SelectObject(penOld);
		//pen.DeleteObject();
	}
	if(tmp)
	{
		tmp->draw(MemDC);
	}
	//先绘制文件中的，再绘制内存中的
	pDC->BitBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(pOldBit);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
	// TODO: 在此处为本机数据添加绘制代码
}


// C图片管理器View 打印

BOOL C图片管理器View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C图片管理器View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void C图片管理器View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// C图片管理器View 诊断

#ifdef _DEBUG
void C图片管理器View::AssertValid() const
{
	CView::AssertValid();
}

void C图片管理器View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C图片管理器Doc* C图片管理器View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C图片管理器Doc)));
	return (C图片管理器Doc*)m_pDocument;
}
#endif //_DEBUG


// C图片管理器View 消息处理程序


void C图片管理器View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	//m_mousestatus = true;
	if (cm->enabledraw)
	{
		switch (cm->drawstatus)
		{
		case DRAW_LINE:
			if(tmp==NULL)tmp=new MyLine(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);
			else {delete tmp;tmp=new  MyLine(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);}
			
			break;
		case DRAW_RECT:
			if(tmp==NULL)tmp=new MyRectangle(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);
				else {delete tmp;tmp=new MyRectangle(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);}
			break;

		case DRAW_ECLIPSE:
			if(tmp==NULL)tmp=new MyEllipse(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);
			else {delete tmp;tmp=new MyEllipse(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);}
			break;
		case DRAW_CIRCLE:
			if(tmp==NULL)tmp=new MyCircle(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);
			else {delete tmp;tmp=new MyCircle(point.x,point.y,point.x,point.y,cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);}
			break;

		}
		
	
	}
	
	
	
	
	m_pre_point = point;
	Invalidate();
	UpdateWindow();
	CView::OnLButtonDown(nFlags, point);
	
}


void C图片管理器View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//m_mousestatus = false;
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	if (cm->enabledraw)
	{
		if(tmp)GetDocument()->data.push_back(tmp);
		tmp=NULL;
		if (cm->drawstatus==DRAW_BRUSH)
		{
			Invalidate();
			UpdateWindow();
		}
	}


	CView::OnLButtonUp(nFlags, point);
}


void C图片管理器View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CPen pen(cm->m_nLineStyle, cm->m_nLineWidth, cm->m_clr); 
	CPen* pOldpen = dc.SelectObject(&pen);
	if (cm->enabledraw)
		switch (cm->drawstatus)
	{
		case (DRAW_BRUSH) : 
			if (nFlags&MK_LBUTTON)
			{
				//dc.SetDCBrushColor(cm->m_clr);
				dc.MoveTo(m_pre_point);
				dc.LineTo(point);
				tmp=new MyLine(m_pre_point.x,m_pre_point.y,point.x,point.y, cm->m_nLineStyle,cm->m_nLineWidth,cm->m_clr);
				GetDocument()->data.push_back(tmp);
				//dc.SetPixel(point, cm->m_clr);
				m_pre_point = point;
			};
			break;
		case (DRAW_LINE):
			if(nFlags&MK_LBUTTON)//鼠标左键处于按下状态才进行处理
			{
				
				if(tmp){
					MyLine* ml = (MyLine*)tmp;
					ml->_x2=point.x;
					ml->_y2=point.y;
				ml->m_clr = cm->m_clr;
				ml->m_style = cm->m_nLineStyle;
				ml->m_width = cm->m_nLineWidth;
				}
				Invalidate();
				UpdateWindow();
			}
			break;

		case DRAW_RECT:
			if(nFlags&MK_LBUTTON)//鼠标左键处于按下状态才进行处理
			{

				if(tmp){
					MyRectangle* mr = (MyRectangle*)tmp;
					mr->_x2=point.x;
					mr->_y2=point.y;
					mr->m_clr = cm->m_clr;
					mr->m_style = cm->m_nLineStyle;
					mr->m_width = cm->m_nLineWidth;
				}
				Invalidate();
				UpdateWindow();
			}
			break;
		case DRAW_ECLIPSE:
			if(nFlags&MK_LBUTTON)//鼠标左键处于按下状态才进行处理
			{

				if(tmp){
					MyEllipse* mr = (MyEllipse*)tmp;
					mr->_x2=point.x;
					mr->_y2=point.y;
					mr->m_clr = cm->m_clr;
					mr->m_style = cm->m_nLineStyle;
					mr->m_width = cm->m_nLineWidth;
				}
				Invalidate();
				UpdateWindow();
			}
			break;
		case DRAW_CIRCLE:
			if(nFlags&MK_LBUTTON)//鼠标左键处于按下状态才进行处理
			{

				if(tmp){
					MyCircle* mr = (MyCircle*)tmp;
					mr->_x2=point.x;
					mr->_y2=point.y;
					mr->m_clr = cm->m_clr;
					mr->m_style = cm->m_nLineStyle;
					mr->m_width = cm->m_nLineWidth;
				}
				Invalidate();
				UpdateWindow();
				SaveCurrentImage("2.bmp");
			}
			break;


		default:
		break;
	} 
	
	
	CView::OnMouseMove(nFlags, point);
}


BOOL C图片管理器View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	return CView::OnEraseBkgnd(pDC);
}


bool C图片管理器View::SaveBitmap(HBITMAP  hBitmap, char* filename)
{
	BITMAP bitmap;
	GetObject(hBitmap,sizeof(BITMAP),&bitmap);

	LPVOID lp=VirtualAlloc(0,bitmap.bmHeight*bitmap.bmWidthBytes,MEM_COMMIT,PAGE_READWRITE);
	if(lp==0) return false;
	GetBitmapBits(hBitmap,bitmap.bmHeight*bitmap.bmWidthBytes,lp);
	BITMAPFILEHEADER b1={0};
	BITMAPINFOHEADER b2={0};
	b1.bfType=(DWORD)(('M'<<8)|'B');
	b1.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	b1.bfSize=sizeof(BITMAPFILEHEADER)+bitmap.bmHeight*bitmap.bmWidthBytes+sizeof(BITMAPINFOHEADER);

	b2.biSize=sizeof(BITMAPINFOHEADER);
	b2.biWidth=bitmap.bmWidth;
	b2.biHeight=bitmap.bmHeight;
	b2.biPlanes=1;
	b2.biBitCount=bitmap.bmBitsPixel;
	b2.biCompression=BI_RGB;
	b2.biSizeImage=bitmap.bmHeight*bitmap.bmWidthBytes;

	HANDLE hFile=CreateFileA(filename,FILE_ALL_ACCESS,NULL,NULL,CREATE_ALWAYS,NULL,NULL);
	HANDLE hmap=CreateFileMapping(hFile,NULL,PAGE_READWRITE,0,b1.bfSize,0);
	LPVOID l=MapViewOfFile(hmap,FILE_MAP_WRITE,0,0,0);
	if(l==0) return false;
	memcpy(l,&b1,sizeof(BITMAPFILEHEADER));
	memcpy((BYTE*)l+sizeof(b1),&b2,sizeof(BITMAPINFOHEADER));
	for(int i=0;i<bitmap.bmHeight;i++)
		memcpy((BYTE*)l+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+i*bitmap.bmWidthBytes,(BYTE*)lp+(bitmap.bmHeight-1-i)*bitmap.bmWidthBytes,bitmap.bmWidthBytes);
	UnmapViewOfFile(l);
	CloseHandle(hmap);
	CloseHandle(hFile);
	VirtualFree(lp,bitmap.bmHeight*bitmap.bmWidthBytes,MEM_FREE);
	if(GetLastError()) return false;
	return true;
}


bool C图片管理器View::SaveCurrentImage(char* filename)
{
	bool flag;
	C图片管理器Doc* pDoc = GetDocument();
	CMainFrame * cm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return FALSE;
	
	RECT rect;
	GetClientRect(&rect);
	CDC MemDC;
	MemDC.CreateCompatibleDC(CDC::FromHandle(::GetDC(NULL)));
	CBitmap MemBitmap;
	CDC *pDC=GetDC();
	MemBitmap.CreateCompatibleBitmap(CDC::FromHandle(::GetDC(NULL)),rect.right-rect.left,rect.bottom-rect.top);
	//MemBitmap.LoadBitmap(IDR_IDB_BITMAP11); 
	MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0,0,rect.right-rect.left,rect.bottom-rect.top,pDoc->m_bkgclr);
	//给MeMDC绘图


	for(int i=0;i<pDoc->data.size();i++)
	{
		

		pDoc->data[i]->draw(MemDC);
		
	}
	
	MemDC.BitBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,GetDC(),rect.left,rect.top,SRCCOPY);
	flag = SaveBitmap(*(MemDC.GetCurrentBitmap()),"1.bmp");
	

	MemBitmap.DeleteObject();
	MemDC.DeleteDC();



	




	return flag;
}
