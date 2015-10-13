#include "StdAfx.h"
#include "ESdkStatusCtrl.h"
#include "PublicFunction.h"
#include "resource.h"
#include <iostream>
#include "comutil.h"
#include <string>
#include "Language.h"
#include "Logger.h"
using namespace eSDK;

CESdkStatusCtrl::CESdkStatusCtrl(void):MOUDEL_NAME("CESdkStatusCtrl")
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    m_eventHandler = NULL;
    pIEspaceApp = NULL;
    m_logInfo="";
#ifdef _DEBUG
    CLogger::SetLevel(CLogger::LEVEL_DEBUG,true);
#else
    CLogger::SetLevel(CLogger::LEVEL_INFO,true);
#endif
   CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("CESdkStatusCtrl")));

}

CESdkStatusCtrl::~CESdkStatusCtrl(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("~CESdkStatusCtrl")));
    if(!this->m_ucAccount.empty() && m_statusSubscribed)
    {
        CComPtr<eSpace::IECSEspaceApp>  m_Espace;
        HRESULT hr;
        hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
            COINIT_DISABLE_OLE1DDE);

        hr = m_Espace.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp), NULL, CLSCTX_ALL);
        if(m_Espace)
        {
            eSpace::IECSEspaceApp * pEspaceApp = NULL;
            hr=m_Espace->QueryInterface(__uuidof(eSpace::IECSEspaceApp),(void **)&pEspaceApp);
            if(SUCCEEDED(hr))
            {
                CComPtr<eSpace::IECSContactMgr> pContactMgr;
                pContactMgr = pEspaceApp->GetContactMgr();
                if(pContactMgr)
                {
                    BSTR com_ucAccount=_com_util::ConvertStringToBSTR(this->m_ucAccount.c_str());
                    pContactMgr->SubscribeContactStatus(com_ucAccount, 1);
                    CLogger::Info(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("SubscribeContactStatus")));
                }

            }
        }

        CoUninitialize();
    }

    if(m_eventHandler != NULL)
    {
        delete m_eventHandler;
    }
}


//��ʼ��COM���
bool CESdkStatusCtrl::InitComPtr()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("InitComPtr")));

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
        COINIT_DISABLE_OLE1DDE);

    CComPtr<eSpace::IECSEspaceApp>  m_Espace;//�ؼ���ʹ�õ���
    m_Espace.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp), NULL, CLSCTX_ALL);
    if(m_Espace)
    {
        //������queryInterfaceһ��,������com���UnInitializeʱ��,���ü����ϻ����
        HRESULT hr = m_Espace->QueryInterface(__uuidof(eSpace::IECSEspaceApp),(void**)&pIEspaceApp);
        return SUCCEEDED(hr);
    }
    else
    {
        CLogger::Error(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("init com failed")));
        return false;
    }
    CoUninitialize();
}

