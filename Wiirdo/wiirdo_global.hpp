#ifndef WIIRDO_GLOBAL_HPP
#define WIIRDO_GLOBAL_HPP

#include <QtCore/qglobal.h>

#if defined(WIIRDO_LIBRARY)
#  define WIIRDOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WIIRDOSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WIIRDO_GLOBAL_HPP
