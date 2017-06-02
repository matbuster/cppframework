/**
 * \file 		Date.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef DATE_H
#define DATE_H

#define DATE_OK	0
#define DATE_KO	1

#include <time.h> 

namespace Timing {
	
	namespace Date {

		class DateTime {
		
		private:
			time_t m_rawtime;
			char m_buffer [80];

			int m_iYear;
			int m_iMonth;
			/** Day of the week, 1 to 7 from monday to Sunday*/
			int m_iDayOfTheWeek;
			int m_iDay;
			int m_iHour;
			int m_iMinutes;
			int m_iSeconds;
			int m_iMillesconds;

		public:
			/** constructor and destructor */
			DateTime();
			~DateTime();

			/** getters */
			int getYear() const;
			int getMonth() const;
			int getDay() const;
			int getHour() const;
			int getMinutes() const;
			int getSeconds() const;
			int getMilliseconds() const;
			const char * getFormated(const char * _format);

			/** setters */
			void setDate(int _iYear, int _iMonth, int _iDay);
			void setTime(int _iHour, int _iMinutes, int _iSeconds);
			void setTime(int _iHour, int _iMinutes, int _iSeconds, int _iMilliseconds);
						

			/**! operators */
			DateTime& operator=(DateTime const & /*second*/) {return *this;};

			/**! getter on the current datetime */
			static DateTime * Now();
		};

		/**! datetimes operators */
		bool operator< (DateTime const &d1, DateTime const &d2); 
	
		/** return a date string value to prefix a file name
		 * example : YYYY_MM_DD_HH_MM_SS_
		 */
		long GetStringDateForFile(char * _pOutDateFormatted, int _iSizeBuffer, int * _iDateSize);

	};
};
#endif /* DATE_H */