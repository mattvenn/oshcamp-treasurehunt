import unittest
import requests
import ipdb

host = "http://192.168.4.1:800"
text_file = "data/test.txt"
image_file = "data/meter.jpg"

class TestClue2(unittest.TestCase):

    def setUp(self):
        req = requests.get(host)

    def test_root(self):
        req = requests.get(host)
        self.assertEqual(req.status_code, 404)
        
    def test_download_text(self):
        url = host + "/file?file=/test.txt"
        req = requests.get(url)
        self.assertEqual(req.status_code, 200)
        file = open(text_file).read()
        self.assertEqual(req.content, file)

    def test_download_image(self):
        url = host + "/file?file=/meter.jpg"
        req = requests.get(url)
        self.assertEqual(req.status_code, 200)
        file = open(image_file).read()
        self.assertEqual(req.content, file)

if __name__ == '__main__':
    unittest.main()
