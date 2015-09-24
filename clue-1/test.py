import urllib2
import unittest
import requests
import ipdb
import time

host = "http://192.168.4.1:800"
clue = "have a seat and wait for SSID=glimpse PW=492duxw"
correct = 173

class TestClue1(unittest.TestCase):

    def setUp(self):
        req = requests.get(host)

    def test_root(self):
        req = requests.get(host)
        self.assertEqual(req.status_code, 200)
        self.assertIn("the data you need", req.content)

    def test_wrong_url(self):
        for i in range(20):
            url = host + "/" + str(i)
            req = requests.get(url)
            self.assertEqual(req.status_code, 404)
            self.assertIn("try another number", req.content)
    
    # 100 requests complete in 5 seconds
    def test_load(self):
        start_t = time.time()
        for i in range(100):
            req = requests.get(host)

        end_t = time.time()
        self.assertLess(end_t - start_t, 5)

    def test_decode_clue(self):
        url = host + "/" + str(correct)
        req = requests.get(url)
        self.assertEqual(req.status_code, 200)
        self.assertEqual(urllib2.base64.decodestring(req.content), clue)
    

if __name__ == '__main__':
    print("plaintext clue = " + clue)
    print("encoded clue = " + urllib2.base64.encodestring(clue))

    unittest.main()
