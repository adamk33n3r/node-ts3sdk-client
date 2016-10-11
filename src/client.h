/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_CLIENT_H
#define ADDON_CLIENT_H

#include "shared.h"

class Client : public Nan::ObjectWrap
{
public:
    static NAN_METHOD(GetOwnID);
    static NAN_METHOD(GetOwnVarAsInt);
    static NAN_METHOD(GetOwnVarAsString);
    static NAN_METHOD(SetOwnVarAsInt);
    static NAN_METHOD(SetOwnVarAsString);
    static NAN_METHOD(GetList);
    static NAN_METHOD(GetClones);
    static NAN_METHOD(GetChannelID);
    static NAN_METHOD(GetConectionInfo);
    static NAN_METHOD(GetVars);
    static NAN_METHOD(GetVarAsInt);
    static NAN_METHOD(GetVarAsUInt64);
    static NAN_METHOD(GetVarAsString);
    static NAN_METHOD(FlushUpdates);
    static NAN_METHOD(Mute);
    static NAN_METHOD(Unmute);
    static NAN_METHOD(Move);
    static NAN_METHOD(KickFromChannel);
    static NAN_METHOD(KickFromServer);
    static NAN_METHOD(SendMessage);
};

#endif // ADDON_CLIENT_H