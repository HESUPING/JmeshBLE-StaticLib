#! /usr/bin/env python
import win32clipboard as w
import win32con

fp = open("BX2400.map",'r')
rtt = open("SeggerRTT.txt",'w')

def settext(aString):
    w.OpenClipboard()
    w.EmptyClipboard()
    w.SetClipboardData(win32con.CF_UNICODETEXT, aString)
    w.CloseClipboard()
	
for line in fp:
    if "_SEGGER_RTT" in line:
        split = line.split()[1]
        rtt.write(split)
        #print(split)
        settext(split)
        #input("press enter to exit:")
rtt.close()
fp.close()


