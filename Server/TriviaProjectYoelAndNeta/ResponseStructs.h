#pragma once
struct LoginResponse
{
	unsigned int status;
} typedef  LoginResponse;

struct SignupResponse
{
	unsigned int status;
} typedef  SignupResponse;

struct ErrorResponse
{
	std::string message;
} typedef ErrorResponse;

