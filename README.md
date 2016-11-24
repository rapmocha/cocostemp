# cocostemp

cocos2d-xプロジェクトを、ライブラリとヘッダがあればmakefileでビルドできる。Vimからでも。

## Usage

1. clone repositry
1. mv cocostemp PROJECT_NAME
1. cd PROJECT_NAME
1. bash init.sh
1. make
1. make run

## Requirement

- MacOSX 10.10.5 Yosemite
- Xcode 7.2.1
- cocos2d-x3.8 static library
  - /usr/local/mylib/libcocos2dMac3.8.a にあるとする
- cocos2d-x3.8 library headers: copy from original cocos project
  - /usr/local/myinclude/cocos2d にあるとする

## Note

Info.plistの更新が適当。
