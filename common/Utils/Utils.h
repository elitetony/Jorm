#pragma once
#include <windows.h>
#include "../Rjson/Rjson.h"
#include <sstream>
#include "GlobalConstants.h"

class Utils {
public:
	static Rjson MakeJsonObjectForFuncReturn(StatusCodes code) {
		Rjson rs;
		rs.AddValueInt("code", code);
		rs.AddValueString("msg", STCODEMESSAGES[code]);
		return rs;
	}

	static char* U8ToUnicode(char* szU8)
	{
		//UTF8 to Unicode
		//Ԥת�����õ�����ռ�Ĵ�С
		int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
		//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�
		wchar_t* wszString = new wchar_t[wcsLen + 1];
		//ת��
		::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
		//������'\0'
		wszString[wcsLen] = '\0';

		char* m_char;
		int len = WideCharToMultiByte(CP_ACP, 0, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
		m_char = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, wszString, wcslen(wszString), m_char, len, NULL, NULL);
		m_char[len] = '\0';
		return m_char;
	}

	static char* UnicodeToU8(string str)
	{
		wchar_t* wszString = multiByteToWideChar(str);
		// unicode to UTF8
		//Ԥת�����õ�����ռ�Ĵ�С������õĺ��������������෴
		int u8Len = ::WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
		//ͬ�ϣ�����ռ�Ҫ��'\0'�����ռ�
		//UTF8��Ȼ��Unicode��ѹ����ʽ����Ҳ�Ƕ��ֽ��ַ��������Կ�����char����ʽ����
		char* szU8 = new char[u8Len + 1];
		//ת��
		//unicode���Ӧ��strlen��wcslen
		::WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), szU8, u8Len, NULL, NULL);
		//������'\0'
		szU8[u8Len] = '\0';
		return szU8;
	}


	static wchar_t* multiByteToWideChar(const string& pKey)
	{
		char* pCStrKey = (char *)pKey.c_str();
		//��һ�ε��÷���ת������ַ������ȣ�����ȷ��Ϊwchar_t*���ٶ����ڴ�ռ�
		int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
		wchar_t* pWCStrKey = new wchar_t[pSize];
		//�ڶ��ε��ý����ֽ��ַ���ת����˫�ֽ��ַ���
		MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
		return pWCStrKey;
	}

};

