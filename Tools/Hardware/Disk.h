#ifndef _HARDWARE_DISK_HELPERS_H_
#define _HARDWARE_DISK_HELPERS_H_

//////////////////////////////////////////////////////////////////////////
//      This file describes the helper functions available
//  Note: if you add a function, you HAVE TO IMPLEMENT ALL EXISTING PLATFORMS !
//////////////////////////////////////////////////////////////////////////

namespace Tools
{
    namespace Hardware
    {
        namespace Disk
        {
            //available space on drive
            double          getDiskFreeSpace( const char * _path);
            int             getDiskFreeSpaceInMo( const char * _path);
        }
    }
}

#endif //_HARDWARE_DISK_HELPERS_H_