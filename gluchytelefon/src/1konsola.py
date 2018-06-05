#! /usr/bin/env python3
# -*- coding: utf-8 -*-

CMD_RESET = "\x1b[0m"
CMD_RED = "\x1b[31m"
# CMD_GREEN = "\x1b[32m"
CMD_ORANGE = "\x1b[33m"
CMD_YELLOW = "\x1b[38;5;11m"
CMD_BG_VIOLET = "\x1b[48;5;57m"

TXT_ERROR_INPUT_OUT_OF_RANGE = "Input is out of range"
TXT_ERROR_OUTPUT_OUT_OF_RANGE = "Output is out of range"

UINT_MAX = 2**32-1

import signal
import sys


def breakHandler(signal, frame):
    print("\nShutting down...")
    sys.exit(0)


def checkRange(number):
    if(number < 0 or number > UINT_MAX):
        return False
    else:
        return True


def displayInfo(type, txt):
    if(type == "ERROR"):
        print("[{}ERROR{}] {}".format(CMD_RED, CMD_RESET, txt))
    elif(type == "INPUT"):
        print("[{}INPUT{}]  {}".format(CMD_YELLOW, CMD_RESET, txt))
    elif(type == "INTRO"):
        print("{}{}{}".format(CMD_BG_VIOLET, txt, CMD_RESET))
    elif(type == "OUTPUT"):
        print("[{}OUTPUT{}] {}".format(CMD_ORANGE, CMD_RESET, txt))


def send(number):
    import os
    os.system("./2argument.out -i {}".format(number))


def transform(number):
    return number+1


signal.signal(signal.SIGINT, breakHandler)

while 1:
    print("\n\n\n")
    displayInfo("INTRO", "#####     1     #####   x=x+1")

    try:
        number_str = input("Enter number [0-{}]: ".format(UINT_MAX))
        number = int(number_str)
    except ValueError:
        displayInfo("ERROR", "Incorrect characters")
        continue

    if(checkRange(number) == False):
        displayInfo("ERROR", TXT_ERROR_INPUT_OUT_OF_RANGE)
        continue
    displayInfo("INPUT", number)

    number = transform(number)
    if(checkRange(number) == False):
        displayInfo("ERROR", TXT_ERROR_OUTPUT_OUT_OF_RANGE)
        continue
    displayInfo("OUTPUT", number)

    send(number)
