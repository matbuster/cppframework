#ifndef ERNO_BASE_TRANSLATOR_H
#define ERNO_BASE_TRANSLATOR_H

#define	ID_EPERM		 1	/* Operation not permitted */
#define	ID_ENOENT		 2	/* No such file or directory */
#define	ID_ESRCH		 3	/* No such process */
#define	ID_EINTR		 4	/* Interrupted system call */
#define	ID_EIO                  5	/* I/O error */
#define	ID_ENXIO		 6	/* No such device or address */
#define	ID_E2BIG		 7	/* Argument list too long */
#define	ID_ENOEXEC		 8	/* Exec format error */
#define	ID_EBADF		 9	/* Bad file number */
#define	ID_ECHILD		10	/* No child processes */
#define	ID_EAGAIN		11	/* Try again */
#define	ID_ENOMEM		12	/* Out of memory */
#define	ID_EACCES		13	/* Permission denied */
#define	ID_EFAULT		14	/* Bad address */
#define	ID_ENOTBLK		15	/* Block device required */
#define	ID_EBUSY		16	/* Device or resource busy */
#define	ID_EEXIST		17	/* File exists */
#define	ID_EXDEV		18	/* Cross-device link */
#define	ID_ENODEV		19	/* No such device */
#define	ID_ENOTDIR		20	/* Not a directory */
#define	ID_EISDIR		21	/* Is a directory */
#define	ID_EINVAL		22	/* Invalid argument */
#define	ID_ENFILE		23	/* File table overflow */
#define	ID_EMFILE		24	/* Too many open files */
#define	ID_ENOTTY		25	/* Not a typewriter */
#define	ID_ETXTBSY		26	/* Text file busy */
#define	ID_EFBIG		27	/* File too large */
#define	ID_ENOSPC		28	/* No space left on device */
#define	ID_ESPIPE		29	/* Illegal seek */
#define	ID_EROFS		30	/* Read-only file system */
#define	ID_EMLINK		31	/* Too many links */
#define	ID_EPIPE		32	/* Broken pipe */
#define	ID_EDOM                 33	/* Math argument out of domain of func */
#define	ID_ERANGE		34	/* Math result not representable */

#define	STR_MSG_EPERM		 	"[EPERM] Operation not permitted"
#define	STR_MSG_ENOENT		 	"[ENOENT] No such file or directory"
#define	STR_MSG_ESRCH		 	"[ESRCH] No such process"
#define	STR_MSG_EINTR		 	"[EINTR] Interrupted system call"
#define	STR_MSG_EIO		 	"[EIO] I/O error"
#define	STR_MSG_ENXIO		 	"[ENXIO] No such device or address"
#define	STR_MSG_E2BIG		 	"[E2BIG] Argument list too long"
#define	STR_MSG_ENOEXEC		 	"[ENOEXEC] Exec format error"
#define	STR_MSG_EBADF		 	"[EBADF] Bad file number"
#define	STR_MSG_ECHILD			"[ECHILD] No child processes"
#define	STR_MSG_EAGAIN			"[EAGAIN] Try again"
#define	STR_MSG_ENOMEM			"[ENOMEM] Out of memory"
#define	STR_MSG_EACCES			"[EACCES] Permission denied"
#define	STR_MSG_EFAULT			"[EFAULT] Bad address"
#define	STR_MSG_ENOTBLK			"[ENOTBLK] Block device required"
#define	STR_MSG_EBUSY			"[EBUSY] Device or resource busy"
#define	STR_MSG_EEXIST			"[EEXIST] File exists"
#define	STR_MSG_EXDEV			"[EXDEV] Cross-device link"
#define	STR_MSG_ENODEV			"[ENODEV] No such device"
#define	STR_MSG_ENOTDIR			"[ENOTDIR] Not a directory"
#define	STR_MSG_EISDIR			"[EISDIR] Is a directory"
#define	STR_MSG_EINVAL			"[EINVAL] Invalid argument"
#define	STR_MSG_ENFILE			"[ENFILE] File table overflow"
#define	STR_MSG_EMFILE			"[EMFILE] Too many open files"
#define	STR_MSG_ENOTTY			"[ENOTTY] Not a typewriter"
#define	STR_MSG_ETXTBSY			"[ETXTBSY] Text file busy"
#define	STR_MSG_EFBIG			"[EFBIG] File too large"
#define	STR_MSG_ENOSPC			"[ENOSPC] No space left on device"
#define	STR_MSG_ESPIPE			"[ESPIPE] Illegal seek"
#define	STR_MSG_EROFS			"[EROFS] Read-only file system"
#define	STR_MSG_EMLINK			"[EMLINK] Too many links"
#define	STR_MSG_EPIPE			"[EPIPE] Broken pipe"
#define	STR_MSG_EDOM			"[EDOM]	Math argument out of domain of func"
#define	STR_MSG_ERANGE			"[ERANGE] Math result not representable"
#define STR_MSG_ERROR			"Unknwon message"

// ------------------------------------------------------------------
const char * getTranslatedMessage(int _erno_value);
// ------------------------------------------------------------------

#endif // ERNO_BASE_TRANSLATOR_H