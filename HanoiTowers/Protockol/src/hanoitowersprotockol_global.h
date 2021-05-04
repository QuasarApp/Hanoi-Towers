#ifndef HANOITOWERSPROTOCOL_GLOBAL_H
#define HANOITOWERSPROTOCOL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HANOITOWERSPROTOCOL_LIBRARY)
#  define HANOITOWERSPROTOCOL_EXPORT Q_DECL_EXPORT
#else
#  define HANOITOWERSPROTOCOL_EXPORT Q_DECL_IMPORT
#endif

#define DEFAULT_HANOI_ADDRESS "127.0.0.1"
#define DEFAULT_HANOI_PORT 7770

#endif // HANOITOWERSPROTOCOL_GLOBAL_H
