#include "StdAfx.h"
#include "SDKButton.h"
#include "ESdkDialCtrl.h"
#include "resource.h"
#include "PublicFunction.h"
#include "Logger.h"
using namespace eSDK;


// 拨号盘控件
CESdkDialPadCtrl::CESdkDialPadCtrl()
{
#ifdef _DEBUG
    CLogger::SetLevel(CLogger::LEVEL_DEBUG,true);
#else
    CLogger::SetLevel(CLogger::LEVEL_INFO,true);
#endif
}
CESdkDialPadCtrl::~CESdkDialPadCtrl(void)
{
}
void CESdkDialPadCtrl::OnClick()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CLogger::Debug(_T("%s"),_T("CESdkDialPadCtrl::OnClick()"));
    // 获取光标位置
    CPoint pmenu;
    // 获取光标的屏幕坐标，存放在pmenu中
    ::GetCursorPos(&pmenu);

    // 使用独立线程来调用com组件
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
        COINIT_DISABLE_OLE1DDE);

    // 智能指针
    CComPtr<eSpace::IECSEspaceApp>  m_eSpaceApp;

    // 初始化指针，两种方法
    //m_EspaceApp.CoCreateInstance(__uuidof(eSpace::ECSExternService),NULL, CLSCTX_ALL);
    CLSID clsid;	// 类标识符
    CLSIDFromProgID(OLESTR("eSpace.ECSEspaceApp.1"),&clsid);	// 由程序标识符获取对应的类标识符
    m_eSpaceApp.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

    if(m_eSpaceApp)
    {
        eSpace::IECSEspaceApp * pEntity=NULL;
        //查询接口
        HRESULT hr = m_eSpaceApp->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
        if(SUCCEEDED(hr))
        { 
            //eSpace::IECSMainWindow*	pMainWindow;
            CComPtr<eSpace::IECSMainWindow> pMainWindow;
            pMainWindow = pEntity->GetMainWindow();

            if(pMainWindow)//获取主窗口成功
            {
                // 1.调出拨号盘
                HRESULT hr = pMainWindow->ShowDialPad(pmenu.x, pmenu.y);
            }
            else//获取主窗口失败
            {
                CLogger::Error(_T("%s"),_T("CESdkDialPadCtrl::OnClick() get main window failed"));
            }
        }
        else
        {
            CLogger::Error(_T("%s"),_T("CESdkDialPadCtrl::OnClick() get espace app com interface failed"));
        }
    }

    CoUninitialize();
}

// 点击呼叫控件
CESdkDialingCtrl::CESdkDialingCtrl()
{
#ifdef _DEBUG
    CLogger::SetLevel(CLogger::LEVEL_DEBUG,true);
#else
    CLogger::SetLevel(CLogger::LEVEL_INFO,true);
#endif
}
CESdkDialingCtrl::~CESdkDialingCtrl(void)
{
}
bool CESdkDialingCtrl::SetDialTarget(std::string strUri, std::string strPhone)
{
    CLogger::Debug(_T("%s"),_T("CESdkDialingCtrl::SetDialTarget"));
    m_strUri			=	strUri;
    m_strPhone	=	strPhone;
    return	true;
}
void CESdkDialingCtrl::OnClick()
{
    CLogger::Debug(_T("%s"),_T("CESdkDialingCtrl::OnClick"));
    // 使用独立线程来调用com组件
    CoInitialize(NULL);

    // 智能指针
    CComPtr<eSpace::IECSEspaceApp>  m_eSpaceApp;

    // 初始化指针，两种方法
    //m_Espace.CoCreateInstance(__uuidof(eSpace::ECSExternService),NULL, CLSCTX_ALL);
    CLSID clsid;	// 类标识符
    CLSIDFromProgID(OLESTR("eSpace.ECSEspaceApp.1"),&clsid);	// 由程序标识符获取对应的类标识符
    m_eSpaceApp.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

    if(m_eSpaceApp)
    {
        eSpace::IECSEspaceApp * pEntity=NULL;
        //查询接口
        HRESULT hr = m_eSpaceApp->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
        if(SUCCEEDED(hr))
        { 
            CComPtr<eSpace::IECSMainWindow>	pMainWindow;
            pMainWindow = pEntity->GetMainWindow();
            if(pMainWindow)//获取主窗口成功
            {
                // 2.直接拨号
                pMainWindow->MakeCall(m_strUri.c_str(), m_strPhone.c_str());
            }
            else//获取主窗口失败
            {
                CLogger::Error(_T("%s"),_T("CESdkDialingCtrl::OnClick() get main window failed"));
            }
        }
    }
    else
    {
        CLogger::Error(_T("%s"),_T("CESdkDialingCtrl::OnClick() get espace app com interface failed"));
    }

    CoUninitialize();
}


