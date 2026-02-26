import unittest
import myBmi    
class TestBMI(unittest.TestCase):
    def test_computeBMIOK(self):
        self.assertEqual(myBmi.printResult(2.9, 1.7), 'ERROR INPUT')
        self.assertEqual(myBmi.printResult(200.1, 1.7), 'ERROR INPUT')
        self.assertEqual(myBmi.printResult(70, 0.49), 'ERROR INPUT')
        self.assertEqual(myBmi.printResult(70, 2.51), 'ERROR INPUT')
        self.assertEqual(myBmi.printResult(1, 3.0), 'ERROR INPUT')
        self.assertEqual(myBmi.printResult(15, 1.0), 'Underweight')
        self.assertEqual(myBmi.printResult(63.5, 1.7), 'Normal')
        self.assertEqual(myBmi.printResult(68, 1.65), 'Overweight')
        self.assertEqual(myBmi.printResult(90, 1.75), 'Obesity')