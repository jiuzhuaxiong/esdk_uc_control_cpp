#include "StdAfx.h"
#include "SDKButton.h"
#include "ESdkDialCtrl.h"
#include "resource.h"
#include "PublicFunction.h"
#include "Logger.h"
using namespace eSDK;


// �����̿ؼ�
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
    // ��ȡ���λ��
    CPoint pmenu;
    // ��ȡ������Ļ���꣬�����pmenu��
    ::GetCursorPos(&pmenu);

    // ʹ�ö����߳�������com���
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
        COINIT_DISABLE_OLE1DDE);

    // ����ָ��
    CComPtr<eSpace::IECSEspaceApp>  m_eSpaceApp;

    // ��ʼ��ָ�룬���ַ���
    //m_EspaceApp.CoCreateInstance(__uuidof(eSpace::ECSExternService),NULL, CLSCTX_ALL);
    CLSID clsid;	// ���ʶ��
    CLSIDFromProgID(OLESTR("eSpace.ECSEspaceApp.1"),&clsid);	// �ɳ����ʶ����ȡ��Ӧ�����ʶ��
    m_eSpaceApp.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

    if(m_eSpaceApp)
    {
        eSpace::IECSEspaceApp * pEntity=NULL;
        //��ѯ�ӿ�
        HRESULT hr = m_eSpaceApp->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
        if(SUCCEEDED(hr))
        { 
            //eSpace::IECSMainWindow*	pMainWindow;
            CComPtr<eSpace::IECSMainWindow> pMainWindow;
            pMainWindow = pEntity->GetMainWindow();

            if(pMainWindow)//��ȡ�����ڳɹ�
            {
                // 1.����������
                HRESULT hr = pMainWindow->ShowDialPad(pmenu.x, pmenu.y);
            }
            else//��ȡ������ʧ��
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

// ������пؼ�
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
    // ʹ�ö����߳�������com���
    CoInitialize(NULL);

    // ����ָ��
    CComPtr<eSpace::IECSEspaceApp>  m_eSpaceApp;

    // ��ʼ��ָ�룬���ַ���
    //m_Espace.CoCreateInstance(__uuidof(eSpace::ECSExternService),NULL, CLSCTX_ALL);
    CLSID clsid;	// ���ʶ��
    CLSIDFromProgID(OLESTR("eSpace.ECSEspaceApp.1"),&clsid);	// �ɳ����ʶ����ȡ��Ӧ�����ʶ��
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
                // 2.ֱ�Ӳ���
                pMainWindow->MakeCall(m_strUri.c_str(), m_strPhone.c_str());
            }
            else//��ȡ������ʧ��
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


// ��Ƶ���пؼ�
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
				// 2.ֱ�Ӳ���
				pMainWindow->MakeVideoCall(m_strUri.c_str(), m_strPhone.c_str());
			}
			//��ȡ������ʧ��
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

// ѡ����пؼ�
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

