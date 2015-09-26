import socket
import time

host = "10.10.0.29"
port = 1337
password = 'MK_DCBY07I3YA8]PBVEU'

def test_strobe_on():
    soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    soc.connect((host, port))
    soc.send(password + " strobe_on")

def test_strobe_off():
    soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    soc.connect((host, port))
    soc.send(password + " strobe_off")
    
if __name__ == '__main__':
    test_strobe_on()
    time.sleep(5)
    test_strobe_off()
