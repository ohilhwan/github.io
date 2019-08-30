# 신입사원 SW 직무교육 프로젝트
## 1. 개요
이 repository는 신입사원 직무교육 프로젝트 중 **실제 프로그램 개발**에 대해 설명하고, **interface code**를 제공하는 목적을 가진다.

## 2. Prerequisites

아래 프로그램은 프로젝트를 진행하기 개발환경으로 필수적으로 설치하여야 한다.


**PATH 환경변수 설정 필요**

* [git](https://git-scm.com/)
* [mingGW g++](https://mingw-w64.org/doku.php)
* [cmake](https://cmake.org/)
* [mingw-make](http://mingw-w64.yaxm.org/doku.php/download/mingw-builds)


## 3. Build

    # windows
    mkdir build
    cd build
    cmake .. -G "MinGW Makefiles" -DDEFINE_DEBUG=ON -DNPHASE1=OFF
    mingw32-make
    .\bin\employee_management.exe

위의 `cmake .. -G "MinGW Makefiles" -DDEFINE_DEBUG=ON -DNPHASE1=OFF` 의 옵션 설정에 따라 실제 코드 내에서 전처리된 DEBUG, NPHASE1 매크로를 사용할 수 있다. DEBUG는 1이면 DEBUG 상태를 나타내고 0이면 PROD 상태를 나타내도록 의도하였다. NPHASE1은 PHASE1 프로그램이 아닐때 1이고, PHASE1 프로그램이면 0이 되도록 의도하였다.

    #if DEBUG
        std::cout << "DEBUG STATE" << std::endl;
    #endif

이것을 활용하면 같이 DEBUG 상태에서만 컴파일되는 코드을 생성할 수 있다.

## 4. 요구사항

**제공되는 문서 참조**

샘플 코드가 이 repository에 주어지나 **요구사항만 만족한다면** 자유롭게 변경하여도 상관없다. 이 repo를 fork 하여도 좋고 새롭게 시작하여도 좋다. 다만 빌드 툴은 cmake를 사용하여야 하고, compiler는 g++을 사용하여야 한다. 또한 빌드 방법을 주어진 것과 다르게 구성한다면, 채점자가 빌드를 할 수 있게 적절한 빌드 매뉴얼을 제공해야한다.

## 5. 참고자료 & 툴


[cmake 관련 문서](https://gist.github.com/luncliff/6e2d4eb7ca29a0afd5b592f72b80cb5c)

[Database storage structures](https://en.wikipedia.org/wiki/Database_storage_structures)

[WinMerge (문서비교 툴)](https://winmerge.org/)
