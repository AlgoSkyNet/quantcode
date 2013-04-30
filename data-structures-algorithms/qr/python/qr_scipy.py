import pprint
import scipy
import scipy.linalg   # SciPy Linear Algebra Library

A = scipy.array([[12, -51, 4], [6, 167, -68], [-4, 24, -41]])  # From the Wikipedia Article on QR Decomposition
Q, R = scipy.linalg.qr(A)

print "A:"
pprint.pprint(A)

print "Q:"
pprint.pprint(Q)

print "R:"
pprint.pprint(R)
