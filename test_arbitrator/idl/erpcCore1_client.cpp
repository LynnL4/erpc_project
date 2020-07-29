/*
 * Generated by erpcgen 1.7.4 on Wed Jul 29 16:11:36 2020.
 *
 * AUTOGENERATED - DO NOT EDIT
 */


#include "erpc_client_manager.h"
#include "erpc_port.h"
#include "erpc_codec.h"
extern "C"
{
#include "erpcCore1.h"
}

#if 10704 != ERPC_VERSION_NUMBER
#error "The generated shim code version is different to the rest of eRPC code."
#endif

using namespace erpc;
using namespace std;

extern ClientManager *g_client;

//! @brief Function to write struct binary_t
static void write_binary_t_struct(erpc::Codec * codec, const binary_t * data);


// Write struct binary_t function implementation
static void write_binary_t_struct(erpc::Codec * codec, const binary_t * data)
{
    codec->writeBinary(data->dataLength, data->data);
}


//! @brief Function to read struct binary_t
static void read_binary_t_struct(erpc::Codec * codec, binary_t * data);


// Read struct binary_t function implementation
static void read_binary_t_struct(erpc::Codec * codec, binary_t * data)
{
    uint8_t * data_local;
    codec->readBinary(&data->dataLength, &data_local);
    data->data = (uint8_t *) erpc_malloc(data->dataLength * sizeof(uint8_t));
    if (data->data == NULL)
    {
        codec->updateStatus(kErpcStatus_MemoryError);
    }
    else
    {
        memcpy(data->data, data_local, data->dataLength);
    }
}



// Core1 interface Core1_demoHello1 function client shim.
binary_t * Core1_demoHello1(const binary_t * txInput)
{
    erpc_status_t err = kErpcStatus_Success;

    binary_t * result = NULL;

    // Get a new request.
    RequestContext request = g_client->createRequest(false);

    // Encode the request.
    Codec * codec = request.getCodec();

    if (codec == NULL)
    {
        err = kErpcStatus_MemoryError;
    }
    else
    {
        codec->startWriteMessage(kInvocationMessage, kCore1_service_id, kCore1_Core1_demoHello1_id, request.getSequence());

        write_binary_t_struct(codec, txInput);

        // Send message to server
        // Codec status is checked inside this function.
        g_client->performRequest(request);

        result = (binary_t *) erpc_malloc(sizeof(binary_t));
        if (result == NULL)
        {
            codec->updateStatus(kErpcStatus_MemoryError);
        }
        read_binary_t_struct(codec, result);

        err = codec->getStatus();
    }

    // Dispose of the request.
    g_client->releaseRequest(request);

    // Invoke error handler callback function
    g_client->callErrorHandler(err, kCore1_Core1_demoHello1_id);

    return result;
}

// Core1 interface Core1_demoHello2 function client shim.
lockErrors_t Core1_demoHello2(const binary_t * txInput, binary_t * txOutput)
{
    erpc_status_t err = kErpcStatus_Success;

    lockErrors_t result;

    // Get a new request.
    RequestContext request = g_client->createRequest(false);

    // Encode the request.
    Codec * codec = request.getCodec();

    if (codec == NULL)
    {
        err = kErpcStatus_MemoryError;
    }
    else
    {
        codec->startWriteMessage(kInvocationMessage, kCore1_service_id, kCore1_Core1_demoHello2_id, request.getSequence());

        write_binary_t_struct(codec, txInput);

        // Send message to server
        // Codec status is checked inside this function.
        g_client->performRequest(request);

        int32_t _tmp_local;

        read_binary_t_struct(codec, txOutput);

        codec->read(&_tmp_local);
        result = static_cast<lockErrors_t>(_tmp_local);

        err = codec->getStatus();
    }

    // Dispose of the request.
    g_client->releaseRequest(request);

    // Invoke error handler callback function
    g_client->callErrorHandler(err, kCore1_Core1_demoHello2_id);

    if (err)
    {
        return (lockErrors_t) -1;
    }

    return result;
}

// Core1 interface Core1_demoHello3 function client shim.
lockErrors_t Core1_demoHello3(const binary_t * txInput, int8_t txOutput[64], int32_t * size)
{
    erpc_status_t err = kErpcStatus_Success;

    lockErrors_t result;

    // Get a new request.
    RequestContext request = g_client->createRequest(false);

    // Encode the request.
    Codec * codec = request.getCodec();

    if (codec == NULL)
    {
        err = kErpcStatus_MemoryError;
    }
    else
    {
        codec->startWriteMessage(kInvocationMessage, kCore1_service_id, kCore1_Core1_demoHello3_id, request.getSequence());

        write_binary_t_struct(codec, txInput);

        // Send message to server
        // Codec status is checked inside this function.
        g_client->performRequest(request);

        int32_t _tmp_local;

        for (uint32_t arrayCount0 = 0; arrayCount0 < 64; ++arrayCount0)
        {
            codec->read(&txOutput[arrayCount0]);
        }

        codec->read(size);

        codec->read(&_tmp_local);
        result = static_cast<lockErrors_t>(_tmp_local);

        err = codec->getStatus();
    }

    // Dispose of the request.
    g_client->releaseRequest(request);

    // Invoke error handler callback function
    g_client->callErrorHandler(err, kCore1_Core1_demoHello3_id);

    if (err)
    {
        return (lockErrors_t) -1;
    }

    return result;
}

// Core1 interface callback function client shim.
void callback(const binary_t * txInput)
{
    erpc_status_t err = kErpcStatus_Success;

    // Get a new request.
    RequestContext request = g_client->createRequest(false);

    // Encode the request.
    Codec * codec = request.getCodec();

    if (codec == NULL)
    {
        err = kErpcStatus_MemoryError;
    }
    else
    {
        codec->startWriteMessage(kInvocationMessage, kCore1_service_id, kCore1_callback_id, request.getSequence());

        write_binary_t_struct(codec, txInput);

        // Send message to server
        // Codec status is checked inside this function.
        g_client->performRequest(request);

        err = codec->getStatus();
    }

    // Dispose of the request.
    g_client->releaseRequest(request);

    // Invoke error handler callback function
    g_client->callErrorHandler(err, kCore1_callback_id);

    return;
}
