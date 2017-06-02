#ifndef BASE_PROFILE_H
#define BASE_PROFILE_H

#include <string>
#include "BaseProfileGender.h"
#include "../../Timing/Date.h"

#define KEY_UNKNWON		"Unknown"

namespace Tools {

    namespace Profile {

        class BaseProfile {

            private:
                /**! Profile First name */
                std::string m_strFirstName;
                /**! Profile Last name */
                std::string m_strLastName;
                /**! Profile Surname */
                std::string m_strSurname;
                /**! actuel location */
				std::string m_strActuelLocation;
				/**! age of profile */
                int m_iAge;
				/**! Birthdate */
				Timing::Date::DateTime * m_birthdate;
				/**! Gender of profile */
				Tools::Profile::ProfileGender m_gender;

            public:
				/** constructor and destructor */
                BaseProfile();
                ~BaseProfile();

				/**! getters */
				std::string getFirstName();
				std::string getLastName();
				std::string getSurname();
				std::string getActuelLocation();
				int getAge();
				Tools::Profile::ProfileGender getGender();
				Timing::Date::DateTime * getBirthdate();

				/**! setters */
				void setFirstName(std::string _strFirstname);
				void setLastName(std::string _strLastname);
				void setSurname(std::string _strSurname);
				void setActuelLocation(std::string _strLocation);
				void setAge(int _iAge);
				void setGender(Tools::Profile::ProfileGender _gender);
				void setBirthdate(Timing::Date::DateTime * _birthdate);
        };
    };
};

#endif // BASE_PROFILE_H