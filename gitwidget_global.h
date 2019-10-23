#ifndef GITWIDGET_GLOBAL_H
#define GITWIDGET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GITWIDGET_LIBRARY)
#  define GITWIDGET_EXPORT Q_DECL_EXPORT
#else
#  define GITWIDGET_EXPORT Q_DECL_IMPORT
#endif

#endif // GITWIDGET_GLOBAL_H
