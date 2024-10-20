/**
 * @file main.cpp
 * @author Massinissa Bandou
 * @brief
 * @version 0.1
 * @date 2024-10-12
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include "Logger.hpp"

/// @brief main thread
/// @param argc 
/// @param argv 
/// @return success
int main(int argc, const char *argv[])
{
    LOG_WARN("This message is a warning");
    LOG_DEBUG("This message is a debug");
    LOG_FAULT("THIS IS CRITICAL!!!!!!!!!!");
    return (0);
} // main
