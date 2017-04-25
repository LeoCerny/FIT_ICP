#!/usr/bin/env python3

#Generuje soubor soliter.pro

from subprocess import call
import re

file = open('src/hra2017.pro', 'r')

data = file.read()
file.close()

call(['rm', 'src/hra2017.pro'])

punct = re.compile(r'[\ ]{0,1}main\-cli\.cpp[\ ]{0,1}')
data = punct.sub(' ', data)

punct = re.compile(r'(?<=\#\n)(?=\n)')
data = punct.sub('\nQT += core gui\ngreaterThan(QT_MAJOR_VERSION, 4): QT += widgets\n', data)

punct = re.compile(r'TARGET = .*\n')
#data = punct.sub('TARGET = hra2017\nCONFIG += c++11\nQMAKE_CXXFLAGS += -std=c++11 -O3 -w\n', data)
#for test
data = punct.sub('TARGET = hra2017\nCONFIG += c++11\nQMAKE_CXXFLAGS += -std=c++11 -O3 -Wall -Wextra -pedantic-errors\n', data)
#print(data)
file = open('src/hra2017.pro', 'w+')
file.write(data)
file.close()