// 视频呼叫控件
CESdkVideoCallCtrl::CESdkVideoCallCtrl()
{
#ifdef _DEBUG
	CLogger::SetLevel(CLogger::LEVEL_DEBUG,true);
#else
	CLogger::SetLevel(CLogger::LEVEL_INFO,true);
#endif
}
CESdkVideoCallCtrl::~CESdkVideoCallCtrl(void)
{
}
bool CESdkVideoCallCtrl::SetDialTarget(std::string strUri, std::string strPhone)
{
	CLogger::Debug(_T("%s"),_T("CESdkVideoCallCtrl::SetDialTarget"));
	m_strUri			=	strUri;
	m_strPhone	=	strPhone;
	return	true;
}
void CESdkVideoCallCtrl::OnClick()
{
	CLogger::Debug(_T("%s"),_T("CESdkVideoCallCtrl::OnClick"));
	// 使用独立线程来调用com组件
	CoInitialize(NULL);

	// 智能指针
	CComPtr<eSpace::IECSEspaceApp>  m_eSpaceApp;

	// 类标识符
	CLSID clsid;	

	// 由程序标识符获取对应的类标识符
	CLSIDFromProgID(OLESTR("eSpace.ECSEspaceApp.1"),&clsid);	
	m_eSpaceApp.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

	if(m_eSpaceApp)
	{
		eSpace::IECSEspaceApp * pEntity=NULL;
		//查询接口
		HRESULT hr = m_eSpaceApp->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
		if(SUCCEEDED(hr))
		{ 
			CComPtr<eSpace::IECSMainWindow>	pMainWindow;
			pMainWindow = pEntity->GetMainWindow();
			//获取主窗口成功
			if(pMainWindow)
			{
				// 2.直接拨号
				pMainWindow->MakeVideoCall(m_strUri.c_str(), m_strPhone.c_str());
			}
			//获取主窗口失败
			else
			{
				CLogger::Error(_T("%s"),_T("CESdkVideoCallCtrl::OnClick() get main window failed"));
			}
		}
	}
	else
	{
		CLogger::Error(_T("%s"),_T("CESdkVideoCallCtrl::OnClick() get espace app com interface failed"));
	}

	CoUninitialize();
}

// 选择呼叫控件
CESdkChooseToDialCtrl::CESdkChooseToDialCtrl()
{
#ifdef _DEBUG
    CLogger::SetLevel(CLogger::LEVEL_DEBUG,true);
#else
    CLogger::SetLevel(CLogger::LEVEL_INFO,true);
#endif
}

CESdkChooseToDialCtrl::~CESdkChooseToDialCtrl(void)
{

}

//设置呼叫对象的帐号
bool CESdkChooseToDialCtrl::SetDialTarget(std::string strAccount)
{
    CLogger::Debug(_T("%s"),_T("CESdkChooseToDialCtrl::SetDialTarget"));
    m_strAccount	=	strAccount;
    return	true;
}

