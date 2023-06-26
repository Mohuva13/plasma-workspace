/* config-workspace.h.  Generated by cmake from config-workspace.h.cmake  */

/* Defines if your system has the libfontconfig library */
#cmakedefine HAVE_FONTCONFIG 1

/* Define to 1 if you have the <sys/time.h> header file. */
#cmakedefine HAVE_SYS_TIME_H 1

/* place where plasma-frameworks things are installed */
#define PLASMA_RELATIVE_DATA_INSTALL_DIR "@PLASMA_RELATIVE_DATA_INSTALL_DIR@"

#define WORKSPACE_VERSION_STRING "${PROJECT_VERSION}"
#define PROJECT_VERSION_MAJOR ${PROJECT_VERSION_MAJOR}
#define PROJECT_VERSION_MINOR ${PROJECT_VERSION_MINOR}
#define PROJECT_VERSION_PATCH ${PROJECT_VERSION_PATCH}

#cmakedefine01 UBUNTU_LOCALE
#cmakedefine01 GLIBC_LOCALE_AUTO
#cmakedefine01 GLIBC_LOCALE_GENERATED

#if defined(GLIBC_LOCALE_AUTO) || defined(GLIBC_LOCALE_GENERATED)
#define GLIBC_LOCALE
#endif
