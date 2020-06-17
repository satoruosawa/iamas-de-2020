import shutil

# toLocation = '00_lcd/00_simple_text/src/'
# toDirName = '../00_arduino_ide/'
# fileName = '00_simple_text'

# src = fromDirName + dirName + 'main.cpp'
# copy = toDirName  + fileName + '.ino'
# shutil.copyfile(src, copy)

import glob
import re
import os

fromRootPath = '../01_platformio/'
toRootPath = '../00_arduino_ide/'

# Clear toRootPath
for root, dirs, files in os.walk(toRootPath, topdown = False):
  for name in files:
    os.remove(os.path.join(root, name))
  for name in dirs:
    os.rmdir(os.path.join(root, name))

# Copy platformio to arduino_ide
li = glob.glob(fromRootPath + '/**/src/', recursive = True)
for fromSrcPath in li:
  toDirPath = fromSrcPath.replace(fromRootPath, toRootPath)
  toDirPath = toDirPath.replace('src/', '')
  os.makedirs(toDirPath, exist_ok = True)
  for fromFilePath in glob.glob(fromSrcPath + '*.*'):
    fileName = fromFilePath.split('/')[-1]
    # Exception
    if fileName == 'wifi-info.h':
      continue
    fromFileName = fileName
    toFileName = fileName
    if fileName == 'main.cpp':
      toFileName = toDirPath.split('/')[-2] + '.ino'
    fromFilePath = fromSrcPath + fromFileName
    toFilePath = toDirPath + toFileName
    print('Copy from')
    print(fromFilePath)
    print('Copy to')
    print(toFilePath)
    print('\n')
    shutil.copyfile(fromFilePath, toFilePath)