void CESdkChooseToDialCtrl::OnClick()
{
    CLogger::Debug(_T("%s"),_T("CESdkChooseToDialCtrl::OnClick"));
    if (m_strAccount.empty())
    {
        //没有呼叫对象，退出呼叫
        CLogger::Warn(_T("%s"),_T("CESdkChooseToDialCtrl::OnClick() uc account is empty"));
        return;
    }

    // 使用独立线程来调用com组件
    CoInitialize(NULL);

    // 智能指针
    CComPtr<eSpace::IECSEspaceApp>	m_eSpaceApp;

	// 类标识符
    CLSID	clsidApp;	

	// 由程序标识符获取对应的类标识符
    CLSIDFromProgID(OLESTR("eSpace.ECSeSpaceApp.1"),&clsidApp);
    m_eSpaceApp.CoCreateInstance(clsidApp,NULL, CLSCTX_ALL);

    if(m_eSpaceApp)
    {
        eSpace::IECSEspaceApp * pEntity=NULL;
        //查询接口
        HRESULT hr = m_eSpaceApp->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
        if(SUCCEEDED(hr))
        { 
            // 3.选择呼叫
            // 3.0.获取光标位置
            CPoint pmenu;
            // 获取光标的屏幕坐标，存放在pmenu中
            ::GetCursorPos(&pmenu);

            // 3.1.获取联系人电话
            BSTR	bstrAccount	=	SysAllocString(CA2W (m_strAccount.c_str ()));
            BSTR	bstrUri	=	 SysAllocString (CA2W (m_strUri.c_str ()));
            CComPtr<eSpace::IECSContactInfo> pContactInfo;
            //eSpace::IECSContactMgr*	pContactMgr;
            CComPtr<eSpace::IECSContactMgr> pContactMgr;
            pContactMgr = pEntity->GetContactMgr();
            if(pContactMgr)//获取联系人管理器成功
            {
                pContactInfo = pContactMgr->GetContactInfo(bstrAccount);

                if(pContactInfo)//获取联系人信息成功
                {
                    m_strUri						=	pContactInfo->GetUcUri();
                    m_strAccount			=	pContactInfo->GetUcAccount();
                    m_strHomePhone	=	pContactInfo->GetHomePhone();
                    m_strOfficePhone	=	pContactInfo->GetOfficePhone();
                    m_strMobile				=	pContactInfo->GetMobile();
                    m_strOtherPhone	=	pContactInfo->GetOtherPhone();

                    // 3.2.创建menu
                    CMenu phoneMenu;
                    phoneMenu.CreatePopupMenu();
                    int iMenuNo = 0;
                    // 在该菜单中添加URI选项
                    phoneMenu.AppendMenu(MF_STRING, ID_DIAL_URI, CPublicFunction::UTF2UNICODE(m_strAccount));
                    // 在该菜单中添加电话选项
                    if (!m_strHomePhone.empty())
                    {
                        phoneMenu.AppendMenu(MF_STRING, ID_DIAL_HOME_PHONE, CPublicFunction::UTF2UNICODE(m_strHomePhone));
                        iMenuNo++;
                    }
                    if (!m_strOfficePhone.empty())
                    {
                        phoneMenu.AppendMenu(MF_STRING, ID_DIAL_OFFICE_PHONE, CPublicFunction::UTF2UNICODE(m_strOfficePhone));
                        iMenuNo++;
                    }
                    if (!m_strMobile.empty())
                    {
                        phoneMenu.AppendMenu(MF_STRING, ID_DIAL_MOBILE, CPublicFunction::UTF2UNICODE(m_strMobile));
                        iMenuNo++;
                    }
                    if (!m_strOtherPhone.empty())
                    {
                        phoneMenu.AppendMenu(MF_STRING, ID_DIAL_OTHER_PHONE, CPublicFunction::UTF2UNICODE(m_strOtherPhone));
                        iMenuNo++;
                    }
                    if (0  == iMenuNo)
                    {
                        // 没有任何电话，任然弹出菜单，但内容为空
                        phoneMenu.AppendMenu(MF_STRING, ID_DIAL_NO_PHONE, _T(""));
                    }
                    // 在屏幕上pmenu所指的位置显示菜单
                    phoneMenu.TrackPopupMenu(TPM_LEFTBUTTON, pmenu.x, pmenu.y, &button_);

                    // 3.3.释放资源
                    ::SysFreeString(bstrAccount);
                    ::SysFreeString(bstrUri);
                }
                else//获取联系人信息失败
                {
                    CLogger::Error(_T("%s"),_T("CESdkChooseToDialCtrl::OnClick() get contact info failed"));
                }

            }
            else//获取联系人管理器失败
            {
                CLogger::Error(_T("%s"),_T("CESdkChooseToDialCtrl::OnClick() get contact manager failed"));
            }
        }
    }

    CoUninitialize();
}

