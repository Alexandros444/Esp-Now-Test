from ESPythoNOW import *
import time



msg = "THIS IS A CHAR"
msg += "\0" * (32 - len(msg))
msg = chr(0) + msg

# print(msg, len(msg))
# exit()


def callback(from_mac, to_mac, msg):
  print("ESP-NOW message from %s to %s: %s" % (from_mac, to_mac, msg))

espnow = ESPythoNow(interface="wlan0", callback=callback)
espnow.start()


msg_idx = 0
r = 0xDA
g = 0x88
b = 0xFF
payload = [0,r,g,b]
print(bytes(payload))

while True:
  print("Sending")
  # msg=b'\x01'
  # msg2 = bytes([0xDE,0xAD])
  # espnow.send("94:b9:7e:c0:25:58", msg2)
  payload[0] = msg_idx
  msg_idx += 1
  if msg_idx > 255: msg_idx = 0
  # print(bytes(msg,"UTF-8"))
  print(payload)
  espnow.send("c0:49:ef:c9:41:c4", bytes(payload))
  # time.sleep(.01)