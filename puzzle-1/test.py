import urllib2
import unittest
import requests
import ipdb
import time

host = "http://192.168.4.1:800"

rick = "http://ven.nz/solution-stage1"
rick_page = 3

steg_pass = "xojezj"
steg_pass_page = 100

clue = "take a break and wait for a glimpse with 492duxwx"
clue_page = 173 

steg = "http://ven.nz/stegz"
steg_page = 180


class TestClue1(unittest.TestCase):

    def setUp(self):
        req = requests.get(host)

    def test_rick(self):
        url = host + "/" + str(rick_page)
        req = requests.get(url)

        self.assertEqual(req.status_code, 200)
        self.assertIn(rick, req.content)

    def test_steg(self):
        url = host + "/" + str(steg_page)
        req = requests.get(url)

        self.assertEqual(req.status_code, 200)
        self.assertIn(steg, req.content)

    def test_steg_pass(self):
        url = host + "/" + str(steg_pass_page)
        req = requests.get(url)

        self.assertEqual(req.status_code, 200)
        self.assertIn(steg_pass, req.content)

    def test_root(self):
        req = requests.get(host)
        self.assertEqual(req.status_code, 200)
        self.assertIn("the data you need", req.content)

    def test_wrong_url(self):
        for i in range(10,20):
            url = host + "/" + str(i)
            req = requests.get(url)
            self.assertEqual(req.status_code, 404)
            self.assertIn("try another number", req.content)
    
    # 100 requests complete in 2 seconds
    def test_load(self):
        start_t = time.time()
        for i in range(100):
            req = requests.get(host)

        end_t = time.time()
        self.assertLess(end_t - start_t, 2)

    def test_decode_clue(self):
        url = host + "/" + str(clue_page)
        req = requests.get(url)
        self.assertEqual(req.status_code, 200)
        self.assertEqual("form data: " + urllib2.base64.encodestring(clue), req.content)
   

if __name__ == '__main__':
    print("plaintext clue = " + clue)
    print("encoded clue = " + urllib2.base64.encodestring(clue))

    unittest.main()
