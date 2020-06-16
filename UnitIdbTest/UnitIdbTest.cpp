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
			Rjson rs1 = db->select("users", qObj);
			string v1;
			int vType;
			rs1.GetValueAndTypeByKey("code", &v1, &vType);
			Assert::AreEqual(atoi(v1.c_str()), (int)STSUCCESS);
		}
		TEST_METHOD(TestDbQuerySelectFields)						//test select id,..... from ...
		{
			DbBase* db = new DbBase(dbStr);
			Rjson qObj;
			string str[] = { "id","password", "username" };
			vector<string> fields(str, str + sizeof(str) / sizeof(str[0]));
			Rjson rs = db->select("users", qObj, fields);

			string v;
			int vType;
			rs.GetValueAndTypeByKey("code", &v, &vType);
			Assert::AreEqual(atoi(v.c_str()), (int)STSUCCESS);
		}
		TEST_METHOD(TestDbQuerySelectEqualResultExist)						//test select filed condition equal & result exist & value is chinese
		{
			DbBase* db = new DbBase(dbStr);
			Rjson qObj("{\"username\":\"张三\"}");
			Rjson rs = db->select("users", qObj);

			string v;
			int vType;
			rs.GetValueAndTypeByKey("code", &v, &vType);
			Assert::AreEqual(atoi(v.c_str()), (int)STSUCCESS);
			//size_t dd = (rs.GetArrayByKey("data")).size();
			Assert::IsTrue(rs.GetArrayByKey("data").size() > 0);
		}
		TEST_METHOD(TestDbQuerySelectEqualResultNotExist)						//test select filed condition equal & result not exist
		{
			DbBase* db = new DbBase(dbStr);
			Rjson qObj("{\"username\":\"张三丰不存在\"}");
			Rjson rs = db->select("users", qObj);

			string v;
			int vType;
			rs.GetValueAndTypeByKey("code", &v, &vType);
			Assert::AreEqual(atoi(v.c_str()), (int)STQUERYEMPTY);
			//size_t dd = (rs.GetArrayByKey("data")).size();
			Assert::IsTrue(rs.GetArrayByKey("data").size() == 0);
		}
		TEST_METHOD(TestDbQueryParamsError)						//test params isObject is false
		{
			DbBase* db = new DbBase(dbStr);
			Rjson qObj("{");
			Rjson rs = db->select("users", qObj);

			string v;
			int vType;
			rs.GetValueAndTypeByKey("code", &v, &vType);
			Assert::AreEqual(atoi(v.c_str()), (int)STPARAMERR);
		}
		TEST_METHOD(TestDbQueryFiledError)						//test select filed is not exist
		{
			DbBase* db = new DbBase(dbStr);
			Rjson qObj("{\"username1\":\"张三\"}");
			Rjson rs = db->select("users", qObj);

			string v;
			int vType;
			rs.GetValueAndTypeByKey("code", &v, &vType);
			Assert::AreEqual(atoi(v.c_str()), (int)STDBOPERATEERR);
		}
		TEST_METHOD(TestDbCURDRecord)						//test curd
		{
			DbBase* db = new DbBase(dbStr);
			Rjson qObj("{\"username\":\"麻子测试\", \"password\":1298}");
			Rjson rs = db->create("users", qObj);

			string v;
			int vType;
			rs.GetValueAndTypeByKey("code", &v, &vType);
			Assert::AreEqual(atoi(v.c_str()), (int)STSUCCESS);				//assert create

			v = "";
			rs = db->select("users", Rjson("{\"username\":\"麻子测试\"}"));
			rs.GetValueAndTypeByKey("code", &v, &vType);
			Assert::AreEqual(atoi(v.c_str()), (int)STSUCCESS);				//assert query =

			vector<Rjson> rsData = rs.GetArrayByKey("data");
			Rjson data0 = rsData[0];
			string id = "";
			data0.GetValueAndTypeByKey("id", &id, &vType);

			Rjson qUp("{\"username\":\"麻子修改\"}");
			rs = db->update("users", qUp);

			v = "";
			rs.GetValueAndTypeByKey("code", &v, &vType);
			Assert::AreEqual(atoi(v.c_str()), (int)STPARAMERR);				//assert update no id

			qUp.AddValueInt("id", atoi(id.c_str()));
			qUp.AddValueString("password", "123321");
			rs = db->update("users", qUp);

			v = "";
			rs.GetValueAndTypeByKey("code", &v, &vType);
			Assert::AreEqual(atoi(v.c_str()), (int)STSUCCESS);				//assert update with id

			

			string sss = "{\"id\":" + id + "}";
			Rjson rData(sss);
			//rData.AddValueInt("id", atoi(v.c_str()));
			rs = db->remove("users", rData);
			v = "";
			rs.GetValueAndTypeByKey("code", &v, &vType);
			Assert::AreEqual(atoi(v.c_str()), (int)STSUCCESS);				//assert remove

		}
	};
}
