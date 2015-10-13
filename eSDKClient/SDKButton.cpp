// ConfButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SDKButton.h"
#include "ESdkCtrl.h"
#include "resource.h"


// CSDKButton

IMPLEMENT_DYNAMIC(CSDKButton, CMFCButton)

CSDKButton::CSDKButton()
{
    m_pOwnerCtrl = NULL;

}

CSDKButton::~CSDKButton()
{
    m_pOwnerCtrl = NULL;
}


BEGIN_MESSAGE_MAP(CSDKButton, CMFCButton)
    ON_CONTROL_REFLECT(BN_CLICKED, &CSDKButton::OnBnClicked)
	/*ON_COMMAND_RANGE(ID_DIAL_URI, ID_DIAL_NO_PHONE, &CSDKButton::OnClickMenu)*/
	ON_COMMAND_RANGE(ID_DIAL_URI, ID_STATUSCTRL_ADD_CONTACT, &CSDKButton::OnClickMenu)
	ON_CONTROL_REFLECT(BN_DOUBLECLICKED, &CSDKButton::OnBnDoubleclicked)
END_MESSAGE_MAP()

// CSDKButton ��Ϣ�������
BOOL CSDKButton::SetImagePosRight(unsigned int bSetPos)
{
    m_bRightImage = bSetPos & 0x1;
    m_bTopImage	= (bSetPos >> 1) & 0x1;
    Invalidate(TRUE);
    //UpdateWindow();
    return TRUE;
}
BOOL CSDKButton::SetImagePath(CString cstrPath)
{
  CImage	img;
  HRESULT	ret = img.Load(cstrPath);
  if(ret == S_OK)
  {
    HBITMAP	hBitmap = img.Detach();
    if (NULL == hBitmap)
    {
      return FALSE;
    }
    SetImage(hBitmap);
    Invalidate(TRUE);
    return TRUE;
  }
  else
  {
    SetImage(IDB_BITMAP1);
    return FALSE;
  }
}
void CSDKButton::SetOwner(CESdkCtrl* pOwnerCtrl)
{
    m_pOwnerCtrl = pOwnerCtrl;
}
void CSDKButton::OnBnClicked()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    TRACE(_T("CSDKButton::OnBnClicked\n"));

    if(m_pOwnerCtrl)
    {
        m_pOwnerCtrl->OnClick();
    }
}

// ����˵���Ӧ����
void CSDKButton::OnClickMenu(UINT uID)
{
	TRACE(_T("CSDKButton::OnClickMenu\n"));

	if(m_pOwnerCtrl)
	{
		m_pOwnerCtrl->OnClickMenu(uID);
	}

}
void CSDKButton::OnBnDoubleclicked()
{
	TRACE(_T("CSDKButton::OnBnDoubleclicked\n"));

	if(m_pOwnerCtrl)
	{
		m_pOwnerCtrl->OnDbClick();
	}
}
