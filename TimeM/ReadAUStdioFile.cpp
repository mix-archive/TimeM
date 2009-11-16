// ReadAUStdioFile.cpp : 实现文件
//

#include "stdafx.h"
#include "afx.h"
#include "ReadAUStdioFile.h"

//
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReadAUStdioFile 对话框

CReadAUStdioFile::~CReadAUStdioFile()
{
	
}
CReadAUStdioFile::CReadAUStdioFile(BOOL IsSaveByUnicode)
: CStdioFile()
,m_IsAlreadyWrite(false)
,m_IsUnicodeFile(false)
,bSaveByUnicode(IsSaveByUnicode)
{

	
} 
BOOL CReadAUStdioFile::Open(LPCTSTR lpszFileName, UINT nOpenFlags,CFileException* pError)
{
	
BOOL rtValue=CStdioFile::Open(lpszFileName,nOpenFlags|CFile::typeBinary,pError);
if(rtValue)
try
{
if((nOpenFlags&CFile::modeWrite)!=CFile::modeWrite)
	{
		SeekToBegin();
	BYTE buf[2];
	Read(buf,2);
	if(buf[0]!=0xff||buf[1]!=0xfe)
	{
		SeekToBegin();
	m_IsUnicodeFile=false;
	

	}
	else
	{
	m_IsUnicodeFile=true;

	}
	}
}
catch(...)
{
	m_IsUnicodeFile=false;
}
return rtValue;
}

LPTSTR CReadAUStdioFile::ReadString(__out_ecount(nMax) LPTSTR lpsz, UINT nMax)
{
	ASSERT(lpsz != NULL);
	ASSERT(AfxIsValidAddress(lpsz, nMax));
	ASSERT(m_pStream != NULL);
	LPWSTR lpszResult;
	char *pszresult;
	if (lpsz == NULL)
	{
		AfxThrowInvalidArgException();
	}
	if(m_IsUnicodeFile)
	lpszResult = fgetws(lpsz, nMax, m_pStream);
		else
		{
			
					char *lpsz2=new char[nMax+1];
			//lpsz=NULL;
		pszresult = fgets(lpsz2, nMax+1, m_pStream);
		lpszResult=(TCHAR*)pszresult;
		if(lpszResult)
		MultiByteToWideChar(CP_ACP,0,lpsz2,-1,lpsz,nMax);
		else
		{
			lpsz=NULL; 
		}
lpszResult=lpsz;
		delete []lpsz2;
		
		}


	if (lpszResult == NULL && !feof(m_pStream))
	{
		Afx_clearerr_s(m_pStream);
		AfxThrowFileException(CFileException::genericException, _doserrno, m_strFileName);
	}

if(m_IsUnicodeFile)
{
if(lpsz)
if(lpsz[lstrlen(lpsz)-1]=='\r')
{
lpsz[lstrlen(lpsz)-1]=0;
}

}
	return lpszResult;
}

void CReadAUStdioFile::checkspecialchar()
{
	if(m_IsAlreadyWrite==false&&bSaveByUnicode)
	{
m_IsAlreadyWrite=true;
ULONG ll=GetLength();
if(ll==0)
{
	SeekToBegin();
	CFile::Write("\377\376",2);
}
	}
}
void CReadAUStdioFile::WriteString(const WCHAR * lpsz)
{
checkspecialchar();
if(bSaveByUnicode)
{
	Write(lpsz,lstrlen(lpsz)*sizeof(TCHAR));
}
else
{
CStringA astr=(CStringA)lpsz;
Write(astr,strlen(astr)*sizeof(char));
}


}

void CReadAUStdioFile::WriteString(const char * lpsz)
{
checkspecialchar();
if(bSaveByUnicode)
{
	CStringW wstr=(CStringW)lpsz;
Write(wstr,lstrlen(wstr)*sizeof(TCHAR));
}
else
Write(lpsz,strlen(lpsz)*sizeof(char));

}

void CReadAUStdioFile::Write(const void* lpBuf, UINT nCount)
{
checkspecialchar();
CStdioFile::Write(lpBuf,nCount);
}
BOOL CReadAUStdioFile::ReadString(CString &rString)
{


ASSERT_VALID(this);

	rString = _T("");    // empty string without deallocating
	const int nMaxSize = 512;
	LPTSTR lpsz = rString.GetBuffer(nMaxSize);
	LPTSTR lpszResult;
	char *pszresult;
	int nLen = 0;
	for (;;)
	{

		if(m_IsUnicodeFile)
		lpszResult = _fgetts(lpsz, nMaxSize+1, m_pStream);
		else
		{
			
					char *lpsz2=new char[nMaxSize+1];
			//lpsz=NULL;
		pszresult = fgets(lpsz2, nMaxSize+1, m_pStream);
		lpszResult=(TCHAR*)pszresult;
		if(lpszResult)
		{
		int dlen=MultiByteToWideChar(CP_ACP,0,lpsz2,-1,NULL,0);
			MultiByteToWideChar(CP_ACP,0,lpsz2,-1,lpsz,dlen);
		}
		else
		{
			lpsz=_T(""); 
		}
		
		
		delete []lpsz2;
		}
	
		rString.ReleaseBuffer();

		// handle error/eof case
		if (lpszResult == NULL && !feof(m_pStream))
		{
			Afx_clearerr_s(m_pStream);
			AfxThrowFileException(CFileException::genericException, _doserrno,
				m_strFileName);
		}

		// if string is read completely or EOF
		if (lpszResult == NULL ||
			(nLen = (int)lstrlen(lpsz)) < nMaxSize ||
			lpsz[nLen-1] == '\n')
			break;
		
		nLen = rString.GetLength();
		lpsz = rString.GetBuffer(nMaxSize + nLen) + nLen;

	}

	// remove '\n' from end of string if present
	lpsz = rString.GetBuffer(0);
	nLen = rString.GetLength();
	if (nLen != 0 && lpsz[nLen-1] == '\n')
		rString.GetBufferSetLength(nLen-1);

if(m_IsUnicodeFile)
{rString.TrimRight('\r');}
	return nLen != 0;


}

