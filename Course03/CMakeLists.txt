#
# (c) Jakub Melka 2023
#
# This source file is part of the licensed software between Jakub Melka
# and the users utilizing the software under the specified License Agreement.
# Usage of this source code is subject to the Software License Agreement.
#
# This source code is provided solely for educational, research, or teaching purposes,
# including paid ones. Licensee may modify, adapt, and create derivative works,
# but all modifications must be released as Public Domain or under a license having
# the same legal effect as publishing as Public Domain under US jurisdiction.
#
# The Software is provided "as is," without warranty of any kind. Licensor shall not be liable
# for any damages arising from the use or performance of this source code.
#
# Ownership and intellectual property rights to this source code remain with Licensor.
# It is important for the Licensee to read and understand the complete Software License Agreement.
#

cmake_minimum_required(VERSION 3.5)

add_executable(Course03
               bubble_sort.h
               insert_sort.h
               selection_sort.h
               merge_sort.h
               quick_sort.h
               heap_sort.h
               main.cpp)

install(TARGETS Course03 LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