bool CESdkStatusCtrl::UnInitComPtr()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("UnInitComPtr")));
    //if(m_comInitiated)
    //{
    //	CoUninitialize();
    //}
    return true;
}
long CESdkStatusCtrl::CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("default CreateCtrl")));
    //���ÿؼ�����
    if(emCtrlType!=USER_STATUS_CTRL)
    {
        return SDK_INVAD_PARA;
    }
    else
    {
        emtype_ = emCtrlType;
    }


    CString strTitle = _T("");
    CRect crt(150,150,150,40);//Ĭ�Ͽؼ���ť�Ĵ�С
    button_.Create(strTitle,WS_VISIBLE,crt,wnd, ID_BUTTON);


	button_.SetOwner(this);
    //<2>�л���ť�ķ��Ϊwindows7���
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows)); 
    CMFCButton::EnableWindowsTheming();


	this->SetStatus(STATUS_OFFLINE);//������ֱ��ʹ��SetImagePath������״̬ͼ��

    if(!IsEspaceInstalled())
    {
        CLogger::Warn(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("espace not installed,disable ctrol window")));
        button_.EnableWindow(FALSE);
    }
    else
    {
        //��ʼ��COM�ؼ�
        if(!this->InitComPtr())
        {
            return SDK_ERROR;
        }
    }
    return SDK_SUCCESS;


}
//��ָ��λ�ô���״̬��ʾ�ؼ�
long CESdkStatusCtrl::CreateCtrl(CWnd *wnd,int iLefTopX,int iLeftTopY,int iWidth,int iHeight)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("CreateCtrl at defined position with defined size")));
    if(iLefTopX<0||iLeftTopY<0||iWidth<0||iHeight<0)
    {
        return SDK_INVAD_PARA;
    }
    CRect crt(iLefTopX,iLeftTopY,iWidth,iHeight);//Ĭ�Ͽؼ���ť�Ĵ�С

    this->emtype_ = USER_STATUS_CTRL;//�ؼ��������ó�״̬�ؼ�
    CString strTitle = _T("");//�ؼ���Ĭ�ϲ���ʾ����
    button_.Create(strTitle,WS_VISIBLE,crt,wnd, 0);
    button_.SetOwner(this);

    this->SetStatus(STATUS_OFFLINE);//������ֱ��ʹ��SetImagePath������״̬ͼ��
    //<2>�л���ť�ķ��Ϊwindows7���
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows)); 
    CMFCButton::EnableWindowsTheming();

    if(!IsEspaceInstalled())
    {
        CLogger::Warn(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("espace not installed, disable window")));
        button_.EnableWindow(FALSE);
    }

    return SDK_SUCCESS;
}
//��ť���µ��¼�����
void CESdkStatusCtrl::OnClick()
{
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("status control Clicked")));
    CMenu contextMenu;
    contextMenu.CreatePopupMenu();
    contextMenu.AppendMenu(MF_STRING, ID_STATUSCTRL_IM, eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_STATUS_CTRL_IM)));
    contextMenu.AppendMenu(MF_STRING, ID_STATUSCTRL_CTD, eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_STATUS_CTRL_CTD)));
    contextMenu.AppendMenu(MF_STRING, ID_STATUSCTRL_EMAIL,eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_STATUS_CTRL_EMAIL)));
    //contextMenu.AppendMenu(MF_STRING, ID_STATUSCTRL_INFO, eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_STATUS_CTRL_INFO)));
    //contextMenu.AppendMenu(MF_STRING, ID_STATUSCTRL_ADD_CONTACT,eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_STATUS_CTRL_ADD_CONTACT)));
    // ����Ļ��pmenu��ָ��λ����ʾ�˵�
    CRect rect;
    this->button_.GetWindowRect(&rect);
    CPoint leftPos=rect.TopLeft();
    CPoint righPos=rect.BottomRight();
    contextMenu.TrackPopupMenu(TPM_LEFTBUTTON, leftPos.x, righPos.y, &button_);
}

//״̬�ؼ�˫���¼�����
void CESdkStatusCtrl::OnDbClick()
{
    //AfxMessageBox(_T("չʾ�û���Ϣ"));
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("status control double Clicked")));
}

bool CESdkStatusCtrl::RefreshStatus()
{
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("status control RefreshStatus")));
    bool returnRes=false;
    if(this->m_ucAccount.empty())
    {
        CLogger::Warn(_T("%s"),_T("no account set"));
        returnRes=false;
    }
    else
    {
        CComPtr<eSpace::IECSEspaceApp>  m_Espace;
        HRESULT hr=S_FALSE;
        CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
            COINIT_DISABLE_OLE1DDE);

        hr = m_Espace.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp), NULL, CLSCTX_ALL);
        if(m_Espace)
        {
            //ʹ��__uuidof����ȡһ��һ��com�齨��uuid(GUID),���GUID��ֵ�Ǵ�espace����Դ�ʼ��еõ���
            eSpace::IECSEspaceApp * pEspaceApp = NULL;
            hr=m_Espace->QueryInterface(__uuidof(eSpace::IECSEspaceApp),(void **)&pEspaceApp);
            if(SUCCEEDED(hr))
            {
                //eSpace::IECSContactMgr * pContactMgr=NULL;
                CComPtr<eSpace::IECSContactMgr> pContactMgr;
                pContactMgr = pEspaceApp->GetContactMgr();
                if(NULL != pContactMgr)//��ȡ��ϵ�˹������ɹ�
                {
                    //eSpace::IECSContactInfo* pContactInfo=NULL;
                    BSTR com_ucAccount=_com_util::ConvertStringToBSTR(this->m_ucAccount.c_str());
                    CComPtr<eSpace::IECSContactInfo> pContactInfo;
                    pContactInfo = pContactMgr->GetContactInfo(com_ucAccount);

                    if(NULL != pContactInfo)//�����ȡUC�˺���Ϣ�ɹ�
                    {
                        CLogger::Info(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("get contact info success")));
                        LONG status = pContactInfo->GetStatus();
                        this->m_ucUri=_com_util::ConvertBSTRToString(pContactInfo->GetUcUri());
                        this->SetStatus((EnStatus)status);
                        BSTR bEmail=  pContactInfo->GetEmail();
                        if(SysStringLen(bEmail))
                        {
                            this->m_ucEmail=_com_util::ConvertBSTRToString(bEmail);
                        }
                        else
                        {
                            CLogger::Info(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("contact's email is empty")));
                            this->m_ucEmail="";
                        }
                        m_statusSubscribed = true;
                        pContactMgr->SubscribeContactStatus(com_ucAccount, 0);
                        returnRes=true;
                    }
                    else//�����ȡuc�˺���Ϣʧ��,��ʱ��û���ҵ�uc�˺Ŷ�Ӧ���û�
                    {
                        CLogger::Error(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("get contact info failed")));
                        this->SetStatus(STATUS_OFFLINE);
                        returnRes=false;
                    }

                }
                else//��ȡContactMgrָ��ʧ��
                {
                    CLogger::Error(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("get ContactMgr interface failed")));
                    this->SetStatus(STATUS_OFFLINE);
                    returnRes=false;
                }

            }
            else//��ѯespaceApp�ӿ�ʧ��
            {
                CLogger::Error(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("get espaceapp interface failed")));
                this->SetStatus(STATUS_OFFLINE);
                returnRes=false;
            }

        }
        else//����comָ��ʧ��
        {
            CLogger::Error(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("init com failed")));
            this->SetStatus(STATUS_OFFLINE);
            returnRes=false;
        }
        CoUninitialize();
    }

    return returnRes;
}
void CESdkStatusCtrl::OnClickMenu(UINT uID)
{
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("status control menu clicked")));
    HRESULT hr=S_FALSE;
    CComPtr<eSpace::IECSEspaceApp>  m_Espace;
    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
        COINIT_DISABLE_OLE1DDE);
    m_Espace.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp), NULL, CLSCTX_ALL);
    if(m_Espace)
    {
        hr=m_Espace->QueryInterface(__uuidof(eSpace::IECSEspaceApp),(void **)&pIEspaceApp);
        if(SUCCEEDED(hr))
        {
            CComPtr<eSpace::IECSMainWindow> pIMainWindow;
            pIMainWindow = pIEspaceApp->GetMainWindow();
            if (pIMainWindow)//��ȡmainwindow�ɹ�
            {
                BSTR account_bstr=_com_util::ConvertStringToBSTR(this->m_ucAccount.c_str());
                switch(uID)
                {
                case ID_STATUSCTRL_EMAIL://�������˷��ʼ��Ĳ˵�
                    if(!this->m_ucEmail.empty())
                    {
                        CString mailStr = _T("mailto:");
                        mailStr += CPublicFunction::UTF2UNICODE(this->m_ucEmail);
                        HINSTANCE result=ShellExecute(this->button_.GetSafeHwnd(), _T("open"), mailStr, NULL, NULL, SW_SHOW);
                    }
                    else
                    {
                        CLogger::Warn(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("account has no email")));
                    }
                    break;
                case ID_STATUSCTRL_IM://�������˷�IM��Ϣ�Ĳ˵�
                    if(!this->m_ucAccount.empty())
                    {
                        try{
                            pIMainWindow->ShowIMChat(account_bstr);
                        }catch(...){
                            CLogger::Error(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("error occour when show im chat")));
                        }
                        
                    }
                    else
                    {
                        CLogger::Warn(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("account is empty, do not start showIMChat")));
                    }
                    break;
                case ID_STATUSCTRL_INFO://�鿴�û���Ϣ
                    break;
                case ID_STATUSCTRL_ADD_CONTACT://�����ϵ��
                    break;
                case ID_STATUSCTRL_CTD://����绰
                    if(!this->m_ucUri.empty())
                    {
                        pIMainWindow->MakeCall(_com_util::ConvertStringToBSTR(this->m_ucUri.c_str()),"");
                    }
                    else
                    {
                        CLogger::Warn(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("uri is empty, do not start makeCall")));
                    }
                    break;
                default:
                    break;
                }
            }
            else//�����ȡ������ʧ��
            {
                CLogger::Error(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("get main windows failed when click status control context menu")));
            }
        }
    }
    else//�����ѯ�ӿ�ʧ��
    {
        CLogger::Error(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("get espace app failed when click status control context menu")));
    }

    CoUninitialize();

}

void CESdkStatusCtrl::SetStatus(EnStatus status)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    //�ı�״̬�ؼ��ϵ�ͼ��ǰ,�����ú�״̬�ؼ�����ʾ��Ϣ
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("SetStatus invoked")));
    this->SetTipsByStatus(status);

    if(this->m_statusImageArray[status].length()>0)
    {
        this->SetIcon(this->m_statusImageArray[status]);
    }
    else
    {
        switch(status)
        {
        case STATUS_OFFLINE:
            this->button_.SetImage(IDB_STATUS_OFFLINE);
            break;
        case STATUS_ONLINE:
            this->button_.SetImage(IDB_STATUS_ONLINE);
            break;
        case STATUS_CALLING:
            this->button_.SetImage(IDB_STATUS_CALLING);
            break;
        case STATUS_BUSY:
            this->button_.SetImage(IDB_STATUS_BUSY);
            break;
        case STATUS_LEAVING:
            this->button_.SetImage(IDB_STATUS_LEAVING);
            break;
        case STATUS_DND:
            this->button_.SetImage(IDB_STATUS_DND);
            break;
        case STATUS_ERROR:
            this->button_.SetImage(IDB_STATUS_ERROR);
            break;
        default:
            this->button_.SetImage(IDB_STATUS_OFFLINE);
            break;
        }

    }
    this->button_.Invalidate(TRUE);

}

bool CESdkStatusCtrl::SetStatusImg( std::string imgStrArray[],int len)
{
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("SetStatusImg invoked")));

    if(len!=STATUS_LEN)
    {
        return false;
    }
    else
    {
        for(int i=0;i<STATUS_LEN;i++)
        {
            this->m_statusImageArray[i]=imgStrArray[i];
        }
        return true;
    }
}


