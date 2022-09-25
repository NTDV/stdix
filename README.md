# About STDIX
STDIX is a simple С library for Software Engineering students from [ICIX MEPHI](https://icis.mephi.ru/). Every year students suffer from low-level C programming. So, there are some useful and easy-to-use functions for them. Hope it helps!


## Quick start
1. Download a latest stable release: [github.com/NTDV/stdix/releases](https://github.com/NTDV/stdix/releases)
2. Copy files from archive to your working folder
3. Include header files in your code. For example, `#inclide "stdix.h"`
4. Compile your program with passing all `*.c` and `*.h` files to compiler.
    * You also should add math.h implemetation in compilation pipeline. For example, in GCC use `-lm` parameter.
5. Profit!

## GCC example
Use `gcc ${pathToLibs}/**.c ${pathToCode}/**.c -I ${pathToLibs}/**.h -lm -o ${outName}.out`

For tree:
```
base
├── labs
│   ├── l1
│   │   └── l1.c
└── libs
    ├── stdix.c
    └── stdix.h
```
```
cd base/labs/l1
gcc base/lib/**.c base/labs/l1/**.c -I base/libs/**.h -lm -o example.out
./example.out
```
Will be created and executed new file at `base/labs/l1/example.out`.