// 点击菜单响应函数
void CESdkChooseToDialCtrl::OnClickMenu(UINT uID)
{

    CLogger::Debug(_T("%s"),_T("CESdkChooseToDialCtrl::OnClickMenu"));
    std::string	strUri;
    std::string	strPhoneNo;
    strUri.clear();
    strPhoneNo.clear();

    // 获取电话号码
    switch (uID)
    {
    case ID_DIAL_URI:
        strUri	=	m_strUri;
        break;
    case ID_DIAL_HOME_PHONE:
        strPhoneNo	= m_strHomePhone;
        break;
    case ID_DIAL_OFFICE_PHONE:
        strPhoneNo	= m_strOfficePhone;
        break;
    case ID_DIAL_MOBILE:
        strPhoneNo	= m_strMobile;
        break;
    case ID_DIAL_OTHER_PHONE:
        strPhoneNo	= m_strOtherPhone;
        break;
    default:
        // 没有电话号码，返回
        return;
    }

    // 将电话号码转换格式
    BSTR	bstrUri	= SysAllocString (CA2W (strUri.c_str ()));
    BSTR	bstrPhoneNo	= SysAllocString (CA2W (strPhoneNo.c_str ()));

    // 使用独立线程来调用com组件
    CoInitialize(NULL);

    // 智能指针
    CComPtr<eSpace::IECSEspaceApp>  m_EspaceApp;

    // 初始化指针
    m_EspaceApp.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp),NULL, CLSCTX_ALL);

    if(m_EspaceApp)
    {
        // 直接拨号
        //eSpace::IECSMainWindow*	pMainWindow;
        CComPtr<eSpace::IECSMainWindow> pMainWindow;
        pMainWindow = m_EspaceApp->GetMainWindow();
        if(pMainWindow)
        {
            // 2.直接拨号
            CLogger::Info(_T("%s"),_T("CESdkChooseToDialCtrl::OnClickMenu() start to make call"));
            pMainWindow->MakeCall(bstrUri, bstrPhoneNo);
        }
        else
        {
            CLogger::Error(_T("%s"),_T("CESdkChooseToDialCtrl::OnClickMenu() get mainWindow failed"));
        }

    }
    else
    {
         CLogger::Error(_T("%s"),_T("CESdkChooseToDialCtrl::OnClickMenu() com init failed"));
    }

    // 释放资源
    SysFreeString(bstrUri);
    SysFreeString(bstrPhoneNo);

    CoUninitialize();
}


// 调用COM接口的接口
long ShowDialPad(void)
{
    TRACE(_T("ShowDialPad()\n"));
    CLogger::Debug(_T("%s"),_T("ShowDialPad"));
    //// 使用独立线程来调用com组件
    //CoInitialize(NULL);

    //// 智能指针
    //CComPtr<eSpace::IECSExternService>  m_Espace;

    //// 初始化指针，两种方法
    ////m_Espace.CoCreateInstance(__uuidof(eSpace::ECSExternService),NULL, CLSCTX_ALL);
    //CLSID clsid;	// 类标识符
    //CLSIDFromProgID(OLESTR("eSpace.ECSExternService.1"),&clsid);	// 由程序标识符获取对应的类标识符
    //m_Espace.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

    //if(m_Espace)
    //{
    //	// 1.调出拨号盘
    //	m_Espace->ShowDialPad();	
    //}

    //CoUninitialize();

    return SDK_SUCCESS;
}

