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
	// ʹ�ö����߳�������com���
	CoInitialize(NULL);
	// ����ָ��
	CComPtr<eSpace::IECSEspaceApp>  m_EspaceApp;

	// ��ʼ��ָ�룬���ַ���
	CLSID clsid;	// ���ʶ��
	CLSIDFromProgID(OLESTR("eSpace.ECSEspaceApp.1"),&clsid);	// �ɳ����ʶ����ȡ��Ӧ�����ʶ��
	m_EspaceApp.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

	if(m_EspaceApp)
	{
		eSpace::IECSEspaceApp * pEntity=NULL;
		//��ѯ�ӿ�
		HRESULT hr = m_EspaceApp->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
		if(SUCCEEDED(hr))
		{ 
			//eSpace::IECSMainWindow*	pMainWindow;
			CComPtr<eSpace::IECSMainWindow> pMainWindow;
			pMainWindow=pEntity->GetMainWindow();
			if (NULL != pMainWindow)//��ȡpMainWindow�ɹ�
			{
				if(emtype_ == CONF_IM_CTRL)
				{
					//����IMMeeting
          CLogger::Info(_T("%s"),_T("create IMMeeting"));
					pMainWindow->ShowCreateIMMeeting();
				}
				else
				{
					//����MMMeeting
          CLogger::Info(_T("%s"),_T("create MMMeeting"));
					pMainWindow->ShowCreateMMMeeting();
				}

			}
			else//��ȡpMainWindow���ɹ�
			{
         CLogger::Error(_T("%s"),_T("get main window failed"));
			}
		}
	}
  else
  {
       CLogger::Error(_T("%s"),_T("com init failed"));
  }

	//��ʹ��������ָ���,Ϊ��ֹCOM���������������ߣ���Ҫ��CoUninitialize()�ĵ���ȥ��
	//CoUninitialize();

}
long CESdkConfCtrl::CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
  CLogger::Debug(_T("%s"),_T("CESdkConfCtrl::CreateCtrl"));

	emtype_ = emCtrlType;

	//<1>������ʼ��С��ť ,����ͼ��  
	CString strTitle = _T("");

	UINT resImage = 0;


	switch (emtype_)
	{
	case CONF_IM_CTRL:
		{
			strTitle = _T("����ʱ��Ϣ����");      
			resImage = IDB_PNG_IM_MEETING;
      CLogger::Info(_T("%s"),_T("Create IM Conf Ctrl"));
			break;
		}
	case CONF_AUDIO_CTRL:
		{
			strTitle = _T("������������");
			resImage = IDB_PNG_AUDIO_MEETING;
      CLogger::Info(_T("%s"),_T("Create Audio Conf Ctrl"));
			break;
		}
	default:
		{
			strTitle = _T("������������");
			resImage = IDB_PNG_AUDIO_MEETING;
      CLogger::Info(_T("%s"),_T("Create Audio Conf Ctrl"));
			break;
		}
	}

	CRect crt(0,0,150,40);//Ĭ�Ͽؼ���ť�Ĵ�С
	button_.Create(strTitle,WS_VISIBLE,crt,wnd,ID_BUTTON);

	button_.SetImage(resImage);
	button_.SetOwner(this);

	//<2>�л���ť�ķ��Ϊwindows7���
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
			//��ѯ�ӿ�
			hr = m_Espace->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
			if(SUCCEEDED(hr))
			{ 

				CComPtr<eSpace::IECSMainWindow> pMainWiondow;
				pMainWiondow = pEntity->GetMainWindow();

				if(NULL != pMainWiondow)//��ȡ�����ڳɹ�
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
				else//��ȡ������ʧ��
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
	//��ʹ��������ָ���,Ϊ��ֹCOM���������������ߣ���Ҫ��CoUninitialize()�ĵ���ȥ��
	//CoUninitialize();

	return ret;
}
long StartAudioConf(void)
{
  CLogger::Info(_T("%s"),_T("StartAudioConf()"));
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//��������������Ľӿڡ�
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
			//��ѯ�ӿ�
			hr = m_Espace->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
			if(SUCCEEDED(hr))
			{ 
				CComPtr<eSpace::IECSMainWindow> pMainWiondow;
				pMainWiondow = pEntity->GetMainWindow();
				if(NULL != pMainWiondow)//��ȡ�����ڳɹ�
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
				else//��ȡ�����ڲ��ɹ�
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

	//��ʹ��������ָ���,Ϊ��ֹCOM���������������ߣ���Ҫ��CoUninitialize()�ĵ���ȥ��
	//CoUninitialize();

	return ret;
}
long StartConfMgr(void)
{
  CLogger::Info(_T("%s"),_T("StartConfMgr()"));
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  //�����û������Ľӿڡ�
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
      //��ѯ�ӿ�
      hr = m_Espace->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
      if(SUCCEEDED(hr))
      { 
        CComPtr<eSpace::IECSMainWindow>  pMainWiondow;
        pMainWiondow = pEntity->GetMainWindow();
        if(NULL != pMainWiondow)//��ȡ�����ڳɹ�
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
        else//��ȡ�����ڲ��ɹ�
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

  //��ʹ��������ָ���,Ϊ��ֹCOM���������������ߣ���Ҫ��CoUninitialize()�ĵ���ȥ��
  //CoUninitialize();

  return ret;
}