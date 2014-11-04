#pragma once
#include "SDKLink.h"
#include "SDKButton.h"
#include <string>

//�����ؼ�������
enum ESDK_API SDK_CTRL_TYPE
{
	DIAL_PAD_CTRL=0,//�����̿ؼ�����
	DIRECT_CALL_CTRL,//ֱ�Ӻ��пؼ�
	SELECT_CALL_CTRL,//ѡ�����
	CONF_IM_CTRL,//��ʱ��Ϣ����
	CONF_AUDIO_CTRL,//��������
	IM_CTRL,//��ʱ��Ϣ�ؼ�
	USER_STATUS_CTRL//�û�״̬�ؼ�
	//�������͵Ŀؼ��ڴ˽������
};
//�ؼ���ʾ�ķ�ʽ
enum ESDK_API SDK_CTRL_SHOW_TYPE
{
	SHOW_NODISPLAY=0,//���ر��ؼ�
	SHOW_ICON_TEXT_LEFT,//ͼ�������������ʾ
	SHOW_ICON_TEXT_UP//ͼ����ı�������ʾ

};
//ESDK�ӿڷ����룬���пؼ��Ͳ˵��ӿ�ͳһʹ��ʹ��
enum ESDK_API SDK_RET_CODE
{
	SDK_SUCCESS=0,
	SDK_ERROR,//����������Ҫ�����
	SDK_INVAD_PARA//�������Ϸ�
};

//	��ť���ֵ��ַ�������
const int		BN_TITLE_SIZE_MAX	= 20;
const int		BN_TIPS_SIZE_MAX		= 200;

class ESDK_API CESdkCtrl
{
public:
	CESdkCtrl(void);
	virtual ~CESdkCtrl(void);
public:
	virtual long CreateCtrl(CWnd *wnd ,SDK_CTRL_TYPE emCtrlType);//�ؼ������꣬����������
	virtual long SetIcon(std::string strPath);//���ÿؼ���ͼ��
	virtual long SetTitle(std::string strShowContent);//���ð�ť�ϵ�����
	virtual long SetTip(std::string strTip); //������ʾ����Ϣ 
	virtual long SetSize(int x,int y,int cx,int cy);//���ð�ť�Ĵ�С
	virtual long ShowCtrl(SDK_CTRL_SHOW_TYPE emShowType); //������ʾ��ʽ

	virtual long ChangeSize(int width,int height);//�ı��С
	virtual long ChangePosition(int xPos,int yPos);//�ı�λ��
	virtual void OnClickMenu(UINT uID);//�����ؼ��Լ�ʵ�ֵ����ؼ�����
	virtual void OnClick()=0;//�����ؼ��Լ�ʵ�ֵ����ؼ�����
	virtual void OnDbClick();//�����ؼ��Լ�ʵ��˫���ؼ��Ĳ���
	virtual void SetLangID(LANGID langId);
	virtual LANGID GetLangID();
protected:
    void ImageFromIDResource(CImage& image, UINT nID, LPCTSTR lpType); //!< ����Դ�ļ�����ͼƬ
    BOOL IsEspaceInstalled();  
    
	CSDKButton button_;
	SDK_CTRL_TYPE emtype_;
	LANGID m_langID;//����id,���������ʻ���


};