//���ú��ж�����ʺ�
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
        //û�к��ж����˳�����
        CLogger::Warn(_T("%s"),_T("CESdkChooseToDialCtrl::OnClick() uc account is empty"));
        return;
    }

    // ʹ�ö����߳�������com���
    CoInitialize(NULL);

    // ����ָ��
    CComPtr<eSpace::IECSEspaceApp>	m_eSpaceApp;

	// ���ʶ��
    CLSID	clsidApp;	

	// �ɳ����ʶ����ȡ��Ӧ�����ʶ��
    CLSIDFromProgID(OLESTR("eSpace.ECSeSpaceApp.1"),&clsidApp);
    m_eSpaceApp.CoCreateInstance(clsidApp,NULL, CLSCTX_ALL);

    if(m_eSpaceApp)
    {
        eSpace::IECSEspaceApp * pEntity=NULL;
        //��ѯ�ӿ�
        HRESULT hr = m_eSpaceApp->QueryInterface(__uuidof(eSpace::IECSEspaceApp), (void**)&pEntity);
        if(SUCCEEDED(hr))
        { 
            // 3.ѡ�����
            // 3.0.��ȡ���λ��
            CPoint pmenu;
            // ��ȡ������Ļ���꣬�����pmenu��
            ::GetCursorPos(&pmenu);

            // 3.1.��ȡ��ϵ�˵绰
            BSTR	bstrAccount	=	SysAllocString(CA2W (m_strAccount.c_str ()));
            BSTR	bstrUri	=	 SysAllocString (CA2W (m_strUri.c_str ()));
            CComPtr<eSpace::IECSContactInfo> pContactInfo;
            //eSpace::IECSContactMgr*	pContactMgr;
            CComPtr<eSpace::IECSContactMgr> pContactMgr;
            pContactMgr = pEntity->GetContactMgr();
            if(pContactMgr)//��ȡ��ϵ�˹������ɹ�
            {
                pContactInfo = pContactMgr->GetContactInfo(bstrAccount);

                if(pContactInfo)//��ȡ��ϵ����Ϣ�ɹ�
                {
                    m_strUri						=	pContactInfo->GetUcUri();
                    m_strAccount			=	pContactInfo->GetUcAccount();
                    m_strHomePhone	=	pContactInfo->GetHomePhone();
                    m_strOfficePhone	=	pContactInfo->GetOfficePhone();
                    m_strMobile				=	pContactInfo->GetMobile();
                    m_strOtherPhone	=	pContactInfo->GetOtherPhone();

                    // 3.2.����menu
                    CMenu phoneMenu;
                    phoneMenu.CreatePopupMenu();
                    int iMenuNo = 0;
                    // �ڸò˵������URIѡ��
                    phoneMenu.AppendMenu(MF_STRING, ID_DIAL_URI, CPublicFunction::UTF2UNICODE(m_strAccount));
                    // �ڸò˵�����ӵ绰ѡ��
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
                        // û���κε绰����Ȼ�����˵���������Ϊ��
                        phoneMenu.AppendMenu(MF_STRING, ID_DIAL_NO_PHONE, _T(""));
                    }
                    // ����Ļ��pmenu��ָ��λ����ʾ�˵�
                    phoneMenu.TrackPopupMenu(TPM_LEFTBUTTON, pmenu.x, pmenu.y, &button_);

                    // 3.3.�ͷ���Դ
                    ::SysFreeString(bstrAccount);
                    ::SysFreeString(bstrUri);
                }
                else//��ȡ��ϵ����Ϣʧ��
                {
                    CLogger::Error(_T("%s"),_T("CESdkChooseToDialCtrl::OnClick() get contact info failed"));
                }

            }
            else//��ȡ��ϵ�˹�����ʧ��
            {
                CLogger::Error(_T("%s"),_T("CESdkChooseToDialCtrl::OnClick() get contact manager failed"));
            }
        }
    }

    CoUninitialize();
}

// ����˵���Ӧ����
void CESdkChooseToDialCtrl::OnClickMenu(UINT uID)
{

    CLogger::Debug(_T("%s"),_T("CESdkChooseToDialCtrl::OnClickMenu"));
    std::string	strUri;
    std::string	strPhoneNo;
    strUri.clear();
    strPhoneNo.clear();

    // ��ȡ�绰����
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
        // û�е绰���룬����
        return;
    }

    // ���绰����ת����ʽ
    BSTR	bstrUri	= SysAllocString (CA2W (strUri.c_str ()));
    BSTR	bstrPhoneNo	= SysAllocString (CA2W (strPhoneNo.c_str ()));

    // ʹ�ö����߳�������com���
    CoInitialize(NULL);

    // ����ָ��
    CComPtr<eSpace::IECSEspaceApp>  m_EspaceApp;

    // ��ʼ��ָ��
    m_EspaceApp.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp),NULL, CLSCTX_ALL);

    if(m_EspaceApp)
    {
        // ֱ�Ӳ���
        //eSpace::IECSMainWindow*	pMainWindow;
        CComPtr<eSpace::IECSMainWindow> pMainWindow;
        pMainWindow = m_EspaceApp->GetMainWindow();
        if(pMainWindow)
        {
            // 2.ֱ�Ӳ���
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

    // �ͷ���Դ
    SysFreeString(bstrUri);
    SysFreeString(bstrPhoneNo);

    CoUninitialize();
}


// ����COM�ӿڵĽӿ�
long ShowDialPad(void)
{
    TRACE(_T("ShowDialPad()\n"));
    CLogger::Debug(_T("%s"),_T("ShowDialPad"));
    //// ʹ�ö����߳�������com���
    //CoInitialize(NULL);

    //// ����ָ��
    //CComPtr<eSpace::IECSExternService>  m_Espace;

    //// ��ʼ��ָ�룬���ַ���
    ////m_Espace.CoCreateInstance(__uuidof(eSpace::ECSExternService),NULL, CLSCTX_ALL);
    //CLSID clsid;	// ���ʶ��
    //CLSIDFromProgID(OLESTR("eSpace.ECSExternService.1"),&clsid);	// �ɳ����ʶ����ȡ��Ӧ�����ʶ��
    //m_Espace.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

    //if(m_Espace)
    //{
    //	// 1.����������
    //	m_Espace->ShowDialPad();	
    //}

    //CoUninitialize();

    return SDK_SUCCESS;
}

long StartDialing(void)
{
    TRACE(_T("StartDialing()\n"));
    CLogger::Debug(_T("%s"),_T("StartDialing"));
    //// ʹ�ö����߳�������com���
    //CoInitialize(NULL);

    //// ����ָ��
    //CComPtr<eSpace::IECSExternService>  m_Espace;

    //// ��ʼ��ָ�룬���ַ���
    ////m_Espace.CoCreateInstance(__uuidof(eSpace::ECSExternService),NULL, CLSCTX_ALL);
    //CLSID clsid;	// ���ʶ��
    //CLSIDFromProgID(OLESTR("eSpace.ECSExternService.1"),&clsid);	// �ɳ����ʶ����ȡ��Ӧ�����ʶ��
    //m_Espace.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

    //if(m_Espace)
    //{
    //	// 2.ֱ�Ӳ���
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
    //// ʹ�ö����߳�������com���
    //CoInitialize(NULL);

    //// ����ָ��
    //CComPtr<eSpace::IECSExternService>  m_Espace;

    //// ��ʼ��ָ�룬���ַ���
    ////m_Espace.CoCreateInstance(__uuidof(eSpace::ECSExternService),NULL, CLSCTX_ALL);
    //CLSID clsid;	// ���ʶ��
    //CLSIDFromProgID(OLESTR("eSpace.ECSExternService.1"),&clsid);	// �ɳ����ʶ����ȡ��Ӧ�����ʶ��
    //m_Espace.CoCreateInstance(clsid,NULL, CLSCTX_ALL);

    //if(m_Espace)
    //{
    //	// ת�����ж����Uri
    //	BSTR	bstrUri	=	 SysAllocString (CA2W (strUri.c_str ()));
    //	// �绰���봫���������ȳ�ʼ��Ϊtempֵ
    //	BSTR	bstrHomePhone	= ::SysAllocString(L"temp");
    //	BSTR	bstrOfficePhone	= ::SysAllocString(L"temp");
    //	BSTR	bstrMobile			= ::SysAllocString(L"temp");
    //	BSTR	bstrOtherPhone	= ::SysAllocString(L"temp");
    //	//BSTR	bstrPhoneNo[4];
    //	// ��ȡ��ϵ�˵�4���绰���룬�������ڳ�Ա������
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

    //	// 3.3.�ͷ���Դ
    //	::SysFreeString(bstrUri);
    //	::SysFreeString(bstrHomePhone);
    //	::SysFreeString(bstrOfficePhone);
    //	::SysFreeString(bstrMobile);
    //	::SysFreeString(bstrOtherPhone);
    //}

    //CoUninitialize();

    return SDK_SUCCESS;
}
