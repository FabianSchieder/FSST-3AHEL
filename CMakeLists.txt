cmake_minimum_required(VERSION 3.29)
project(FSST_3AHEL C)

set(CMAKE_C_STANDARD 11)

add_executable(FSST_3AHEL
    main.c
        src/insertSortedLastName.c
        src/printAscending.c
        src/printfDescending.c
        src/readFile.c
        src/writeFile.c
        src/searchTradeName.c
        src/searchConsumption.c
        src/deleteByLastName.c
        src/deleteByDriveType.c
        inlcude/functions.h
        src/utils.c
)
