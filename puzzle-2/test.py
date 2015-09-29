import unittest
import requests
import ipdb
import os

host = "http://192.168.4.1:9600"
image_name = "bust.jpg"
image_file = "data/" + image_name
clue_file = "clue.txt"

class TestClue2(unittest.TestCase):

    def setUp(self):
        req = requests.get(host)

    def test_root(self):
        req = requests.get(host)
        self.assertEqual(req.status_code, 200)
        self.assertIn("the data you need", req.content)
        
    def test_download_image(self):
        url = host + "/file?file=/" + image_name
        req = requests.get(url)
        self.assertEqual(req.status_code, 200)
        with open(image_file) as fh:
            self.assertEqual(req.content, fh.read())

        # extract the data file
        extracted_clue = '/tmp/t'
        passphrase = "xojezj"
        os.system("steghide extract -sf %s -p %s -xf %s" % (image_file, passphrase, extracted_clue))

        # test the clue files are the same
        with open(clue_file) as cf:
            with open(extracted_clue) as ef:
                self.assertEqual(cf.read(), ef.read())

        os.unlink('/tmp/t')

if __name__ == '__main__':
    unittest.main()
