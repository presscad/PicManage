
// 图片管理器View.h : C图片管理器View 类的接口
//

#pragma once
using namespace std;

class C图片管理器View : public CView
{
	enum
	{
		DRAW_CONNOTDRAW,
		DRAW_LINE,
		DRAW_BRUSH,
		DRAW_CIRCLE,
		DRAW_ECLIPSE,
		DRAW_RECT,
		DRAW_CURL,
		DRAW_ERASER
	};
protected: // 仅从序列化创建
	C图片管理器View();
	DECLARE_DYNCREATE(C图片管理器View)

// 特性
public:
	C图片管理器Doc* GetDocument() const;

// 操作
public:
	CRect m_client;
	CPoint m_pre_point;
//	Line* tmp;
	//用于跟踪鼠标的信息
//	vector<Line*> data;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~C图片管理器View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
	MyObject* tmp;
	bool SaveBitmap(HBITMAP  Bipmap, char* filename);
	bool SaveCurrentImage(char* filename);
};

#ifndef _DEBUG  // 图片管理器View.cpp 中的调试版本
inline C图片管理器Doc* C图片管理器View::GetDocument() const
   { return reinterpret_cast<C图片管理器Doc*>(m_pDocument); }
#endif

