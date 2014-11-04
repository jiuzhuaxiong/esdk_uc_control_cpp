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
	std::string m_statusImageArray[STATUS_LEN];//状态图标存储数组
	IECSExternEventHandler  *m_eventHandler;//控件对应的回调事件监听器
	eSpace::IECSEspaceApp *pIEspaceApp;
	std::string m_ucAccount;//控件绑定的UC账号
	std::string m_ucUri;//控件绑定的UC账号对应的uri
    std::string m_ucEmail;//控件绑定的UC账号对应的email
    bool m_statusSubscribed;//是否已被初始化的标记位
    std::string m_logInfo;
public:
	CESdkStatusCtrl(void);
	~CESdkStatusCtrl(void);
	
public:
    const std::string MOUDEL_NAME;
	virtual long CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType);//控件创建完，赋给父窗口
	long CreateCtrl(CWnd *wnd,int iLefTopX,int iLeftTopY,int iWidth,int iHeight);
	//bool InitBtnConfig(void);//加载配置文件,初始化状态图片路径数组
	//void InitStatusImg(const EnStatus status, std::string& imgDir, std::string& imgName);//从配置文件中初始化状态图片路径数组
	bool SetStatusImg(std::string imgStrArray[],int len);//从外部数组来初始化控件
	bool RefreshStatus();//主动刷新控件上显示的状态,需要调用COM接口
	void SetStatus(EnStatus status);//设置控件当前显示的状态
	std::string GetAccount(void) ;// 获取当前控件关联到的UC账号
	void SetAccount(std::string& account);// 设置和控件绑定的uc账号
	bool InitComPtr();//初始化COM组件
	bool UnInitComPtr();//销毁COM组件

	virtual void OnClickMenu(UINT uID);
	virtual void OnClick();
	virtual void OnDbClick();

	HRESULT OnEventOccured//事件处理程序
		(
		eSpace::ECSEventType eventId,
		const _variant_t & param1,
		const _variant_t & param2,
		IUnknown * eventInfo
		);

	void SetTipsByStatus(EnStatus status);
    std::string getLogInfo(std::string newInfo);
};
