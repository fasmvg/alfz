/*
 * Project: alfz
 * File: main.c
 * Description: The main file of the project.
 *              Accepts string arguments and sorts them alphabetically
 *              based on the first character (case-insensitive).
 *
 * MIT License
 * 
 * Copyright (c) 2025 mvghasty
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXECUTION_ERROR_ABORT 1     // Exit code for execution error  
#define ALF_S 26                    // Alphabet size

int i;                              // Global iterator used across loops

/**
 * @brief Lowercase alphabet array.
 */
const char alfm_arr[ALF_S] = { 
    'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' 
}; 

/**
 * @brief Uppercase alphabet array.
 */
const char alfc_arr[ALF_S] = { 
    'A','B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' 
}; 

size_t alfm_length = sizeof(alfm_arr) / sizeof(alfm_arr[0]);
size_t alfc_length = sizeof(alfc_arr) / sizeof(alfc_arr[0]);

/**
 * @brief Returns the alphabet index (0-25) of a given character.
 *
 * @param c The character to look up.
 * @return Index of the character in the alphabet (case-insensitive),
 *         or -1 if the character is not in the alphabet.
 */
int alf_index(char c) {
    for (i = 0; i < ALF_S; i++) {
        if (c == alfm_arr[i] || c == alfc_arr[i]) return i;
    }
    return -1;
}

/**
 * @brief Comparator function for sorting strings alphabetically
 *        by their first character using qsort().
 *
 * @param a Pointer to the first string.
 * @param b Pointer to the second string.
 * @return Negative if a < b, positive if a > b, 0 if equal (or both invalid).
 */
int fchar_compare(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;

    int i1 = alf_index(str1[0]);
    int i2 = alf_index(str2[0]);

    if (i1 == -1 && i2 == -1) return 0;
    if (i1 == -1) return 1;
    if (i2 == -1) return -1;

    return i1 - i2;
} 

/**
 * @brief Main entry point. Takes CLI arguments, sorts them alphabetically,
 *        and prints them.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of argument strings.
 * @return Exit code (0 on success, 1 on error).
 */
int main(int argc, char *argv[]) {
    int num_args = argc - 1;

    // Check if arguments were passed
    const int no_args = (argc <= 1) ? 1 : 0; 
    if (no_args == 1) {
        puts("ERROR: no arguments passed");
        return EXECUTION_ERROR_ABORT;
    }

    // Allocate memory to copy arguments
    char **arg_arr = malloc(num_args * sizeof(char *));
    if (arg_arr == NULL) {
        puts("ERROR: memory allocation failure");
        return EXECUTION_ERROR_ABORT;
    }

    // Duplicate each argument into arg_arr
    for (i = 0; i < num_args; i++) {
        arg_arr[i] = strdup(argv[i + 1]);
        if (arg_arr[i] == NULL) {
            puts("ERROR: null pointer exception (NPE)");
            return EXECUTION_ERROR_ABORT;
        }
    }

    // Sort the array using custom comparator
    qsort(arg_arr, num_args, sizeof(char *), fchar_compare);

    // Print the sorted result
    for (i = 0; i < num_args; i++) {
        printf("[%d][%c]: %s \n", i, arg_arr[i][0], arg_arr[i]);
    }

    // Free allocated memory
    for (i = 0; i < num_args; i++) {
        free(arg_arr[i]);
    } free(arg_arr);
    
    return 0;
}
