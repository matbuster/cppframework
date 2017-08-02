#ifndef FILE_FOLDER_INFOS_H
#define FILE_FOLDER_INFOS_H

// framework includes
#include "../../Timing/Date.h"

// general includes
#include <string>

#define KEY_DIRECTORY	"<DIR>"
#define KEY_FILE		"<FIL>"

namespace Tools {
	
	namespace Files {

		/**! \brief enumeration associated to the type of file folder informations */
		typedef enum {
			
			file,
			folder,
			link

		} FileFolderType;

		/** \brief FileFolderInfos is
		 */
		class FileFolderInfos {

		private:
			/**! path of the target file */
			std::string m_strFilepath;

			/**! name of the target file */
			std::string m_strFilename;

			/**! file has read permission */
			bool m_bReadPermission;

			/**! file has write permission*/
			bool m_bWritePermission;

			/**! file has exec permission*/
			bool m_bExexPermission;

			/**! type file or folder */
			Tools::Files::FileFolderType m_eType;

			/**! date for creation */
			Timing::Date::DateTime * m_creationDateInfos;

			/**! formmated creation time */
			std::string m_strFormattedCreationDate;

			/**! formatted modification date (temporary?) */
			std::string m_strFormattedModificationDate;

			/**! formmated last access time */
			std::string m_strFormatedLastAccesDate;

			/**! value of file size */
			long m_lFileSize;

		public:
			/**! constructor and destructor */
			FileFolderInfos();
			~FileFolderInfos();

			/**! getter on the file path (no filename in file path) 
			 * \return file path
			 */
			std::string getFilepath();

			/**! setter on the filepath
			 * \param [in] _strfilepath : file path
			 */
			void setFilepath(std::string _strfilepath);

			/**! getter on the file name */
			std::string getFilename();

			/**! setter on the file name */
			void setFilename(std::string _strfilename);

			/**! getter on the full name of file path and file
			 * \return full path
			 */
			std::string getFullName();

			/**! getter on the creation date information 
			 * \return creation date information
			 */
			Timing::Date::DateTime * getCreationDateInformations();

			/**! setter on the creation date information
			 * \param [in] creation date information
			 */
			void setCreationDateInformation(Timing::Date::DateTime * date);

			/**! getter on the file size
			 * \return file size
			 */
			long getFileSize();

			/**! setter on the file size
			 * \param [in] _lSize : value to update
			 */
			void setFileSize(long _lSize);

			/**! getter on the keyword associated to the enumeration
			 * \return keyword for file infos folder
			 */
			std::string getTypeKeyword();

			/**! getter on the type value
			 * \return type value
			 */
			Tools::Files::FileFolderType getType();

			/**! setter on the type value
			 * \param [in] type value
			 */
			void setType(Tools::Files::FileFolderType eType);

			/**! getter on the cration date
			 * \return string associated to the cration date
			 */
			std::string getCreationDate();

			/**! getter on the formatted string for modification date
			 * \return string associated to the modification date
			 */
			std::string getModificationDate();

			/**! getter on the last creation date
			 * \return string associated to the last cration date 
			 */
			std::string getLastAccessDate();

			/**! setter on the string value of the modification date
			 * \param [in] _strModificationDate : value of the modification date
			 */
			void setFormattedModificationDate(std::string _strModificationDate);

			/**! setter on the string value of the creation date
			 * \param [in] _strCreationDate : value of the creation date
			 */
			void setFormattedCreationDate(std::string _strCreationDate);

			/**! setter on the string value of the last access date
			 * \param [in] _strLastAccessDate : value of the last access date
			 */
			void setFormattedLastAccessDate(std::string _strLastAccessDate);

			/**! getter on the reading permission
			 * \return read permission 
			 */
			bool isReadingAllowed();

			/**! setter on the reading permission
			 * \param [in] _bValue : reading permission value
			 */
			void setReadingAllowedProperty(bool _bValue);

			/**! getter on the writing permission
			 * \return writing permission
			 */
			bool isWritingAllowed();
			
			/**! setter on the writing permission
			 * \param [in] _bValue : writing permission value
			 */
			void setWritingAllowedProperty(bool _bValue);

			/**! getter on the execution permission
			 * \return exec permission
			 */
			bool isExecAllowed();

			/**! setter on the exec permission
			 * \param [in] _bValue : exec permission value
			 */
			void setExecAllowedProperty(bool _bValue);
		};
	};
};

#endif // FILE_FOLDER_INFOS_H