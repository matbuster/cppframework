#include "Disk.h"
#include <Windows.h>

namespace Tools
{
    namespace Hardware
    {
        namespace Disk
        {
            //note : this function must not get out of this file !
            static ULONGLONG     internal_getDiskFreeSpace(const char * _path)
            {
                ULARGE_INTEGER uliFreeBytesAvailableToCaller;
                ULARGE_INTEGER uliTotalNumberOfBytes;
                ULARGE_INTEGER uliTotalNumberOfFreeBytes;

                if(::GetDiskFreeSpaceEx( (LPCWSTR)_path ,
                    &uliFreeBytesAvailableToCaller,
                    &uliTotalNumberOfBytes,
                    &uliTotalNumberOfFreeBytes) == TRUE)
                {
                    return uliTotalNumberOfFreeBytes.QuadPart;
                }
                else
                    return 0;
            }

            //returns the free disk space in bytes
            double  getDiskFreeSpace(const char * _path)
            {
                return (double) internal_getDiskFreeSpace(_path);
            }

            //returns the free disk space in Mo
            int   getDiskFreeSpaceInMo(const char * _path)
            {
                return (int) (internal_getDiskFreeSpace(_path) / (1024 * 1024)) ;

            }
        }
    }
}