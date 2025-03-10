/*
 * Generated by erpcgen 1.7.4 on Wed Jul 29 15:58:40 2020.
 *
 * AUTOGENERATED - DO NOT EDIT
 */


#if !defined(_erpcCore0_h_)
#define _erpcCore0_h_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "erpc_version.h"

#if 10704 != ERPC_VERSION_NUMBER
#error "The generated shim code version is different to the rest of eRPC code."
#endif

#if !defined(ERPC_TYPE_DEFINITIONS)
#define ERPC_TYPE_DEFINITIONS

// Enumerators data types declarations
typedef enum lockErrors_t
{
    lErrorOk_c = 0,
    lErrorOutofMemory_c = 1,
    lErrorMaxError_c = 2
} lockErrors_t;

// Aliases data types declarations
typedef struct binary_t binary_t;

// Structures/unions data types declarations
struct binary_t
{
    uint8_t * data;
    uint32_t dataLength;
};


#endif // ERPC_TYPE_DEFINITIONS

/*! @brief Core0 identifiers */
enum _Core0_ids
{
    kCore0_service_id = 1,
    kCore0_Core0_demoHello1_id = 1,
    kCore0_Core0_demoHello2_id = 2,
    kCore0_Core0_demoHello3_id = 3,
};

#if defined(__cplusplus)
extern "C" {
#endif

//! @name Core0
//@{
binary_t * Core0_demoHello1(const binary_t * txInput);

lockErrors_t Core0_demoHello2(const binary_t * txInput, binary_t * txOutput);

lockErrors_t Core0_demoHello3(const binary_t * txInput, int8_t txOutput[64], int32_t * size);
//@}

#if defined(__cplusplus)
}
#endif

#endif // _erpcCore0_h_
