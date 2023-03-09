import unittest
from arithmetics import *

class TestLcm(unittest.TestCase):

    def test_00(self):
        with self.assertRaises(AssertionError):
            lcm(0,0)

    def test_X0(self):
        with self.assertRaises(AssertionError):
            lcm(1,0)

    def test_0X(self):
        with self.assertRaises(AssertionError):
            lcm(0,1)

    def test_XX(self):
        self.assertEqual(lcm(1,1), 1)


    def test_value(self):
        self.assertEqual(lcm(60,168),840)

class TestLcmBetter(unittest.TestCase):

    def test_00(self):
        with self.assertRaises(AssertionError):
            lcm_better(0,0)

    def test_X0(self):
        with self.assertRaises(AssertionError):
            lcm_better(1,0)

    def test_0X(self):
        with self.assertRaises(AssertionError):
            lcm_better(0,1)

    def test_XX(self):
        self.assertEqual(lcm_better(1,1), 1)

    def test_value(self):
        self.assertEqual(lcm_better(60,168),840)

class TestLcmFaulty(unittest.TestCase):

    def test_00(self):
        with self.assertRaises(AssertionError):
            lcm_better(0,0)

    def test_X0(self):
        with self.assertRaises(AssertionError):
            lcm_better(1,0)

    def test_0X(self):
        with self.assertRaises(AssertionError):
            lcm_faulty(0,1)

    def test_XX(self):
        self.assertEqual(lcm_faulty(1,1), 1)

    def test_value(self):
        self.assertEqual(lcm_faulty(60,168),840)
        


if __name__ == '__main__':
    unittest.main()