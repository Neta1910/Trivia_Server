#pragma once
#include <vector>
#include <string>
#include <WinSock2.h>
#include <map>
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <deque>



// ---- Messages Codes ----
#define CODE_LOGIN_RESP 200
#define CODE_SIGN_UP_RESP 201
#define CODE_ERROR_RESPONSE 202

#define CODE_LOGIN_REQ 100
#define CODE_SIGN_UP_REQ 101

// ---- Message constants ----
#define USERNAME "username"
#define PASSWORD "password"