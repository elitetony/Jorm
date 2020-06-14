#include "pch.h"
#include "CppUnitTest.h"
#include "../common/Idb/DbBase.h"
#include "../common/Rjson/Rjson.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitIdbTest
{
	char* dbStr = "D:\\codes\\Jorm\\Sqlit3\\db.db";
	TEST_CLASS(UnitIdbTest)
	{
	public:
		TEST_METHOD(TestDbQuerySelectStar)							//test select * from ...
		{
			DbBase* db = new DbBase(dbStr);
			Rjson qObj;		
			Rjson rs1 = db->retrieve("users", qObj);
			string v1;
			bool v_number1;
			rs1.GetValueAndTypeByKey("code", &v1, &v_number1);
			Assert::AreEqual(atoi(v1.c_str()), (int)STSUCCESS);
		}
		TEST_METHOD(TestDbQuerySelectFields)						//test select id,..... from ...
		{
			DbBase* db = new DbBase(dbStr);
			Rjson qObj;	
			string str[] = { "id","password", "username" };
			vector<string> fields(str, str + sizeof(str) / sizeof(str[0]));
			Rjson rs = db->retrieve("users", qObj, fields);

			string v;
			bool v_number;
			rs.GetValueAndTypeByKey("code", &v, &v_number);
			Assert::AreEqual(atoi(v.c_str()), (int)STSUCCESS);
		}
		TEST_METHOD(TestDbQuerySelectEqualResultExist)						//test select filed condition equal & result exist & value is chinese
		{
			DbBase* db = new DbBase(dbStr);
			Rjson qObj("{\"username\":\"����\"}");
			Rjson rs = db->retrieve("users", qObj);

			string v;
			bool v_number;
			rs.GetValueAndTypeByKey("code", &v, &v_number);
			Assert::AreEqual(atoi(v.c_str()), (int)STSUCCESS);
			//size_t dd = (rs.GetArrayByKey("data")).size();
			Assert::IsTrue(rs.GetArrayByKey("data").size() > 0);
		}
		TEST_METHOD(TestDbQuerySelectEqualResultNotExist)						//test select filed condition equal & result not exist
		{
			DbBase* db = new DbBase(dbStr);
			Rjson qObj("{\"username\":\"�����᲻����\"}");
			Rjson rs = db->retrieve("users", qObj);

			string v;
			bool v_number;
			rs.GetValueAndTypeByKey("code", &v, &v_number);
			Assert::AreEqual(atoi(v.c_str()), (int)STQUERYEMPTY);
			//size_t dd = (rs.GetArrayByKey("data")).size();
			Assert::IsTrue(rs.GetArrayByKey("data").size() == 0);
		}
		TEST_METHOD(TestDbQueryParamsError)						//test params isObject is false
		{
			DbBase* db = new DbBase(dbStr);
			Rjson qObj("{");
			Rjson rs = db->retrieve("users", qObj);

			string v;
			bool v_number;
			rs.GetValueAndTypeByKey("code", &v, &v_number);
			Assert::AreEqual(atoi(v.c_str()), (int)STPARAMERR);
		}
		TEST_METHOD(TestDbQueryFiledError)						//test select filed is not exist
		{
			DbBase* db = new DbBase(dbStr);
			Rjson qObj("{\"username1\":\"����\"}");
			Rjson rs = db->retrieve("users", qObj);

			string v;
			bool v_number;
			rs.GetValueAndTypeByKey("code", &v, &v_number);
			Assert::AreEqual(atoi(v.c_str()), (int)STDBOPERATEERR);
		}
	};
}
