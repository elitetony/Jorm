// Jorm.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Idb.h"
#include "DbBase.h"
#include "rapidjson/document.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	DbBase * db = new DbBase("D:\\codes\\Jorm\\Sqlit3\\db.db");
	Document qObj;
	qObj.Parse("{}");
	string str[] = { "id","password", "username" };
	vector<string> fields(str, str + sizeof(str) / sizeof(str[0]));
	Document rs = db->retrieve("users"); //, &qObj, fields

	StringBuffer strBuffer;
	Writer<StringBuffer> writer(strBuffer);
	rs.Accept(writer);

	cout << "the result is : " << strBuffer.GetString() << endl;

	system("pause");
	return 0;
}

