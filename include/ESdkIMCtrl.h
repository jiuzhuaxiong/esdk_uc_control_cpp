#pragma once

#include "ESdkCtrl.h"
#include "SDKLink.h"
#include <vector>


//����ؼ�
class ESDK_API CESdkIMCtrl : public CESdkCtrl
{
public:
    CESdkIMCtrl();
    virtual ~CESdkIMCtrl(void);
public:
    virtual long CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType);//�ؼ������꣬����������
    virtual void OnClick();

    long SetUCAccount(std::string ucAcc);                   //!< ����uc�˺�
	void SetLangID(LANGID langId);

private:
    std::string ucAccount_;         //!< uc�˺�
};

//����˵��ӿ�
long ESDK_API StartIMConversation(std::string ucAcc);//����
//long ESDK_API StartAudioConf(void);//��������


/***add by h00169570***/
//���Ͷ��ſؼ�
class ESDK_API CESdkSMSCtrl : public CESdkCtrl
{
public:
	CESdkSMSCtrl();
	virtual ~CESdkSMSCtrl(void);
public:
	virtual long CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType);//�ؼ������꣬����������
	virtual void OnClick();

	long SetUCAccount(std::vector<std::string> ucAcc,std::string groupid);                   //!< ����uc�˺�
	void SetLangID(LANGID langId);

private:
	std::vector<std::string> m_ucAcc;         //!< uc�˺�
	std::string m_groupno;            //�̶�Ⱥ��
};

long ESDK_API StartSMSConversation(std::vector<std::string> ucAcc,std::string Groupid);//����

class ESDK_API CESdkPERMCtrl : public CESdkCtrl
{
public:
	CESdkPERMCtrl();
	virtual ~CESdkPERMCtrl(void);
public:
	virtual long CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType);//�ؼ������꣬����������
	virtual void OnClick();
	void SetLangID(LANGID langId);

};

long ESDK_API StartPERM();//��Ȩ