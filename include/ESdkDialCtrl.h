#pragma once

#include "ESdkCtrl.h"
#include "SDKLink.h"



//拨号盘控件
class ESDK_API CESdkDialPadCtrl : public CESdkCtrl
{
public:
  CESdkDialPadCtrl();
  virtual ~CESdkDialPadCtrl(void);
public:
  virtual void OnClick();
};

//点击呼叫控件
class ESDK_API CESdkDialingCtrl : public CESdkCtrl
{
public:
	CESdkDialingCtrl();
	virtual ~CESdkDialingCtrl(void);
public:
	// 呼叫号码
	std::string	m_strPhone;
	// 呼叫Uri
	std::string	m_strUri;

	//设置呼叫对象的Uri和电话
	bool	SetDialTarget(std::string strUri, std::string strPhone);
	virtual void OnClick();
};

//视频呼叫控件
class ESDK_API CESdkVideoCallCtrl : public CESdkCtrl
{
public:
	CESdkVideoCallCtrl();
	virtual ~CESdkVideoCallCtrl(void);
public:
	// 呼叫号码
	std::string	m_strPhone;
	// 呼叫Uri
	std::string	m_strUri;

	//设置呼叫对象的Uri和电话
	bool	SetDialTarget(std::string strUri, std::string strPhone);
	virtual void OnClick();
};

//选择呼叫控件
class ESDK_API CESdkChooseToDialCtrl : public CESdkCtrl
{
public:
	CESdkChooseToDialCtrl();
	virtual ~CESdkChooseToDialCtrl(void);
public:
	// 联系人URI
	std::string	m_strUri;
	std::string	m_strAccount;
	// 联系人的四种电话号码
	std::string	m_strHomePhone;
	std::string	m_strOfficePhone;
	std::string	m_strMobile;
	std::string	m_strOtherPhone;
	//std::vector<std::string> m_vecPhoneNo;

	// 点击菜单响应函数
	void OnClickMenu(UINT uID);

	//设置呼叫对象的帐号
	bool	SetDialTarget(std::string strAccount);
	void OnClick();
	void OnClick2();
};

//呼叫菜单接口
long ESDK_API ShowDialPad(void);	//显示拨号盘
long ESDK_API StartDialing(void);	//语言呼叫
long ESDK_API QueryContactPhoneNo(void);	//获取联系人号码
