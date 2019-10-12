/*
 *  
 * Copyright (c) 2019 Seeed Technology Co., Ltd.
 * Website    : www.seeed.cc
 * Author     : downey
 * Create Time: Jan 2019
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __AT_SERIAL_H__
#define __AT_SERIAL_H__

#include <Arduino.h>
#if defined(SAMD21)
#else
#include "SoftwareSerial.h"
#endif


// Architecture specific include
#if defined(ARDUINO_ARCH_AVR)
#define UART_MAX_LEN   512
#define debug Serial
#define DEBUG_EN 0
#elif defined(ARDUINO_ARCH_SAM)
#define SAMD21
#define UART_MAX_LEN   1024
#define debug SerialUSB
#define DEBUG_EN 1
#elif defined(ARDUINO_ARCH_SAMD)
#define SAMD21
#define UART_MAX_LEN   1024
#define debug SerialUSB
#define DEBUG_EN 1
#elif defined(ARDUINO_ARCH_STM32F4)
#define UART_MAX_LEN   1024
#define debug Serial
#define DEBUG_EN 0
#else
#define debug Serial
#define DEBUG_EN 0
#define UART_MAX_LEN   512
#endif

#define DEBUG_EN 1

#ifndef UART_DELAY
#define UART_DELAY 100
#endif

#ifndef UART_TIMEOUT
#define UART_TIMEOUT 8000 //TODO make default 3000 again
#endif

#define DEFAULT_RX 0
#define DEFAULT_TX 1

#define DEFAULT_BAUD 115200

#define DEFAULT_PORT 8468

#define MAX_RESEND_CNT  2
#define TIME_OUT_MS     2000


/**class ATSerial ,provide data transfer interface.
 * 
 * 
 * */
class ATSerial {
  protected:
  #if defined(SAMD21)
    HardwareSerial *_uart;
  #else 
    SoftwareSerial *_uart;
  #endif
  private:
    uint32_t _timeout;
    uint8_t _max_resend_cnt;
  public:
    ATSerial(uint32_t timeout=TIME_OUT_MS,uint8_t max_resend_cnt = MAX_RESEND_CNT);

    /** If arduino board is AVR,using softwareSerial,else if samd board,using hardwareSerial.
     * 
     * */
    #if defined(SAMD21)
      void begin(HardwareSerial &uart,uint32_t baud);
    #else 
      void begin(SoftwareSerial &uart,uint32_t baud);
    #endif


    void flush(void);
    bool readResp(char* rsp);
    bool checkResponse(const char* prefix,char* resp_buffer);
    bool sendCmdAndCheckRsp(const char* cmd, const char* prefix, char* resp_buffer);
    bool waitForData(uint8_t *recv_msg,uint32_t *recv_len);

    int read(void);
    int ATWrite(const char* s);
    int ATWrite(const uint8_t uc);
    void binWrite(uint8_t *msg,uint32_t len);

};
#endif
