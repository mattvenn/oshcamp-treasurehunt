import unittest
import socket
import time

host = "10.10.0.29"
port = 1337
password = 'MK_DCBY07I3YA8]PBVEU'
# has good pass embedded
bad_pass = 'B3d,P@U^=S<GPc*VNdN\MK_DCBY07I3YA8]PBVEUO``EM*)M2Ma,5CGAN<)'

class TestClue3(unittest.TestCase):

    def test_bad_pass(self):
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        soc.connect((host, port))
        soc.send("bad_pass")
        self.assertEqual(soc.recv(1000), "bad password")

    """
    def test_pass_overflow(self):
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        soc.connect((host, port))
        # ddoesn't actually overflow! thought 40k would do it.
        soc.send("a" * 100000)
        self.assertEqual(soc.recv(1000), "bad password")
    """

    def test_no_pass_strobe_on(self):
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        soc.connect((host, port))
        soc.send("strobe_on")
        self.assertEqual(soc.recv(1000), "bad password")

    def test_bad_pass_strobe_on(self):
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        soc.connect((host, port))
        soc.send("aaaaa:strobe_on")
        self.assertEqual(soc.recv(1000), "bad password")

    def test_good_pass(self):
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        soc.connect((host, port))
        soc.send(password)
        self.assertEqual(soc.recv(1000), "invalid request")

    def test_strobe_on(self):
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        soc.connect((host, port))
        soc.send(password + " strobe_on")
        time.sleep(3)  # so we can see it
        self.assertEqual(soc.recv(1000), "strobe on")

    def test_strobe_off(self):
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        soc.connect((host, port))
        soc.send(password + " strobe_off")
        self.assertEqual(soc.recv(1000), "strobe off")
    
    def tearDown(self):
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        soc.connect((host, port))
        soc.send(password + " strobe_off")
        self.assertEqual(soc.recv(1000), "strobe off")

if __name__ == '__main__':
    unittest.main()
