// Jorm.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Idb.h"
#include "DbBase.h"
#include "Rjson.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	DbBase * db = new DbBase("D:\\codes\\Jorm\\Sqlit3\\db.db");

	/*Rjson qObjCreate("{\"id\":9}");
	Rjson rs = db->remove("users", qObjCreate);*/

	//Rjson qObj("{\"id\": 1, \"password\":\"123\", \"username\":\"����\"}");		//\"username\": \"john\"
	Rjson qObj;		//("{")    \"username\": \"john\"    ("{\"username\":\"����\"}")
	string str[] = { "password" };   //"username", "password", "update_time"
	vector<string> fields(str, str + sizeof(str) / sizeof(str[0]));
	Rjson rsa = db->select("users", qObj, fields);			//, &qObj, fields

	cout << "1111111 the result is : " << rsa.GetJsonString() << endl;

	vector<string> keys = rsa.GetAllKeys();

	int len = keys.size();
	for (int i = 0; i < len; i++) {
		string v, key = keys[i];
		int vType;
		rsa.GetValueAndTypeByKey(key, &v, &vType);
		if (vType == 4) {
			cout << "    " << key << " is array: " << endl;
			cout << "-------------------------------------" << endl;
			vector<Rjson> arr = rsa.GetArrayByKey(key);
			for (size_t j = 0; j < arr.size(); j++) {
				Rjson al = arr[j];
				vector<string> subKeys = al.GetAllKeys();
				for (size_t k = 0; k < subKeys.size(); k++) {
					string sv;
					int nstype;
					al.GetValueAndTypeByKey(subKeys[k], &sv, &nstype);
					cout << "    " << subKeys[k] << ", value: " << sv << endl;
				}
				cout << endl;
			}
			//cout << "-------------------------------------" << endl;
		}else
			cout << "key: " << key << ", value: " << v << endl;
	}

	//cout << "22222222 the result is : " << rsa.GetJsonString() << endl;

	system("pause");
	return 0;
}

