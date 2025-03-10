/* 定义项目名称,也是所有生成的源码文件名前缀 */

/*
 * Generated by erpcgen 1.7.4 on Wed Jul 29 15:07:49 2020.
 *
 * AUTOGENERATED - DO NOT EDIT
 */


#if !defined(_erpcdemo_h_)
#define _erpcdemo_h_

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
/*! 定义返回状态枚举类型 */
typedef enum lockErrors_t
{
    lErrorOk_c = 0,
    lErrorOutofMemory_c = 1,
    lErrorMaxError_c = 2
} lockErrors_t;

// Aliases data types declarations
typedef struct binary_t binary_t;
typedef void (*callback1_t)(int32_t a, int32_t b);

// Structures/unions data types declarations
struct binary_t
{
    uint8_t * data;
    uint32_t dataLength;
};


#endif // ERPC_TYPE_DEFINITIONS

/*! @brief DEMO identifiers */
enum _DEMO_ids
{
    kDEMO_service_id = 1,
    kDEMO_RD_demoHello_id = 1,
    kDEMO_RD_demoHello2_id = 2,
    kDEMO_RD_demoHello3_id = 3,
};

/*! @brief Core0Interface identifiers */
enum _Core0Interface_ids
{
    kCore0Interface_service_id = 2,
    kCore0Interface_myFun_id = 1,
    kCore0Interface_callback1_id = 2,
};

#if defined(__cplusplus)
extern "C" {
#endif

/*! 定义服务接口函数, 'RD_' 为服务接口函数名前缀 */
//! @name DEMO
//@{
binary_t * RD_demoHello(const binary_t * txInput);

lockErrors_t RD_demoHello2(const binary_t * txInput, binary_t * txOutput);

lockErrors_t RD_demoHello3(const binary_t * txInput, int8_t txOutput[64], int32_t * size);
//@}

//! @name Core0Interface
//@{
void myFun(const callback1_t pCallback1_t);

void callback1(int32_t a, int32_t b);
//@}

#if defined(__cplusplus)
}
#endif

#endif // _erpcdemo_h_
