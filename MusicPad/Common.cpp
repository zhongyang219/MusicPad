#include "stdafx.h"
#include "Common.h"


CCommon::CCommon()
{
}


CCommon::~CCommon()
{
}

CString CCommon::IntToString(int n)
{
	CString str;
	str.Format(_T("%d"), n);
	return str;
}
