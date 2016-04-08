
#include "ErnoBaseTranslator.h"

const char * getTranslatedMessage(int _erno_value) {
	
	if(ID_EPERM == _erno_value) return STR_MSG_EPERM;
	else if(ID_ENOENT == _erno_value) return STR_MSG_ENOENT;	
	else if(ID_ESRCH == _erno_value) return STR_MSG_ESRCH;
	else if(ID_EINTR == _erno_value) return STR_MSG_EINTR;
	else if(ID_EIO == _erno_value) return STR_MSG_EIO;		
	else if(ID_ENXIO == _erno_value) return STR_MSG_ENXIO;	
	else if(ID_E2BIG == _erno_value) return STR_MSG_E2BIG;	
	else if(ID_ENOEXEC == _erno_value) return STR_MSG_ENOEXEC;	
	else if(ID_EBADF == _erno_value) return STR_MSG_EBADF;	
	else if(ID_ECHILD == _erno_value) return STR_MSG_ECHILD;	
	else if(ID_EAGAIN == _erno_value) return STR_MSG_EAGAIN;	
	else if(ID_ENOMEM == _erno_value) return STR_MSG_ENOMEM;	
	else if(ID_EACCES == _erno_value) return STR_MSG_EACCES;	
	else if(ID_EFAULT == _erno_value) return STR_MSG_EFAULT;	
	else if(ID_ENOTBLK == _erno_value) return STR_MSG_ENOTBLK;	
	else if(ID_EBUSY == _erno_value) return STR_MSG_EBUSY;	
	else if(ID_EEXIST == _erno_value) return STR_MSG_EEXIST;	
	else if(ID_EXDEV == _erno_value) return STR_MSG_EXDEV;	
	else if(ID_ENODEV == _erno_value) return STR_MSG_ENODEV;	
	else if(ID_ENOTDIR == _erno_value) return STR_MSG_ENOTDIR;	
	else if(ID_EISDIR == _erno_value) return STR_MSG_EISDIR;	
	else if(ID_EINVAL == _erno_value) return STR_MSG_EINVAL;	
	else if(ID_ENFILE == _erno_value) return STR_MSG_ENFILE;	
	else if(ID_EMFILE == _erno_value) return STR_MSG_EMFILE;	
	else if(ID_ENOTTY == _erno_value) return STR_MSG_ENOTTY;	
	else if(ID_ETXTBSY == _erno_value) return STR_MSG_ETXTBSY;	
	else if(ID_EFBIG == _erno_value) return STR_MSG_EFBIG;	
	else if(ID_ENOSPC == _erno_value) return STR_MSG_ENOSPC;	
	else if(ID_ESPIPE == _erno_value) return STR_MSG_ESPIPE;	
	else if(ID_EROFS == _erno_value) return STR_MSG_EROFS;	
	else if(ID_EMLINK == _erno_value) return STR_MSG_EMLINK;	
	else if(ID_EPIPE == _erno_value) return STR_MSG_EPIPE;
	else if(ID_EDOM	 == _erno_value) return STR_MSG_EDOM;	
	else if(ID_ERANGE == _erno_value) return STR_MSG_ERANGE;
	else return STR_MSG_ERROR;
}
