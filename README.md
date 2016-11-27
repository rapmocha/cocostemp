# cocostemp

cocos2d-xプロジェクトをCMakeでビルドする。別途cocos2d-xの静的ライブラリが必要。

## Usage

1. clone repositry
1. mv cocostemp ProjectName
1. cd ProjectName
1. Edit CMakeLists.txt
1. cd build
1. cmake ..
1. make run

## Requirement

- MacOSX 10.10.5 Yosemite
- Xcode 7.2.1
- cocos2d-x3.8 static library
  - /usr/local/mylib/libcocos2dMac3.8.a にあるとする
- cocos2d-x3.8 library headers: copy from original cocos project
  - /usr/local/myinclude/cocos2d にあるとする

## Note

Info.plist
