#pragma once
#include "stdafx.h"
#include "SDKLink.h"
#include <string>

// CSDKButton
class CESdkCtrl;
class CSDKButton : public CMFCButton
{
	DECLARE_DYNAMIC(CSDKButton)

public:
	CSDKButton();
	virtual ~CSDKButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
  BOOL SetImagePosRight(unsigned int bSetPos);
  BOOL SetImagePath(CString cstrPath);
  void SetOwner(CESdkCtrl* pOwnerCtrl);
public:
  afx_msg void OnBnClicked();
  afx_msg void OnClickMenu(UINT uID);
  afx_msg void OnBnDoubleclicked();
private:
  CESdkCtrl* m_pOwnerCtrl;

};


