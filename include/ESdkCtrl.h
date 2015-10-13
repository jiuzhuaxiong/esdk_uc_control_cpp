#pragma once
#include "SDKLink.h"
#include "SDKButton.h"
#include <string>

//创建控件的类型
enum ESDK_API SDK_CTRL_TYPE
{
	DIAL_PAD_CTRL=0,//拨号盘控件类型
	DIRECT_CALL_CTRL,//直接呼叫控件
	SELECT_CALL_CTRL,//选择呼叫
	CONF_IM_CTRL,//即时消息会议
	CONF_AUDIO_CTRL,//语音会议
	IM_CTRL,//即时消息控件
	USER_STATUS_CTRL//用户状态控件
	//其他类型的控件在此进行添加
};
//控件显示的方式
enum ESDK_API SDK_CTRL_SHOW_TYPE
{
	SHOW_NODISPLAY=0,//隐藏本控件
	SHOW_ICON_TEXT_LEFT,//图标和文字左右显示
	SHOW_ICON_TEXT_UP//图标和文本上下显示

};
//ESDK接口返回码，所有控件和菜单接口统一使用使用
enum ESDK_API SDK_RET_CODE
{
	SDK_SUCCESS=0,
	SDK_ERROR,//后续根据需要逐步添加
	SDK_INVAD_PARA//参数不合法
};

//	按钮文字的字符数限制
const int		BN_TITLE_SIZE_MAX	= 20;
const int		BN_TIPS_SIZE_MAX		= 200;

class ESDK_API CESdkCtrl
{
public:
	CESdkCtrl(void);
	virtual ~CESdkCtrl(void);
public:
	virtual long CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType);//控件创建完，赋给父窗口
	virtual long SetIcon(std::string strPath);//设置控件的图标
	virtual long SetTitle(std::string strShowContent);//设置按钮上的文字
	virtual long SetTip(std::string strTip); //设置提示框信息 
	virtual long SetSize(int x,int y,int cx,int cy);//设置按钮的大小
	virtual long ShowCtrl(SDK_CTRL_SHOW_TYPE emShowType); //设置显示方式

	virtual long ChangeSize(int width,int height);//改变大小
	virtual long ChangePosition(int xPos,int yPos);//改变位置
	virtual void OnClickMenu(UINT uID);//各个控件自己实现单击控件操作
	virtual void OnClick()=0;//各个控件自己实现单击控件操作
	virtual void OnDbClick();//各个控件自己实现双击控件的操作
	virtual void SetLangID(LANGID langId);
	virtual LANGID GetLangID();
protected:
    void ImageFromIDResource(CImage& image, UINT nID, LPCTSTR lpType); //!< 从资源文件加载图片
    BOOL IsEspaceInstalled();  
    
	CSDKButton button_;
	SDK_CTRL_TYPE emtype_;
	LANGID m_langID;//语言id,用来做国际化用


};
