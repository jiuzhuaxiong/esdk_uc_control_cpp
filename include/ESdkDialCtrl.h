#pragma once

#include "ESdkCtrl.h"
#include "SDKLink.h"



//�����̿ؼ�
class ESDK_API CESdkDialPadCtrl : public CESdkCtrl
{
public:
  CESdkDialPadCtrl();
  virtual ~CESdkDialPadCtrl(void);
public:
  virtual void OnClick();
};

//������пؼ�
class ESDK_API CESdkDialingCtrl : public CESdkCtrl
{
public:
	CESdkDialingCtrl();
	virtual ~CESdkDialingCtrl(void);
public:
	// ���к���
	std::string	m_strPhone;
	// ����Uri
	std::string	m_strUri;

	//���ú��ж����Uri�͵绰
	bool	SetDialTarget(std::string strUri, std::string strPhone);
	virtual void OnClick();
};

//��Ƶ���пؼ�
class ESDK_API CESdkVideoCallCtrl : public CESdkCtrl
{
public:
	CESdkVideoCallCtrl();
	virtual ~CESdkVideoCallCtrl(void);
public:
	// ���к���
	std::string	m_strPhone;
	// ����Uri
	std::string	m_strUri;

	//���ú��ж����Uri�͵绰
	bool	SetDialTarget(std::string strUri, std::string strPhone);
	virtual void OnClick();
};

//ѡ����пؼ�
class ESDK_API CESdkChooseToDialCtrl : public CESdkCtrl
{
public:
	CESdkChooseToDialCtrl();
	virtual ~CESdkChooseToDialCtrl(void);
public:
	// ��ϵ��URI
	std::string	m_strUri;
	std::string	m_strAccount;
	// ��ϵ�˵����ֵ绰����
	std::string	m_strHomePhone;
	std::string	m_strOfficePhone;
	std::string	m_strMobile;
	std::string	m_strOtherPhone;
	//std::vector<std::string> m_vecPhoneNo;

	// ����˵���Ӧ����
	void OnClickMenu(UINT uID);

	//���ú��ж�����ʺ�
	bool	SetDialTarget(std::string strAccount);
	void OnClick();
	void OnClick2();
};

//���в˵��ӿ�
long ESDK_API ShowDialPad(void);	//��ʾ������
long ESDK_API StartDialing(void);	//���Ժ���
long ESDK_API QueryContactPhoneNo(void);	//��ȡ��ϵ�˺���
