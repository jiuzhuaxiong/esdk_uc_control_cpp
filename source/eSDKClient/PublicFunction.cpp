#include "StdAfx.h"
#include "PublicFunction.h"

CPublicFunction::CPublicFunction(void)
{
}

CPublicFunction::~CPublicFunction(void)
{
}
CString CPublicFunction::UTF2UNICODE(const std::string str)
{
  //确定转换为Unicode需要多少缓冲区(返回值也包含了最后一个NULL字符)。
  int nLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
  wchar_t *pUnicode =  new  wchar_t[nLen+1];  
  memset(pUnicode,0,(nLen+1)*sizeof(wchar_t));  
  ::MultiByteToWideChar( CP_ACP,0,str.c_str(),-1,(LPWSTR)pUnicode,nLen );  
  std::wstring  rt;  
  rt = ( wchar_t* )pUnicode;
  CString cstr = rt.c_str();
  delete  pUnicode; 
  return cstr;
}
std::string CPublicFunction::UNICODE2UTF(const CString cstr)
{
  char*     pElementText;
  int    iTextLen;
  std::wstring wstr = cstr;
  // wide char to multi char
  iTextLen = WideCharToMultiByte( CP_ACP,
    0,
    wstr.c_str(),
    -1,
    NULL,
    0,
    NULL,
    NULL );
  pElementText = new char[iTextLen + 1];
  memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
  ::WideCharToMultiByte( CP_ACP,
    0,
    wstr.c_str(),
    -1,
    pElementText,
    iTextLen,
    NULL,
    NULL );
  std::string strText;
  strText = pElementText;
  delete[] pElementText;
  return strText;



}
