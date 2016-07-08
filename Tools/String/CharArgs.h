#ifndef CHAR_ARGS_H
#define CHAR_ARGS_H

#ifdef WIN32

namespace Tools {

	namespace String {
		
		class CharArgs {
			
		private:
			char **l_argn;
			int arg_num;

			/** getter on the _TCHAR string len
			 * @return len of string
			 */
			int wstrlen(_TCHAR * wstr);

			/** Allocate char string and copy TCHAR->char->string
			 */
			char *wstrdup(_TCHAR *wSrc);

			CharArgs & operator=(const CharArgs&); // does not allow assignment of class
			CharArgs(const CharArgs&); // does not allow copy construction

		public:
			CharArgs(int argcc, _TCHAR* argv[]);
			~CharArgs();

			const char * operator[](const int &i)
			{
				if (i < arg_num) return l_argn[i]; else return 0;
			}

			const int argc() { return arg_num; }
		};			
	};
};

#endif // WIN32

#endif // CHAR_ARGS_H