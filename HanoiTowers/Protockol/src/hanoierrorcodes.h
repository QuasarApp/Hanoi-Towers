#ifndef HANOIERRORCODES_H
#define HANOIERRORCODES_H
#include "dberrorcodes.h"

/**
 * @brief ErrorCodes This namesapce contains all error codes of the Heart Library.
 */
namespace ErrorCodes {

/**
 * @brief The HanoiErrorCodes enum This enum with dafault error codes.
 */
enum HanoiErrorCodes: unsigned char {
    /// User with sendet token do not have a permision to requested object.
    PermissionDenied = QH::ErrorCodes::DBErrorCodes::DBErrorCodes,

};
}


#endif // HANOIERRORCODES_H
