from random import random

def generateVectors(count, min, max):
	vecs = [(0,0,0)] * count

	rng = max - min

	for i in range(count):
		vecs[i] = (
				random() * rng + min,
				random() * rng + min,
				random() * rng + min
			)


		# vecs[i][0] = random() * rng + min
		# vecs[i][1] = random() * rng + min
		# vecs[i][2] = random() * rng + min

	return vecs

def formatVectors(vecs, precision, openStr, closeStr):
	count = len(vecs)
	reprs = [""] * count

	for i in range (count):
		reprs [i] = openStr + "{:.{prec}f}f, {:.{prec}f}f, {:.{prec}f}f".format(vecs[i][0], vecs[i][1], vecs[i][2], prec=precision) + closeStr

	return reprs


vecs = generateVectors(10, -180, 180)

for vec in formatVectors(vecs, 3, "new Vector3(", "),"):
	print(vec)

print()

for vec in formatVectors(vecs, 3, "vector3f(", "),"):
	print(vec)	