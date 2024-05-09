#include "NetworkSender.h"
#include "../../Constants/EnvConstants.h"

void NetworkSender::init() {
    ether.printIp("IP:  ", ether.myip);
    ether.printIp("GW:  ", ether.gwip);
    ether.printIp("DNS: ", ether.dnsip);
    memcpy(ether.hisip, adressIp, sizeof adressIp);
    ether.printIp("SRV: ", ether.hisip);
}

void NetworkSender::send(const char *path, const char *code) {
    ether.packetLoop(ether.packetReceive());
    char *query;
    makeQuery(query, code);
    ether.browseUrl(path, query, adress, NetworkSender::callback);
    NetworkSender::isRequestFinished = false;
}

void NetworkSender::callback (byte status, word off, word len) {
    NetworkSender::isRequestFinished = true;
    Ethernet::buffer[off+300] = 0;
    Serial.print((const char*) Ethernet::buffer + off);
    const char isSuccessChar = Ethernet::buffer[off - 1 + len];
    NetworkSender::isRequestSuccessed = (isSuccessChar == '1');
    Serial.println("");
}

void NetworkSender::makeQuery(char*& query, char* code) {
    const char *prefix = "?code=";
    size_t codeSize = strlen(code) + strlen(prefix);
    query = (char *)malloc(codeSize);
    strcpy(query, prefix);
    strcat(query, code);
}