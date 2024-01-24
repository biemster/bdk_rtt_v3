#!/usr/bin/env python
import sys
if len(sys.argv) == 2 and sys.argv[1][-4:] == '.bin':
	fname = sys.argv[1]
	infile = open(fname, 'rb')
	outfile = open(fname[:-4] + '_uncrc' + fname[-4:], 'wb')
	x = infile.read(34)
	while len(x) == 34:
		outfile.write(x[:32])
		x = infile.read(34)
	if len(x):
		outfile.write(x)
else:
	print(f'usage: {sys.argv[0]} <crc\'ed .bin file>')