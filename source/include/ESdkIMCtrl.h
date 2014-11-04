#pragma once

#include "ESdkCtrl.h"
#include "SDKLink.h"
#include <vector>


//会议控件
class ESDK_API CESdkIMCtrl : public CESdkCtrl
{
public:
    CESdkIMCtrl();
    virtual ~CESdkIMCtrl(void);
public:
    virtual long CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType);//控件创建完，赋给父窗口
    virtual void OnClick();

    long SetUCAccount(std::string ucAcc);                   //!< 设置uc账号
	void SetLangID(LANGID langId);

private:
    std::string ucAccount_;         //!< uc账号
};

//会议菜单接口
long ESDK_API StartIMConversation(std::string ucAcc);//聊天
//long ESDK_API StartAudioConf(void);//语音会议


/***add by h00169570***/
//发送短信控件
class ESDK_API CESdkSMSCtrl : public CESdkCtrl
{
public:
	CESdkSMSCtrl();
	virtual ~CESdkSMSCtrl(void);
public:
	virtual long CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType);//控件创建完，赋给父窗口
	virtual void OnClick();

	long SetUCAccount(std::vector<std::string> ucAcc,std::string groupid);                   //!< 设置uc账号
	void SetLangID(LANGID langId);

private:
	std::vector<std::string> m_ucAcc;         //!< uc账号
	std::string m_groupno;            //固定群号
};

long ESDK_API StartSMSConversation(std::vector<std::string> ucAcc,std::string Groupid);//聊天

class ESDK_API CESdkPERMCtrl : public CESdkCtrl
{
public:
	CESdkPERMCtrl();
	virtual ~CESdkPERMCtrl(void);
public:
	virtual long CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType);//控件创建完，赋给父窗口
	virtual void OnClick();
	void SetLangID(LANGID langId);

};

long ESDK_API StartPERM();//鉴权