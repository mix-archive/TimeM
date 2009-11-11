// ReadAUStdioFile.h : 头文件
//

#pragma once


class CReadAUStdioFile : public CStdioFile
{
// 构造
public:	
	virtual ~CReadAUStdioFile();
	CReadAUStdioFile(BOOL IsSaveByUnicode=true);	
	void checkspecialchar();
void WriteString(const WCHAR * lpsz);
void WriteString(const char * lpsz);
void Write(const void* lpBuf, UINT nCount);
virtual	LPTSTR ReadString(__out_ecount(nMax) LPTSTR lpsz, UINT nMax);
virtual BOOL ReadString(CString& rString);	
virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags,CFileException* pError = NULL);
	BOOL bSaveByUnicode;
protected:
	BOOL m_IsUnicodeFile;

private:
	BOOL m_IsAlreadyWrite;
};
