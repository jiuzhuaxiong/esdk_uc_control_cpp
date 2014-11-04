#include "StdAfx.h"
#include "SDKButton.h"
#include "ESdkIMCtrl.h"
#include "resource.h"
#include "Language.h"
#include "PublicFunction.h"
#include "Logger.h"
using namespace eSDK;

CESdkIMCtrl::CESdkIMCtrl()
{
#ifdef _DEBUG
    CLogger::SetLevel(CLogger::LEVEL_DEBUG,true);
#else
    CLogger::SetLevel(CLogger::LEVEL_INFO,true);
#endif
}
CESdkIMCtrl::~CESdkIMCtrl(void)
{
}

long CESdkIMCtrl::CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType)//控件创建完，赋给父窗口
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CLogger::Debug(_T("%s"),_T("CESdkIMCtrl::CreateCtrl"));
    emtype_ = emCtrlType;

    //<1>创建初始大小按钮 ,加载图标  
    CString strTitle = _T("发送即时消息");

    CRect crt(0,0,100,40);//默认控件按钮的大小
    button_.Create(strTitle,WS_VISIBLE,crt,wnd, ID_BUTTON);
    button_.SetImage(IDB_PNG_IM);
    button_.SetOwner(this);

    //<2>切换按钮的风格为windows7风格
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows)); 
    CMFCButton::EnableWindowsTheming();

    if(!IsEspaceInstalled())
    {
        CLogger::Warn(_T("%s"),_T("espace not installed"));
        button_.EnableWindow(FALSE);
    }

    return SDK_SUCCESS;

}
void CESdkIMCtrl::OnClick()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    //AfxMessageBox(_T("发起会议"));
    CLogger::Debug(_T("%s"),_T("start meeting"));
    if(!ucAccount_.empty())
    {
        long result = StartIMConversation(ucAccount_);

		if(result == SDK_ERROR)
		{
			CString errorInfo = eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_IM_CALL_FAIL));
			AfxMessageBox(errorInfo.GetBuffer());
		}

		
    }
}


long CESdkIMCtrl::SetUCAccount(std::string ucAcc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CLogger::Debug(_T("%s"),_T("SetUCAccount"));
    this->ucAccount_ = ucAcc;
    return SDK_SUCCESS;
}

void CESdkIMCtrl::SetLangID(LANGID langId)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CLogger::Debug(_T("%s"),_T("SetLangID"));
    CESdkCtrl::SetLangID(langId);

	CString imText = eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_IM_CALL));

	string text = CPublicFunction::UNICODE2UTF(imText);
	SetTip(text);
	SetTitle(text);
}


long ESDK_API StartIMConversation(std::string ucAcc)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CLogger::Debug(_T("%s"),_T("StartIMConversation"));
    long result = SDK_ERROR;
    
    TRACE(_T("StartIMConversation()\n"));
    //后续在此添加“调用群聊的接口”
    CComPtr<eSpace::IECSEspaceApp>  m_Espace;

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
        COINIT_DISABLE_OLE1DDE);

    if (SUCCEEDED(hr))
    {
        HRESULT hr = m_Espace.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp),NULL, CLSCTX_ALL);

        if(SUCCEEDED(hr) && m_Espace)
        {
            //AfxMessageBox(_T("CoCreateInstance OK"));
            eSpace::IECSEspaceApp * pEntity=NULL;
            //查询接口
            hr = m_Espace->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
            if(pEntity)
            { 

                //eSpace::IECSMainWindow * pMainWiondow = NULL;
				CComPtr<eSpace::IECSMainWindow> pMainWiondow ;
				pMainWiondow = pEntity->GetMainWindow();
                if(pMainWiondow)
                {
                    try
                    {
                        hr = pMainWiondow->ShowIMChat(_bstr_t(ucAcc.c_str()));
                        if(SUCCEEDED(hr))
                        {
                            result = SDK_SUCCESS;
                        }

                    }
                    catch (_com_error e)
                    {
                        CLogger::Error(_T("%s"),e.ErrorMessage());
                        result = SDK_ERROR;
                    }

                }
            }
        }
    }

    CoUninitialize();

    return result;
}



/***add by h00169570***/
CESdkSMSCtrl::CESdkSMSCtrl()
{
#ifdef _DEBUG
	CLogger::SetLevel(CLogger::LEVEL_DEBUG,true);
#else
	CLogger::SetLevel(CLogger::LEVEL_INFO,true);
#endif
}
CESdkSMSCtrl::~CESdkSMSCtrl(void)
{
}

long CESdkSMSCtrl::CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType)//控件创建完，赋给父窗口
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CLogger::Debug(_T("%s"),_T("CESdkSMSCtrl::CreateCtrl"));
	emtype_ = emCtrlType;

	//<1>创建初始大小按钮 ,加载图标  
	CString strTitle = _T("发送短信");
	CRect crt(0,50,100,90);//默认控件按钮的大小
	button_.Create(strTitle,WS_VISIBLE,crt,wnd, ID_BUTTON);
	button_.SetImage(IDB_PNG_IM);
	button_.SetOwner(this);

	//<2>切换按钮的风格为windows7风格
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows)); 
	CMFCButton::EnableWindowsTheming();

	if(!IsEspaceInstalled())
	{
		CLogger::Warn(_T("%s"),_T("espace not installed"));
		button_.EnableWindow(FALSE);
	}

	return SDK_SUCCESS;

}
void CESdkSMSCtrl::OnClick()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CLogger::Debug(_T("%s"),_T("send sms"));
	
	//调用发送短信COM接口,m_ucAcc为UC账号数组，m_groupno为群组号
	long result = StartSMSConversation(m_ucAcc,m_groupno);

	if(result == SDK_ERROR)
	{
		CString errorInfo = eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_SMS_CALL_FAIL));
		AfxMessageBox(errorInfo.GetBuffer());
	}

}


long CESdkSMSCtrl::SetUCAccount(std::vector<std::string> ucAcc,std::string groupno)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CLogger::Debug(_T("%s"),_T("SetUCAccount"));
	this->m_ucAcc = ucAcc;
	this->m_groupno = groupno;
	return SDK_SUCCESS;
}

void CESdkSMSCtrl::SetLangID(LANGID langId)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CLogger::Debug(_T("%s"),_T("SetLangID"));
	CESdkCtrl::SetLangID(langId);

	CString imText = eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_SMS_CALL));

	string text = CPublicFunction::UNICODE2UTF(imText);
	SetTip(text);
	SetTitle(text);
}


long ESDK_API StartSMSConversation(std::vector<std::string> ucAcc,std::string Groupno)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	long result = SDK_ERROR;
	CLogger::Debug(_T("%s"),_T("CESdkSMSCtrl::OnClick"));
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
			if(pMainWindow)//获取主窗口成功
			{
				//调用短信鉴权接口
				long lperm = pMainWindow->GetSmsPERM();
				if (0 != lperm)
				{
					try
					{
						//调用发端短信com接口
						if (0 != ucAcc.size())
						{
							SAFEARRAY *psa = SafeArrayCreateVector(
								VT_BSTR,
								0,
								ucAcc.size());

							std::vector<std::string>::iterator ucUriIter = ucAcc.begin();
							for(unsigned int i=0;i< ucAcc.size(),ucUriIter != ucAcc.end();i++)
							{
								BSTR pbstrAcc = _com_util::ConvertStringToBSTR(ucUriIter->c_str());
								SafeArrayPutElement(psa,   (long *)&i,   pbstrAcc); 
								ucUriIter++;
							}

							//调用com接口，给临时群发送
							hr = pMainWindow->ShowSMSChat(psa);
						} 
						else if("" != Groupno)
						{
							//调用com接口，给固定群发送
							hr = pMainWindow->ShowSMSGroupChat(_bstr_t(Groupno.c_str()));
						}
						
						if(SUCCEEDED(hr))
						{
							result = SDK_SUCCESS;
						}

					}
					catch (_com_error e)
					{
						CLogger::Error(_T("%s"),e.ErrorMessage());
						result = SDK_ERROR;
					}
				}
				else
				{
					CString errorInfo = eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_SMSPERM_FAIL));
					AfxMessageBox(errorInfo.GetBuffer());
					result = SDK_SUCCESS;
				}
				
			}
			else//获取主窗口失败
			{
				CLogger::Error(_T("%s"),_T("CESdkSMSCtrl::OnClick() get main window failed"));
			}
		}
	}
	else
	{
		CLogger::Error(_T("%s"),_T("CESdkSMSCtrl::OnClick() get espace app com interface failed"));
	}

	CoUninitialize();
	return result;
}

CESdkPERMCtrl::CESdkPERMCtrl()
{
#ifdef _DEBUG
	CLogger::SetLevel(CLogger::LEVEL_DEBUG,true);
#else
	CLogger::SetLevel(CLogger::LEVEL_INFO,true);
#endif
}

CESdkPERMCtrl::~CESdkPERMCtrl(void)
{

}

long CESdkPERMCtrl::CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType)//控件创建完，赋给父窗口
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CLogger::Debug(_T("%s"),_T("CESdkPERMCtrl::CreateCtrl"));
	emtype_ = emCtrlType;

	//<1>创建初始大小按钮 ,加载图标  
	CString strTitle = _T("发送鉴权");

	//默认控件按钮的大小
	CRect crt(0,50,100,90);
	button_.Create(strTitle,WS_VISIBLE,crt,wnd, ID_BUTTON);
	button_.SetImage(IDB_PNG_IM);
	button_.SetOwner(this);

	//<2>切换按钮的风格为windows7风格
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows)); 
	CMFCButton::EnableWindowsTheming();

	if(!IsEspaceInstalled())
	{
		CLogger::Warn(_T("%s"),_T("espace not installed"));
		button_.EnableWindow(FALSE);
	}

	return SDK_SUCCESS;

}
void CESdkPERMCtrl::OnClick()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CLogger::Debug(_T("%s"),_T("start PERM"));
	
	long result = StartPERM();

	if(result == SDK_ERROR)
	{
		CString errorInfo = eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_SMSPERM_SEND_FAIL));
		AfxMessageBox(errorInfo.GetBuffer());
	}
}

void CESdkPERMCtrl::SetLangID(LANGID langId)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CLogger::Debug(_T("%s"),_T("SetLangID"));
	CESdkCtrl::SetLangID(langId);

	CString imText = eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_SMSPERM_SEND));

	string text = CPublicFunction::UNICODE2UTF(imText);
	SetTip(text);
	SetTitle(text);
}


long ESDK_API StartPERM()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	long result = SDK_ERROR;
	CLogger::Debug(_T("%s"),_T("CESdkPERMCtrl::OnClick"));
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
				long lperm = pMainWindow->GetSmsPERM();
				if (0 == lperm)
				{
					CString errorInfo = eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_SMSPERM_FAIL));
					AfxMessageBox(errorInfo.GetBuffer());
				}
				result = SDK_SUCCESS;
			}
			//获取主窗口失败
			else
			{
				CLogger::Error(_T("%s"),_T("CESdkPERMCtrl::OnClick() get main window failed"));
			}
		}
	}
	else
	{
		CLogger::Error(_T("%s"),_T("CESdkPERMCtrl::OnClick() get espace app com interface failed"));
	}

	CoUninitialize();
	return result;
}
