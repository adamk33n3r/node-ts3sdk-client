/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "capture.h"
#include "channel.h"
#include "client.h"
#include "clientlib.h"
#include "connection.h"
#include "error.h"
#include "event.h"
#include "filetransfer.h"
#include "identity.h"
#include "log.h"
#include "playback.h"
#include "server.h"

/**
 * Initializes the Node.js addon.
 */
NAN_MODULE_INIT(Init)
{
    // clientlib
    Nan::SetMethod(target, "initClientLib",             ClientLib::Init);
    Nan::SetMethod(target, "destroyClientLib",          ClientLib::Destroy);
    Nan::SetMethod(target, "getClientLibVersion",       ClientLib::GetVersion);
    Nan::SetMethod(target, "getClientLibVersionNumber", ClientLib::GetVersionNumber);
    
    // connection
    Nan::SetMethod(target, "spawnNewServerConnectionHandler", Connection::Init);
    Nan::SetMethod(target, "destroyServerConnectionHandler",  Connection::Destroy);
    Nan::SetMethod(target, "startConnection",                 Connection::Start);
    Nan::SetMethod(target, "startConnectionWithChannelID",    Connection::StartWithChannelID);
    Nan::SetMethod(target, "stopConnection",                  Connection::Stop);
    Nan::SetMethod(target, "getConnectionStatus",             Connection::GetStatus);
    Nan::SetMethod(target, "getServerConnectionHandlerList",  Connection::GetList);
    Nan::SetMethod(target, "getConnectionVariableAsUInt64",   Connection::GetInfoVarAsUInt64);
    Nan::SetMethod(target, "getConnectionVariableAsDouble",   Connection::GetInfoVarAsDouble);
    Nan::SetMethod(target, "getConnectionVariableAsString",   Connection::GetInfoVarAsString);
    Nan::SetMethod(target, "cleanUpConnectionInfo",           Connection::CleanupInfo);
    
    // identity
    Nan::SetMethod(target, "createIdentity",                   Identity::Create);
    Nan::SetMethod(target, "identityStringToUniqueIdentifier", Identity::GetUID);
    
    // capture
    Nan::SetMethod(target, "openCaptureDevice",             Capture::OpenDevice);
    Nan::SetMethod(target, "closeCaptureDevice",            Capture::CloseDevice);
    Nan::SetMethod(target, "activateCaptureDevice",         Capture::ActivateDevice);
    Nan::SetMethod(target, "setLocalTestMode",              Capture::SetLocalTestMode);
    Nan::SetMethod(target, "getCaptureDeviceList",          Capture::ListDevices);
    Nan::SetMethod(target, "getCurrentCaptureDeviceName",   Capture::GetCurrentDevice);
    Nan::SetMethod(target, "getCurrentCaptureMode",         Capture::GetCurrentMode);
    Nan::SetMethod(target, "getCaptureModeList",            Capture::ListModes);
    Nan::SetMethod(target, "getPreProcessorInfoValueFloat", Capture::GetInfoValue);
    Nan::SetMethod(target, "getPreProcessorConfigValue",    Capture::GetConfigValue);
    Nan::SetMethod(target, "setPreProcessorConfigValue",    Capture::SetConfigValue);
    Nan::SetMethod(target, "getEncodeConfigValue",          Capture::GetEncoderValue);
    
    // playback
    Nan::SetMethod(target, "openPlaybackDevice",               Playback::OpenDevice);
    Nan::SetMethod(target, "closePlaybackDevice",              Playback::CloseDevice);
    Nan::SetMethod(target, "initiateGracefulPlaybackShutdown", Playback::ShutdownDevice);
    Nan::SetMethod(target, "playWaveFile",                     Playback::PlayWaveFile);
    Nan::SetMethod(target, "getPlaybackDeviceList",            Playback::ListDevices);
    Nan::SetMethod(target, "getCurrentPlaybackDeviceName",     Playback::GetCurrentDevice);
    Nan::SetMethod(target, "getCurrentPlaybackMode",           Playback::GetCurrentMode);
    Nan::SetMethod(target, "getPlaybackModeList",              Playback::ListModes);
    Nan::SetMethod(target, "getPlaybackConfigValueAsFloat",    Playback::GetConfigValue);
    Nan::SetMethod(target, "setPlaybackConfigValue",           Playback::SetConfigValue);
    
    // client
    Nan::SetMethod(target, "getClientID",                   Client::GetOwnID);
    Nan::SetMethod(target, "getClientSelfVariableAsInt",    Client::GetOwnVarAsInt);
    Nan::SetMethod(target, "getClientSelfVariableAsString", Client::GetOwnVarAsString);
    Nan::SetMethod(target, "setClientSelfVariableAsInt",    Client::SetOwnVarAsInt);
    Nan::SetMethod(target, "setClientSelfVariableAsString", Client::SetOwnVarAsString);
    Nan::SetMethod(target, "getClientList",                 Client::GetList);
    Nan::SetMethod(target, "requestClientIDs",              Client::GetClones);
    Nan::SetMethod(target, "getChannelOfClient",            Client::GetChannelID);
    Nan::SetMethod(target, "requestConnectionInfo",         Client::GetConectionInfo);
    Nan::SetMethod(target, "requestClientVariables",        Client::GetVars);
    Nan::SetMethod(target, "getClientVariableAsInt",        Client::GetVarAsInt);
    Nan::SetMethod(target, "getClientVariableAsUInt64",     Client::GetVarAsUInt64);
    Nan::SetMethod(target, "getClientVariableAsString",     Client::GetVarAsString);
    Nan::SetMethod(target, "flushClientSelfUpdates",        Client::FlushUpdates);
    Nan::SetMethod(target, "requestMuteClients",            Client::Mute);
    Nan::SetMethod(target, "requestUnmuteClients",          Client::Unmute);
    Nan::SetMethod(target, "requestClientMove",             Client::Move);
    Nan::SetMethod(target, "requestClientKickFromChannel",  Client::KickFromChannel);
    Nan::SetMethod(target, "requestClientKickFromServer",   Client::KickFromServer);
    Nan::SetMethod(target, "requestSendPrivateTextMsg",     Client::SendMessage);
    Nan::SetMethod(target, "startVoiceRecording",           Client::SetRecordingStatus);
    Nan::SetMethod(target, "stopVoiceRecording",            Client::UnsetRecordingStatus);
    Nan::SetMethod(target, "requestClientSetWhisperList",   Client::SetWhisperList);
    Nan::SetMethod(target, "allowWhispersFrom",             Client::AllowWhispersFrom);
    Nan::SetMethod(target, "removeFromAllowedWhispersFrom", Client::PreventWhispersFrom);
    Nan::SetMethod(target, "setClientVolumeModifier",       Client::SetVolumeModifier);

    // channel
    Nan::SetMethod(target, "getChannelList",               Channel::GetList);
    Nan::SetMethod(target, "getChannelClientList",         Channel::GetClients);
    Nan::SetMethod(target, "getChannelIDFromChannelNames", Channel::GetID);
    Nan::SetMethod(target, "getParentChannelOfChannel",    Channel::GetPID);
    Nan::SetMethod(target, "getChannelEmptySecs",          Channel::GetSecondsEmpty);
    Nan::SetMethod(target, "requestChannelDescription",    Channel::GetDescription);
    Nan::SetMethod(target, "getChannelVariableAsInt",      Channel::GetVarAsInt);
    Nan::SetMethod(target, "getChannelVariableAsUInt64",   Channel::GetVarAsUInt64);
    Nan::SetMethod(target, "getChannelVariableAsString",   Channel::GetVarAsString);
    Nan::SetMethod(target, "setChannelVariableAsInt",      Channel::SetVarAsInt);
    Nan::SetMethod(target, "setChannelVariableAsUInt64",   Channel::SetVarAsUInt64);
    Nan::SetMethod(target, "setChannelVariableAsString",   Channel::SetVarAsString);
    Nan::SetMethod(target, "flushChannelCreation",         Channel::FlushCreation);
    Nan::SetMethod(target, "flushChannelUpdates",          Channel::FlushUpdates);
    Nan::SetMethod(target, "requestChannelMove",           Channel::Move);
    Nan::SetMethod(target, "requestChannelDelete",         Channel::Delete);
    Nan::SetMethod(target, "requestChannelSubscribe",      Channel::Subscribe);
    Nan::SetMethod(target, "requestChannelUnsubscribe",    Channel::Unsubscribe);
    Nan::SetMethod(target, "requestChannelSubscribeAll",   Channel::SubscribeAll);
    Nan::SetMethod(target, "requestChannelUnsubscribeAll", Channel::UnsubscribeAll);
    Nan::SetMethod(target, "requestSendChannelTextMsg",    Channel::SendMessage);
    
    // server
    Nan::SetMethod(target, "requestServerConnectionInfo",         Server::GetConectionInfo);
    Nan::SetMethod(target, "getServerConnectionVariableAsUInt64", Server::GetConectionVarAsUInt64);
    Nan::SetMethod(target, "getServerConnectionVariableAsFloat",  Server::GetConectionVarAsFloat);
    Nan::SetMethod(target, "requestServerVariables",              Server::GetVars);
    Nan::SetMethod(target, "getServerVariableAsInt",              Server::GetVarAsInt);
    Nan::SetMethod(target, "getServerVariableAsUInt64",           Server::GetVarAsUInt64);
    Nan::SetMethod(target, "getServerVariableAsString",           Server::GetVarAsString);
    Nan::SetMethod(target, "requestSendServerTextMsg",            Server::SendMessage);
    
    // filetransfer
    Nan::SetMethod(target, "sendFile",                                 FileTransfer::InitUpload);
    Nan::SetMethod(target, "requestFile",                              FileTransfer::InitDownload);
    Nan::SetMethod(target, "haltTransfer",                             FileTransfer::Stop);
    Nan::SetMethod(target, "requestFileList",                          FileTransfer::GetFileList);
    Nan::SetMethod(target, "requestFileInfo",                          FileTransfer::GetFileInfo);
    Nan::SetMethod(target, "requestDeleteFile",                        FileTransfer::DeleteFile);
    Nan::SetMethod(target, "requestRenameFile",                        FileTransfer::RenameFile);
    Nan::SetMethod(target, "requestCreateDirectory",                   FileTransfer::CreateDirectory);
    Nan::SetMethod(target, "setInstanceSpeedLimitUp",                  FileTransfer::SetInstanceSpeedLimitUpload);
    Nan::SetMethod(target, "setInstanceSpeedLimitDown",                FileTransfer::SetInstanceSpeedLimitDownload);
    Nan::SetMethod(target, "setServerConnectionHandlerSpeedLimitUp",   FileTransfer::SetServerSpeedLimitUpload);
    Nan::SetMethod(target, "setServerConnectionHandlerSpeedLimitDown", FileTransfer::SetServerSpeedLimitDownload);
    Nan::SetMethod(target, "setTransferSpeedLimit",                    FileTransfer::SetTransferSpeedLimit);
    Nan::SetMethod(target, "getInstanceSpeedLimitUp",                  FileTransfer::GetInstanceSpeedLimitUpload);
    Nan::SetMethod(target, "getInstanceSpeedLimitDown",                FileTransfer::GetInstanceSpeedLimitDownload);
    Nan::SetMethod(target, "getServerConnectionHandlerSpeedLimitUp",   FileTransfer::GetServerSpeedLimitUpload);
    Nan::SetMethod(target, "getServerConnectionHandlerSpeedLimitDown", FileTransfer::GetServerSpeedLimitDownload);
    Nan::SetMethod(target, "setTransferSpeedLimit",                    FileTransfer::GetTransferSpeedLimit);
    Nan::SetMethod(target, "getTransferFileName",                      FileTransfer::GetTransferFileName);
    Nan::SetMethod(target, "getTransferFilePath",                      FileTransfer::GetTransferFilePath);
    Nan::SetMethod(target, "getTransferFileRemotePath",                FileTransfer::GetTransferFilePathRemote);
    Nan::SetMethod(target, "getTransferFileSize",                      FileTransfer::GetTransferFileSize);
    Nan::SetMethod(target, "getTransferFileSizeDone",                  FileTransfer::GetTransferFileSizeDone);
    Nan::SetMethod(target, "getTransferStatus",                        FileTransfer::GetTransferStatus);
    Nan::SetMethod(target, "getTransferRunTime",                       FileTransfer::GetTransferRuntime);
    Nan::SetMethod(target, "getCurrentTransferSpeed",                  FileTransfer::GetTransferSpeed);
    Nan::SetMethod(target, "getAverageTransferSpeed",                  FileTransfer::GetTransferSpeedAverage);
    Nan::SetMethod(target, "isTransferSender",                         FileTransfer::IsTransferSender);
    
    // log
    Nan::SetMethod(target, "logMessage",      Log::AddMessage);
    Nan::SetMethod(target, "setLogVerbosity", Log::SetVerbosity);
    
    // error
    Nan::SetMethod(target, "getLastError",        Error::GetLastCode);
    Nan::SetMethod(target, "getLastErrorMessage", Error::GetLastMessage);
    Nan::SetMethod(target, "getErrorMessage",     Error::GetMessage);
    
    // callback
    Nan::SetMethod(target, "on", Event::On);
}

#if NODE_MAJOR_VERSION >= 10
NAN_MODULE_WORKER_ENABLED(ts3client, Init)
#else
NODE_MODULE(ts3client, Init);
#endif
