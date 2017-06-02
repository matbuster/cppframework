
#include "Math/Matrix.hpp"

#define MAX_ROWS			10
#define MAX_COLUMNS			12
#define MATH_TEST_STR_HUGE	8092
#define MATH_BIG_TEST		256

// -----------------------------------------------------------
// test configuration
//define TEST_MATH_MATRIX_FULL
#ifdef TEST_MATH_MATRIX_FULL

#define TEST_MATH_MATRIX_GET_SET
#define TEST_MATH_MATRIX_MANAGE_CLASS

#else

#define TEST_MATH_MATRIX_GET_SET
//define TEST_MATH_MATRIX_MANAGE_CLASS

#endif
// ------------------------------------------------------------
/** template enum definition
 */
typedef enum {
	
	enDefault = 0,
	enBusy,
	enFree,
	enUnknown

} enTemplate;
// ------------------------------------------------------------
class cTemplate {
private:
	int m_x;
	int m_y;
public:
	cTemplate(){m_x=0;m_y=0;}
	cTemplate(int x, int y){m_x=x;m_y=y;}
	~cTemplate(){}
	int getX(){return m_x;}
	int getY(){return m_y;}
};
// -----------------------------------------------------------
class MathMemTestClass {
private:
	char cTemp[MATH_TEST_STR_HUGE];
public:
	MathMemTestClass() {memset(cTemp, 0x00, MATH_TEST_STR_HUGE);}
	~MathMemTestClass() {}
};
namespace Test{
	// ------------------------------------------------------------
	int tester_math_matrix_set_get_integer();
	int tester_math_matrix_set_get_enum();
	// ------------------------------------------------------------
	int tester_math_matrix();
	// ------------------------------------------------------------
}