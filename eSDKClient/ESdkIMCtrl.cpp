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

long CESdkIMCtrl::CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType)//�ؼ������꣬����������
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CLogger::Debug(_T("%s"),_T("CESdkIMCtrl::CreateCtrl"));
    emtype_ = emCtrlType;

    //<1>������ʼ��С��ť ,����ͼ��  
    CString strTitle = _T("���ͼ�ʱ��Ϣ");

    CRect crt(0,0,100,40);//Ĭ�Ͽؼ���ť�Ĵ�С
    button_.Create(strTitle,WS_VISIBLE,crt,wnd, ID_BUTTON);
    button_.SetImage(IDB_PNG_IM);
    button_.SetOwner(this);

    //<2>�л���ť�ķ��Ϊwindows7���
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
    //AfxMessageBox(_T("�������"));
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
    //�����ڴ���ӡ�����Ⱥ�ĵĽӿڡ�
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
            //��ѯ�ӿ�
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

long CESdkSMSCtrl::CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType)//�ؼ������꣬����������
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CLogger::Debug(_T("%s"),_T("CESdkSMSCtrl::CreateCtrl"));
	emtype_ = emCtrlType;

	//<1>������ʼ��С��ť ,����ͼ��  
	CString strTitle = _T("���Ͷ���");
	CRect crt(0,50,100,90);//Ĭ�Ͽؼ���ť�Ĵ�С
	button_.Create(strTitle,WS_VISIBLE,crt,wnd, ID_BUTTON);
	button_.SetImage(IDB_PNG_IM);
	button_.SetOwner(this);

	//<2>�л���ť�ķ��Ϊwindows7���
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
	
	//���÷��Ͷ���COM�ӿ�,m_ucAccΪUC�˺����飬m_groupnoΪȺ���
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
	// ʹ�ö����߳�������com���
	CoInitialize(NULL);

	// ����ָ��
	CComPtr<eSpace::IECSEspaceApp>  m_eSpaceApp;

	// ���ʶ��
	CLSID clsid;	

	// �ɳ����ʶ����ȡ��Ӧ�����ʶ��
	CLSIDFromProgID(OLESTR("eSpace.ECSEspaceApp.1"),&clsid);	
	m_eSpaceApp.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

	if(m_eSpaceApp)
	{
		eSpace::IECSEspaceApp * pEntity=NULL;
		//��ѯ�ӿ�
		HRESULT hr = m_eSpaceApp->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
		if(SUCCEEDED(hr))
		{ 
			CComPtr<eSpace::IECSMainWindow>	pMainWindow;
			pMainWindow = pEntity->GetMainWindow();
			if(pMainWindow)//��ȡ�����ڳɹ�
			{
				//���ö��ż�Ȩ�ӿ�
				long lperm = pMainWindow->GetSmsPERM();
				if (0 != lperm)
				{
					try
					{
						//���÷��˶���com�ӿ�
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

							//����com�ӿڣ�����ʱȺ����
							hr = pMainWindow->ShowSMSChat(psa);
						} 
						else if("" != Groupno)
						{
							//����com�ӿڣ����̶�Ⱥ����
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
			else//��ȡ������ʧ��
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

long CESdkPERMCtrl::CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType)//�ؼ������꣬����������
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CLogger::Debug(_T("%s"),_T("CESdkPERMCtrl::CreateCtrl"));
	emtype_ = emCtrlType;

	//<1>������ʼ��С��ť ,����ͼ��  
	CString strTitle = _T("���ͼ�Ȩ");

	//Ĭ�Ͽؼ���ť�Ĵ�С
	CRect crt(0,50,100,90);
	button_.Create(strTitle,WS_VISIBLE,crt,wnd, ID_BUTTON);
	button_.SetImage(IDB_PNG_IM);
	button_.SetOwner(this);

	//<2>�л���ť�ķ��Ϊwindows7���
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
	// ʹ�ö����߳�������com���
	CoInitialize(NULL);

	// ����ָ��
	CComPtr<eSpace::IECSEspaceApp>  m_eSpaceApp;

	// ���ʶ��
	CLSID clsid;	

	// �ɳ����ʶ����ȡ��Ӧ�����ʶ��
	CLSIDFromProgID(OLESTR("eSpace.ECSEspaceApp.1"),&clsid);	
	m_eSpaceApp.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

	if(m_eSpaceApp)
	{
		eSpace::IECSEspaceApp * pEntity=NULL;
		//��ѯ�ӿ�
		HRESULT hr = m_eSpaceApp->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
		if(SUCCEEDED(hr))
		{ 
			CComPtr<eSpace::IECSMainWindow>	pMainWindow;
			pMainWindow = pEntity->GetMainWindow();
			//��ȡ�����ڳɹ�
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
			//��ȡ������ʧ��
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
