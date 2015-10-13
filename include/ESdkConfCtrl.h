#pragma once

#include "ESdkCtrl.h"
#include "SDKLink.h"



//会议控件
class ESDK_API CESdkConfCtrl : public CESdkCtrl
{
public:
  CESdkConfCtrl();
  virtual ~CESdkConfCtrl(void);
public:
  virtual void OnClick();
  virtual long CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType);//控件创建完，赋给父窗口
};

//会议菜单接口
long ESDK_API StartIMConf(void);//群组聊天会议
long ESDK_API StartAudioConf(void);//语音会议
long ESDK_API StartConfMgr(void);//会议管理
