#pragma once
#include "ESdkCtrl.h"
#include "TEventHandler.h"

class CESdkStatusCtrl;
typedef TEventHandler<CESdkStatusCtrl, eSpace::IECSEspaceApp> IECSExternEventHandler;

class ESDK_API CESdkStatusCtrl :
	public CESdkCtrl
{

public:
	const static int STATUS_LEN=7;

	typedef enum MENU_ITEM
	{
		ITEM_CHAT=0,
		ITEM_EMAIL,
		ITEM_INFO,
		ITEM_ADD_CONTACT
	};

	typedef enum EnStatus
	{
		STATUS_OFFLINE = 0,
		STATUS_ONLINE,
		STATUS_CALLING,
		STATUS_BUSY,
		STATUS_LEAVING,
		STATUS_DND,
		STATUS_ERROR
	};

private:
	std::string m_statusImageArray[STATUS_LEN];//״̬ͼ��洢����
	IECSExternEventHandler  *m_eventHandler;//�ؼ���Ӧ�Ļص��¼�������
	eSpace::IECSEspaceApp *pIEspaceApp;
	std::string m_ucAccount;//�ؼ��󶨵�UC�˺�
	std::string m_ucUri;//�ؼ��󶨵�UC�˺Ŷ�Ӧ��uri
    std::string m_ucEmail;//�ؼ��󶨵�UC�˺Ŷ�Ӧ��email
    bool m_statusSubscribed;//�Ƿ��ѱ���ʼ���ı��λ
    std::string m_logInfo;
public:
	CESdkStatusCtrl(void);
	~CESdkStatusCtrl(void);
	
public:
    const std::string MOUDEL_NAME;
	virtual long CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType);//�ؼ������꣬����������
	long CreateCtrl(CWnd *wnd,int iLefTopX,int iLeftTopY,int iWidth,int iHeight);
	//bool InitBtnConfig(void);//���������ļ�,��ʼ��״̬ͼƬ·������
	//void InitStatusImg(const EnStatus status, std::string& imgDir, std::string& imgName);//�������ļ��г�ʼ��״̬ͼƬ·������
	bool SetStatusImg(std::string imgStrArray[],int len);//���ⲿ��������ʼ���ؼ�
	bool RefreshStatus();//����ˢ�¿ؼ�����ʾ��״̬,��Ҫ����COM�ӿ�
	void SetStatus(EnStatus status);//���ÿؼ���ǰ��ʾ��״̬
	std::string GetAccount(void) ;// ��ȡ��ǰ�ؼ���������UC�˺�
	void SetAccount(std::string& account);// ���úͿؼ��󶨵�uc�˺�
	bool InitComPtr();//��ʼ��COM���
	bool UnInitComPtr();//����COM���

	virtual void OnClickMenu(UINT uID);
	virtual void OnClick();
	virtual void OnDbClick();

	HRESULT OnEventOccured//�¼��������
		(
		eSpace::ECSEventType eventId,
		const _variant_t & param1,
		const _variant_t & param2,
		IUnknown * eventInfo
		);

	void SetTipsByStatus(EnStatus status);
    std::string getLogInfo(std::string newInfo);
};