HRESULT CESdkStatusCtrl::OnEventOccured
(
 eSpace::ECSEventType eventId,
 const _variant_t & param1,
 const _variant_t & param2,
 IUnknown * eventInfo
 )
{
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("OnEventOccured invoked")));
    if(eventId == eSpace::APP_SHUTDOWN)
    {
        CLogger::Info(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("espace shutdown")));
        this->SetStatus(CESdkStatusCtrl::STATUS_OFFLINE);
    }
    else if(eventId == eSpace::LOGIN_STATE_CHANGE)
    {
        CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("LOGIN_STATE change")));
        if(param1.intVal == 0)//�����߱�����
        {
            //this->SetStatus(EnStatus::STATUS_ONLINE);
            this->RefreshStatus();
        }
        else
        {
            this->SetStatus(EnStatus::STATUS_OFFLINE);
        }

    }
    else if(eventId == eSpace::CONTACT_STATE_CHANGE)
    {
        long	lStatus = 0;
        lStatus = param2.intVal;
        BSTR ucacc = param1.bstrVal;
        std::string ucAccountStr=_com_util::ConvertBSTRToString(ucacc);
        if (this->m_ucAccount==ucAccountStr)
        {
            this->SetStatus((EnStatus)lStatus);
        }
        else
        {
            //���״̬�ı��uc�˺źͿؼ��󶨵�uc�˺Ų�һ��,�����κβ���
            CLogger::Info(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("contact state change")));
        }
    }
    return S_OK;
}
// ��ȡ��ǰ�ؼ���������UC�˺�
std::string CESdkStatusCtrl::GetAccount(void) 
{
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("GetAccount")));
    return this->m_ucAccount;
}

// ���úͿؼ��󶨵�uc�˺�
void CESdkStatusCtrl::SetAccount(std::string& account)
{
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("SetAccount")));
    this->m_ucAccount=account;

    HRESULT hr=S_FALSE;
    CComPtr<eSpace::IECSEspaceApp>  m_Espace;
    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
        COINIT_DISABLE_OLE1DDE);
    m_Espace.CoCreateInstance(__uuidof(eSpace::ECSEspaceApp), NULL, CLSCTX_ALL);

    if(m_Espace)
    {
        if(m_eventHandler == NULL)
            m_eventHandler = new IECSExternEventHandler(*this, m_Espace, &CESdkStatusCtrl::OnEventOccured);
    }

    CoUninitialize();

    this->RefreshStatus();
}

void CESdkStatusCtrl::SetTipsByStatus(EnStatus status)
{
    CLogger::Debug(_T("%s"),CPublicFunction::UTF2UNICODE(getLogInfo("SetTipsByStatus")));
    std::string tips;
    switch(status)
    {
    case STATUS_OFFLINE:
        tips.append(CPublicFunction::UNICODE2UTF(eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_STATUS_TIP_OFFLINE))));
        break;
    case STATUS_BUSY:
        tips.append(CPublicFunction::UNICODE2UTF(eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_STATUS_TIP_BUSY))));
        break;
    case STATUS_CALLING:
        tips.append(CPublicFunction::UNICODE2UTF(eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_STATUS_TIP_CALLING))));
        break;
    case STATUS_DND:
        tips.append(CPublicFunction::UNICODE2UTF(eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_STATUS_TIP_DND))));
        break;
    case STATUS_LEAVING:
        tips.append(CPublicFunction::UNICODE2UTF(eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_STATUS_TIP_LEAVING))));
        break;
    case STATUS_ONLINE:
        tips.append(CPublicFunction::UNICODE2UTF(eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_STATUS_TIP_ONLINE))));
        break;
    case STATUS_ERROR:
        tips.append(CPublicFunction::UNICODE2UTF(eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_STATUS_TIP_ERROR))));
        break;
    default:
        tips.append(CPublicFunction::UNICODE2UTF(eSDK::CLanguage::GetInstance()->GetString(GET_STRING_PARAM(IDS_STATUS_TIP_ERROR))));
        break;
    }
    this->SetTip(tips);
}

std::string CESdkStatusCtrl::getLogInfo(std::string newInfo)
{
    this->m_logInfo.clear();
    this->m_logInfo.append("[");
    this->m_logInfo.append(MOUDEL_NAME);
    this->m_logInfo.append("]");
    this->m_logInfo.append(newInfo);
    return this->m_logInfo;
}