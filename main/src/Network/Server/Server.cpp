#include "Server.h"

Server::Server(byte pin) {
    this->pin = pin;
}

void Server::init() {
    if (ether.begin(ServerConstants::bufferSize, ServerConstants::sharedArraysInstanse()->mymac, pin) == 0)
      Serial.println(F("Failed to access Ethernet controller"));
    else {
        Serial.println(F("Inet succesfully connected"));
    }
    if (!ether.dhcpSetup()) {
        Serial.println(F("DHCP failed"));
    } else {
        Serial.println("DHCP successed");
    }
    ether.staticSetup(ServerConstants::sharedArraysInstanse()->myip);
}

bool Server::isRequestDone() {
    word len = ether.packetReceive();
    word req = ether.packetLoop(len);
    if (req) {
        if (verifyRequest(req)) {
            sendResponse();
            return true;
        } else {
            sendFailuire();
        }
    }
    return false;
}

bool Server::verifyRequest(word req) {
    char *data = (char *) Ethernet::buffer + req;
    if (strncmp(ServerConstants::sharedArraysInstanse()->requestStart, data, ServerConstants::neededReqSize) != 0) {
        return false;
    } else {
        return verifyCode(data + ServerConstants::neededReqSize);
    }
}

bool Server::verifyCode(char *code) {
    if (strncmp(prevCode, code, ServerConstants::codeSize) != 0) {
        strncpy(prevCode, code, ServerConstants::codeSize);
        return true;
    } else {
        return false;
    }
}

void Server::sendResponse() {
    unsigned int offset = 0;
    memcpy(
        ether.tcpOffset() + offset, 
        ServerConstants::sharedArraysInstanse()->s200,    
        sizeof ServerConstants::sharedArraysInstanse()->s200
    );    
    offset += sizeof ServerConstants::sharedArraysInstanse()->s200;
    memcpy(
        ether.tcpOffset() + offset, 
        ServerConstants::sharedArraysInstanse()->headers, 
        sizeof ServerConstants::sharedArraysInstanse()->headers
    );
    offset += sizeof ServerConstants::sharedArraysInstanse()->headers;
    memcpy(
        ether.tcpOffset() + offset, 
        ServerConstants::sharedArraysInstanse()->b200,    
        sizeof ServerConstants::sharedArraysInstanse()->b200
    );    
    offset += sizeof ServerConstants::sharedArraysInstanse()->b200;
    ether.httpServerReply(offset);
}

void Server::sendFailuire() {
    unsigned int offset = 0;
    memcpy(
        ether.tcpOffset() + offset, 
        ServerConstants::sharedArraysInstanse()->s503,    
        sizeof ServerConstants::sharedArraysInstanse()->s503
    );    
    offset += sizeof ServerConstants::sharedArraysInstanse()->s503;
    memcpy(
        ether.tcpOffset() + offset, 
        ServerConstants::sharedArraysInstanse()->headers, 
        sizeof ServerConstants::sharedArraysInstanse()->headers
    );
    offset += sizeof ServerConstants::sharedArraysInstanse()->headers;
    memcpy(
        ether.tcpOffset() + offset, 
        ServerConstants::sharedArraysInstanse()->b503,    
        sizeof ServerConstants::sharedArraysInstanse()->b503
    );    
    offset += sizeof ServerConstants::sharedArraysInstanse()->b503;
    ether.httpServerReply(offset);
}