import sys
from operator import xor
import fileinput

class RC4:
	def __init__(self, key, text):
		self.key = [ord(e) for e in key] #conversion tu numerical representation
		self.text = text
		self.S = ''

	def _KSA(self, key):
		S = [i for i in range(256)]
		j = 0
		for i in range(256):
			j = (j + S[i] + key[i % len(key)]) % 256
			S[i], S[j] = S[j], S[i]
		return S

	def _PRGA(self, S):
		i = 0
		j = 0
		for c in self.text:
			i = (i+1) % 256
			j = (j + S[i]) % 256
			S[i], S[j] = S[j], S[i]
			K = S[(S[i] + S[j]) % 256]
			sys.stdout.write("%02X" % (xor(ord(c), K)))
		print()

	def run(self):
		self.S = self._KSA(self.key)
		self._PRGA(self.S)

if __name__ == '__main__':
	key = input()
	text = input()
	RC4(key, text).run()
