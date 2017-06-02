
#include "testMathMatrix.h"
#include "Diagnostic\assertion.h"
#include "cppFrameworkTesterDefines.h"
#include "TesterReport.h"

// test and example
// http://www.drdobbs.com/a-c-matrix-template-class/184403323?pgno=2
// ------------------------------------------------------------
int Test::tester_math_matrix_set_get_integer()
{
#ifdef TEST_MATH_MATRIX_GET_SET
	
	bool bSuccess = true;
	Math::matrix< int > C(2,2);

	// setter for intilization
	C(0,0) = 1;	
	C(0,1) = 2;
	C(1,0) = 3;
	C(1,1) = 4;

	if(1 != C(0,0))
	{
		Debug::Assert(false, "tester_math_matrix_set_get_integer() : Wrong item value C(0,0).");
		bSuccess = false;
	}
	if(2 != C(0,1))
	{
		Debug::Assert(false, "tester_math_matrix_set_get_integer() : Wrong item value C(0,1).");
		bSuccess = false;
	}
	if(3 != C(1,0))
	{
		Debug::Assert(false, "tester_math_matrix_set_get_integer() : Wrong item value C(1,0).");
		bSuccess = false;
	}
	if(4 != C(1,1))
	{
		Debug::Assert(false, "tester_math_matrix_set_get_integer() : Wrong item value C(1,1).");
		bSuccess = false;
	}

	Test::TesterReport::getInstance()->printSummary((true == bSuccess), "Math::matrix", "tester_math_matrix_set_get_integer()");

#endif /* TEST_MATH_MATRIX_GET_SET */
	return 0;
}
int Test::tester_math_matrix_set_get_enum()
{
#ifdef TEST_MATH_MATRIX_GET_SET
	bool bSuccess = true;
	Math::matrix< enTemplate > C(2,2);

	// setter for intilization
	C(0,0) = enBusy;	
	C(0,1) = enDefault;
	C(1,0) = enFree;
	C(1,1) = enUnknown;

	if(enBusy != C(0,0))
	{
		Debug::Assert(false, "tester_math_matrix_set_get_enum() : Wrong item value C(0,0).");
		bSuccess = false;
	}
	if(enDefault != C(0,1))
	{
		Debug::Assert(false, "tester_math_matrix_set_get_enum() : Wrong item value C(0,1).");
		bSuccess = false;
	}
	if(enFree != C(1,0))
	{
		Debug::Assert(false, "tester_math_matrix_set_get_enum() : Wrong item value C(1,0).");
		bSuccess = false;
	}
	if(enUnknown != C(1,1))
	{
		Debug::Assert(false, "tester_math_matrix_set_get_enum() : Wrong item value C(1,1).");
		bSuccess = false;
	}

	Test::TesterReport::getInstance()->printSummary((true == bSuccess), "Math::matrix", "tester_math_matrix_set_get_enum()");

#endif /* TEST_MATH_MATRIX_GET_SET */
	return 0;
}
int tester_math_matrix_set_get_class()
{
#ifdef TEST_MATH_MATRIX_GET_SET
	bool bSuccess = true;
	Math::matrix< cTemplate > C(2,2);

	// setter for intilization
	C(0,0) = cTemplate(0,0);	
	C(0,1) = cTemplate(0,1);
	C(1,0) = cTemplate(1,0);
	C(1,1) = cTemplate(1,1);

	if(0 != C(0,0).getX() && 0 != C(0,0).getX())
	{
		Debug::Assert(false, "tester_math_matrix_set_get_class() : Wrong item value C(0,0).");
		bSuccess = false;
	}
	if(1 != C(1,1).getX() && 1 != C(1,1).getX())
	{
		Debug::Assert(false, "tester_math_matrix_set_get_class() : Wrong item value C(1,1).");
		bSuccess = false;
	}

	Test::TesterReport::getInstance()->printSummary((true == bSuccess), "Math::matrix", "tester_math_matrix_set_get_class()");

#endif /* TEST_MATH_MATRIX_GET_SET */
	return 0;
}
int tester_math_matrix_manage_class()
{
#ifdef TEST_MATH_MATRIX_MANAGE_CLASS
	bool bSuccess = true;
	Math::matrix< MathMemTestClass* > M(MATH_BIG_TEST, MATH_BIG_TEST);

	for(int i = 0; i< MATH_BIG_TEST; i++)
	{
		for(int j=0;j<MATH_BIG_TEST;j++)
		{
			M(i,j) = new MathMemTestClass();
		}
	}

	for(int i = 0; i< MATH_BIG_TEST; i++)
	{
		for(int j=0;j<MATH_BIG_TEST;j++)
		{
			delete M(i,j);
		}
	}


#endif /* TEST_MATH_MATRIX_MANAGE_CLASS */
	return 0;
}
// ------------------------------------------------------------
int Test::tester_math_matrix()
{
	Test::TesterReport::getInstance()->printHeader("testing Math::matrix");

	tester_math_matrix_set_get_integer();
	tester_math_matrix_set_get_enum();
	tester_math_matrix_set_get_class();
	tester_math_matrix_manage_class();

	return 0;
}
// ------------------------------------------------------------
