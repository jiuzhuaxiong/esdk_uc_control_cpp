#pragma once

#include "ESdkCtrl.h"
#include "SDKLink.h"



//����ؼ�
class ESDK_API CESdkConfCtrl : public CESdkCtrl
{
public:
  CESdkConfCtrl();
  virtual ~CESdkConfCtrl(void);
public:
  virtual void OnClick();
  virtual long CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType);//�ؼ������꣬����������
};

//����˵��ӿ�
long ESDK_API StartIMConf(void);//Ⱥ���������
long ESDK_API StartAudioConf(void);//��������
long ESDK_API StartConfMgr(void);//�������
