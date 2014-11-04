#include "StdAfx.h"
#include "ESdkCtrl.h"
#include "PublicFunction.h"
#include "resource.h"
#include "Language.h"
CESdkCtrl::CESdkCtrl(void)
{
}

CESdkCtrl::~CESdkCtrl(void)
{
}

long CESdkCtrl::CreateCtrl(CWnd *wnd,SDK_CTRL_TYPE emtype)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    emtype_ = emtype;

    //<1>创建初始大小按钮 ,加载图标  

    CString strTitle = _T("eSDKCtrl");

    CRect crt(0,0,150,40);//默认控件按钮的大小
    button_.Create(strTitle,WS_VISIBLE,crt,wnd,ID_BUTTON);
    button_.SetOwner(this);

    //<2>切换按钮的风格为windows7风格
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows)); 
    CMFCButton::EnableWindowsTheming();

    if(!IsEspaceInstalled())
    {
        button_.EnableWindow(FALSE);
    }

    return SDK_SUCCESS;
}
long CESdkCtrl::ShowCtrl(SDK_CTRL_SHOW_TYPE emShowType)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    switch (emShowType)
    {
    case SHOW_NODISPLAY://隐藏
        {
            button_.ShowWindow(SW_HIDE);
            break;
        }
    case SHOW_ICON_TEXT_LEFT:
        {
            button_.SetImagePosRight(0);//0表示文字在右，图片在左
            button_.ShowWindow(SW_SHOW);
            break;
        }
    case SHOW_ICON_TEXT_UP:
        {
            button_.SetImagePosRight(3);//3表示图片在上，文字在下
            button_.ShowWindow(SW_SHOW);
            break;
        }
    default:
        break;

    }

    return SDK_SUCCESS;
}
long CESdkCtrl::SetIcon(std::string strPath)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if(("") == strPath)
    {
        return SDK_INVAD_PARA;
    }
    CString cstrPath = CPublicFunction::UTF2UNICODE(strPath);
    if(button_.SetImagePath(cstrPath))
    {
        return SDK_SUCCESS;
    }
    else
    {
        return SDK_ERROR;
    }

}
long CESdkCtrl::SetSize(int x,int y,int cx,int cy)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if( x <0 || y<0 || cx<=0 || cy<=0)
    {
        return SDK_INVAD_PARA;
    }
    button_.SetWindowPos(NULL,x,y,cx,cy,SWP_NOZORDER|SWP_SHOWWINDOW);
    return SDK_SUCCESS;
}
long CESdkCtrl::SetTitle(std::string strShowContent)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // 限制字数
    if(BN_TITLE_SIZE_MAX < strShowContent.size())
    {
        return SDK_INVAD_PARA;
    }

    CString cstrContent = CPublicFunction::UTF2UNICODE(strShowContent);
    button_.SetWindowText(cstrContent);
    return SDK_SUCCESS;

}
long CESdkCtrl::SetTip(std::string strTip)
{
    // 限制字数
    if(BN_TIPS_SIZE_MAX < strTip.size())
    {
        return SDK_INVAD_PARA;
    }

    CString cstrTip = CPublicFunction::UTF2UNICODE(strTip);
    button_.SetTooltip(cstrTip);

    return SDK_SUCCESS;

}
void CESdkCtrl::OnClickMenu(UINT uID)
{
    //this->button_.OnClickMenu(uID);
}

//控件双击事件
void CESdkCtrl::OnDbClick()
{
	//AfxMessageBox(_T("db "));
}

void CESdkCtrl::ImageFromIDResource(CImage& image, UINT nID, LPCTSTR lpType)  
{  
    AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

    HINSTANCE hInst = AfxGetResourceHandle(); // GetModuleHandle(NULL);
    HRSRC hRsrc = ::FindResource (hInst,MAKEINTRESOURCE(nID),lpType);   
    if(hRsrc == NULL)  
        return;  
    DWORD dwLen = SizeofResource(hInst, hRsrc);  
    BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);  
    if (!lpRsrc)  
        return;;  
    HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, dwLen);  
    BYTE* pmem = (BYTE*)GlobalLock(m_hMem);  
    memcpy(pmem,lpRsrc,dwLen);  
    IStream* pstm = NULL;  
    CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);  
    image.Load(pstm);  
    GlobalUnlock(m_hMem);  
    pstm->Release();  
    FreeResource(lpRsrc);  
}

long CESdkCtrl::ChangeSize(int width,int height)
{

    AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
    if(width<=0||height<=0)
    {
        return SDK_INVAD_PARA;
    }
    CRect   rect; 
    this->button_.GetWindowRect(&rect);
    CPoint leftPos = rect.TopLeft();
    ::ScreenToClient(button_.GetParent()->GetSafeHwnd(), &leftPos);
    this->button_.MoveWindow(leftPos.x,leftPos.y,width,height);
    return SDK_SUCCESS;

}
long CESdkCtrl::ChangePosition(int xPos,int yPos)
{

    AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
    if (xPos<0||yPos<0)
    {
        return SDK_INVAD_PARA;
    }
    CRect   rect; 
    this->button_.GetClientRect(&rect);
    this->button_.MoveWindow(xPos,yPos,rect.Width(),rect.Height());
    return SDK_SUCCESS;

}

BOOL CESdkCtrl::IsEspaceInstalled()
{  
    CLSID	IID_Espace = __uuidof(eSpace::ECSEspaceApp);	// 类标识符
    LPOLESTR sIID_Espace = NULL; 
    ::StringFromCLSID(IID_Espace, &sIID_Espace); 

    CString keyString;
    keyString.Format( _T("CLSID\\%s\\LocalServer32"), sIID_Espace);
    ::CoTaskMemFree(sIID_Espace);

    HKEY hKey  =  NULL;  
    BOOL bPresent  =  FALSE;  
    ::RegOpenKey(HKEY_CLASSES_ROOT,  keyString.GetBuffer(0),  &hKey);  
    if(hKey)    
    {  
        HANDLE	hfile;  
        TCHAR	szPath[_MAX_PATH];  
        DWORD	dwRegType;  
        DWORD	cbData  =  sizeof  szPath  *  sizeof  TCHAR;  

        TCHAR * path = NULL;

        szPath[0]  =  0;  
        ::RegQueryValueEx(hKey,  NULL,  NULL,  &dwRegType,  (LPBYTE)szPath,  &cbData);  
        ::RegCloseKey(hKey);  

        path = szPath;

        int len = _tcslen(szPath);
        if(len > 2)
        {
            TCHAR first = szPath[0];
            TCHAR last = szPath[len-1];
            //去除多余的引号
            if(first == L'"' && last== L'"')
            {
                szPath[len-1] = L'\0';
                path += 1;
            }

            hfile  =  ::CreateFile(path,  0,  FILE_SHARE_READ ,  NULL,  OPEN_EXISTING,  0,  NULL);  
            if(INVALID_HANDLE_VALUE  !=  hfile)  
            {  
                bPresent  =  TRUE;  
                ::CloseHandle(hfile);  
            } 
            //else
            //{
            //    CString   str; 
            //    int   err   =   GetLastError();	
            //    str.Format(_T("创建临时文件失败,%d "),err); 
            //    AfxMessageBox(str); 
            //}
        }

        
    }  

    return  bPresent;  
}  


void CESdkCtrl::SetLangID(LANGID langId)//设置控件上显示的语言
{
	this->m_langID=langId;
	eSDK::CLanguage::GetInstance()->LoadLanguage(langId);
}
LANGID CESdkCtrl::GetLangID()//获取控件上要显示的语言类型
{
	return this->m_langID;
}