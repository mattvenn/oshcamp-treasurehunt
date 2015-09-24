import unittest
import socket

host = "192.168.4.1"
port = 1337
password = "abcd"

class TestClue3(unittest.TestCase):

    def test_bad_pass(self):
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        soc.connect((host, port))
        soc.send("aaaaa")
        self.assertEqual(soc.recv(1000), "bad password")

    def test_pass_overflow(self):
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        soc.connect((host, port))
        # ddoesn't actually overflow! thought 40k would do it.
        soc.send("a" * 100000)
        self.assertEqual(soc.recv(1000), "bad password")

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
        self.assertEqual(soc.recv(1000), "strobe on")

    def test_strobe_off(self):
        soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        soc.connect((host, port))
        soc.send(password + " strobe_off")
        self.assertEqual(soc.recv(1000), "strobe off")

if __name__ == '__main__':
    unittest.main()
