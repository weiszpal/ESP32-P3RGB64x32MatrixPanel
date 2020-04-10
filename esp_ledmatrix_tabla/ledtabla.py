#!-*-encoding:UTF-8-*-

import socket
import msvcrt
from os import system
import ctypes
ctypes.windll.kernel32.SetConsoleTitleA("LED kijelzo")

HOST = '192.168.0.1'
PORT = 23

try: 
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
    print "Socket successfully created"
except socket.error as err: 
    print "socket creation failed with error %s" %(err) 

s.connect((HOST, PORT))

while True:

	print "\nRakd ossze az uzenetet:"
	important = ["          ", "Ne zavarj "]

	i = 0
	for msg in important:
		print i,important[i]
		i = i + 1

	important_sel = ord(msvcrt.getch()) - 48
	print ""

	if(important_sel==0):
		action = ["          ", " Bejohetsz", "  Pihenek ", "Szunet van"]
	else:
		action = ["          ", "  ZH-zom  ", " tanulok  ", " videozok ", " beszelek ", "  [SEM]   "]

	i = 0
	for msg in action:
		print i,action[i]
		i = i + 1

	action_sel = ord(msvcrt.getch()) - 48
	print ""

	targy_sel = 0;
	targy = ["          ", " SZABTECH ", " uELEKTRO ", " MERESTECH", " INFOKOMM ", "  INFO 1  ", "  INFO 2  ", "INNOVATIV ", "  gyules  "]

	if(important_sel==1):
		i = 0
		for msg in targy:
			print i,targy[i]
			i = i + 1

		targy_sel = ord(msvcrt.getch()) - 48
		print ""
		
	s.send(important[important_sel] + action[action_sel] + targy[targy_sel])
	#s.send(action[action_sel])
	#s.send(targy[targy_sel])
	system('cls')
	print ""
	print "[",important[important_sel],"]"
	print "[",action[action_sel],"]"
	print "[",targy[targy_sel],"]"
	
	if(important_sel==0 and action_sel==0):
		break
	
s.close()