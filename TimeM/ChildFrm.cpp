
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "TimeM.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}
void   CChildFrame::OnUpdateFrameTitle(BOOL   bAddToTitle)   
  {   
        //   First   let   MFC   do   standard   title   
        CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);   
          
        CDocument*   pDoc   =   GetActiveDocument();   
        if   (pDoc)   {   
              CMultiDocTemplate*   pTemplate   =     
                    (CMultiDocTemplate*)pDoc->GetDocTemplate();   
              ASSERT_KINDOF(CMultiDocTemplate,   pTemplate);   
              ASSERT_VALID(pTemplate);   
    
          
        }   
  }
// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������
