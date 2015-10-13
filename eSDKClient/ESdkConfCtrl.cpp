#include "StdAfx.h"
#include "SDKButton.h"
#include "ESdkConfCtrl.h"
#include "Resource.h"
#include "Logger.h"
using namespace eSDK;

CESdkConfCtrl::CESdkConfCtrl()
{
#ifdef _DEBUG
    CLogger::SetLevel(CLogger::LEVEL_DEBUG,true);
#else
    CLogger::SetLevel(CLogger::LEVEL_INFO,true);
#endif
}
CESdkConfCtrl::~CESdkConfCtrl(void)
{
}


void CESdkConfCtrl::OnClick()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
  CLogger::Debug(_T("%s"),_T("CESdkConfCtrl::OnClick()"));
  CLogger::Info(_T("%s"),_T("clicked Conf Ctrl"));
	// 使用独立线程来调用com组件
	CoInitialize(NULL);
	// 智能指针
	CComPtr<eSpace::IECSEspaceApp>  m_EspaceApp;

	// 初始化指针，两种方法
	CLSID clsid;	// 类标识符
	CLSIDFromProgID(OLESTR("eSpace.ECSEspaceApp.1"),&clsid);	// 由程序标识符获取对应的类标识符
	m_EspaceApp.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

	if(m_EspaceApp)
	{
		eSpace::IECSEspaceApp * pEntity=NULL;
		//查询接口
		HRESULT hr = m_EspaceApp->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
		if(SUCCEEDED(hr))
		{ 
			//eSpace::IECSMainWindow*	pMainWindow;
			CComPtr<eSpace::IECSMainWindow> pMainWindow;
			pMainWindow=pEntity->GetMainWindow();
			if (NULL != pMainWindow)//获取pMainWindow成功
			{
				if(emtype_ == CONF_IM_CTRL)
				{
					//创建IMMeeting
          CLogger::Info(_T("%s"),_T("create IMMeeting"));
					pMainWindow->ShowCreateIMMeeting();
				}
				else
				{
					//创建MMMeeting
          CLogger::Info(_T("%s"),_T("create MMMeeting"));
					pMainWindow->ShowCreateMMMeeting();
				}

			}
			else//获取pMainWindow不成功
			{
         CLogger::Error(_T("%s"),_T("get main window failed"));
			}
		}
	}
  else
  {
       CLogger::Error(_T("%s"),_T("com init failed"));
  }

	//当使用了智能指针后,为防止COM拉不起来被调用者，需要将CoUninitialize()的调用去掉
	//CoUninitialize();

}
long CESdkConfCtrl::CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
  CLogger::Debug(_T("%s"),_T("CESdkConfCtrl::CreateCtrl"));

	emtype_ = emCtrlType;

	//<1>创建初始大小按钮 ,加载图标  
	CString strTitle = _T("");

	UINT resImage = 0;


	switch (emtype_)
	{
	case CONF_IM_CTRL:
		{
			strTitle = _T("发起即时消息会议");      
			resImage = IDB_PNG_IM_MEETING;
      CLogger::Info(_T("%s"),_T("Create IM Conf Ctrl"));
			break;
		}
	case CONF_AUDIO_CTRL:
		{
			strTitle = _T("发起语音会议");
			resImage = IDB_PNG_AUDIO_MEETING;
      CLogger::Info(_T("%s"),_T("Create Audio Conf Ctrl"));
			break;
		}
	default:
		{
			strTitle = _T("发起语音会议");
			resImage = IDB_PNG_AUDIO_MEETING;
      CLogger::Info(_T("%s"),_T("Create Audio Conf Ctrl"));
			break;
		}
	}

	CRect crt(0,0,150,40);//默认控件按钮的大小
	button_.Create(strTitle,WS_VISIBLE,crt,wnd,ID_BUTTON);

	button_.SetImage(resImage);
	button_.SetOwner(this);

	//<2>切换按钮的风格为windows7风格
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows)); 
	CMFCButton::EnableWindowsTheming();

	if(!IsEspaceInstalled())
	{
    CLogger::Warn(_T("%s"),_T("espace not installed, disable conf ctrl window"));
		button_.EnableWindow(FALSE);
	}
  else
  {
    CLogger::Info(_T("%s"),_T("espace installed, enable conf ctrl window"));
    button_.EnableWindow(TRUE);
  }

  CLogger::Info(_T("%s"),_T("Create Audio Conf Ctrl Success"));

	return SDK_SUCCESS;
}

long StartIMConf(void)
{
  CLogger::Info(_T("%s"),_T("StartIMConf()"));

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

  long ret = SDK_SUCCESS;  

	CComPtr<eSpace::IECSEspaceApp>  m_Espace;

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
		COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		HRESULT hr = m_Espace.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp),NULL, CLSCTX_ALL);

		if(m_Espace)
		{
			eSpace::IECSEspaceApp * pEntity=NULL;
			//查询接口
			hr = m_Espace->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
			if(SUCCEEDED(hr))
			{ 

				CComPtr<eSpace::IECSMainWindow> pMainWiondow;
				pMainWiondow = pEntity->GetMainWindow();

				if(NULL != pMainWiondow)//获取主窗口成功
				{

					VARIANT param;
					param.vt = VT_INT;
					param.intVal = 0;

					try
					{
            CLogger::Info(_T("%s"),_T("Call COM-ShowCreateIMMeeting()"));
						hr = pMainWiondow->ShowCreateIMMeeting();
					}
					catch (_com_error e)
					{
             CLogger::Error(_T("%s"),_T("ShowCreateIMMeeting failed"));
             ret = SDK_ERROR;
					}
				}
				else//获取主窗口失败
				{
           CLogger::Error(_T("%s"),_T("get main window failed"));
           ret = SDK_ERROR;
				}
			}
			else
			{
         CLogger::Error(_T("%s"),_T("QueryInterface espaceapp failed"));
         ret = SDK_ERROR;
			}
		}
		else
		{
      CLogger::Error(_T("%s"),_T("CoCreateInstance fail"));
      ret = SDK_ERROR;
		}

	}
	else
	{
    CLogger::Error(_T("%s"),_T("CoInitializeEx failed"));
    ret = SDK_ERROR;
	}
	//当使用了智能指针后,为防止COM拉不起来被调用者，需要将CoUninitialize()的调用去掉
	//CoUninitialize();

	return ret;
}
long StartAudioConf(void)
{
  CLogger::Info(_T("%s"),_T("StartAudioConf()"));
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//“调用语音会议的接口”
  long ret = SDK_SUCCESS;
	CComPtr<eSpace::IECSEspaceApp>  m_Espace;

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
		COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		HRESULT hr = m_Espace.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp),NULL, CLSCTX_ALL);

		if(SUCCEEDED(hr) && m_Espace)
		{
			eSpace::IECSEspaceApp * pEntity=NULL;
			//查询接口
			hr = m_Espace->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
			if(SUCCEEDED(hr))
			{ 
				CComPtr<eSpace::IECSMainWindow> pMainWiondow;
				pMainWiondow = pEntity->GetMainWindow();
				if(NULL != pMainWiondow)//获取主窗口成功
				{
					VARIANT param;
					param.vt = VT_INT;
					param.intVal = 0;
					try
					{
						hr = pMainWiondow->ShowCreateMMMeeting();
            CLogger::Info(_T("%s"),_T("Call COM-ShowCreateMMMeeting()"));
					}
					catch (_com_error e)
					{
            CLogger::Error(_T("%s"),_T("ShowCreateMMMeeting failed"));
            ret = SDK_ERROR;
					}
				}
				else//获取主窗口不成功
				{
          CLogger::Error(_T("%s"),_T("Get Espace MainWnd failed"));
          ret = SDK_ERROR;
				}
			}
		}
	}
	else
	{
    CLogger::Error(_T("%s"),_T("CoInitializeEx failed"));
    ret = SDK_ERROR;
	}

	//当使用了智能指针后,为防止COM拉不起来被调用者，需要将CoUninitialize()的调用去掉
	//CoUninitialize();

	return ret;
}
long StartConfMgr(void)
{
  CLogger::Info(_T("%s"),_T("StartConfMgr()"));
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  //“调用会议管理的接口”
  CComPtr<eSpace::IECSEspaceApp>  m_Espace;
  long ret = SDK_SUCCESS;

  HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
    COINIT_DISABLE_OLE1DDE);

  if (SUCCEEDED(hr))
  {
    HRESULT hr = m_Espace.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp),NULL, CLSCTX_ALL);

    if(SUCCEEDED(hr) && m_Espace)
    {
      eSpace::IECSEspaceApp * pEntity=NULL;
      //查询接口
      hr = m_Espace->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
      if(SUCCEEDED(hr))
      { 
        CComPtr<eSpace::IECSMainWindow>  pMainWiondow;
        pMainWiondow = pEntity->GetMainWindow();
        if(NULL != pMainWiondow)//获取主窗口成功
        {
          VARIANT param;
          param.vt = VT_INT;
          param.intVal = 0;
          try
          {
            hr = pMainWiondow->ShowMeetingMgr();
            CLogger::Info(_T("%s"),_T("Call COM-ShowMeetingMgr()"));
          }
          catch (_com_error e)
          {
            CLogger::Error(_T("%s"),_T("ShowMeetingMgr() failed"));   
            ret = SDK_ERROR;
          }
        }
        else//获取主窗口不成功
        {
          CLogger::Error(_T("%s"),_T("Get Espace MainWnd failed"));
          ret = SDK_ERROR;
        }
      }
    }
  }
  else
  {
    CLogger::Error(_T("%s"),_T("CoInitializeEx failed"));
    ret = SDK_ERROR;
  }

  //当使用了智能指针后,为防止COM拉不起来被调用者，需要将CoUninitialize()的调用去掉
  //CoUninitialize();

  return ret;
}