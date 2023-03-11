def bench(n, createT, hashT):
	vec = []
	for i in range(n):
		vec.append(createT(i))
	print("Size:", len(vec))
	checksum = 0
	for i in range(n):
		checksum += hashT(vec[i])
	print("Checksum:", checksum)
	while len(vec) > 0:
		vec.pop(len(vec)-1)
	return checksum

class PQnode:
	def __init__(self, key, item):
		self.key = key # float
		self.item = item # int

# n = 10
n = 100000000
print("Samples: %d\n" % n)

bench(n, lambda x : chr(x % 256), lambda x : ord(x))
bench(n, lambda x : int(x), lambda x : int(x))
bench(n, lambda x : PQnode(x, x), lambda x : int(x.key) + int(x.item))
# bench(n, lambda x : (float(x), int(x)), lambda x : int(x[0]) + int(x[1]))
