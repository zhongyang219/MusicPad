#pragma once

//音符结构体
struct Note
{
	int note;		//音符。1~7分别为简谱中的1~7，0：休止符
	int octave;		//升降8度。例如 0：中央C所在的8度，1:升8度，2:升两个8度，-1:降8度
	int type;		//音符类型：1：全音符，2：2分音符，4：4分音符，依此类推
	DWORD extend_half;	//音符时值延长（bit0:延长1/2; bit1:延长1/4; bit2:延长1/8, 依此类推）
	int signature;		//升降记号：0：无变化，-1：降半音，1：升半音
};


class CCommon
{
public:
	CCommon();
	~CCommon();

	static CString IntToString(int n);
};