long StartDialing(void)
{
    TRACE(_T("StartDialing()\n"));
    CLogger::Debug(_T("%s"),_T("StartDialing"));
    //// 使用独立线程来调用com组件
    //CoInitialize(NULL);

    //// 智能指针
    //CComPtr<eSpace::IECSExternService>  m_Espace;

    //// 初始化指针，两种方法
    ////m_Espace.CoCreateInstance(__uuidof(eSpace::ECSExternService),NULL, CLSCTX_ALL);
    //CLSID clsid;	// 类标识符
    //CLSIDFromProgID(OLESTR("eSpace.ECSExternService.1"),&clsid);	// 由程序标识符获取对应的类标识符
    //m_Espace.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

    //if(m_Espace)
    //{
    //	// 2.直接拨号
    //	m_Espace->StartDialing("71010", "", "71010");	
    //}

    //CoUninitialize();

    return SDK_SUCCESS;
}

long QueryContactPhoneNo(std::string strUri, std::string* pstrHomePhone, std::string* pstrOfficePhone, std::string* pstrMobile, std::string* pstrOtherPhone)
{
    TRACE(_T("QueryContactPhoneNo()\n"));
    CLogger::Debug(_T("%s"),_T("QueryContactPhoneNo"));
    //
    //// 使用独立线程来调用com组件
    //CoInitialize(NULL);

    //// 智能指针
    //CComPtr<eSpace::IECSExternService>  m_Espace;

    //// 初始化指针，两种方法
    ////m_Espace.CoCreateInstance(__uuidof(eSpace::ECSExternService),NULL, CLSCTX_ALL);
    //CLSID clsid;	// 类标识符
    //CLSIDFromProgID(OLESTR("eSpace.ECSExternService.1"),&clsid);	// 由程序标识符获取对应的类标识符
    //m_Espace.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

    //if(m_Espace)
    //{
    //	// 转换呼叫对象的Uri
    //	BSTR	bstrUri	=	 SysAllocString (CA2W (strUri.c_str ()));
    //	// 电话号码传递容器，先初始化为temp值
    //	BSTR	bstrHomePhone	= ::SysAllocString(L"temp");
    //	BSTR	bstrOfficePhone	= ::SysAllocString(L"temp");
    //	BSTR	bstrMobile			= ::SysAllocString(L"temp");
    //	BSTR	bstrOtherPhone	= ::SysAllocString(L"temp");
    //	//BSTR	bstrPhoneNo[4];
    //	// 获取联系人的4个电话号码，并保存在成员变量中
    //	m_Espace->QueryContactPhoneNo(bstrUri, 
    //		&bstrHomePhone, 
    //		&bstrOfficePhone, 
    //		&bstrMobile, 
    //		&bstrOtherPhone);
    //	//button_.m_vecPhoneNo.push_back(std::string(_com_util::ConvertBSTRToString(bstrHomePhone)));
    //	//button_.m_vecPhoneNo.push_back(std::string(_com_util::ConvertBSTRToString(bstrOfficePhone)));
    //	//button_.m_vecPhoneNo.push_back(std::string(_com_util::ConvertBSTRToString(bstrMobile)));
    //	//button_.m_vecPhoneNo.push_back(std::string(_com_util::ConvertBSTRToString(bstrOtherPhone)));

    //	_bstr_t	bstr_t1(bstrHomePhone);
    //	*pstrHomePhone	= bstr_t1;
    //	_bstr_t	bstr_t2(bstrOfficePhone);
    //	*pstrOfficePhone	= bstr_t2;
    //	_bstr_t	bstr_t3(bstrMobile);
    //	*pstrMobile			= bstr_t3;
    //	_bstr_t	bstr_t4(bstrOtherPhone);
    //	*pstrOtherPhone	= bstr_t4;

    //	// 3.3.释放资源
    //	::SysFreeString(bstrUri);
    //	::SysFreeString(bstrHomePhone);
    //	::SysFreeString(bstrOfficePhone);
    //	::SysFreeString(bstrMobile);
    //	::SysFreeString(bstrOtherPhone);
    //}

    //CoUninitialize();

    return SDK_SUCCESS;
}
